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

#include <iostream>
#include <string.h>
#include <QMessageBox>
//#include <qmessagebox.h>

class MyException
{
private :
	char Meldung[400];
public :
	MyException(const char *String)
	{
		strcpy(Meldung, String);
	}
	void Message()
	{
		if(Meldung)
			std::cerr << Meldung;
	}
	void QtMessage()
	{
		if(Meldung)
			QMessageBox::critical(0, "Fehler", Meldung);


	}
};
