#include "BookingService.h"

int booking::core::BookingService::Run()
{

    m_data.LoadTheatresData();
    m_data.LoadMoviesData();
    m_data.LoadBookingData();

    m_isStop = false;
    m_mainThread = std::thread(&BookingService::mainThread, this);

    return 0;
}

int booking::core::BookingService::Stop()
{

    m_isStop = true;

    return 0;
}

void booking::core::BookingService::mainThread()
{

    while(!m_isStop){

        if(m_queueRequests.size() == 0) continue;

        BookingRequest request = m_queueRequests.front();


        data::BookingData::SEAT status =  m_data.GetSeatStatus(request.theatre,
                                         request.movie,
                                         request.row,
                                         request.seat);

        switch (status) {
            case data::BookingData::BOOKED:
                    // FEATURE: Need to make cancel booking
                    NotifyOnRequestUpdate(request.client, request.row, request.seat, -1);
                break;
            case data::BookingData::FREE:
                if(request.status == data::BookingData::BOOKED){
                    m_data.SetSeatStatus(request.theatre,
                                       request.movie,
                                       request.row,
                                       request.seat-1,
                                       request.status);

                    NotifyOnRequestUpdate(request.client, request.row, request.seat, 0);
                    NotifyOnUpdate(request.theatre, request.movie);
                }else{
                    NotifyOnRequestUpdate(request.client, request.row, request.seat, -1);
                }
                break;
        }

        m_queueRequests.pop();
    }


}

void booking::core::BookingService::NotifyOnRequestUpdate(IBookingServiceObserver* observer, string &row, unsigned char seat, int error)
{
    for(const auto& o : m_list_observer){
        if(observer == o)
            o->OnRequestUpdate(row, seat, error);
    }
}

void booking::core::BookingService::NotifyOnUpdate(const string &theatre, const string &movie)
{
    for(const auto& observer : m_list_observer){
        observer->OnUpdate(theatre, movie);
    }
}

void booking::core::BookingService::Attach(IBookingServiceObserver *observer)
{
    m_list_observer.push_back(observer);
}

void booking::core::BookingService::Detach(IBookingServiceObserver *observer)
{
    m_list_observer.remove(observer);
}

void booking::core::BookingService::MakeBookRequest(string theatre, string movie, string row, unsigned char seat)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    BookingRequest r;
    r.theatre = theatre;
    r.movie = movie;
    r.row = row;
    r.seat = seat;
    r.status = data::BookingData::BOOKED;

    m_queueRequests.push(r);
}

void booking::core::BookingService::MakeBookRequest(IBookingServiceObserver *observer, string theatre, string movie, string row, unsigned char seat)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    BookingRequest r;
    r.client = observer;
    r.theatre = theatre;
    r.movie = movie;
    r.row = row;
    r.seat = seat;
    r.status = data::BookingData::BOOKED;

    m_queueRequests.push(r);

}

std::vector<string> booking::core::BookingService::GetAllMovies()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_data.GetAllMovies();
}

std::vector<string> booking::core::BookingService::GetAllTheatres()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_data.GetAllTheatres();
}

std::vector<string> booking::core::BookingService::GetAllMoviesByTheatre(string theatre)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_data.GetAllMoviesByTheatre(theatre);
}

std::vector<string> booking::core::BookingService::GetAllTheatresByMovie(string movie)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_data.GetAllTheatresByMovie(movie);
}

std::map<std::string, std::vector<int>> booking::core::BookingService::GetAllSeats(string theatre, string movie)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    std::map<std::string, std::vector<int>> seats;

    const std::vector<booking::data::BookingSeats>* d = m_data.GetBookingSeats();

    for(const auto& b : *d){
        if(b.Name != theatre) continue;
        for(const auto& m : b.Movies){
            if(m.Name != movie) continue;
                seats["a"] = m.a;
                seats["b"] = m.b;
                seats["c"] = m.c;
                seats["d"] = m.d;
        }
    }


    return seats;
}


