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

/*
StrFilter filtertet einen String und gibt eine ZeichenKette zurück
StrFilter ( "Das;ist;ein;Test", 2, ';'); //liefert ist
*/
//#include <windows.h>
#include <stdio.h>
#include <string.h>

char *StrFilter( char *str, unsigned int Feld, char Zeichen)
{
	static char returntext[100] = "";
	char *temp = str;
	unsigned int Offset[2] = {0,0}, z = 0, test = 1, loop;
	
	
	test = Feld * 2 - 1;
	for (loop = 0; loop < strlen( str ); loop++)
	{
		if (temp[loop] == Zeichen)
		{
			z++;
			//if ( z == Feld + test )
			if ( z == test )
				Offset[0] = loop + 1;

			//if ( z == Feld + 1 + test )
			if ( z == 1 + test )
			{
				Offset[1] = loop;
				break;
			}
		}
		if (loop < 100)
			returntext[loop]= '\0';
	}
	for (loop = Offset[0]; loop < Offset[1]; loop++)
	{
		returntext[loop - Offset[0]] = temp[loop];
	}
	
	return returntext;
}

char *StrFilter( char *str, unsigned int Feld, char Zeichen1, char Zeichen2)
{
	static char returntext[100] = "";
	char *temp = str;
	unsigned int Offset[2] = {0,0}, z = 0, test = 1, loop;
	
	test = Feld * 2 - 1;
	for (loop = 0; loop < strlen( str ); loop++)
	{
		if (temp[loop] == Zeichen1)
		{
			z++;
			//if ( z == Feld + test )
			if ( z == test )
				Offset[0] = loop + 1;

		}
		if(temp[loop] == Zeichen2)
		{
			if(Offset[0])
			{
				z++;
				Offset[1] = loop;
				break;
			}

		}
		if (loop < 100)
			returntext[loop]= '\0';
	}
	for (loop = Offset[0]; loop < Offset[1]; loop++)
	{
		returntext[loop - Offset[0]] = temp[loop];
	}
	
	return returntext;
}

char *StrFilterReverse( char *str, unsigned int Feld, char Zeichen1, char Zeichen2)
{
	static char returntext[100] = "";
	char *temp = str;
	unsigned int Offset[2] = {0,0}, test = 1, z = 0;
	int loop = 0;
	
	test = Feld * 2 - 1;
	for (loop = strlen( str ) - 1; loop >= 0; loop--)
	{
		if (temp[loop] == Zeichen2)
		{
			z++;
			//if ( z == Feld + test )
			if ( z == test )
				Offset[1] = loop;

		}
		if(temp[loop] == Zeichen1)
		{
			if(Offset[1])
			{
				z++;
				Offset[0] = loop + 1;
				break;
			}

		}
		if (loop < 100)
			returntext[loop]= '\0';
	}
	for(loop = 0; loop < 100; loop++)
		returntext[loop] = '\0';
	for (loop = Offset[0]; loop < Offset[1]; loop++)
	{
		returntext[loop - Offset[0]] = temp[loop];
	}
	
	return returntext;
}

char *StrFilterReverse( char *str, unsigned int Feld, char Zeichen)
{
	static char returntext[100] = "";
	char *temp = str;
	unsigned int Offset[2] = {0,0}, z = 0, test = 1;
	int loop;	
	
	test = Feld * 2 - 1;
	for (loop = strlen( str ) - 1; loop >= 0; loop--)
	{
		if (temp[loop] == Zeichen)
		{
			z++;
			//if ( z == Feld + test )
			if ( z == test )
				Offset[1] = loop;

			//if ( z == Feld + 1 + test )
			if ( z == 1 + test )
			{
				Offset[0] = loop + 1;
				break;
			}
		}
		if (loop < 100)
			returntext[loop]= '\0';
	}
	for(loop = 0; loop < 100; loop++)
		returntext[loop] = '\0';

	for (loop = Offset[0]; loop < Offset[1]; loop++)
	{
		returntext[loop - Offset[0]] = temp[loop];
	}
	
	return returntext;
}
