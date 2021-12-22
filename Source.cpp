#include <conio.h>
#include <Windows.h>
#include "TourArray.h"

int GetKey()
{
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
}

bool SetString(char* current, const char* stringName)
{
	char string[50] = { '\0' };
	while (true)
	{
		system("cls");
		printf("\n   Enter %s: ", stringName);
		gets_s(string, 50);
		printf("\n   ________________________________________\n\n   [Enter]\tContinue\n   [Backspace]\tCorrection\n   [ESC]\tCancel input\n");
		int key = GetKey();
		while (key != 13 && key != 27 && key != 8) 
			key = GetKey();
		if (key == 27)
			return false;
		if (key == 13)
		{
			strcpy_s(current, 50, string);
			return true;
		}
	}
}

bool SetUnsignedDouble(double& current, const char* stringName)
{
	char string[21] = { '\0' };
	while (true)
	{
		system("cls");
		printf("\n   Enter %s: ", stringName);
		gets_s(string, 21);
		unsigned size = strlen(string), i = 0;
		bool flag = true;
		if (size == 0) 
			flag = false;
		while (flag && i < size)
		{
			if (!isdigit(string[i]) && string[i] != '.' && string[i] != ',')
				flag = false;
			i++;
		}
		if (!flag)
		{
			printf("\n   ________________________________________\n\n   Invalid value format\n\n   [Backspace]\tCorrection\n   [ESC]\tCancel input\n");
			int key = GetKey();
			while (key != 27 && key != 8)
				key = GetKey();
			if (key == 27)
				return false;
		}
		else
		{
			printf("\n   ________________________________________\n\n   [Enter]\tContinue\n   [Backspace]\tCorrection\n   [ESC]\tCancel input\n");
			int key = GetKey();
			while (key != 13 && key != 27 && key != 8)
				key = GetKey();
			if (key == 27)
				return false;
			if (key == 13)
			{
				current = atof(string);
				return true;
			}
		}
	}
}

bool SetInt(int& current, const char* valueName)
{
	char string[21] = { '\0' };
	while (true)
	{
		system("cls");
		printf("\n   Enter %s: ", valueName);
		gets_s(string, 21);
		unsigned size = strlen(string), i = 0;
		bool flag = true;
		if (size == 0) 
			flag = false;
		while (flag && i < size)
		{
			if (!isdigit(string[i++]))
				flag = false;
		}
		if (!flag)
		{
			printf("\n   ________________________________________\n\n   Invalid value format\n\n   [Backspace]\tCorrection\n   [ESC]\tCancel input\n");
			int key = GetKey();
			while (key != 27 && key != 8)
				key = GetKey();
			if (key == 27)
				return false;
		}
		else
		{
			printf("\n   ________________________________________\n\n   [Enter]\tContinue\n   [Backspace]\tCorrection\n   [ESC]\tCancel input\n");
			int key = GetKey();
			while (key != 13 && key != 27 && key != 8)
				key = GetKey();
			if (key == 27)
				return false;
			if (key == 13)
			{
				current = atoi(string);
				return true;
			}
		}
	}
}

Tour UserTour()
{
	char city[50] = { '\0' };
	int hotelCategory = 0, days = 0;
	double price = 0.0;
	if (SetString(city, "city") && SetInt(hotelCategory, "hotel category (1-5)") && SetInt(days, "number of days") && SetUnsignedDouble(price, "price"))
	{
		try { return Tour(city, hotelCategory, days, price);}
		catch (ESetException & err) { throw err; }
	}
	throw ECancelAdd();
}

void ErrorMessage(ESetException &err)
{
	printf("\n   ________________________________________\n\n   %s\n   Press Enter to continue\n", err.GetMsg());
	int key = GetKey();
	while (key != 13) key = GetKey();
}

void PrintElement(const Tour* tour, const int& current, const int& size)
{
	if (tour)
	{
		printf("   TOUR no.%u of %u\n", current + 1, size);
		printf("\n   City:\t\t%s\n   Hotel Category:\t%u\n   Days:\t\t%u\n   Price:\t\t%.2lf\n",
			tour->GetCity(), tour->GetHotelCategory(), tour->GetDays(), tour->GetPrice());
		printf("   ________________________________________\n\n");
	}
}

void ElementMenu(Tour* tour)
{
	int m = 0;
	while (tour)
	{
		char tempString[50] = { '\0' };
		int tempInt = 0;
		double tempDouble = 0.0;
		system("cls");
		printf("\n   ELEMENT MENU\n   ________________________________________\n");
		printf("\n   City:\t\t%s\n   Hotel Category:\t%u\n   Days:\t\t%u\n   Price:\t\t%.2lf\n",
			tour->GetCity(), tour->GetHotelCategory(), tour->GetDays(), tour->GetPrice());
		printf("   ________________________________________\n\n");
		switch (m)
		{
		case 0:
			printf(" > Edit city\n   Edit hotel category\n   Edit number of days\n   Edit price\n   Return to array menu\n"); break;
		case 1:
			printf("   Edit city\n > Edit hotel category\n   Edit number of days\n   Edit price\n   Return to array menu\n"); break;
		case 2:
			printf("   Edit city\n   Edit hotel category\n > Edit number of days\n   Edit price\n   Return to array menu\n"); break;
		case 3:
			printf("   Edit city\n   Edit hotel category\n   Edit number of days\n > Edit price\n   Return to array menu\n"); break;
		case 4:
			printf("   Edit city\n   Edit hotel category\n   Edit number of days\n   Edit price\n > Return to array menu\n"); break;
		}
		printf("   ________________________________________\n\n   [Up/Down]\t\tMenu navigation\n   [Enter]\t\tAccept\n   [ESC]\t\tReturn to array menu");
		switch (GetKey())
		{
		case 72:
			if (m > 0) m--;
			else m = 4;
			break;
		case 80:
			if (m < 4) m++;
			else m = 0;
			break;
		case 27:
			return;
		case 13:
			switch (m)
			{
			case 0:
				if (SetString(tempString, "new city"))
					tour->SetCity(tempString);
				break;
			case 1:
				if (SetInt(tempInt, "new hotel category (1-5)"))
					tour->SetHotelCategory(tempInt);
				break;
			case 2:
				if (SetInt(tempInt, "new number of days"))
					tour->SetDays(tempInt);
				break;
			case 3:
				if (SetUnsignedDouble(tempDouble, "new price"))
					tour->SetPrice(tempDouble);
				break;
			case 4:
				return;
			}
		}
	}
}

void ArrayMenu(TourArray& tours)
{
	int m = 0, current = 0;
	char tempString[50] = { '\0' };
	while (true)
	{
		system("cls");
		printf("\n   ARRAY MENU\n   ________________________________________\n\n");
		PrintElement(tours.GetDataByIndex(current), current, tours.GetSize());
		switch (m)
		{
		case 0:
			printf(" > Edit element data\n   Find element by city\n   Insert new element before current\n"
				"   Insert new element to end of the array\n   Delete current element\n   Return to main menu\n"); break;
		case 1:
			printf("   Edit element data\n > Find element by city\n   Insert new element before current\n"
				"   Insert new element to end of the array\n   Delete current element\n   Return to main menu\n"); break;
		case 2:
			printf("   Edit element data\n   Find element by city\n > Insert new element before current\n"
				"   Insert new element to end of the array\n   Delete current element\n   Return to main menu\n"); break;
		case 3:
			printf("   Edit element data\n   Find element by city\n   Insert new element before current\n"
				" > Insert new element to end of the array\n   Delete current element\n   Return to main menu\n"); break;
		case 4:
			printf("   Edit element data\n   Find element by city\n   Insert new element before current\n"
				"   Insert new element to end of the array\n > Delete current element\n   Return to main menu\n"); break;
		case 5:
			printf("   Edit element data\n   Find element by city\n   Insert new element before current\n"
				"   Insert new element to end of the array\n   Delete current element\n > Return to main menu\n"); break;
		}
		printf("   ________________________________________\n\n   [Up/Down]\t\tMenu navigation\n"
			"   [Left/Right]\t\tPrevious/Next element\n   [Enter]\t\tAccept\n   [ESC]\t\tReturn to main menu");
		switch (GetKey())
		{
		case 72:
			if (m > 0) m--;
			else m = 5;
			break;
		case 80:
			if (m < 5) m++;
			else m = 0;
			break;
		case 77:
			if (tours.GetSize() > 0)
			{
				if (current < tours.GetSize() - 1) current++;
				else current = 0;
			}
			break;
		case 75:
			if (tours.GetSize() > 0)
			{
				if (current > 0) current--;
				else current = tours.GetSize() - 1;
			}
			break;
		case 27:
			return;
		case 13:
			try
			{
				switch (m)
				{
				case 0:
					ElementMenu(tours.GetDataByIndex(current));
					break;
				case 1:
					if (SetString(tempString, "city"))
						//tours.SearchElementFromIndex(current, tempString);
						current = tours.SearchElementFromIndex(current, tempString);
					break;
				case 2:
					tours.AddBeforeIndex(current, UserTour());
					break;
				case 3:
					tours.AddToEnd(UserTour());
					break;
				case 4:
					tours.DeleteDataByIndex(current);
					if (current >= tours.GetSize())
						current = tours.GetSize() - 1;
					break;
				case 5:
					return;
				}
			}
			catch (ESetException& err)
			{
				ErrorMessage(err);
			}
		}
	}
}

void ResultArrayMenu(TourArray* resultArray)
{
	int current = 0;
	char tempString[50] = { '\0' };
	while (true)
	{
		system("cls");
		printf("\n   RESULT ARRAY MENU\n   ________________________________________\n\n");
		PrintElement(resultArray->GetDataByIndex(current), current, resultArray->GetSize());
		printf("   [Left/Right]\t\tPrevious/Next element\n   [Enter]\t\tSave result array to binary file\n   [ESC]\t\tReturn to main menu");
		try
		{
			switch (GetKey())
			{
			case 77:
				if (resultArray->GetSize() > 0)
				{
					if (current < resultArray->GetSize() - 1) 
						current++;
					else 
						current = 0;
				}
				break;
			case 75:
				if (resultArray->GetSize() > 0)
				{
					if (current > 0)
						current--;
					else
						current = resultArray->GetSize() - 1;
				}
				break;
			case 27:
				delete resultArray;
				return;
			case 13:
				if (SetString(tempString, "file destination"))
					resultArray->WriteInFile(tempString);
				break;
			}
		}
		catch (ESetException& err)
		{
			ErrorMessage(err);
		}
	}
}

void SortMenu(TourArray& tours)
{
	int m = 0;
	char tempString[50] = { '\0' };
	while (true)
	{
		system("cls");
		printf("\n   SORT ARRAY MENU\n   ________________________________________\n\n");
		switch (m)
		{
		case 0:
			printf(" > Sort by city\n   Sort by hotel category\n   Sort by price\n"
				"   Sort by number of days\n   Create result array\n   Return\n"); break;
		case 1:
			printf("   Sort by city\n > Sort by hotel category\n   Sort by price\n"
				"   Sort by number of days\n   Create result array\n   Return\n"); break;
		case 2:
			printf("   Sort by city\n   Sort by hotel category\n > Sort by price\n"
				"   Sort by number of days\n   Create result array\n   Return\n"); break;
		case 3:
			printf("   Sort by city\n   Sort by hotel category\n   Sort by price\n"
				" > Sort by number of days\n   Create result array\n   Return\n"); break;
		case 4:
			printf("   Sort by city\n   Sort by hotel category\n   Sort by price\n"
				"   Sort by number of days\n > Create result array\n   Return\n"); break;
		case 5:
			printf("   Sort by city\n   Sort by hotel category\n   Sort by price\n"
				"   Sort by number of days\n   Create result array\n > Return\n"); break;
		}
		printf("   ________________________________________\n\n   [Up/Down]\t\tMenu navigation\n   [Enter]\t\tAccept\n   [ESC]\t\tExit");
		switch (GetKey())
		{
		case 72:
			if (m > 0) m--;
			else m = 5;
			break;
		case 80:
			if (m < 5) m++;
			else m = 0;
			break;
		case 27:
			return;
		case 13:
			try
			{
				switch (m)
				{
				case 0:
					tours.BubbleSort(CmpCity);
					break;
				case 1:
					tours.BubbleSort(CmpTourHotelCategory);
					break;
				case 2:
					tours.BubbleSort(CmpPrice);
					break;
				case 3:
					tours.BubbleSort(CmpTourNumberOfDays);
					break;
				case 4:
					if (SetString(tempString, "city for sorting"))
						ResultArrayMenu(tours.ResultArray(tempString));
					break;
				case 5:
					return;
				}
			}
			catch (ESetException& err)
			{
				ErrorMessage(err);
			}
		}
	}
}

void MainMenu()
{
	TourArray tours;
	int m = 0;
	char tempString[50] = { '\0' };
	while (true)
	{
		system("cls");
		printf("\n   MAIN MENU\n   ________________________________________\n\n");
		switch (m)
		{
		case 0:
			printf(" > View array\n   Clear array\n   Sort array\n"
				"   Load data from binary file\n   Save data to binary file\n   Shut down the programm\n"); break;
		case 1:
			printf("   View array\n > Clear array\n   Sort array\n"
				"   Load data from binary file\n   Save data to binary file\n   Shut down the programm\n"); break;
		case 2:
			printf("   View array\n   Clear array\n > Sort array\n"
				"   Load data from binary file\n   Save data to binary file\n   Shut down the programm\n"); break;
		case 3:
			printf("   View array\n   Clear array\n   Sort array\n"
				" > Load data from binary file\n   Save data to binary file\n   Shut down the programm\n"); break;
		case 4:
			printf("   View array\n   Clear array\n   Sort array\n"
				"   Load data from binary file\n > Save data to binary file\n   Shut down the programm\n"); break;
		case 5:
			printf("   View array\n   Clear array\n   Sort array\n"
				"   Load data from binary file\n   Save data to binary file\n > Shut down the programm\n"); break;
		}
		printf("   ________________________________________\n\n   [Up/Down]\t\tMenu navigation\n   [Enter]\t\tAccept\n   [ESC]\t\tExit");
		switch (GetKey())
		{
		case 72:
			if (m > 0) m--;
			else m = 5;
			break;
		case 80:
			if (m < 5) m++;
			else m = 0;
			break;
		case 27:
			return;
		case 13:
			try
			{
				switch (m)
				{
				case 0:
					ArrayMenu(tours);
					break;
				case 1:
					tours.ClearArray();
					break;
				case 2:
					SortMenu(tours);
					break;
				case 3:
					if (SetString(tempString, "file destination"))
						tours.ReadFromFile(tempString);
					break;
				case 4:
					if (SetString(tempString, "file destination"))
						tours.WriteInFile(tempString);
					break;
				case 5:
					return;
				}
			}
			catch (ESetException& err)
			{
				ErrorMessage(err);
			}
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	MainMenu();
	system("cls");
	return 0;
}