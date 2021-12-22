#include "TourArray.h"

int ToLower(int s)
{
	if (s == -88)
		return -72;
	if ((s >= 65 && s <= 90) || (s >= -64 && s <= -33))
		return s + 32;
	else
		return s;
}

bool CmpStr(const char* a, const char* b)
{
	unsigned length = strlen(a);
	if (strlen(b) != length)
		return false;
	for (unsigned i = 0; i < length; i++)
	{
		if (ToLower(a[i]) != ToLower(b[i]))
			return false;
	}
	return true;
}


void TourArray::IncreaseArrayCapacity()
{
	if (_capacity + 10 < INT_MAX)
	{
		Tour* newArray = new Tour[_capacity + 10];
		for (int i = 0; i < _size; i++)
			newArray[i] = _data[i];
		delete[] _data;
		_data = newArray;
		_capacity += 10;
	}
}


TourArray::TourArray() 
	: _capacity(0), _size(0), _data(NULL) 
{}

TourArray::TourArray(const int& capacity)
	: _capacity(capacity), _size(0), _data(new Tour[capacity])
{}

TourArray::TourArray(const TourArray& tours) 
	: _capacity(tours._size), _size(tours._size), _data(NULL)
{
	if (_size > 0)
	{
		_data = new Tour[_size];
		for (int i = 0; i < _size; i++)
			_data[i] = *(tours.GetDataByIndex(i));
	}
}

TourArray::~TourArray()
{
	delete[] _data;
}


void TourArray::ClearArray()
{
	Tour temp;
	for (int i = 0; i < _size; i++)
		_data[i] = temp;
	_size = 0;
}

int TourArray::GetSize() const
{
	return _size;
}


void TourArray::AddToEnd(const Tour& tour)
{
	if (_size == _capacity)
		IncreaseArrayCapacity();
	_data[_size++] = tour;
}

void TourArray::AddBeforeIndex(const int& index, const Tour& tour)
{
	if (_size == _capacity)
		IncreaseArrayCapacity();
	for (int i = _size++; i > index; i--)
		_data[i] = _data[i - 1];
	_data[index] = tour;
}

void TourArray::DeleteDataByIndex(const int& index)
{
	if (GetDataByIndex(index))
	{
		for (int i = index; i < _size; i++)
			_data[i] = _data[i + 1];
		_size--;
	}
	else
		throw EInvalidIndex();
}

Tour* TourArray::GetDataByIndex(const int& index) const
{
	if (_data && index >= 0 && index < _size)
		return &_data[index];
	else
		return NULL;
}

int TourArray::SearchElementFromIndex(const int& current, const char* userCity) const
{
	for (int i = current; i < _size ; i++)
	{
		if (&_data[i] && CmpStr(userCity, _data[i].GetCity()))
			return i;
	}
	return current;
}


void TourArray::ReadFromFile(const char* filename)
{
	FILE* input;
	errno_t err = fopen_s(&input, filename, "rb");
	if (!err && input)
	{
		Tour* temp = NULL;
		int size = 0;

		fread(&size, sizeof(int), 1, input);
		if (size > 0)
		{
			temp = new Tour[size];
			if (temp)
			{
				for (int i = 0; i < size; i++)
				{
					if (fread(&temp[i], sizeof(Tour), 1, input) != 1)
					{
						fclose(input);
						delete[] temp;
						throw EInvalidFileDataFormat();
					}
				}
				fclose(input);
			}
		}
		else
			size = 0;
		delete[] _data;
		_data = temp;
		_capacity = _size = size;
	}
	else
		throw EUnableToReadFile();
}

void TourArray::WriteInFile(const char* filename) const
{
	FILE* output = NULL;
	errno_t err = fopen_s(&output, filename, "wb");
	if (err|| !output)
		throw EUnableToSaveFile();

	fwrite(&_size, sizeof(int), 1, output);
	fwrite(_data, sizeof(Tour), _size, output);
	fclose(output);
}


void TourArray::BubbleSort(TourComparator cmp)
{
	for (int i = 0; i < _size - 1; i++)
	{
		for (int j = 0; j < _size - i - 1; j++)
		{
			if ((cmp(_data[j], _data[j + 1])) > 0)
			{
				Tour temp = _data[j];
				_data[j] = _data[j + 1];
				_data[j + 1] = temp;
			}
		}
	}
}

TourArray* TourArray::ResultArray(const char* userCity)
{
	TourArray* resultArray = new TourArray(0);
	double averageCostOfDay = 0.0;
	int amount = 0;
	for (int i = 0; i < _size; i++)
	{
		if (_stricmp(userCity, _data[i].GetCity()))
		{
			averageCostOfDay += _data[i].GetAvarageCostOfDay();
			amount++;
		}
	}
	averageCostOfDay /= amount;
	for (int i = 0; i < _size; i++)
	{
		if (CmpStr(userCity, _data[i].GetCity()) && averageCostOfDay > _data[i].GetAvarageCostOfDay())
		{
			if (resultArray->_size == resultArray->_capacity)
				resultArray->IncreaseArrayCapacity();
			resultArray->AddToEnd(_data[i]);
		}
	}
	resultArray->BubbleSort(CmpPrice);
	return resultArray;
}