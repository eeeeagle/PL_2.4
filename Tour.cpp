#include "Tour.h"

Tour::Tour() 
	: _city(""), _hotelCategory(0), _days(0), _price(0.0) 
{}

Tour::Tour(const char* city, int hotelCategory, int days, double price)
	: _city(""), _hotelCategory(0), _days(0), _price(0.0)
{
	strcpy_s(_city, 50, city);
	if (hotelCategory >= 1 && hotelCategory <= 5)
		_hotelCategory = hotelCategory;
	else
		throw EInvalidHotelCategory();
	if (days > 0)
		_days = days;
	else
		throw EInvalidNumberOfDays();
	if (price > 0.0)
		_price = price;
	else
		throw EInvalidPrice();
}

Tour::Tour(const Tour& tour) 
	: _hotelCategory(tour._hotelCategory), _days(tour._days), _price(tour._price)
{
	strncpy_s(_city, tour._city, 50);
}


void Tour::SetCity(const char* city)
{
	strncpy_s(_city, city, 50);
}

void Tour::SetHotelCategory(const int& hotelCategory)
{
	if (hotelCategory >= 1 && hotelCategory <= 5)
		_hotelCategory = hotelCategory;
}

void Tour::SetDays(const int& days)
{
	if (days > 0)
		_days = days;
}

void Tour::SetPrice(const double& price)
{
	if (price > 0.0)
		_price = price;
}


const char* Tour::GetCity() const
{
	return _city;
}

int Tour::GetHotelCategory() const
{
	return _hotelCategory;
}

int Tour::GetDays() const
{
	return _days;
}

double Tour::GetPrice() const 
{
	return _price;
}


double Tour::GetAvarageCostOfDay() const
{
	return _days != 0 ? (_price / _days) : 0.0;
}


int CmpTourNumberOfDays(const Tour& a, const Tour& b) 
{
	return a.GetDays() - b.GetDays();
}

int CmpTourHotelCategory(const Tour& a, const Tour& b) 
{
	return (a.GetHotelCategory() - b.GetHotelCategory());
}

int CmpPrice(const Tour& a, const Tour& b) 
{
	return (int)(a.GetPrice() - b.GetPrice());
}

int CmpCity(const Tour& a, const Tour& b) 
{
	return _stricmp(a.GetCity(), b.GetCity());
}