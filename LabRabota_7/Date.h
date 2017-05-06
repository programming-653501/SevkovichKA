#pragma once
#include <time.h>
#include <cmath>
#include <string>
#include <vector>

class Date
{
private:
	int year;
	int month;
	int day;

	void set(unsigned pYear, unsigned pMonth, unsigned pDay);
public:
	Date()
	{
		this->year = this->month = this->day = 0;
	}

	// pDate should be in form "mm/dd/yyyy"
	Date(std::string pDate); 
	Date(unsigned pYear, unsigned pMonth, unsigned pDay);

	static Date GetCurrentDate();

	void Set(unsigned pYear, unsigned pMonth, unsigned pDay);
	void Set(std::string pDate);
	std::string GetAsString() const;
	int GetJulianDate() const;
	int GetDateDifference(Date pDateSecond) const;

	static bool IsDateValid(unsigned pYear, unsigned pMonth, unsigned pDay);
	static bool IsLeapYear(unsigned pYear);
	static std::vector<std::string> SplitString(std::string pString, char delim);
	static bool IsDateStringValid(std::string pDate);

	bool operator == (const Date &other) const;
	int operator - (const Date &other) const;
};

