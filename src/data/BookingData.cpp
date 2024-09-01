#include "BookingData.h"

booking::data::BookingData::BookingData()
{

}

stringstream booking::data::BookingData::LoadData(string filename)
{

    // Check if the folder exists
    if (!fs::exists(m_folderSave)) {
        // Create the directory if it doesn't exist
        fs::create_directory(m_folderSave);
        cout << "Directory created: " << m_folderSave << endl;
    }


    ifstream file(m_folderSave + "/" + filename);
    if (!file.is_open()) {
        ofstream newFile(m_folderSave + "/" + filename);
        if (!newFile) {
            throw runtime_error("Failed to create file: " + filename);
        }
        newFile << R"([{}])";
        newFile.close();

        file.open(m_folderSave + "/" + filename);
    }

    stringstream buffer;
    buffer << file.rdbuf();

    file.close();

    return buffer;
}

bool booking::data::BookingData::LoadTheatresData()
{
    stringstream data = LoadData(m_theatresFile);

    json jsonArray;
    data >> jsonArray;

    try{

        m_theatres = jsonArray.get<vector<Theatre>>();

//        for (const auto& theatre : m_theatres) {
//            cout << "Theatre Name: " << theatre.Name << endl;
//            cout << "Row (Total Seats - a :: b :: c :: d): " << theatre.Row.a << "::"
//                                                             << theatre.Row.b << "::"
//                                                             << theatre.Row.c << "::"
//                                                             << theatre.Row.d
//                                                             << endl;
//        }

    }catch(const json::out_of_range& e){
        cerr << "JSON out of range" << e.what() << endl;
    }

    return true;
}

bool booking::data::BookingData::LoadMoviesData()
{
    stringstream data = LoadData(m_moviesFile);

    json jsonArray;
    data >> jsonArray;

    try{
        m_movies = jsonArray.get<vector<Movie>>();

//        for (const auto& movie : m_movies) {
//            cout << "Movie Name: " << movie.Name << endl;

//            cout << "Theatres: " << endl;
//            for(const auto& theatre : movie.Theatres){
//                cout << theatre << endl;
//            }
//        }

    }catch(const json::out_of_range& e){
        cerr << "JSON out of range" << e.what() << endl;
    }

    return true;
}

void booking::data::BookingData::FillBookingData()
{
    for (const auto& theatre : m_theatres) {

        BookingSeats s;
        s.Name = theatre.Name;

        for (const auto& movie : m_movies) {

            for (const auto& movieTheatre : movie.Theatres){

                if(movieTheatre != theatre.Name) continue;

                    BookingMovie m;
                    m.Name = movie.Name;
                    m.a.insert(m.a.end(), theatre.Row.a, FREE);
                    m.b.insert(m.b.end(), theatre.Row.b, FREE);
                    m.c.insert(m.c.end(), theatre.Row.c, FREE);
                    m.d.insert(m.d.end(), theatre.Row.d, FREE);
                    s.Movies.push_back(m);

            }

        }

        m_bookingSeats.push_back(s);

    }
}

bool booking::data::BookingData::WriteDataToFile(string filename, json jsonArray)
{

    ofstream file(m_folderSave + "/" + filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + m_folderSave +"/" + filename);
    }

    file << jsonArray.dump(4);
    file.close();

    return true;
}

bool booking::data::BookingData::LoadBookingData()
{
    stringstream data = LoadData(m_bookingSeatsFile);

    try{
        FillBookingData();

        json jsonArray;
        jsonArray = m_bookingSeats;

        WriteDataToFile(m_bookingSeatsFile, jsonArray);

    }catch(const json::out_of_range& e){
        cerr << "JSON out of range" << e.what() << endl;
    }

    return true;
}

booking::data::BookingData::SEAT booking::data::BookingData::GetSeatStatus(string theatre, string movie, string row, unsigned char seat)
{
    for (const auto& t : m_bookingSeats) {
        if (t.Name != theatre) continue;

        for(const auto& m : t.Movies){
            if(m.Name != movie) continue;

            if(row == "a"){
                return (SEAT)m.a[seat];
            }

            if(row == "b"){
                return (SEAT)m.b[seat];
            }

            if(row == "c"){
                return (SEAT)m.c[seat];
            };

            if(row == "d"){
                return (SEAT)m.d[seat];
            };
        }
    }

    // Here we need to add error status for unavailble such params
    return FREE;
}

void booking::data::BookingData::SetSeatStatus(string theatre, string movie, string row, unsigned char seat, SEAT status)
{
    for (auto& t : m_bookingSeats) {
        if (t.Name != theatre) continue;

        for(auto& m : t.Movies){
            if(m.Name != movie) continue;

            if(row == "a"){
                m.a[seat] = status;
            }

            if(row == "b"){
                m.b[seat] = status;
            }

            if(row == "c"){
                m.c[seat] = status;
            };

            if(row == "d"){
                m.d[seat] = status;
            };
        }
    }

    json jsonArray;
    jsonArray = m_bookingSeats;

    WriteDataToFile(m_bookingSeatsFile, jsonArray);
}

std::vector<string> booking::data::BookingData::GetAllMovies()
{
    std::vector<string> movies;

    for(const auto& m : m_movies){
        movies.push_back(m.Name);
    }

    return movies;
}

std::vector<string> booking::data::BookingData::GetAllTheatres()
{
    std::vector<string> theatres;

    for(const auto& t : m_theatres){
        theatres.push_back(t.Name);
    }

    return theatres;
}

std::vector<string> booking::data::BookingData::GetAllMoviesByTheatre(string theatre)
{
    std::vector<string> movies;

    for(const auto& m : m_movies){
        for(const auto& t : m.Theatres){
            if(t != theatre) continue;
            movies.push_back(m.Name);
        }
    }

    return movies;
}

std::vector<string> booking::data::BookingData::GetAllTheatresByMovie(string movie)
{
    std::vector<string> theatres;

    for(const auto& m : m_movies){
        if(m.Name != movie) continue;
        theatres = m.Theatres;
    }

    return theatres;
}

const std::vector<booking::data::BookingSeats> *booking::data::BookingData::GetBookingSeats()
{
    return &m_bookingSeats;
}

