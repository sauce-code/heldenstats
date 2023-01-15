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

#include "Spieler.hpp"
#include <qfile.h>
#include <qstringlist.h>
#include "Exception.cpp"
#include "StrFilter.h"
#include <stdio.h>
#include <qmessagebox.h>
#include <string.h>
#include "datum.hpp"
#include <qstring.h>

int StringVorhanden(string *String, const char *ZuSuchen, int Anzahl);
int StringVorhanden(vector<string> &String, const char *ZuSuchen, int Anzahl);

static string StaticMap = "Unbekannte Map";

//Analysiert die LogDatei und ändert dem entsprechend Players
void FileTransformer(const char *LogFile, Spieler *Players)
{
	QFile LogDatei(LogFile);

	if(LogDatei.open(IO_ReadOnly))
	{
		char Line[301];
		string BombPlanted = "";
		int AnzahlAkt=0, AnzahlGekillt=0;
		vector <Datum> datum;
		vector <Zeit> zeit;
		vector <string> AktNamen;
		vector <string> Gekillt;
		Zeit GameStarted;
		Datum GameStartedDate;
		bool GameHasStarted = false;
		//Anonyme Map setzen, wird später ggf. geändert
		//Players->SetCurrentMap("Unbekannte Map");
		Players->SetCurrentMap(StaticMap.c_str());
		
		while(LogDatei.readLine(Line, 300) != -1)
		{
			if(strlen(Line) > 26)
			{
				if(!GameHasStarted)
				{
					QString Tag="", Monat="", Jahr="";

					Tag = Tag + Line[2] + Line[3];
					Monat = Monat + Line[5] + Line[6];
					Jahr = Jahr + Line[8] + Line[9] + Line[10] + Line[11];
					GameStartedDate.SetDate(Tag.toInt(), Monat.toInt(), Jahr.toInt());

					QString Sekunde="", Minute="", Stunde="";

					Stunde = Stunde + Line[15] + Line[16];
					Minute = Minute + Line[18] + Line[19];
					Sekunde = Sekunde + Line[21] + Line[22];
					
					GameStarted.SetTime(Stunde.toInt(), Minute.toInt(), Sekunde.toInt());

					GameHasStarted = true;
				}
				int z;
				//cout << Line << "\n";	
				if(Line[25] == '\"')
				{
					Line[25] = '\'';
					char action[100];
					strcpy(action, StrFilter(Line, 1, '\"'));

					//Wenn der Name geändert wurde
					if(strcmp(action, " changed name to ") == 0)
					{
						char *Name, ZuName[100], temp[301];

						//Beispiel:
						//L 07/27/2001 - 21:56:54: "[MFC]-KPC<5><4294967295><TERRORIST>" changed name to "benjamin"


						//Kopiert benjamin in ZuName
						strcpy(ZuName, StrFilterReverse(Line, 1, '\"'));

						//Findet den Namen des Spielers
						strcpy(temp, Line);

						int y, Anzahl = 0;

						for(y = strlen(Line); y > 0; y--)
						{
							if(Line[y] == '<')
								Anzahl++;
							if(Anzahl == 3)
							{
								temp[y] = '\0';
								break;
							}
						}
						Name = &temp[26];

						Players->NameChange(Name, ZuName);

						//Auch in AktNamen und Gekillt ändern

						int Index;
						Index = StringVorhanden(AktNamen, Name, AnzahlAkt);
						if( Index != -1)
						{
							AktNamen.push_back(ZuName);
						}

						Index = StringVorhanden(Gekillt, Name, AnzahlGekillt);
						if (Index != -1)
						{
							Gekillt.push_back(ZuName);
						}

					}
					//wenn jemand einen anderen Spieler angeschossen hat oder ihn gekillt hat
					if(strcmp(action, " killed ") == 0 || strcmp(action, " attacked ") == 0)
					{
						//Wenn jemand gekillt wurde, hier werden Name, Waffe gefiltert und dann an Spieler::NewKills übergeben
						char Buffer[300], *temp;
						char Waffe[50], WasKilledName[50], KillerName[50];
						int WasKilledTeam, KillerTeam;
						
						if(strcmp(action, " killed ") == 0)
							strcpy(Waffe, StrFilterReverse(Line, 1, '\"'));
						else
							strcpy(Waffe, StrFilterReverse(Line, 5, '\"'));
						strcpy(Buffer, StrFilterReverse(Line, 1, '<', '>'));
						if(strcmp(Buffer, "CT") == 0)
							WasKilledTeam = 0;
						else
							WasKilledTeam = 1;

						//Ab hier wird der Name des getöteten Spielers in WasKilledName geschrieben
						strcpy(Buffer, Line);
						unsigned int Anzahl1 = 0, Offset = 0, nachkilled;
						int Anzahl2 = 0;
						
						if(strcmp(action, " attacked ") == 0)
							Anzahl2 = -8;
							
						for(z = strlen(Buffer) - 1; z >= 0; z--)
						{
							if(Buffer[z] == '<')
								Anzahl1++;
							//es gibt 3x das Zeichen '<', dann kommt das ende des Spielernamens, das Zeichen wird durch eine \0 ersetzt
							if(Anzahl1 == 3)
							{
									if(!Offset)
										Offset = z;
							}     	
							if(Buffer[z] == '\"')
								Anzahl2++;
							//Es kommt 4x ein " bis zum Anfang des Spielernamens
							if(Anzahl2 == 4)
							{
        						temp = &Buffer[z+1];
								//Wird später für den Namens des Killers gebraucht
								nachkilled = z - 1;
								break;
							}     	
						}
						Buffer[Offset] = '\0';
						if(Offset == 0)
						{
							char Nachricht[500];
							sprintf(Nachricht, "Die Logdatei : %s ist fehlerhaft!", LogFile);
							throw MyException(Nachricht);
						}
						strcpy(WasKilledName, temp);

						//Ab hier wird der Name des Killers in KillerName geschrieben
						Anzahl1 = 0;
						Offset = 0;
						char tempstring[20] = "";

						for(z = 0; z < 19; z++)
							tempstring[z] = '\0';
						for(z = nachkilled; z > 0; z--)
						{
							if(Buffer[z] == '>')
								if(!Offset)
									Offset = z - 1;
							if(Buffer[z] == '<')
								Anzahl1++;
							//es gibt 3x das Zeichen '<', dann kommt das ende des Spielernamens, das Zeichen wird durch eine \0 ersetzt
							if(Anzahl1 == 1)
							{
								if(strcmp(tempstring, "") == 0)
									for(unsigned int y=z+1; y <= Offset; y++)
										sprintf(tempstring, "%s%c", tempstring, Buffer[y]);        	
							}
							if(Anzahl1 == 3)
							{
								Buffer[z] = '\0';
								break;
							}     	
							
						}
						temp = &Buffer[26];
						strcpy(KillerName, temp);

						if(strcmp(tempstring, "CT") == 0)
							KillerTeam = 0;
						else
							KillerTeam = 1;

						if(strcmp(action, " killed ") == 0)
							Players->NewKills(KillerName, WasKilledName, KillerTeam, WasKilledTeam, Waffe, 1);
						else
						{
							//Hier noch den Schaden an Rüstung und Leben filtern
							int LifeLeech, ArmorLeech;
							char Life[10], Armor[10], TempLeech[50];
							
							strcpy(TempLeech, StrFilterReverse(Line, 3, '\"'));
							//Dann steht in TempLeech : "armor:x", wobei x eine Zahl ist :-)
							strcat(TempLeech, "\"");
							strcpy(Armor, StrFilterReverse(TempLeech, 1, ':', '\"'));							
														
							strcpy(TempLeech, StrFilterReverse(Line, 4, '\"'));
							//Dann steht in TempLeech : "health:x", wobei x eine Zahl ist :-)
							strcat(TempLeech, "\"");
							strcpy(Life, StrFilterReverse(TempLeech, 1, ':', '\"'));							
							
							LifeLeech = atoi(Life);
							ArmorLeech = atoi(Armor);
							
							Players->NewDamage(KillerName, Waffe, LifeLeech, ArmorLeech, KillerTeam, WasKilledTeam);
						}

						QString Tag, Monat, Jahr;

						Tag="";
						Monat="";
						Jahr="";
						Tag = Tag + Line[2] + Line[3];
						Monat = Monat + Line[5] + Line[6];
						Jahr = Jahr + Line[8] + Line[9] + Line[10] + Line[11];

						QString Sekunde="", Minute="", Stunde="";

						Stunde = Stunde + Line[15] + Line[16];
						Minute = Minute + Line[18] + Line[19];
						Sekunde = Sekunde + Line[21] + Line[22];


						if(StringVorhanden(AktNamen, KillerName, AnzahlAkt) == -1)
						{
							AktNamen.push_back(KillerName);
							datum.push_back(Datum(Tag.toInt(), Monat.toInt(), Jahr.toInt()));
							zeit.push_back(Zeit(Stunde.toInt(), Minute.toInt(), Sekunde.toInt()));
							AnzahlAkt++;
						}
						if(StringVorhanden(AktNamen, WasKilledName, AnzahlAkt) == -1)
						{
							AktNamen.push_back(WasKilledName);
//							if(zeit[AnzahlAkt].IsNull() && datum[AnzahlAkt].IsNull())
//							{
							datum.push_back(Datum(Tag.toInt(), Monat.toInt(), Jahr.toInt()));
							zeit.push_back(Zeit(Stunde.toInt(), Minute.toInt(), Sekunde.toInt()));
//							}
							AnzahlAkt++;
						}
						if(StringVorhanden(Gekillt, WasKilledName, AnzahlGekillt) == -1)
						{
							Gekillt.push_back(WasKilledName);
							AnzahlGekillt++;
						}
						
/*						if(AnzahlAkt >= ReservedSpace)

						{
							ReservedSpace += 50;
							datum.resize(ReservedSpace);
							zeit.resize(ReservedSpace);
							AktNamen.resize(ReservedSpace, "");
						}*/
					}

					if(strcmp(action, " triggered ") == 0)
					{
						z=0;
						bool Found = false;

						//Es wird überprüft ob es eine "gültige" Aktion ist, dann wird der Name
						//ausgelesen und an Players.NewAction wird der Name, die Aktion und die Anzahl übergeben
						while(z < AKTIONENANZAHL && !Found)
						{
							char *Name;
							char temp[300];

							if(strcmp(Aktionen[z].text, StrFilterReverse(Line, 1, '\"')) == 0)
							{
								int y=0, Anzahl=0;

								//Ein temporärer String wird erstellt und die aktuelle Zeile hineinkopiert
								//Danach wird nach dem 3. '<' Zeichen gesucht, weil davor der Name steht
								//Der String wird dort mit '\0' abgeschlossen
								//Der Name beginnt beim 26. Zeichen, deswegen Name = &temp[26]
								strcpy(temp, Line);
								for(y = strlen(Line); y > 0; y--)
								{
									if(Line[y] == '<')
										Anzahl++;
									if(Anzahl == 2)
									{
										temp[y-1] = '\0';
									}
								}

								Name = &temp[26];
								Players->NewAction(Name, StrFilterReverse(Line, 1, '\"'), 1);
								Found = true;
								
								if(strcmp(StrFilterReverse(Line, 1, '\"'), "Planted_The_Bomb") == 0)
								{
									BombPlanted = Name;
								}
								if(strcmp(StrFilterReverse(Line, 1, '\"'), "Defused_The_Bomb") == 0)
								{
									if(BombPlanted != "")
									{
										Players->NewAction(BombPlanted.c_str(), "TargetNotBombed", 1);
										BombPlanted = "";
									}
								}
							}
							z++;
						}
					}
					if(strcmp(action, " joined team ") == 0)
					{
						char WelchesTeam[50], *Name, temp[301];
						int y, Anzahl = 0;


						strcpy(WelchesTeam, StrFilterReverse(Line, 1, '\"'));

						//Findet den Namen des Spielers
						strcpy(temp, Line);
						for(y = strlen(Line); y > 0; y--)
						{
							if(Line[y] == '<')
								Anzahl++;
							if(Anzahl == 3)
							{
								temp[y] = '\0';
								break;
							}
						}
						Name = &temp[26];
						if(strcmp(WelchesTeam, "TERRORIST") == 0 || strcmp(WelchesTeam, "CT") == 0)
							Players->NewAction(Name, WelchesTeam, 1);


						//Spieler zu den aktuellen hinzufügen und Datum + Zeit
						if(StringVorhanden(AktNamen, Name, AnzahlAkt) == -1)
						{
							AktNamen.push_back(Name);
							QString Tag="", Monat="", Jahr="";

							Tag = Tag + Line[2] + Line[3];
							Monat = Monat + Line[5] + Line[6];
							Jahr = Jahr + Line[8] + Line[9] + Line[10] + Line[11];


							QString Sekunde="", Minute="", Stunde="";

							Stunde = Stunde + Line[15] + Line[16];
							Minute = Minute + Line[18] + Line[19];
							Sekunde = Sekunde + Line[21] + Line[22];

							datum.push_back(Datum(Tag.toInt(), Monat.toInt(), Jahr.toInt()));
							zeit.push_back(Zeit(Stunde.toInt(), Minute.toInt(), Sekunde.toInt()));
							
							AnzahlAkt++;
/*							if(AnzahlAkt >= ReservedSpace)
							{
								ReservedSpace += 50;
								datum.resize(ReservedSpace);
								zeit.resize(ReservedSpace);
								AktNamen.resize(ReservedSpace, "");
							}*/
						}
	//					QMessageBox::information(0, WelchesTeam, Name);

					}
					if(strcmp(action, " committed suicide with ") == 0)
					{
						if(strcmp(StrFilterReverse(Line, 1, '\"'), "grenade") == 0 || strcmp(StrFilterReverse(Line, 1, '\"'), "worldspawn") == 0)
						{
							char *Name, temp[301];
							int y, Anzahl = 0;

							//Findet den Namen des Spielers
							strcpy(temp, Line);
							for(y = strlen(Line); y > 0; y--)
							{
								if(Line[y] == '<')
									Anzahl++;
								if(Anzahl == 3)
								{
									temp[y] = '\0';
									break;
								}
							}
							Name = &temp[26];
							Players->NewAction(Name, "Suicide", 1);
						}
					}
				}

				if(strcmp(StrFilterReverse(Line, 3, '\"' ), "CTs_Win") == 0)
					Players->CTWin();
				if(strcmp(StrFilterReverse(Line, 3, '\"' ), "Terrorists_Win") == 0)
					Players->TSWin();
								
				
				if(strcmp(StrFilterReverse(Line, 3, '\"' ), "Target_Bombed") == 0)
				{
					if(BombPlanted != "")
						Players->NewAction(BombPlanted.c_str(), "TargetBombed", 1);
					BombPlanted = "";
				}
				//Ändert die AktNamen Liste -> Löscht den Namen, der disconnected hat
				//Wichtig für die Rundenberechnung
				//Berechnet die gespielte Zeit
				if(strcmp(StrFilterReverse(Line, 1, ' ', 'd' ), "disconnecte") == 0)
				{
					char temp[301], *Name;
					int Anzahl = 0;

					//Findet den Namen des Spielers
					strcpy(temp, Line);
					for(int y = strlen(Line); y > 0; y--)
					{
						if(Line[y] == '<')
							Anzahl++;
						if(Anzahl == 3)
						{
							temp[y] = '\0';
							break;
						}
					}
					Name = &temp[26];


					//QMessageBox::information(0, "HeldenStats",Name);
					int Index = StringVorhanden(AktNamen, Name, AnzahlAkt);

					if(Index != -1)
					{
						//int PlayedTime = datum[Index] - discDate;
						//Datum und Uhrzeit beim disconnecten speichern
						if(!zeit[Index].IsNull() && !datum[Index].IsNull())
						{
							QString Tag="", Monat="", Jahr="";

							Tag = Tag + Line[2] + Line[3];
							Monat = Monat + Line[5] + Line[6];
							Jahr = Jahr + Line[8] + Line[9] + Line[10] + Line[11];


							QString Sekunde="", Minute="", Stunde="";

							Stunde = Stunde + Line[15] + Line[16];
							Minute = Minute + Line[18] + Line[19];
							Sekunde = Sekunde + Line[21] + Line[22];

							Datum discDate(Tag.toInt(), Monat.toInt(), Jahr.toInt());
							Zeit discTime(Stunde.toInt(), Minute.toInt(), Sekunde.toInt());
							discTime.AddHours((discDate - datum[Index]) * 24);

							if(discTime - zeit[Index] > 0)
								Players->AddPlayedTime(Name, discTime - zeit[Index]);
						}
						AnzahlAkt--;
						
					
						//Löschen
						zeit.erase(zeit.begin() + Index);
						datum.erase(datum.begin() + Index);
						AktNamen.erase(AktNamen.begin() + Index);
						
						//QMessageBox::information(0, "HeldenStats", Test.c_str());


					}
				}
				if(strcmp(StrFilter(Line, 1, '\"'), "Round_End") == 0)
				{
					vector<string> Auslagerung;
					int z, AuslagerungAnz = 0;


					//Eine Runde addieren
					Players->NewRound();

					if(BombPlanted != "")
					{
						Players->NewAction(BombPlanted.c_str(), "TargetBombed", 1);					
						BombPlanted = "";
					}
					for(z = 0; z < AnzahlAkt; z++)
					{
						Players->NewAction(AktNamen[z].c_str(), "NewRound", 1);
						//Guckt welcher Spieler überlebt hat
				 		if(StringVorhanden(Gekillt, AktNamen[z].c_str(), AnzahlGekillt) == -1)
				 		{
				 			Auslagerung.push_back(AktNamen[z]);
				 			AuslagerungAnz++;
				 		}
					}
					
					//Wenn nur ein SPieler überlebt hat, kriegt er Last man Standing
					if(AuslagerungAnz == 1)
						Players->NewAction(Auslagerung[0].c_str(), "LastManStanding", 1);
					//Alle Spieler die überlebt haben, kriegen ein RoundSurvived gutgeschrieben
					for(z = 0; z < AuslagerungAnz; z++)
					{
						Players->NewAction(Auslagerung[z].c_str(), "RoundSurvived", 1);
					}
//					for(z = 0; z < AnzahlGekillt; z++)
//						Gekillt[z] = "";

					//Alle Elemente loeschen
					Gekillt.clear();
					AnzahlGekillt = 0;
				}

				//Sucht nach Loading Map mit temp[24] = '\"' sieht es so aus :
				//L 08/05/2001 - 22:27:06:"Loading map "de_aztec"
				//Also -> strcmp(StrFilter(temp, 1, '\"'), "Loading map ") == 0

				char temp[301];
				strcpy(temp, Line);

				temp[24] = '\"';

//				QMessageBox::information(0, StrFilter(temp, 1, '\"'), StrFilterReverse(temp, 1, '\"'));
				if(strcmp(StrFilter(temp, 1, '\"'), "Loading map ") == 0 ||

					strcmp(StrFilter(temp, 1, '\"'), "Spawning server ") == 0)
				{
					//QMessageBox::information(0, "HeldenStats", StrFilterReverse(temp, 1, '\"'));
					Players->SetCurrentMap(StrFilterReverse(temp, 1, '\"'));
					StaticMap = StrFilterReverse(temp, 1, '\"');
				}
			}

		}
		QString Tag="", Monat="", Jahr="";

		Tag = Tag + Line[2] + Line[3];
		Monat = Monat + Line[5] + Line[6];
		Jahr = Jahr + Line[8] + Line[9] + Line[10] + Line[11];


		QString Sekunde="", Minute="", Stunde="";

		Stunde = Stunde + Line[15] + Line[16];
		Minute = Minute + Line[18] + Line[19];
		Sekunde = Sekunde + Line[21] + Line[22];

		Datum discDate(Tag.toInt(), Monat.toInt(), Jahr.toInt());
		Zeit discTime(Stunde.toInt(), Minute.toInt(), Sekunde.toInt());
		discTime.AddHours((discDate - GameStartedDate) * 24);

		if(discTime - GameStarted > 0)
			Players->AddPlayedTimeOnMap(discTime - GameStarted);

		//Spielzeit für die Leute berechnen, die den Server nicht verlassen haben!
		Datum discDate2(Tag.toInt(), Monat.toInt(), Jahr.toInt());
		for(int z = 0; z < AnzahlAkt; z++)
		{			
					if(!zeit[z].IsNull() && !datum[z].IsNull())
					{
						Zeit discTime2(Stunde.toInt(), Minute.toInt(), Sekunde.toInt());
					
						discTime2.AddHours((discDate2 - datum[z]) * 24);
						if(discTime2 - zeit[z] > 0)
							Players->AddPlayedTime(AktNamen[z].c_str(), discTime2 - zeit[z]);
					}								
		}
			
		LogDatei.close();
	}
	else
	{
		char Nachricht[500];
		
		sprintf(Nachricht, "Datei: %s konnte nicht geöffnet werden", LogFile);
		throw MyException(Nachricht);
	}
}

int StringVorhanden(string *String, const char *ZuSuchen, int Anzahl)
{
	for(int z = 0; z < Anzahl; z++)
	{
		if(strcmp(String[z].c_str(), ZuSuchen) == 0)
			return z;
	}
	return -1;

}

int StringVorhanden(vector <string> &String, const char *ZuSuchen, int Anzahl)
{
	for(int z = 0; z < Anzahl; z++)
	{
		if(strcmp(String[z].c_str(), ZuSuchen) == 0)
			return z;
	}
	return -1;

}
