/*
HeldenStats transforms logfiles of CounterStrike into a detailled statistic
Started on 7-10-2001
Written by Benjamin Held
Copyright (C)

This program is free software; you can redistribute it and/ or modify it 
under the terms of the GNU General Public License as published by 
the Free Software Foundation; either version 2 of the License, 
or (at your option) any later version.

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with this program; if not, write to the Free Software 
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "datum.hpp"

Datum::Datum(int tt, int mm, int jj)
{
	t = tt;
	m = mm;
	j = jj;

	int SchaltJahre = (jj / 4);

	//Daysto0 = SchaltJahre * 366 + (jj - SchaltJahre) * 365  ;
	CalcDaysto0();
}

int Datum::operator-(Datum &datum)
{
	return Daysto0 - datum.Daysto0;
}

int Datum::DaysToNull()
{
	return Daysto0;
}

int Datum::CalcDaysto0()
{
	long int Tage=0, z;

	for(z = 1; z <= j; z++)
	{
		if((z % 4) == 0)
			Tage = Tage + 366;
		else
			Tage = Tage + 365;
	}
	
	for(z = 0; z < m-1; z++)
	{
		Tage = Tage + Monate[z];
	}
	Tage = Tage + t - 1;
	Daysto0 = Tage;
	return Tage;
}

Zeit::Zeit(int hh, int mm, int ss)
{
	h = hh;
	m = mm;
	s = ss;

	CalcSekunden();
}

int Zeit::Seconds()
{
	return Sekunden;
}

int Zeit::operator-(Zeit &zeit)
{
/*	int Diffh = h - zeit.h;
	int Diffm = m - zeit.m;
	int Diffs = s - zeit.s;

	return Diffh * 60 * 60 + Diffm * 60 + Diffs;*/
	return Sekunden - zeit.Sekunden;
}

void Zeit::AddHours(int Hours)
{
	h += Hours;
}

int Zeit::CalcSekunden()
{
	Sekunden = h * 60 * 60 + m * 60 + s;
	return Sekunden;
}
/*#include <iostream.h>
#include <math.h>
#include <stdlib.h>

int max (int a, int b)
{
   if (a>b) return(a) ; else return (b);
}

int min (int a, int b)
{
   if (a>b) return(b); else return (a);
}

class Date
{
 public:
    Date ();
    Date ( int mn, int day, int yr);  // constructor
    void display();                   // function to display date
    int GetMonth();
    void SetMonth(int mn);
    ~Date();
 private:
    int month, day, year;
    int DaysSoFar();
};

// constructor definition
 Date::Date ()
{
   month = day = year = 1;
}

Date::Date (int mn, int dy, int yr)
{
   static int length[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   month = max(1, mn);
   month = min(month,12);

   day = max(1,dy);
   day = min(day, length[month]);

   year = max(1, yr);
}

void Date::display()
{
   static char *name[] = {"nothing", "January", "February", "March", "April",
            "May", "June", "July", "August", "September", "October",
            "November", "December" };

   cout << '\n' << name[month] << ' ' << day << "," << year << '\n';
   cout << "Days so far: " << DaysSoFar() << '\n';
}

Date::~Date()
{
   cout << "Thank You for using DateLine Services and have a nice date\n";
}

int Date::DaysSoFar()
{
   int total = 0;
   static int length[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   for (int i=1; i < month; i++) total += length[i];
   total += day;
   return (total);
}

int Date::GetMonth()
{
   return month;
}

void Date::SetMonth(int mn)
{
   month = max(1, mn);
   month = min(month, 12);
}

*/