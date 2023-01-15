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

#include <qapplication.h>
#include "MyHeldenStatsDialog.hpp"
#include <qfiledialog.h>
#include <string>

using std::string;

int main( int argc, char **argv )

{

	QApplication app( argc, argv );

	MyHeldenStats MainWindow;//(0, "HeldenStats", true);
	app.setMainWidget( &MainWindow );

	bool Hide = false, Exit = false, Messages = false, StartAtOnce = false;
	int z;
	
	MainWindow.SetOptions(false, true);
	
	if(argc >= 4)
	{	
		//Optionen rausfiltern und übergeben
		//H = Hide
		//E = Exit
		//M = Messages
		
		for(z = 0; z < strlen(argv[1]); z++)
		{
			if(argv[1][z] == 'H')
				Hide = true;		
			else if(argv[1][z] == 'E')
				Exit = true;
			else if(argv[1][z] == 'M')
				Messages = true;
			else if(argv[1][z] == 'S')
				StartAtOnce = true;
		}	
		MainWindow.SetOptions(Exit, Messages);
		
		//Das OutputVerzeichnis übergeben
		char Output[200];
		
		strcpy(Output, argv[2]);
		if(Output[strlen(Output) - 1] != '/' && Output[strlen(Output) - 1] != '\\')
			strcat(Output, "/");
			
		MainWindow.SetOutputDir(Output);			
		
		//Die Logdateien/Verzeichnisse übergeben
		string Temp;
		for(z = 3; z < argc; z++)
		{
			//Wenn es kein absoluter Pfad ist
			#ifndef _WS_WIN_
				if(argv[z][0] != '/' && argv[z][0] != '\\')
				{
					Temp = (QDir::currentDirPath()).latin1();
					if(Temp[strlen(Temp.c_str()) - 1] != '/')
						Temp += '/';
				}
			#endif
			Temp += argv[z];
			//wenn es ein Verzeichnis ist, überprüfen ob ein / am Ende ist
			if(argv[z][strlen(argv[z]) - 4] != '.')
				if(argv[z][strlen(argv[z]) - 1] != '/' && argv[z][strlen(argv[z]) - 1] != '\\')
					Temp += '/';
			
			MainWindow.NewLog(Temp.c_str());
		}
	}
	if(!Hide)
		MainWindow.show();

	if(StartAtOnce)
		MainWindow.CreateHTML();

	int ret=app.exec();
	//app.quit();
	return ret;

}
