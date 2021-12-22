#pragma once
#include <string.h>
#include <stdio.h>
class ESetException
{
	char _message[70];
public:
	ESetException(const char* msg);
	const char* GetMsg();
};


class EInvalidIndex : public ESetException
{
public:
	EInvalidIndex();
};

class ECancelAdd : public ESetException
{
public:
	ECancelAdd();
};

class EArrayIsEmpty : public ESetException
{
public:
	EArrayIsEmpty();
};

class EUnableToReadFile : public ESetException
{
public:
	EUnableToReadFile();
};

class EUnableToSaveFile : public ESetException
{
public:
	EUnableToSaveFile();
};

class EInvalidFileDataFormat : public ESetException
{
public:
	EInvalidFileDataFormat();
};

class EIsNotExists : public ESetException
{
public:
	EIsNotExists();
};

class EInvalidHotelCategory : public ESetException
{
public:
	EInvalidHotelCategory();
};

class EInvalidNumberOfDays : public ESetException
{
public:
	EInvalidNumberOfDays();
};

class EInvalidPrice : public ESetException
{
public:
	EInvalidPrice();
};