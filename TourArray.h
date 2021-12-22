#pragma once
#include "Tour.h"
#include "ESetException.h"
#include <stdlib.h>

typedef int (TourComparator)(const Tour&, const Tour&);

class TourArray
{
private:
	int _capacity, _size;
	Tour* _data;

	void IncreaseArrayCapacity();
public:
	TourArray();
	TourArray(const int& _capacity);
	TourArray(const TourArray& tour);
	~TourArray();
	
	void ClearArray();
	
	int GetSize() const;

	void AddToEnd(const Tour& tour);
	void AddBeforeIndex(const int& index, const Tour& tour);
	void DeleteDataByIndex(const int& index);
	Tour* GetDataByIndex(const int& index) const;
	int SearchElementFromIndex(const int& current, const char* userCity) const;
	
	void ReadFromFile(const char* filename);
	void WriteInFile(const char* filename) const;

	void BubbleSort(TourComparator cmp);
	TourArray* ResultArray(const char* userCity);
};