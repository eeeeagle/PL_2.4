#pragma once
#include "ESetException.h"

class Tour 
{
private:
	char _city[50];
	int _hotelCategory, _days;
	double _price;
public:
	Tour();
	Tour(const char* city, int hotelCategory, int days, double price);
	Tour(const Tour& tour);
	
	void SetCity(const char* city);
	void SetHotelCategory(const int& hotelCategory);
	void SetDays(const int& days);
	void SetPrice(const double& price);
	
	const char* GetCity() const;
	int GetHotelCategory() const;
	int GetDays() const;
	double GetPrice() const;
	
	double GetAvarageCostOfDay() const;
};

int CmpTourNumberOfDays(const Tour& a, const Tour& b);
int CmpTourHotelCategory(const Tour& a, const Tour& b);
int CmpPrice(const Tour& a, const Tour& b);
int CmpCity(const Tour& a, const Tour& b);