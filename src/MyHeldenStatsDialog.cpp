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

#include "MyHeldenStatsDialog.hpp"
#include "linetransformer.hpp"
#include "Exception.cpp"
#include "StrFilter.h"

#include <QMessageBox>
#include <QFileDialog>
#include <Q3StrList>
#include <QLabel>
#include <QRegExp>
#include <QTabWidget>
#include <QDateTime>
#include <Q3ProgressBar>

Spieler *Players = new Spieler; 

/* 
0 = UngeradeFarbe
1 = GeradeFarbe
2 = HTMLHintergrund
3 = KopfzeileBG
4 = TableBG
5 = Kopfzeile
6 = TabellenFont
7 = NormalFont
8 = LinkFarbe
9 = HoverLink
*/

//F�r den Timer zust�ndig
int Zeit = 0;
bool Messages=true;

MyHeldenStats::MyHeldenStats( QWidget* parent, const char* name,
	bool modal, WFlags f) : HeldenStats( parent, name, modal, f )
{

	//FarbAnzahl = 25;
	Farben.resize(FarbAnzahl);

	Farben[0] = UnEvenBG;
	Farben[1] = EvenBG;
	Farben[2] = HTMLBG;
	Farben[3] = TableCaptionBG;
	Farben[4] = TableBG;
	Farben[5] = TableCaptionColor;
	Farben[6] = TableFontColor;
	Farben[7] = FontColor;
	Farben[8] = LinkColor;
	Farben[9] = HoverLinkColor;
	Farben[10]= TableCaptionFont;
	Farben[11]=	TableFont;
	Farben[12]= Font;
	Farben[13]= LinkFont;
	Farben[14]= HoverLinkFont;

	Farben[15]= TableCaptionSize;
	Farben[16]= TableFontSize;
	Farben[17]= FontSize;
	Farben[18]= LinkFontSize;
	Farben[19]= HoverLinkSize;
	Farben[20]= TableCaptionStyle;
	Farben[21]= TableFontStyle;
	Farben[22]= FontStyle;
	Farben[23]= LinkFontStyle;
	Farben[24]= HoverLinkFontStyle;
	Farben[25]= TableBorderColor;
	Farben[26]= TableBorderSize;
	Farben[27]=	TableCellSpacingSize;

	Voraussetzungen.resize(RequiresCount);

	Voraussetzungen[0] = MinSkill;
	Voraussetzungen[1] = MinKills;
	Voraussetzungen[2] = MinDeaths;
	Voraussetzungen[3] = MaxPlayers;
	
	RequireCheck.resize(RequiresCount);

	RequireCheck[0] = CheckSkill;
	RequireCheck[1] = CheckKills;
	RequireCheck[2] = CheckDeaths;
	RequireCheck[3] = CheckPlayers;

	#ifdef _WS_WIN_
		strcpy(ConfigDir, (QDir::currentDirPath()).latin1());
		if(ConfigDir[strlen(ConfigDir) - 1] != '/')
			strcat(ConfigDir, "/");
	#else
		strcpy(ConfigDir, (QDir::homeDirPath()).latin1());
		if(ConfigDir[strlen(ConfigDir) - 1] != '/')
			strcat(ConfigDir, "/");
		//Als versteckte Daatei markieren
		strcat(ConfigDir, ".");			
	#endif
	ReadDirs();
	Working = false;
	ExitWhenRdy = false;

}

void MyHeldenStats::SelectLogFiles()
{
	//ReadDirs();	
	QStringList LogFiles = QFileDialog::getOpenFileNames ( "Log Dateien(*.log)", InputDir,
		this, "", "Bitte die Logdateien ausw�hlen" );

	if(LogFiles.count() > 0)
	{
		LogDateienListe->insertStringList(LogFiles); 

		char LogPath[200];
		strcpy(LogPath, LogDateienListe->text(0));
		//Sucht nach dem letzten '/' und schreibt dann NUR den Pfad in LogPath
		for(int y = strlen(LogPath)-1; y >= 0; y--)
			if(LogPath[y] == '/')
			{
				LogPath[y] = '\0';
				break;					
			}
				
		//strcat(LogPath, "/\n");
		InputDir = LogPath;
	}
}

void MyHeldenStats::SelectOutputDir()
{
	QFile ConfigFile("HeldenConfig.cfg");
	char OutputPath[201];


	
	//Die letzten Verzeichnisse lesen aus der Configdatei(falls vorhanden)
	if(ConfigFile.open(IO_ReadOnly))
	{
		//Zweite Linie enth�lt das OutputDir
		ConfigFile.readLine(OutputPath, 200);
		ConfigFile.readLine(OutputPath, 200);
		ConfigFile.close();
	}		
	else
	{
		strcpy(OutputPath, QDir::rootDirPath ());

	}
	
	OutputDir = QFileDialog::getExistingDirectory(OutputPath, this, "test", "Bitte das Output Verzeichnis angeben", true);
	QString Current = "Aktuelles Verzeichnis : " + OutputDir;

	CurrentDirLabel->setText(Current); 
}

void MyHeldenStats::CreateHTML()
{
	if(!Working)
	{
		Working = true;
		if(OutputDir.isEmpty())
		{
			if(Messages)
			{
				QMessageBox::critical(this, "Fehler", "Bitte das Output Verzeichnis ausw�hlen");
			}
		}
		else
			if(LogDateienListe->count() == 0)
			{
				if(Messages)
					QMessageBox::critical(this, "Fehler", "Bitte Logdateien ausw�hlen");
			}
			else
			{
				//Kein Fehler -> �ffne die LogDateien und schreibe die HTML Files
				char Bild[100];

				if(Players->CheckForPics(Bild))
				{
					//Schrift/Hintergrund-Farbe setzen
					QTime zeit;
					
					zeit.start();


					unsigned int z;								
					//Setzt die Spieler, die zusammengef�gt werden m�ssen
					for(z = 0; z < CombinedPlayers->count(); z++)
					{
						char NameString[200], Name1[100], Name2[100];

						strcpy(NameString, (CombinedPlayers->text(z)).latin1());
						//name1 ist JoinPlayer
						strcpy(Name1, StrFilter(NameString, 1, '\"'));
						//Name2 ist BasePlayer

						strcpy(Name2, StrFilter(NameString, 2, '\"'));
						Players->NewCombinePlayers(Name2, Name1);
					}

					//Setzt DeleteUnranked und HideMaps
					if(!(HideMaps->isChecked()))
						Players->MapsOn();
					if(DeleteUnranked->isChecked())
						Players->DeleteUnranked();
					
					//Setzt die Maximale Anzahl von Gegner in der Spielerstatistik(wichtig!)
					Players->SetPvsPCount((MaxPvsP->text()).toInt());


					for(int zaehler = 0; zaehler < FarbAnzahl; zaehler++)
						Players->SetColor((Farben[zaehler]->text() ).latin1(), zaehler );

					//char temp[6];

					for(int y = 0; y < RequiresCount; y++)
					{
						Players->SetRequires((Voraussetzungen[y]->text()).toInt(), y);
						Players->SetRequiresCheck(RequireCheck[y]->isChecked(), y);
					}

					int LogAnzahl=0; 

					//Vorher die Logdateien z�hlen f�r die Progressbar!
					for(z = 0; z < LogDateienListe->count(); z++)
					{
						QString Datei = LogDateienListe->text(z);

						if(Datei.right(1) == "/")
						{
							QDir Dir(Datei, "*.log");
							QStringList Dateien = Dir.entryList();
							
							LogAnzahl += Dateien.count();
						}
						else
							LogAnzahl++;

					}
					ProgressBar->setTotalSteps(LogAnzahl+1);
					ProgressBar->setProgress(0);

					//Die NameTags setzen!
					Players->SetNameTagCount(Namen->count());
					for(z = 0; z < Namen->count(); z++)
						Players->NewNameTag(Namen->text(z), z);
	

					for(z = 0; z < LogDateienListe->count(); z++)
					{
						QString Datei = LogDateienListe->text(z);

						if(Datei.right(1) == "/")
						{
							QDir Dir(Datei, "*.log");

							QStringList Dateien = Dir.entryList();
							for(int y=0; y < Dateien.count(); y++)
							{
	//							QMessageBox::information(this, "HeldenStats", Dateien[y]);
								char temp[200];

								sprintf(temp, "%s%s", Datei.latin1(), Dateien[y].latin1());
								try
								{
									FileTransformer(temp, Players);
								}
								catch (MyException &Fehler)
								{
									if(Messages)
										Fehler.QtMessage();
								}
								ProgressBar->setProgress(ProgressBar->progress() + 1);
							}
							//LogAnzahl+=Dateien.count();
							//LogDateienListe->insertStringList(Dateien);
						}
						else
						{
							try
							{
								FileTransformer(LogDateienListe->text(z), Players);
							}
							catch (MyException &Fehler)
							{
								if(Messages)
									Fehler.QtMessage();
							}
							ProgressBar->setProgress(ProgressBar->progress() + 1);
							//LogAnzahl++;
						}
					}

					try
					{
						Players->WritePlayerHTML(OutputDir.latin1(), LogAnzahl);
						WriteDirs();
						delete Players;
						Players = new Spieler;

					}
					catch(MyException Fehler)
					{
						if(Messages)
							Fehler.QtMessage();
					}
					

					ProgressBar->setProgress(ProgressBar->progress() + 1);
					if(Messages)
					{
						char Nachricht[100];
						sprintf(Nachricht, "Fertig : %i Datei(en) kompiliert in %d Sekunde(n)!", LogAnzahl, zeit.elapsed() / 1000);
						QMessageBox::information(this, "HeldenStats", Nachricht);
					}
					ProgressBar->setProgress(0);
				}
				else
				{
					char Nachricht[200];
					sprintf(Nachricht, "Das Bild : %s konnte nicht gefunden werden, �berpr�fen sie bitte ob es vorhanden ist!", Bild);
					QMessageBox::critical(this, "Fehler", Nachricht);
				}
			}
		Working = false;
	}
	if(ExitWhenRdy)
	{
		//done(1);
		//accept();
		//reject();
		exit(0);
	}
}

void MyHeldenStats::ResetColors()
{
	int zaehler;

	//Schrift/Hintergrund-Farbe setzen in der Klasse Spieler

	//Schrift/Hintergrund-Farbe setzen
	for(zaehler = 0; zaehler < FarbAnzahl; zaehler++)
	{
		Farben[zaehler]->setText(Colors[zaehler].c_str());
		Players->SetColor(Colors[zaehler].c_str(), zaehler );
	}

}

void MyHeldenStats::SaveColors()
{
	try
	{
		WriteDirs();
		QMessageBox::information(this, "HeldenStats", "Einstellungen gespeichert!");
	}
	catch(MyException Fehler)
	{
		Fehler.QtMessage();
	}

}

void MyHeldenStats::WriteDirs()
{
	char Path[300];

	sprintf(Path, "%sHeldenConfig.cfg", ConfigDir);
	QFile ConfigFile(Path);
	
	if(ConfigFile.open(IO_WriteOnly))
	{
		string Inhalt="";

		Inhalt = Inhalt + InputDir.latin1() + "\n";
		Inhalt = Inhalt + OutputDir.latin1() + "\n";
		for(int zaehler = 0; zaehler < FarbAnzahl; zaehler++)
			Inhalt = Inhalt + (Farben[zaehler]->text()).latin1() + "\n";

		Inhalt = Inhalt + (MaxPvsP->text()).latin1() + "\n";

		int z;

		for(z=0; z < RequiresCount; z++)
		{
			Inhalt = Inhalt + (Voraussetzungen[z]->text()).latin1() + "\n";
		}
		for(z=0; z < RequiresCount; z++)
		{
			if(RequireCheck[z]->isChecked())
				Inhalt = Inhalt + "true" + "\n";
			else
				Inhalt = Inhalt + "false" + "\n";
		}
		//Nametags schreiben, erst die Anzahl, dann die einzelnen Nametags
		char temp[10];
		sprintf(temp, "%i", Namen->count());
		
		Inhalt = Inhalt + temp  + "\n";
		
		for(z = 0; z < Namen->count(); z++)
		{
			Inhalt = Inhalt + (Namen->text(z)).latin1() + "\n";		
		}
		//Die beiden Checkaestchen HideMaps und ShowDamage scrheiben
		if(HideMaps->isChecked())
			Inhalt = Inhalt + "true" + "\n";
		else
			Inhalt = Inhalt + "false" + "\n";

		if(DeleteUnranked->isChecked())
			Inhalt = Inhalt + "true" + "\n";
		else
			Inhalt = Inhalt + "false" + "\n";
		
		//CombinedPlayers schreiben, erst die Anzahl, dann die einzelnen Spieler
		sprintf(temp, "%i", CombinedPlayers->count());

		Inhalt = Inhalt + temp + "\n";

		for(z = 0; z < CombinedPlayers->count(); z++)
		{
			char NameString[200], Name1[100], Name2[100];

			strcpy(NameString, (CombinedPlayers->text(z)).latin1());
			strcpy(Name1, StrFilter(NameString, 1, '\"'));
			strcpy(Name2, StrFilter(NameString, 2, '\"'));

			Inhalt = Inhalt + Name1 + "\n" + Name2 + "\n";
		}

		ConfigFile.writeBlock(Inhalt.c_str(), strlen(Inhalt.c_str()));
		ConfigFile.close();
	}
	else
		throw MyException("Fehler beim �ffnen der Config Datei!");
}

void MyHeldenStats::ReadDirs()
{
	if(InputDir != QDir::rootDirPath () && OutputDir != QDir::rootDirPath ())
	{
		char Path[300];

		sprintf(Path, "%sHeldenConfig.cfg", ConfigDir);
		QFile ConfigFile(Path);

		char LogPath[201];

		if(ConfigFile.open(IO_ReadOnly))
		{
			ConfigFile.readLine(LogPath, 200);
			LogPath[strlen(LogPath)-1] = '\0';
			InputDir = LogPath;
			ConfigFile.readLine(LogPath, 200);
			LogPath[strlen(LogPath)-1] = '\0';
			OutputDir = LogPath;

			for(int zaehler = 0; zaehler < FarbAnzahl; zaehler++)
			{
				if(ConfigFile.readLine(LogPath, 200) != -1)
				{
					LogPath[strlen(LogPath)-1] = '\0';
					Farben[zaehler]->setText(LogPath);
				}
			}
			int z;

			//F�r PvsP
			ConfigFile.readLine(LogPath, 200);
			LogPath[strlen(LogPath)-1] = '\0';
			MaxPvsP->setText(LogPath);

			for(z = 0; z < RequiresCount; z++)
			{
				if(ConfigFile.readLine(LogPath, 200) != -1)
				{
					LogPath[strlen(LogPath)-1] = '\0';
					Voraussetzungen[z]->setText(LogPath);
				}
			}
			for(z = 0; z < RequiresCount; z++)
			{
				if(ConfigFile.readLine(LogPath, 200) != -1)
				{
					LogPath[strlen(LogPath)-1] = '\0';
					if(strcmp(LogPath, "true") == 0)
						RequireCheck[z]->setChecked(true);
					else
						RequireCheck[z]->setChecked(false);
				}
			}
			int NameCount;
			if(ConfigFile.readLine(LogPath, 200) != -1)
			{
				LogPath[strlen(LogPath)-1] = '\0';
				NameCount = atoi(LogPath);
				
				for(z = 0; z < NameCount; z++)
				{
					if(ConfigFile.readLine(LogPath, 200) != -1)
					{
						LogPath[strlen(LogPath)-1] = '\0';
						Namen->insertItem(LogPath);				
					}					
				}							
			}			
			if(ConfigFile.readLine(LogPath, 200) != -1)
			{
				LogPath[strlen(LogPath)-1] = '\0';

				if(strcmp(LogPath, "true") == 0)
					HideMaps->setChecked(true);
				else
					HideMaps->setChecked(false);
			}			
			
			if(ConfigFile.readLine(LogPath, 200) != -1)
			{
				LogPath[strlen(LogPath)-1] = '\0';

				if(strcmp(LogPath, "true") == 0)
					DeleteUnranked->setChecked(true);
				else
					DeleteUnranked->setChecked(false);
			}			

			//
			if(ConfigFile.readLine(LogPath, 200) != -1)
			{
				LogPath[strlen(LogPath)-1] = '\0';

				NameCount = atoi(LogPath);
				for(z = 0; z < NameCount; z++)
				{
					string Beide="";
					if(ConfigFile.readLine(LogPath, 200) != -1)
					{
						LogPath[strlen(LogPath)-1] = '\0';
					}
					Beide = Beide + "Spieler: \"" + LogPath + "\" wird zu Spieler: \"";
					if(ConfigFile.readLine(LogPath, 200) != -1)
					{
						LogPath[strlen(LogPath)-1] = '\0';
					}
					Beide = Beide + LogPath + "\" hinzugef�gt.";
					CombinedPlayers->insertItem(Beide.c_str());
				}
			}
			ConfigFile.close();
		}	
		else
		{
			InputDir = QDir::rootDirPath ();
			OutputDir = QDir::rootDirPath ();
		}
	}
}

void MyHeldenStats::SelectLogDir()
{
	QString LogDir = QFileDialog::getExistingDirectory(InputDir, this, "test", "Bitte das ein Verzeichnis angeben, indem sich die Logdateien befinden", true);
	
	if(LogDir != NULL)
	{
		InputDir = LogDir;
  	LogDateienListe->insertStringList(LogDir);
	}

}

MyHeldenStats::~MyHeldenStats()
{
	delete Players;
}


void MyHeldenStats::TimerEnabled()
{
	if(CheckTimer->isChecked())
	{
		Messages=false;
		startTimer(1000*60);

		char LabelText[200];
		sprintf(LabelText, "Noch %i Minuten bis zum umwandeln.", (TimerTime->text()).toInt());
		TimerLabel->setText(LabelText);
	}
	else
	{
		Messages=true;
		killTimers();
		TimerLabel->setText("Der Timer ist nicht aktiviert.");
		Zeit = 0;
	}
}

void MyHeldenStats::timerEvent(QTimerEvent * )
{
	char LabelText[200];

	Zeit++;

	if( (TimerTime->text()).toInt() - Zeit >= 0)
		sprintf(LabelText, "Noch %i Minuten bis zum umwandeln.", (TimerTime->text()).toInt() - Zeit);
	else
		sprintf(LabelText, "Der vorherige Vorgang ist noch nicht abgeschlossen.");
	TimerLabel->setText(LabelText);
	if(Zeit >= (TimerTime->text()).toInt())
	{
		if(!Working)
		{
			CreateHTML();

			sprintf(LabelText, "Noch %i Minuten bis zum umwandeln.", (TimerTime->text()).toInt());
			TimerLabel->setText(LabelText);
			Zeit = 0;
		}
	}
}

void MyHeldenStats::DelFiles()

{
	LogDateienListe->clear();
}


//F�gt einen neuen NameTag hinzu
void MyHeldenStats::NewNameTag()
{
	char NeuerName[300];

	strcpy(NeuerName, NameEdit->text());

	if(strcmp(NeuerName, "") != 0)
	{
		Namen->insertItem(NeuerName);
	}
}

//L�scht die ausgew�hlten Namen aus der Liste
void MyHeldenStats::DeleteNameTag()
{	
	int Deleted = 0, Count = Namen->count();


	for(int z = 0; z < Count; z++)
	{
		if(Namen->isSelected(z - Deleted))
		{
			Namen->removeItem(z - Deleted);
			Deleted++;
		}
	}
}

void MyHeldenStats::DeleteAllNameTags()
{
	Namen->clear();
}

void MyHeldenStats::SaveNameTags()
{
	WriteDirs();
	QMessageBox::information(this, "HeldenStats", "Nametags gespeichert");
	
}

void MyHeldenStats::Combine()
{
	string Namen[2];
	string Beide = "";
	string Nachricht;

	bool Error = false;

	Namen[0] = (BasePlayer->text()).latin1();
	Namen[1] = (JoinPlayer->text()).latin1();

	if(Namen[1] == "")
	{
		Error = true;
		Nachricht = "Sie m�ssen in das zweite Eingabefeld etwas eintragen!";
	}

	if(Namen[0] == "")
	{
		Error = true;
		Nachricht = "Sie m�ssen in das erste Eingabefeld etwas eintragen!";
	}

	for(int z = 0; z < 2; z++)
	{
		for(int y = 0; y < strlen(Namen[z].c_str()); y++)
		{
			if(Namen[z][y] == '\"')
			{
				Nachricht = "Es d�rfen keine \" im Namen sein!";
				Error=true;
			}
		}
	}

	if(!Error)
	{
		Beide = "Spieler: \"" + Namen[1] + "\"" + " wird zu " + "Spieler: \"" + Namen[0] + "\"" + " hinzugef�gt.";
		CombinedPlayers->insertItem(Beide.c_str());
	}
	else
		QMessageBox::critical(this, "HeldenStats", Nachricht.c_str());

}

void MyHeldenStats::DeleteCombinedPlayers()
{
	int Deleted = 0, Count = CombinedPlayers->count();


	for(int z = 0; z < Count; z++)
	{
		if(CombinedPlayers->isSelected(z - Deleted))
		{
			CombinedPlayers->removeItem(z - Deleted);
			Deleted++;
		}
	}
	
}

void MyHeldenStats::SavePlayers()
{
	WriteDirs();
	QMessageBox::information(this, "HeldenStats", "Gespeichert!");
}

void MyHeldenStats::ClearCombinedPlayers()
{
	CombinedPlayers->clear();
}

void MyHeldenStats::SetOptions(bool Exit, bool Messages)
{
	::Messages = Messages;
	ExitWhenRdy = Exit;
	//QMessageBox::information(this, "HeldenStats", "Options");
	
}
void MyHeldenStats::NewLog(const char *Log)
{
	LogDateienListe->insertItem(Log);
}


void MyHeldenStats::SetOutputDir(const char *Output)
{
	OutputDir = Output;
	QString Current = "Aktuelles Verzeichnis : " + OutputDir;

	CurrentDirLabel->setText(Current);

}

