#include "ESetException.h"

ESetException::ESetException(const char* msg)
{
	strncpy_s(_message, msg, 70);
}

const char* ESetException::GetMsg()
{
	return _message;
}


EInvalidIndex::EInvalidIndex() : ESetException("Invalid index") {}

ECancelAdd::ECancelAdd() : ESetException("Cancel adding new data...") {}

EArrayIsEmpty::EArrayIsEmpty() : ESetException("Array is empty!") {}

EUnableToReadFile::EUnableToReadFile() : ESetException("Unable to read file") {}

EUnableToSaveFile::EUnableToSaveFile() : ESetException("Unable to save file") {}

EInvalidFileDataFormat::EInvalidFileDataFormat() : ESetException("Invalid file data format") {}

EIsNotExists::EIsNotExists() : ESetException("Element wasn't found") {}

EInvalidHotelCategory::EInvalidHotelCategory(): ESetException("Invalid hotel category") {}

EInvalidNumberOfDays::EInvalidNumberOfDays(): ESetException("Invalid number of days") {}

EInvalidPrice::EInvalidPrice(): ESetException("Invalid price") {}