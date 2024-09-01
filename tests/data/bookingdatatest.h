#ifndef BOOKINGDATATEST_H
#define BOOKINGDATATEST_H

#include <gtest/gtest.h>
#include <data/BookingData.h>

class BookingDataTest  : public ::testing::Test
{
protected:
    booking::data::BookingData bookingData;

    void SetUp() override;
    void TearDown() override;

public:
    BookingDataTest();


};

#endif // BOOKINGDATATEST_H
