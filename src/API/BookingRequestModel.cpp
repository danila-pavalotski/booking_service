#include "BookingRequestModel.h"
#include "core/BookingService.h"

void booking::api::BookingRequestModel::Attach(IBookingObserver *observer){
    m_list_observer.push_back(observer);
}

void booking::api::BookingRequestModel::Detach(IBookingObserver *observer){
    m_list_observer.remove(observer);
}

void booking::api::BookingRequestModel::NotifyOnRequestUpdate(std::string& row, unsigned char seat, int error){

    for(const auto& observer : m_list_observer){
        observer->OnRequestUpdate(row, seat, error);
    }
}

void booking::api::BookingRequestModel::NotifyOnUpdate(const std::string& theatre, const std::string& movie)
{
    for(const auto& observer : m_list_observer){
        observer->OnUpdate(theatre, movie);
    }
}

void booking::api::BookingRequestModel::OnRequestUpdate(std::string row, unsigned char seat, int error)
{

}

void booking::api::BookingRequestModel::OnUpdate(std::string theatre, std::string movie)
{

}

booking::api::BookingRequestModel::BookingRequestModel()
{
    core::BookingService::getInstance().Attach(this);
}

booking::api::BookingRequestModel::~BookingRequestModel()
{
    core::BookingService::getInstance().Detach(this);
}

std::vector<std::string> booking::api::BookingRequestModel::ListAllMovies()
{
    return core::BookingService::getInstance().GetAllMovies();
}

std::vector<std::string> booking::api::BookingRequestModel::ListAllMoviesByTheatre(std::string value)
{
    return core::BookingService::getInstance().GetAllMoviesByTheatre(value);
}

std::vector<std::string> booking::api::BookingRequestModel::ListAllTheatres()
{
    return core::BookingService::getInstance().GetAllTheatres();
}

std::vector<std::string> booking::api::BookingRequestModel::ListAllTheatresByMovie(std::string value)
{
    return core::BookingService::getInstance().GetAllTheatresByMovie(value);
}

std::map<std::string, std::vector<int>> booking::api::BookingRequestModel::ListAllSeats(std::string theatre, std::string movie)
{
    return core::BookingService::getInstance().GetAllSeats(theatre, movie);
}

void booking::api::BookingRequestModel::BookSeat(std::string theatre, std::string movie, std::string row, int seat)
{
    core::BookingService::getInstance().MakeBookRequest(this, theatre, movie, row, seat);
}
