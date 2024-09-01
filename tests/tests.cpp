#include <gtest/gtest.h>

#include <data/bookingdatatest.h>

TEST_F(BookingDataTest, GetAllMovies_ReturnsCorrectList) {
    // Act

    bookingData.LoadMoviesData();
    std::vector<std::string> movies = bookingData.GetAllMovies();

    // Assert
    EXPECT_EQ(movies.size(), 3);
    EXPECT_EQ(movies[0], "HarryPotter");
    EXPECT_EQ(movies[1], "Interstellar");
    EXPECT_EQ(movies[2], "StarTrek");
}
