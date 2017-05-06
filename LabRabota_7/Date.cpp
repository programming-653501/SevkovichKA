#include "stdafx.h"
#include "Date.h"

int Date::GetJulianDate() const
{
	int a = (14 - this->month) / 12;
	int y = this->year + 4800 - a;
	int m = this->month + 12 * a - 3;

	return (this->day + trunc((153 * m + 2) / 5) + 365 * y +
		trunc(y / 4) - trunc(y / 100) + trunc(y / 400) - 32045);
}

int Date::GetDateDifference(Date pDateSecond) const
{
	return (this->GetJulianDate() - pDateSecond.GetJulianDate());
}

void Date::set(unsigned pYear, unsigned pMonth, unsigned pDay)
{
	this->year = pYear;
	this->month = pMonth;
	this->day = pDay;
}

// pDate should be in form "mm/dd/yyyy"
Date::Date(std::string pDate)
{
	this->Set(pDate);
}

Date::Date(unsigned pYear, unsigned pMonth, unsigned pDay)
{
	this->Set(pYear, pMonth, pDay);
}

Date Date::GetCurrentDate()
{
	time_t t = time(nullptr); //current time 
	tm now;

	localtime_s(&now, &t);

	Date current_date(now.tm_year + 1900, now.tm_mon + 1, now.tm_mday);

	return current_date;
}

void Date::Set(unsigned pYear, unsigned pMonth, unsigned pDay)
{
	this->set(pYear, pMonth, pDay);
}

void Date::Set(std::string pDate)
{
	std::vector<std::string> date = SplitString(pDate, '/');

	unsigned month = atoi(date[0].c_str());
	unsigned day = atoi(date[1].c_str());
	unsigned year = atoi(date[2].c_str());

	this->set(year, month, day);
}

std::string Date::GetAsString() const
{
	std::string result = "";

	if (this->month < 10)
	{
		result += '0';
	}

	result += std::to_string(this->month);
	result += '/';

	if (this->day < 10)
	{
		result += '0';
	}

	result += std::to_string(this->day);
	result += '/';

	if (this->year < 1000)
	{
		result += '0';

		if (this->year < 100)
		{
			result += '0';

			if (this->year < 10)
			{
				result += '0';
			}
		}
	}

	result += std::to_string(this->year);

	return result;
}

bool Date::IsDateValid(unsigned pYear, unsigned pMonth, unsigned pDay)
{
	if (pMonth > 12)
	{
		return false;
	}

	switch (pMonth)
	{
		//31-day long months 
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: return (pDay > 31) ? false : true;

		//30-day long months 
	case 4:
	case 6:
	case 9:
	case 11: return (pDay > 30) ? false : true;

		//28-29-day long month
	case 2:
		if (IsLeapYear(pYear))
		{
			return (pDay > 29) ? false : true;
		}
		else
		{
			return (pDay > 28) ? false : true;
		}
	}
}

bool Date::IsLeapYear(unsigned pYear)
{
	return ((pYear % 4 == 0 && pYear % 100 != 0) || pYear % 400 == 0);
}

std::vector<std::string> Date::SplitString(std::string pString, char delim)
{
	int length = pString.length();
	std::vector<std::string> splitted(0);

	int begin = 0;
	int end;
	size_t i;

	for (i = 0; i < length; i++)
	{
		if (pString[i] == delim)
		{
			end = i;
			std::string tempString = "";

			for (size_t j = begin; j < end; j++)
			{
				tempString += pString[j];
			}

			splitted.push_back(tempString);

			begin = i + 1;
		}
	}

	if (pString[i] == '\0')
	{
		std::string tempString = "";
		for (size_t j = begin; j < i; j++)
		{
			tempString += pString[j];
		}

		splitted.push_back(tempString);
	}

	return splitted;
}

bool Date::IsDateStringValid(std::string pDate)
{
	if (pDate.length() != 10)
	{
		return false;
	}

	if (pDate[2] != '/' || pDate[5] != '/')
	{
		return false;
	}

	for (size_t i = 0; i < pDate.length(); i++)
	{
		if (i == 2 || i == 5)
		{
			continue;
		}

		if (pDate[i] < '0' || pDate[i] > '9')
		{
			return false;
		}
	}

	std::vector<std::string> date = SplitString(pDate, '/');

	unsigned month = atoi(date[0].c_str());
	unsigned day = atoi(date[1].c_str());
	unsigned year = atoi(date[2].c_str());

	if (IsDateValid(year, month, day))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Date::operator==(const Date& other) const
{
	return (this->year == other.year && this->month == other.month 
		&& this->day == other.day);
}

int Date::operator-(const Date& other) const
{
	return (other.GetDateDifference(*this));
}