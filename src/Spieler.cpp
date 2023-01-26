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
#include "Exception.cpp"

#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>

#include <QFile>
#include <QString>
#include <qdir.h>

#ifndef SPIELER_CPP


using namespace std ;

int BalkenBreite = 200;

void FileCopy(char *OutName, char *InName);



/*char IndexDatei[] =
"<html>
<head><title>CSStats</title></head>

<frameset rows=\"20%,80%\">
<frame src=\"�Titel.html\" name=\"Titel\">
<frame src=\"�Spieler.html\" name=\"Haupt\">
</frameset>
</html>
";

char TitelDatei[] =
"<html>
<head></head>
<body>
<a href=\"�Spieler.html\" target=\"Haupt\">Spielerstatistiken</a>
<a href=\"�Awards.html\" target=\"Haupt\">Awards</a>
</body>
</html>
";*/

char IndexDatei[] = "<html><head><title>HeldenStats</title><link rel=stylesheet type=\"text/css\" href=\"style.css\"></head><frameset rows=\"120,*\" border=0><frame src=\"titel.html\" name=\"Titel\" border=0><frame src=\"spieler.html\" name=\"Haupt\"></frameset></html>";

char MapIndex[] = "<html>"

"<head>"
"<title>MapStats</title>"
"</head>"
"<frameset cols=\"15%,85%\" border=0 frameborder=0 framespacing=0>"
"	<frame src=\"maplinks.html\" name=\"LinkesFenster\">"
"   <frame src=\"mapoverview.html\" name=\"HauptFenster\">"
"</frameset>"
"<body>"
"</body>"
"</html>";


//char TitelDatei[2000] ="<html>"
string TitelDatei ="<html>"
"<head>"
"<link rel=stylesheet type=\"text/css\" href=\"style.css\">"
"</head>"
"<body>"
"<script language=\"JavaScript\">"
"<!--\n"
"temp1=new Image\n"
"temp2=new Image\n"
"temp1.src=\"images/title/player.gif\"\n"
"temp2.src=\"images/title/playeron.gif\"\n"
"temp3=new Image\n"
"temp4=new Image\n"
"temp3.src=\"images/title/awards.gif\"\n"
"temp4.src=\"images/title/awardson.gif\"\n"
"temp5=new Image\n"
"temp6=new Image\n"
"temp5.src=\"images/title/weapon.gif\"\n"
"temp6.src=\"images/title/weaponon.gif\"\n"
"temp7=new Image\n"
"temp8=new Image\n"
"temp7.src=\"images/title/maps.gif\"\n"
"temp8.src=\"images/title/mapson.gif\"\n"
"//-->\n"
"</script>\n"
"<center>"
"<a href=\"http://www.heldenstats.de.vu\" target=\"Haupt\">\n"
"<img src=\"images/title/banner.gif\" border=0></a>\n"
"<br>\n"
"<a href=\"spieler.html\" target=\"Haupt\" onmouseout=\"roll1.src=temp1.src\" onmouseover=\"roll1.src=temp2.src\"><img src=\"images/title/player.gif\" border=0 name=roll1></a>"
"<a href=\"awards.html\" target=\"Haupt\" onmouseout=\"roll2.src=temp3.src\" onmouseover=\"roll2.src=temp4.src\"><img src=\"images/title/awards.gif\" border=0 name=roll2></a>"
"<a href=\"weapon.html\" target=\"Haupt\" onmouseout=\"roll3.src=temp5.src\" onmouseover=\"roll3.src=temp6.src\"><img src=\"images/title/weapon.gif\" border=0 name=roll3></a>"
"<a href=\"mapindex.html\" target=\"Haupt\" onmouseout=\"roll4.src=temp7.src\" onmouseover=\"roll4.src=temp8.src\"><img src=\"images/title/maps.gif\" border=0 name=roll4></a>"
"</body>\n"
"</html>";



WAFFEN Waffen[] =
{
{"usp",        0},
{"glock18",    1},
{"deagle",     2},
{"p228",       3},
{"elite",      4},
{"fiveseven",  5},
{"m3",         6},
{"xm1014",     7},
{"mp5navy",    8},
{"tmp",        9},
{"p90",       10},
{"mac10",     11},
{"ump45",     12},
{"ak47",      13},
{"sg552",     14},
{"m4a1",      15},
{"aug",       16},
{"scout",     17},
{"awp",       18},
{"g3sg1",     19},
{"sg550",     20},
{"m249",      21},
{"grenade",   22},
{"knife",     23}
} ;

//Zu Status(letztes) :
//1 = Positiv
//2 = Negativ

//4 = Allgemein
//8 = Counter-Terroristen
//16 = Terroristen

//Die Zahlen werden addiert Beispiel : 
//Terroristen und Positiv = 17

AKTIONEN Aktionen[] =
{
{"Kill", 0, "Kills", true, 0, 5},
{"Deaths", 1, "Deaths", true, 0, 6},
{"KilledCT", 2, "Counter get�tet", true, 0, 17},
{"KilledTS", 3, "Terroristen get�tet", true, 0, 9},
{"Spawned_With_The_Bomb", 4, "Mit der Bombe gestartet", true, 0, 17},
{"Dropped_The_Bomb", 5, "Bombe verloren", true, 0, 18},
{"Got_The_Bomb", 6, "Bombe aufgesammelt", true, 0, 17},
{"Planted_The_Bomb", 7, "Bombe gelegt", true, 2, 17},
{"Begin_Bomb_Defuse_Without_Kit", 8, "Entsch�rfungsversuche ohne Kit", true, 2, 9},
{"Begin_Bomb_Defuse_With_Kit", 9, "Entsch�rfungsversuche mit Kit", true, 2, 9},
{"Defused_The_Bomb", 10, "Bombe entsch�rft", true, 3, 9},
{"TargetBombed", 11, "Bombe explodiert", true, 3, 17},
{"TargetNotBombed", 12, "Bombe nicht explodiert", true, -2, 18},
{"Touched_A_Hostage", 13, "Geisel ber�hrt", true, 2, 9},
{"Killed_A_Hostage", 14, "Geisel get�tet", true, -3, 6},
{"Rescued_A_Hostage", 15, "Geisel gerettet", true, 2, 9},
{"Became_VIP", 16, "Als VIP gestartet", true, 0, 9},
{"Assassinated_The_VIP", 17, "VIP get�tet", true, 3, 17},
{"Escaped_As_VIP", 18, "Als VIP entkommen", true, 3, 9},
{"TERRORIST", 19, "Terroristen beigetreten", true, 0, 17},
{"CT", 20, "Antiterroristen beigetreten", true, 0, 9},
{"KillStreak", 21, "Kills hintereinander ohne sterben", false, 0, 5},
{"DeathsStreak", 22, "Deaths hintereinander ohne Kills", false, 0, 6},
{"RoundSurvived", 23, "Runden �berlebt", false, 0, 5},
{"NewRound", 24, "Runden gespielt", true, 0, 5},
{"TK", 25, "TeamKills", true, -4, 6},
{"WasTKed", 26, "Gestorben durch TeamKills", true, 0, 6},
{"LastManStanding", 27, "Letzter �berlebender", true, 0, 5},
{"Suicide", 28, "Selbstmord", true, 0, 6},
{"PosAwards", 29, "Positive Auszeichnungen", true, 0, 5},
{"NegAwards", 30, "Negative Auszeichnungen", true, 0, 6},
{"CTWin", 31, "Antiterroristen gewonnen", true, 0, 9},
{"TSWin", 32, "Terroristen gewonnen", true, 0, 17},
{"DamageHealths", 33, "Lebensenergie abgezogen", true, 0, 5},
{"DamageArmor", 34, "R�stung zerst�rt", true, 0, 5}
} ;

FLOATAKTIONEN FloatAktionen[] =
{
{"KillsperRnd", 0, "Kills pro Runde", false, 5},
{"DeathsperRnd", 1, "Deaths pro Runde", false, 6},
{"KillsperMin", 2, "Kills pro Minute", false, 5},
{"DeathsperMin", 3, "Deaths pro Minute", false, 6},
{"PlayedTime", 4, "Gespielte Zeit in Minuten", true, 5},
{"DamageHealthsperKill", 5, "Lebensenergie abgezogen pro Kill", false, 5},
{"DamageArmorperKill", 6, "R�stung zerst�rt pro Kill", false, 5},
{"DamageHealthsperRnd", 7, "Lebensenergie abgezogen pro Runde", false, 5},
{"DamageArmorperRnd", 8, "R�stung zerst�rt pro Runde", false, 5}
} ;


//Zu Status(letztes) :
//0 = Allgemein
//1 = Counter-Terroristen
//2 = Terroristen
MAPAKTIONEN MapAktionen[] =
{
{"TeamSkill", 0, "TeamSkill", false, 0, 0},
{"Kill", 1, "Kills", true, 0, 0},
{"Deaths", 2, "Deaths", true, 0, 0},
{"KilledCT", 3, "Counter get�tet", true, 0, 2},
{"KilledTS", 4, "Terroristen get�tet", true, 0, 1},
{"Planted_The_Bomb", 5, "Bombe gelegt", true, 2, 2},
{"Begin_Bomb_Defuse_Without_Kit", 6, "Entsch�rfungsversuche ohne Kit", true, 2, 1},
{"Begin_Bomb_Defuse_With_Kit", 7, "Entsch�rfungsversuche mit Kit", true, 2, 1},
{"Defused_The_Bomb", 8, "Bombe entsch�rft", true, 3, 1},
{"TargetBombed", 9, "Bombe explodiert", true, 3, 2},
{"TargetNotBombed", 10, "Bombe nicht explodiert", true, -2, 2},
{"Touched_A_Hostage", 11, "Geisel ber�hrt", true, 2, 1},
{"Killed_A_Hostage", 12, "Geisel get�tet", true, -3, 0},
{"Rescued_A_Hostage", 13, "Geisel gerettet", true, 2, 1},
{"Assassinated_The_VIP", 14, "VIP get�tet", true, 3, 2},
{"Escaped_As_VIP", 15, "Als VIP entkommen", true, 3, 1},
{"RoundSurvived", 16, "Runden �berlebt", false, 0, 0},
{"NewRound", 17, "Runden gespielt", true, 0, 0},
{"LastManStanding", 18, "Letzter �berlebender", true, 0, 0},
{"Suicide", 19, "Selbstmord", true, 0, 0},
{"CTWin", 20, "Antiterroristen gewonnen", true, 0, 1},
{"TSWin", 21, "Terroristen gewonnen", true, 0, 2}
} ;

string Bilder[] = {"images/title/awards.gif", "images/title/awardson.gif", 
	"images/title/player.gif", "images/title/playeron.gif",
	"images/title/weapon.gif", "images/title/weaponon.gif",
	"images/title/banner.gif", "images/balken.gif", "images/title/maps.gif", "images/title/mapson.gif"};




Spieler::Spieler()
{
	int z;

	#ifdef _WS_WIN_
		strcpy(ImagePath, QDir::currentDirPath());
		if(ImagePath[strlen(ImagePath) - 1] != '/')
			strcat(ImagePath, "/");
		//strcat(ImagePath, "images/");
	#else
		strcpy(ImagePath, "/usr/local/share/heldenstats/");
	#endif

	//Platz reservieren
	SortNames.resize(SortCount);
	//Aktivieren, soll sp�ter �ber eine Option des GUI aktiviert werden k�nnen!
	WriteAwards = true;
	DeleteUnrankedPeople = 0;
	AnzahlSpieler = 0;
	InsgKills = 0;
	InsgSpielZeit = 0;	
	InsgRunden = 0;
	CombineCount = 0;
	UnRankedPlayers = 0;	
				
	ShowMaps = false;
	
	Requires.resize(RequiresCount);
	RequiresIgnore.resize(RequiresCount);
	PlayedTime.resize(ANFANGSNAMEN);
	KDRate.resize(ANFANGSNAMEN);
//	Sortierung.resize(ANFANGSNAMEN);
	KillStreakTmp.resize(ANFANGSNAMEN);
	DeathsStreakTmp.resize(ANFANGSNAMEN);
	Skill.resize(ANFANGSNAMEN);
	TeamSkill.resize(ANFANGSNAMEN);
	//SpielerNamen = new string[sizeof(string) * ANFANGSNAMEN]; //ANFANGSNAMEN Strings f�r !alle! Spieler
	SpielerNamen.resize(ANFANGSNAMEN, "");
	ReservedSpaceForSpielerNamen = ANFANGSNAMEN;
	Kills.resize(ANFANGSNAMEN);
	Rang.resize(ANFANGSNAMEN);

	WaffenKills.resize(WEAPONANZAHL);
	PlayerWeaponKill.resize(WEAPONANZAHL, "");
	NumWeaponKill.resize(WEAPONANZAHL);

	FloatNumAward.resize(FLOATAKTIONENANZAHL);
	FloatPlayerAward.resize(FLOATAKTIONENANZAHL, "");
	FloatCountofAction.resize(FLOATAKTIONENANZAHL);

	PlayerAward.resize(AKTIONENANZAHL, "");
	NumAward.resize(AKTIONENANZAHL);
	CountofAction.resize(AKTIONENANZAHL);

	//Aktivieren, sol sp�ter �ber GUI aktiviert werden k�nnen
	ShowDamage = 1;

	if(ShowDamage == 1)
	{	
		DamageHealths.resize(ANFANGSNAMEN);
		DamageArmor.resize(ANFANGSNAMEN);
	}
	
	Deaths.resize(ANFANGSNAMEN);
	Actions.resize(ANFANGSNAMEN);
	FloatActions.resize(ANFANGSNAMEN);
	
	for(z = 0; z < ANFANGSNAMEN; z++)
	{
		if(ShowDamage == 1)
		{
			DamageHealths[z].resize(WEAPONANZAHL);
			DamageArmor[z].resize(WEAPONANZAHL);
		}
		Kills[z].resize(WEAPONANZAHL);
		Deaths[z].resize(WEAPONANZAHL);
		Actions[z].resize(AKTIONENANZAHL);
		Skill[z] = 100;
		TeamSkill[z] = 100;
		FloatActions[z].resize(FLOATAKTIONENANZAHL);
	}

}
Spieler::~Spieler()
{
	//aufraeumen :
//	delete[] SpielerNamen;
}

inline int Spieler::WelcherSpieler(const char *Name)
{
	char AliasName[100];
	
	strcpy(AliasName, Name);
	int z;
	//�berpr�ft ob Spieler zusammen gef�gt werden m�ssen und liefert dann den Index
	for(z = 0; z < CombineCount; z++)
		if(JoinPlayers[z] == AliasName)
			strcpy(AliasName, BasePlayers[z].c_str());		
	//Sucht nach dem Namen und liefert den Index zur�ck
	for(z = 0; z < AnzahlSpieler; z++)
		if(strcmp(SpielerNamen[z].c_str(), AliasName) == 0)
			return z;



	return NeuerSpieler(AliasName);

}

inline int Spieler::NeuerSpieler(const char *Name)
{
	//Braucht nicht mehr, seit die Spielerdateien als 1.html, 2.html, ... geschrieben werden
	/*for(unsigned int z = 0; z < strlen(Name); z++)
	{
		if(Name[z] == '*' || Name[z] == '|' || Name[z] == '<' || Name[z] == '>' || Name[z] == '\\' || Name[z] == '/' || Name[z] == '?' || Name[z] == ':' || Name[z] == '\"')
		{
			Name[z] = '�';
		}
	}*/

	if(strcmp(Name, "") != 0)
	{
//		if( WelcherSpieler(Name) == -1)
//		{
		if(AnzahlSpieler >= ReservedSpaceForSpielerNamen)
		{
			ReserveNewSpaceForSpielerNamen();
		}
		
		AnzahlSpieler++;
		SpielerNamen[AnzahlSpieler - 1] = Name;
		return AnzahlSpieler - 1;
//		}
	}
	return -1;
}

void Spieler::ReserveNewSpaceForSpielerNamen()
{
	int z;
	
	ReservedSpaceForSpielerNamen += NEWSPACE;
	//Platz f+r SpielerNamen reservieren
	SpielerNamen.resize(ReservedSpaceForSpielerNamen, "");

	//Platz f�r KDRate reservieren
	KDRate.resize(ReservedSpaceForSpielerNamen);	

	//Platz f�r Sortierung reservieren
//	Sortierung.resize(ReservedSpaceForSpielerNamen);	

	//Platz f�r Actions reservieren
	Actions.resize(ReservedSpaceForSpielerNamen);	
	//Platz f�r Skill reservieren
	Skill.resize(ReservedSpaceForSpielerNamen);
	//Platz f�r TeamSkill reservieren
	TeamSkill.resize(ReservedSpaceForSpielerNamen);
	//Platz f�r Kills reservieren
	Kills.resize(ReservedSpaceForSpielerNamen);
	//Platz f�r Deaths reservieren
	Deaths.resize(ReservedSpaceForSpielerNamen);	
	//Platz f�r FloatActions reservieren
	FloatActions.resize(ReservedSpaceForSpielerNamen);	
	//Platz f�r PlayedTime reservieren
	PlayedTime.resize(ReservedSpaceForSpielerNamen);	

	if(ShowDamage == 1)
	{
		//Platz f�r DamageHealths reservieren
		DamageHealths.resize(ReservedSpaceForSpielerNamen);	
		//Platz f�r DamageArmor reservieren
		DamageArmor.resize(ReservedSpaceForSpielerNamen);	
	}
		
	if(MaxPvsPCount)
	{
		PvsPCount.resize(ReservedSpaceForSpielerNamen);
		PvsPKills.resize(ReservedSpaceForSpielerNamen, vector<int>(MaxPvsPCount));
		PvsPDeaths.resize(ReservedSpaceForSpielerNamen, vector<int>(MaxPvsPCount));
		//Hat die Indexe der Gegner(f�r die Spielernamen)
		PvsPIndex.resize(ReservedSpaceForSpielerNamen, vector<int>(MaxPvsPCount));
  }

	if(ShowMaps)
	{
		for(z = 0; z < SpaceForMaps; z++)
		{
			MapActions[z].resize(ReservedSpaceForSpielerNamen);	
			for(int y = ReservedSpaceForSpielerNamen - NEWSPACE; y < ReservedSpaceForSpielerNamen; y++)
			{
				MapActions[z][y].resize(MAPAKTIONENANZAHL);
				//TeamSkill auf 100 setzen
				MapActions[z][y][0] = 100;
			}
		}
	}

	for(z = ReservedSpaceForSpielerNamen - NEWSPACE; z < ReservedSpaceForSpielerNamen; z++)
	{
		if(ShowDamage == 1)
		{
			DamageHealths[z].resize(WEAPONANZAHL);
			DamageArmor[z].resize(WEAPONANZAHL);
		}
		Actions[z].resize(AKTIONENANZAHL);
		Kills[z].resize(WEAPONANZAHL);
		Deaths[z].resize(WEAPONANZAHL);
		Skill[z] = 100;
		TeamSkill[z] = 100;
		FloatActions[z].resize(FLOATAKTIONENANZAHL);
		if(MaxPvsPCount)
		{
			for(int y = 0; y < MaxPvsPCount; y++)
				PvsPIndex[z][y] = -1;
		}
		
	}
	//Platz f�r KillStreakTmp reservieren







	KillStreakTmp.resize(ReservedSpaceForSpielerNamen);

	//Platz f�r DeathsStreakTmp reservieren
	DeathsStreakTmp.resize(ReservedSpaceForSpielerNamen);

	/*for(z = ReservedSpaceForSpielerNamen - NEWSPACE; z < ReservedSpaceForSpielerNamen; z++)
		Skill[z] = 100;*/
		
	//Platz f�r Rang reservieren
	Rang.resize(ReservedSpaceForSpielerNamen);

}

inline void Spieler::GetSpieler(char *Buffer, int Welcher)
{
	strcpy(Buffer, SpielerNamen[Welcher].c_str());
}

void Spieler::NewKills(const char *Killer, const char *Opfer, int KillerTeam, int OpferTeam, const char *Weapon, int n)
{
	int KillerID, OpferID, WaffeID, KillStreakID, DeathsStreakID;
	int KilledCTID, KilledTSID;

	KillerID = WelcherSpieler(Killer);
	OpferID = WelcherSpieler(Opfer);
	WaffeID = WelcheWaffe(Weapon);
	KillStreakID = WelcheAktion("KillStreak");
	DeathsStreakID = WelcheAktion("DeathsStreak");
	KilledCTID = WelcheAktion("KilledCT");
	KilledTSID = WelcheAktion("KilledTS");

	if(KillerID == -1)
	{
		NeuerSpieler(Killer);
		KillerID = WelcherSpieler(Killer);
	}
	if(OpferID == -1)
	{
		NeuerSpieler(Opfer);
		OpferID = WelcherSpieler(Opfer);
	}

	if(WaffeID == -1)
	{
		char Nachricht[500];
		sprintf(Nachricht, "Die angeforderte Kill-Abfrage konnte nicht best�tigt werden, da die Waffe: %s nicht existiert!", Weapon);
		throw MyException(Nachricht);
		cout << Weapon << " : Waffe existiert nicht!\n";

	}
	if(KilledCTID == -1)
	{
		throw MyException("KilledCT existiert nicht");

	}
	if(KilledTSID == -1)

	{

		throw MyException("KilledTS existiert nicht");
	}

	if(KillerTeam == OpferTeam)
	{
		if(KillerTeam == 0)
			NewAction(Killer, "KilledTS", n * -1);
		else if(KillerTeam == 1)
			NewAction(Killer, "KilledCT", n * -1);
		Kills[KillerID][WaffeID] -= n;
		
		NewAction(Killer, "TK", n);
		NewAction(Opfer, "WasTKed", n);
		//KillStreak wird auf 0 gesetzt wegen TK
		KillStreakTmp[KillerID] = 0;
		Skill[KillerID] -= 1;
		
		NewAction(Killer, "Kill", -n);
		NewAction(Opfer, "Deaths", n);


/*		Actions[KillerID][0] -= n;
		Actions[OpferID][1] += n;
		CountofAction[0] -= n;
		CountofAction[1] += n;*/
		
		InsgKills-=n;
		WaffenKills[WaffeID]-=n;
	}
	else
	{
		//Neue Aktion : Kill und Deaths
		NewAction(Killer, "Kill", n);
		NewAction(Opfer, "Deaths", n);
		//Actions[KillerID][0] sind die Kills
		//Actions[OpferID][1] sind die Deaths
/*		Actions[KillerID][0] += n;
		Actions[OpferID][1] += n;
		CountofAction[0] += n;
		CountofAction[1] += n;/*/

		//F�r die PvsPStatistik zust�ndig

		NewPvsPKills(KillerID, OpferID, n);

		if(KillerTeam == 0)
			NewAction(Killer, "KilledTS", n);
		else if(KillerTeam == 1)
			NewAction(Killer, "KilledCT", n);
			
		Kills[KillerID][WaffeID] += n;
		//Killsstreak um n erh�hen
		KillStreakTmp[KillerID] += n;
		//Deathsstreak auf 0 setzen
		DeathsStreakTmp[KillerID] = 0;

		float Increase=0;

		/*Increase = (Skill[OpferID] * (10.0 / ((Skill[OpferID] + Skill[KillerID]) / (float) Skill[OpferID]))) / 100.0;
		if(Increase < 3)
			Increase = 3;
		if(Increase > 10)
			Increase = 10;*/
		int Diff = Skill[KillerID] - Skill[OpferID];
		if(Diff <= 30 && Diff >= -30)
			Increase = 4;

		if(Diff > 30 && Diff <= 50)
			Increase = 3;

		if(Diff > 50)
			Increase = 2;

		if(Diff < -30 && Diff >= -50)
			Increase = 3;

		if(Diff < -50 && Diff >= -80)
			Increase = 4;

		if(Diff < -80)
			Increase = 5;

		if(Diff < -150)
			Increase = 6;
		//if((Diff > 30 && Diff <= 60) || (Diff < -30 && Diff > -60))
		//	Increase = 3;

		Skill[KillerID] += (int) Increase;
		Skill[OpferID] -= (int) Increase;
		InsgKills+=n;
		WaffenKills[WaffeID]+=n;


	}
	//Killstreak auf 0 setzen
	KillStreakTmp[OpferID] = 0;
	//Deathsstreak um n erh�hen
	DeathsStreakTmp[OpferID] += n;
	if(KillStreakTmp[KillerID] > Actions[KillerID][KillStreakID])
		Actions[KillerID][KillStreakID] = KillStreakTmp[KillerID];
	if(DeathsStreakTmp[OpferID] > Actions[OpferID][DeathsStreakID])
		Actions[OpferID][DeathsStreakID] = DeathsStreakTmp[OpferID];

	Deaths[OpferID][WaffeID] += n;
	//Actions[OpferID][1] += n;
	if(Actions[KillerID][1] == 0)
		KDRate[KillerID] = 0;
	else		

		KDRate[KillerID] = (float) Actions[KillerID][0] / Actions[KillerID][1];

	if(Actions[OpferID][1] == 0)
		KDRate[OpferID] = 0;
	else
		KDRate[OpferID] = (float) Actions[OpferID][0] / Actions[OpferID][1];

}

int Spieler::GetKills(char *Player, char *Weapon)
{
	int WelcherS, WelcheW;

	WelcherS = WelcherSpieler(Player);
	WelcheW = WelcheWaffe(Weapon);

	if(WelcherS == -1 || WelcheW == -1)
	{
		throw MyException("Die angeforderte Kill-Abfrage konnte nicht best�tigt werden, da der/die Spieler/Waffe nicht existiert!");
		return -1;




	}

	return Kills[WelcherS][WelcheW];
}

inline int Spieler::WelcheWaffe(const char *Waffe)
{
	for(int z = 0; z < WEAPONANZAHL; z++)
	{
		if(strcmp(Waffen[z].text, Waffe) == 0)
			return z;
	}

	return -1;
}

inline int Spieler::WelcheMap(const char *Map)
{
	for(int z = 0; z < MapCount; z++)
	{
		if(strcmp(MapNames[z].c_str(), Map) == 0)
			return z;

	}
	return -1;
}

inline int Spieler::WelcheAktion(const char *Aktion)
{
	for(int z = 0; z < AKTIONENANZAHL; z++)
	{
		if(strcmp(Aktionen[z].text, Aktion) == 0)
			return z;
	}

	return -1;
}

inline int Spieler::WelcheMapAktion(const char *MapAktion)

{
	for(int z = 0; z < MAPAKTIONENANZAHL; z++)
	{
		if(strcmp(MapAktionen[z].text, MapAktion) == 0)
			return z;
	}
	return -1;
}


inline int Spieler::WelcheFloatAktion(const char *Aktion)
{
	for(int z = 0; z < FLOATAKTIONENANZAHL; z++)
	{
		if(strcmp(FloatAktionen[z].text, Aktion) == 0)
			return z;
	}

	return -1;
}

void Spieler::CoutAllPlayers()
{

	for(int z = 0; z < AnzahlSpieler; z++)
	{
		cout << SpielerNamen[z].c_str() << " hat insgesamt " << Actions[z][0] << " Kills und ist ";
	//	cout << TotalDeaths[z] << "x gestorben, K:D=" << KDRate[z] << " TeamKills= " << TeamKills[z];

	//	cout << " DiedFromTeamKills= " << DiedFromTeamKills[z] << "\n";
	}
}

/*void Spieler::SortierenachKDRate()
{
	int Element, z;
	float temp, temp2;

	for(z = 0; z < AnzahlSpieler; z++)
		Sortierung[z] = 0;

	for(z = 0; z < AnzahlSpieler; z++)
	{
		Element = 0;
   		for(int y = 0; y < AnzahlSpieler; y++)
		{

			if(y != z)
			{
				temp = KDRate[z];
				temp2 = KDRate[y];
     			if(KDRate[y] > KDRate[z])
				{
					Element++;
				}
			}
			if(y == AnzahlSpieler-1)
			{
				if(!Sortierung[Element])
					Sortierung[Element] = z;
				else
				{
					while(Sortierung[Element])

						Element++;

					Sortierung[Element] = z;
				}
				cout << z << " : " << Sortierung[z] << "\n";
			}
		}
		
	}
}    */

void Spieler::WritePlayerHTML(const char *Pfad, int Logdateien)
{
	//Hier werden erstmal die Spieler sortiert
	SortierenachSkill();
	
	
	QFile HTMLDatei;
	
	LogFiles = Logdateien;

	char Path[200], Zeichen[1]; //WholeFile[100000] = "", TempFile[1000] ="";
	string WholeFile("");

	QDir Verzeichnis;


	if(Pfad[strlen(Pfad)-1] == '/')
		strcpy(Zeichen, "");
	else
		strcpy(Zeichen,  "/");


	//Hier werden die Abk�rzungen von den Tabellen erstellt, dann muss man nicht bei 
	//jeder Tabelle etwas �ndern, sondern nur hier
	TableSettings = "";
	TableSettings = TableSettings + " border=" + FarbNamen[26] + " cellspacing=" + FarbNamen[27] + ""
		" bgcolor=" + FarbNamen[4] + " bordercolor=" + FarbNamen[25] + " ";



	TableFontColor = "";
	/*TableFontColor = TableFontColor + "<font color=" + FarbNamen[6] + ""
		" size=" + FarbNamen[16] + ""
		" face=\"" + FarbNamen[11] + "\">";*/
	if(FarbNamen[21] == "Italic" || FarbNamen[21] == "italic")
	{
		TableFontColor = TableFontColor + "<i>";
	}


	TableCaptionColor = "";
	/*TableCaptionColor = TableCaptionColor + "<font color=" + FarbNamen[5] + ""
		" size=" + FarbNamen[15] + ""
		" face=\"" + FarbNamen[10] + "\">";*/
	TableCaptionColor = TableCaptionColor + "<font class=\"captionfont\">";

	if(FarbNamen[20] == "Italic" || FarbNamen[20] == "italic")
	{
		TableCaptionColor = TableCaptionColor + "<i>";
	}


	//ben�tigte Verzeichnisse erstellen
	sprintf(Path, "%s%sspieler", Pfad, Zeichen );
	Verzeichnis.setPath(Path);
	if(!Verzeichnis.exists())
		if(!Verzeichnis.mkdir(Path, true))
			throw MyException("Erstellung des Spieler Verzeichnisses fehlgeschlagen, keine Rechte f�r diesen Ordner?");
	sprintf(Path, "%s%sweapons", Pfad, Zeichen);
	Verzeichnis.setPath(Path);
	if(!Verzeichnis.exists())
		if(!Verzeichnis.mkdir(Path, true))
			throw MyException("Erstellung des Weapon Verzeichnisses fehlgeschlagen, keine Rechte f�r diesen Ordner?");

	sprintf(Path, "%s%simages", Pfad, Zeichen);
	Verzeichnis.setPath(Path);
	if(!Verzeichnis.exists())
		if(!Verzeichnis.mkdir(Path, true))
			throw MyException("Erstellung des Images Verzeichnisses fehlgeschlagen, keine Rechte f�r diesen Ordner?");

	sprintf(Path, "%s%simages/title", Pfad, Zeichen);
	Verzeichnis.setPath(Path);
	if(!Verzeichnis.exists())
		if(!Verzeichnis.mkdir(Path, true))
			throw MyException("Erstellung des Images/Title Verzeichnisses fehlgeschlagen, keine Rechte f�r diesen Ordner?");

	sprintf(Path, "%s%simages/weapons", Pfad, Zeichen);
	Verzeichnis.setPath(Path);
	if(!Verzeichnis.exists())
		if(!Verzeichnis.mkdir(Path, true))
			throw MyException("Erstellung des Images/Weapon Verzeichnisses fehlgeschlagen, keine Rechte f�r diesen Ordner?");

	sprintf(Path, "%s%smaps", Pfad, Zeichen);
	Verzeichnis.setPath(Path);
	if(!Verzeichnis.exists())
		if(!Verzeichnis.mkdir(Path, true))
			throw MyException("Erstellung des Maps Verzeichnisses fehlgeschlagen, keine Rechte f�r diesen Ordner?");

	if(WriteAwards)

	{
		sprintf(Path, "%s%sawards", Pfad, Zeichen);
		Verzeichnis.setPath(Path);
		if(!Verzeichnis.exists())

			if(!Verzeichnis.mkdir(Path, true))
				throw MyException("Erstellung des Awards Verzeichnisses fehlgeschlagen, keine Rechte f�r diesen Ordner?");

	}

	int y;
	// < und > Zeichen im Namen ersetzen!
	for(y = 0; y < AnzahlSpieler; y++)
	{
		typedef string::size_type ST;
		
		ST i1 = SpielerNamen[y].find('<');
		
		while(i1 != string::npos)
		{
			SpielerNamen[y].replace(i1, 1, "&lt;");			
			i1 = SpielerNamen[y].find('<');
		}
		
		ST i2 = SpielerNamen[y].find('>');
		
		while(i2 != string::npos)
		{
			SpielerNamen[y].replace(i2, 1, "&gt;");			
			i2 = SpielerNamen[y].find('>');
		}
	}


	int z;

	vector<int> AktuelleWaffe(AnzahlSpieler);
	for(z = 0; z < WEAPONANZAHL; z++)
	{
		//Die Aktionen werden einzeln in die AktuelleWaffe geschrieben
		for(int y = 0; y < AnzahlSpieler; y++)
		{
			AktuelleWaffe[y] = Kills[y][z];
		}

		//Most holt liefert den h�chten Wert des Vektors zur�ck und speichert den Namen in Name
		char temp[300];


		NumWeaponKill[z] = Most(AktuelleWaffe, temp, AnzahlSpieler);
		if(NumWeaponKill[z] <= 0)

			PlayerWeaponKill[z] = "";
		else
			PlayerWeaponKill[z] = temp;
		

	}


	//Berechnung der FloatAktionen!
	int PlayedRoundsID = WelcheAktion("NewRound");
	int KillspRnd = WelcheFloatAktion("KillsperRnd");
	int DeathsspRnd = WelcheFloatAktion("DeathsperRnd");
	int KillspMin = WelcheFloatAktion("KillsperMin");

	int DeathspMin = WelcheFloatAktion("DeathsperMin");
	int PlayedTimeID = WelcheFloatAktion("PlayedTime");
	int DamageHealthsperKill = WelcheFloatAktion("DamageHealthsperKill");
	int DamageArmorperKill = WelcheFloatAktion("DamageArmorperKill");
	int DamageHealthsperRnd = WelcheFloatAktion("DamageHealthsperRnd");
	int DamageArmorperRnd = WelcheFloatAktion("DamageArmorperRnd");

	int IntDamageHealths = WelcheAktion("DamageHealths");
	int IntDamageArmor = WelcheAktion("DamageArmor");

	for(y = 0; y < AnzahlSpieler; y++)
	{
		//Schaden pro Runde und Kills pro Runde berechnen
		if(Actions[y][PlayedRoundsID] != 0)
		{
			FloatActions[y][DamageHealthsperRnd] = (float) Actions[y][IntDamageHealths] / Actions[y][PlayedRoundsID];
			FloatActions[y][DamageArmorperRnd] = (float) Actions[y][IntDamageArmor] / Actions[y][PlayedRoundsID];
			FloatActions[y][0] = (float) Actions[y][KillspRnd] / Actions[y][PlayedRoundsID];
			FloatActions[y][1] = (float) Actions[y][DeathsspRnd] / Actions[y][PlayedRoundsID];
		}
		else
		{
			FloatActions[y][KillspRnd] = 0;
			FloatActions[y][DeathsspRnd] = 0;
		}
		FloatActions[y][PlayedTimeID] = (PlayedTime[y] / 60.0) ;
		if(PlayedTime[y] != 0)
		{

			FloatActions[y][KillspMin] = Actions[y][0] / FloatActions[y][PlayedTimeID];

			FloatActions[y][DeathspMin] = Actions[y][1] / FloatActions[y][PlayedTimeID];
		}
		else
		{
			FloatActions[y][KillspMin] = 0;
			FloatActions[y][DeathspMin] = 0;
		}

		//Schaden pro Kill berechnen
		if(Actions[y][KillspRnd] != 0)
		{
			FloatActions[y][DamageHealthsperKill] = (float) Actions[y][IntDamageHealths] / Actions[y][0];
			FloatActions[y][DamageArmorperKill] = (float) Actions[y][IntDamageArmor] / Actions[y][0];
		}
		else
		{
			FloatActions[y][DamageHealthsperKill] = 0;
			FloatActions[y][DamageArmorperKill] = 0;
		}

	}

	//Berechnen wer den Award hat und in FloatAwards[z] schreiben(f�r Floatawards)
	vector<float> AktuelleFloatAction(AnzahlSpieler);
	for(z = 0; z < FLOATAKTIONENANZAHL; z++)
	{

		//Die Aktionen werden einzeln in die AktuelleAction geschrieben
		for(int y = 0; y < AnzahlSpieler; y++)
		{
			AktuelleFloatAction[y] = FloatActions[y][z];
		}
		//Most holt liefert den h�chten Wert des Vektors zur�ck und speichert den Namen in Name
		char temp[300];

		FloatNumAward[z] = Most(AktuelleFloatAction, temp, AnzahlSpieler);
		if(FloatNumAward[z] > 0)
		{
			FloatPlayerAward[z] = temp;

			//Positive und negative FloatAwards erh�hen
			if(FloatAktionen[z].Status % 2 != 0)
				NewAction(temp, "PosAwards", 1);
			else
				NewAction(temp, "NegAwards", 1);
		}
  }
	//Berechnen wer den Award hat und in Awards[z] schreiben
	vector<int> AktuelleAction(AnzahlSpieler);
	for(z = 0; z < AKTIONENANZAHL; z++)
	{

		//Die Aktionen werden einzeln in die AktuelleAction geschrieben
		for(int y = 0; y < AnzahlSpieler; y++)
		{
			AktuelleAction[y] = Actions[y][z];
		}
		//Most holt liefert den h�chten Wert des Vektors zur�ck und speichert den Namen in Name
		char temp[300] = "";

		NumAward[z] = Most(AktuelleAction, temp, AnzahlSpieler);
		if(NumAward[z] > 0)
		{
			PlayerAward[z] = temp;


			//Positive und negative Awards erh�hen
			if(Aktionen[z].Status % 2 != 0)
				NewAction(temp, "PosAwards", 1);
			else
				NewAction(temp, "NegAwards", 1);
				
			if(strcmp(Aktionen[z].text, "PosAwards") == 0 || strcmp(Aktionen[z].text, "NegAwards") == 0)
				NumAward[z]++;
		}
		
		//Positive und negative Awards z�hlen
		/*if(FloatAktionen[z].Status % 2 != 0)
		{
			Positiv++;
		}
		else
		{
			Negativ++;
		}*/
	}



	//CountofAction von Positiven und negativen Awards setzen!

	//Erstmal die ID der beiden holen
	/*int PositivID = WelcheAktion("PosAwards");
	int NegativID = WelcheAktion("NegAwards");
	

	CountofAction[PositivID] = Positiv;
	CountofAction[NegativID] = Negativ;*/

	
	if(ShowMaps)
	{
		int deleted = 0, *DeletedIndex;
		
//		QMessageBox::critical(0, "hier", "Vor allem");
		DeletedIndex = new int[MapCount];

		for(int zaehler = 0; zaehler < MapCount; zaehler++)
		{
			if(MapPlayedTime[zaehler] <= 0)

			{

				//MapNames.erase(MapNames.begin() + zaehler);
				//MapActions.erase(MapActions.begin() + zaehler);
				//MapAwardsInsg.erase(MapAwardsInsg.begin() + zaehler);
						
				DeletedIndex[deleted] = zaehler;
				deleted++;
			}
		}
		int a;
		for(a = 0; a < deleted; a++)
		{
			//MapPlayedTime.erase(MapPlayedTime.begin() + DeletedIndex[a]);
			MapPlayedTime[DeletedIndex[a]] = 0;
		}
		for(a = 0; a < MapPlayedTime.size(); a++)
			if(MapPlayedTime[a] == 0)
			{
				MapRounds.erase(MapRounds.begin() + a);
				MapPlayedTime.erase(MapPlayedTime.begin() + a);
				MapNames.erase(MapNames.begin() + a);
				MapActions.erase(MapActions.begin() + a);
				MapAwardsInsg.erase(MapAwardsInsg.begin() + a);
				MapCTWins.erase(MapCTWins.begin() + a);
				MapTSWins.erase(MapTSWins.begin() + a);
			}
		
		
		MapCount -= deleted;
		delete[] DeletedIndex;

		if(MapCount > 0)
		{
			//Initialisieren
			MapAwardsNum.resize(MapCount);
			MapAwardsPlayer.resize(MapCount);
			for(z = 0; z < MapCount; z++)
			{
				MapAwardsNum[z].resize(MAPAKTIONENANZAHL);			
				MapAwardsPlayer[z].resize(MAPAKTIONENANZAHL, "");			
			}
			
			//Berechnen
			vector<int> AktuelleMapAction(AnzahlSpieler);

			for(int i = 0; i < MapCount; i++)
			{
				for(z = 0; z < MAPAKTIONENANZAHL; z++)
				{
					for(int y = 0; y < AnzahlSpieler; y++)
					{
					//Die Aktionen werden einzeln in die AktuelleMapAction geschrieben
						AktuelleMapAction[y] = MapActions[i][y][z];
					}
					//Most holt liefert den h�chten Wert des Vektors zur�ck und speichert den Namen in Name
					char temp[300];
    		
					if(MapAktionen[z].ShowTotal)
					{
						//bei NewRound muss nicht mehr gerechnet werden, steht in MapRounds
						if(strcmp(MapAktionen[z].text, "NewRound") == 0)
							MapAwardsInsg[i][z] = MapRounds[i];
						else if(strcmp(MapAktionen[z].text, "CTWin") == 0)
							MapAwardsInsg[i][z] = MapCTWins[i];						
						else if(strcmp(MapAktionen[z].text, "TSWin") == 0)
							MapAwardsInsg[i][z] = MapTSWins[i];						
						else
							MapAwardsInsg[i][z] = Addiere(AktuelleMapAction, AnzahlSpieler);
					}
					MapAwardsNum[i][z] = Most(AktuelleMapAction, temp, AnzahlSpieler);
					
					if(MapAwardsNum[i][z] > 0)
						MapAwardsPlayer[i][z] = temp;
					else
						MapAwardsPlayer[i][z] = "---";				
				}
			}







		}
	}
	//Insgesamte Anzahl der Runden berechnen und in CountofAction[NewRoundID] schreiben
	int NewRoundID = WelcheAktion("NewRound");

	CountofAction[NewRoundID] = InsgRunden;
	//Insgesamte Ausf�hrung von PlayedTime in FloatCountofAction schreiben
	FloatCountofAction[PlayedTimeID] = InsgSpielZeit / 60.0;
	

	try
	{
		if(strcmp(Zeichen, "/") == 0)
		{
			strcpy(Path, Pfad);
			Path[strlen(Path)-1] = '\0';
		}

		else
			strcpy(Path, Pfad);
		CopyPics(Path);
		WriteCSSFile(Path);
		WriteIndexFile(Path);
		WriteTitelFile(Path);
//		QMessageBox::information(0, "HeldenStats", "Vor SpielerFile");
		WriteSpielerFile(Path);
//		QMessageBox::information(0, "HeldenStats", "Vor SpielerFiles");
		WriteSpielerFiles(Path);
//		QMessageBox::information(0, "HeldenStats", "Vor AwardsFile");
		WriteAwardsFile(Path);
		if(WriteAwards)
			WriteAwardFiles(Path);
//		QMessageBox::information(0, "HeldenStats", "Vor WeaponFiles");
		WriteWeaponFiles(Path);
//		QMessageBox::information(0, "HeldenStats", "Vor WeaponFile");
		WriteWeaponFile(Path);
//		QMessageBox::information(0, "HeldenStats", "Vor MapFile");
		if(ShowMaps)
		{
			WriteMapIndexFile(Path);
			WriteMapLinksFile(Path);
			WriteMapOverViewFile(Path);
			WriteMapFiles(Path);
		}
		else
			WriteNoMaps(Path);
//		QMessageBox::information(0, "HeldenStats", "Nach MapFile");
	}
	catch(MyException)
	{
		throw;
	}

}


int Spieler::MostWeaponKills(const char *Weapon, char *Player)
{
	int MostKills, WelcheW;


	WelcheW = WelcheWaffe(Weapon);
	MostKills = Kills[0][WelcheW];
	strcpy(Player, SpielerNamen[0].c_str());

	for(int z = 1; z < AnzahlSpieler; z++)
	{
		if(Kills[z][WelcheW] > MostKills)
		{
			MostKills = Kills[z][WelcheW];
			strcpy(Player, SpielerNamen[z].c_str());
		}
		
	}
	return MostKills;
}

int Spieler::MostWeaponKills(const char *Weapon)
{
	char temp[100];

	return MostWeaponKills(Weapon, temp);
}
void Spieler::Sortiere(vector<int> &Output, vector<int> &ZuSortieren, int Anzahl)
{

	int Element, z, temp, temp2;

	for(z = 0; z < Anzahl; z++)
		//Output->at(z) = 0;
		Output[z]=0;

	for(z = 0; z < Anzahl; z++)
	{
		Element = 0;
   		for(int y = 0; y < Anzahl; y++)
		{
			if(y != z)
			{
				temp = ZuSortieren[z];
				temp2 = ZuSortieren[y];
     			if(ZuSortieren[y] > ZuSortieren[z])
				{
					Element++;
				}
			}
			if(y == Anzahl-1)
			{
				if(!Output[Element])
					Output[Element] = z;
				else
				{

					while(Output[Element] && Element < Anzahl-1)
						Element++;

					Output[Element] = z;
				}
			}
		}
		
	}
}

void Spieler::Sortiere(vector<int> &Output, vector<float> *ZuSortieren, int Anzahl)
{

	int Element, z;

	for(z = 0; z < Anzahl; z++)
		//Output->at(z) = 0;
		Output[z]=0;

	for(z = 0; z < Anzahl; z++)
	{
		Element = 0;
   	for(int y = 0; y < Anzahl; y++)
		{
			if(y != z)
			{
     		if(ZuSortieren[0][y] > ZuSortieren[0][z] )
				{
					Element++;

				}
			}
			if(y == Anzahl-1)
			{
				if(!Output[Element])

					Output[Element] = z;
				else
				{
					while(Output[Element] && Element < Anzahl-1)
						Element++;




					Output[Element] = z;
				}
			}
		}
		
	}
}


int Spieler::Most(vector<int> &Highest, char *Player, int Element)
{
	int High, temp;

	High = Highest[0];
	strcpy(Player, SpielerNamen[0].c_str());
	for(int z = 1; z < Element; z++)
	{
		temp = Highest[z];
		if(Highest[z] > High)
		{
			High = Highest[z];
			strcpy(Player, SpielerNamen[z].c_str());
		}

	}
	return High;
}

float Spieler::Most(vector<float> &Highest, char *Player, int Element)
{
	float High, temp;


	High = Highest[0];
	strcpy(Player, SpielerNamen[0].c_str());
	for(int z = 1; z < Element; z++)
	{
		temp = Highest[z];
		if(Highest[z] > High)
		{
			High = Highest[z];
			strcpy(Player, SpielerNamen[z].c_str());
		}
	}
	return High;
}

inline void Spieler::NewAction(const char *Player, const char *Action, int n)
{

	int WelcheA, WelcherS, WelcheMA, MapTeamSkill;

	WelcherS = WelcherSpieler(Player);
	WelcheA = WelcheAktion(Action);
	MapTeamSkill = WelcheMapAktion("TeamSkill");
		
	if(WelcheA == -1)
	{
		char Nachricht[200];
		sprintf(Nachricht, "Fehler, Aktion : %s nicht vorhanden!", Action);
		cout << Nachricht;
		throw MyException(Nachricht);
	}

	if(WelcherS == -1)
	{
		NeuerSpieler(Player);
		WelcherS = WelcherSpieler(Player);
	}
	
	//Nur wenn die Maps angezeigt werden sollen
	if(ShowMaps)

	{
		WelcheMA = WelcheMapAktion(Action);
		if(WelcheMA != -1)
		{
			MapActions[CurrentMap][WelcherS][WelcheMA] += n;
			MapActions[CurrentMap][WelcherS][MapTeamSkill] += MapAktionen[WelcheMA].TeamSkill * n;
		}
	}
	TeamSkill[WelcherS] += Aktionen[WelcheA].TeamSkill * n;
	Actions[WelcherS][WelcheA]+=n;
	CountofAction[WelcheA] +=n;

	//Bei Selbstmord, deaths erh�hen und Skill abziehen!
	if(strcmp(Action, "Suicide") == 0)
	{
		NewAction(Player, "Deaths", n);
		Skill[WelcherS] -= 1;
	}
}

int Spieler::Addiere(vector<int> ZuAddieren, int Anzahl)
{
	int Ergebnis = 0;

	for(int z = 0; z < Anzahl; z++)
		Ergebnis+=ZuAddieren[z];

	return Ergebnis;
}

void Spieler::WriteIndexFile(const char *Pfad)
{
	char Path[200];

	QFile HTMLDatei;
	//IndexDatei schreiben, ist in der Variable : IndexDatei gespeichert
	sprintf(Path, "%sindex.html", Pfad);
	HTMLDatei.setName(Path);
	if(!HTMLDatei.open(IO_WriteOnly))

	{

		cout << "Fehler beim �ffnen der Index Datei!";
		throw MyException("Fehler beim �ffnen der IndexDatei!");
	}
	HTMLDatei.writeBlock(IndexDatei, sizeof(IndexDatei));
	HTMLDatei.close();

}

void Spieler::WriteTitelFile(const char *Pfad)
{
	char Path[200];
	QFile HTMLDatei;
	//TitelDatei schreiben, ist in der Variable : TitelDatei gespeichert
	sprintf(Path, "%stitel.html", Pfad);
	HTMLDatei.setName(Path);
	if(!HTMLDatei.open(IO_WriteOnly))
	{
		cout << "Fehler beim �ffnen der Index Datei!";
		throw MyException("Fehler beim �ffnen der TitelDatei!");
	}
	HTMLDatei.writeBlock(TitelDatei.c_str(), TitelDatei.size());
	HTMLDatei.close();

}

void Spieler::WriteMapIndexFile(const char *Pfad)
{
	char Path[200];
	QFile HTMLDatei;
	//MapIndexDatei schreiben, ist in der Variable : MapIndex gespeichert
	sprintf(Path, "%smapindex.html", Pfad);
	HTMLDatei.setName(Path);
	if(!HTMLDatei.open(IO_WriteOnly))
	{
		cout << "Fehler beim �ffnen der MapIndex Datei!";
		throw MyException("Fehler beim �ffnen der MapDatei!");
	}
	HTMLDatei.writeBlock(MapIndex, sizeof(MapIndex));
	HTMLDatei.close();

}


void Spieler::WriteSpielerFile(const char *Pfad)
{
	//Die verschieden Sortierungen erstellen
	for(int i = 0; i < SortCount; i++)
	{
		char Path[200];
		QFile HTMLDatei;
		string WholeFile = "";
		//SPielerDatei schreiben
		sprintf(Path, "%s%s.html", Pfad, SortNames[i].c_str());
		HTMLDatei.setName(Path);
		if(!HTMLDatei.open(IO_WriteOnly))
		{
			cout << "Fehler beim �ffnen der SpielerDatei!";
			MyException("Fehler beim �ffnen der SpielerDatei!");
		}
		WholeFile = "<html><head><title>Counter-Strike Stats</title><link rel=stylesheet type=\"text/css\" href=\"style.css\"></head>";
		WholeFile = WholeFile + "<body><h1 align=center>Spielerstatistiken</h1><br><table" + TableSettings + "align=center>";


/*		WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + "><th>" + TableCaptionColor + "Rang</th>"
			"</th><th>" + TableCaptionColor + "Name</font></th>"
			"</th><th>" + TableCaptionColor + "Kills</a></font></th>"
			"</th><th>" + TableCaptionColor + "Deaths</font></th>"
			"</th><th>" + TableCaptionColor + "K:D</font></th>"
			"</th><th>" + TableCaptionColor + "Bilanz</font></th>"
			"</th><th>" + TableCaptionColor + "Skill</font></th>"
			"</th><th>" + TableCaptionColor + "TeamSkill</font></th>"
			"</th><th>" + TableCaptionColor + "</i>Waffenauszeichnungen</font></th></tr>";*/
		WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + "><th>" + TableCaptionColor + "Rang</th>"
			"</th><th>" + TableCaptionColor + "Name</font></th>"
			"</th><th>" + "<a href=\"" + SortNames[1] + ".html\">" + "Kills</a></th>"
			"</th><th>" + "<a href=\"" + SortNames[2] + ".html\">" + "Deaths</a></th>"
			"</th><th>" + "<a href=\"" + SortNames[5] + ".html\">" + "K:D</a></th>"
			"</th><th>" + "<a href=\"" + SortNames[3] + ".html\">" + "Bilanz</a></th>"
			"</th><th>" + "<a href=\"" + SortNames[0] + ".html\">" + "Skill</a></th>"
			"</th><th>" + "<a href=\"" + SortNames[4] + ".html\">" + "TeamSkill</a></th>"
			"</th><th>" + TableCaptionColor + "</i>Waffenauszeichnungen</font></th></tr>";

		for(int z = 0; z < AnzahlSpieler; z++)
		{
			int Element = Sortierung[i][z];
			if(Rang[Element] != -1 )
			{
				char temp[500];
				//int Element = z;

				//Farbe wird �berall benutzt vor den Eintr�gen
				string Farbe="";
				Farbe = Farbe + TableFontColor;

				char AktFarbe[100];
				sprintf(AktFarbe, "%s", (z+1) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());

      	
				WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + ">";

				sprintf(temp, "%s%i", TableFontColor.c_str(), Rang[Element]);
				WholeFile = WholeFile + "<th>" + temp + "</th>";
				//Schreibt den SpielerNamen, als Verweis in die Tabelle
				sprintf(temp, "%i", Rang[Element]);
				WholeFile = WholeFile + "<th>" + "<a href=\"spieler/" + temp
					+ ".html\">" + SpielerNamen[Element] + "</a>" + "</th>";

				sprintf(temp, "%s%i", Farbe.c_str(), Actions[Element][0]);
				WholeFile = WholeFile + "<th>" + temp + "</th>";

				sprintf(temp, "%s%i", Farbe.c_str(), Actions[Element][1]);
				WholeFile = WholeFile + "<th>" + temp + "</th>";

				sprintf(temp, "%s%f", Farbe.c_str(), KDRate[Element]);
				WholeFile = WholeFile + "<th>" + temp + "</th>";

				sprintf(temp, "%s%i", Farbe.c_str(), Actions[Element][0] - Actions[Element][1]);
				WholeFile = WholeFile + "<th>" + temp + "</th>";

				sprintf(temp, "%s%i", Farbe.c_str(), Skill[Element]);
				WholeFile = WholeFile + "<th>" + temp + "</th>";

				sprintf(temp, "%s%i", Farbe.c_str(), TeamSkill[Element]);
				WholeFile = WholeFile + "<th>" + temp + "</th>";


				WholeFile = WholeFile + "<th align=left>" ;
				bool Found=false;
				for(int y = 0; y < WEAPONANZAHL; y++)
					if(strcmp(PlayerWeaponKill[y].c_str(), SpielerNamen[Element].c_str()) == 0)
					{
						sprintf(temp, "<a href=\"weapons/%s.html\"><img src=\"images/weapons/%s.gif\" alt=\"%s\" border=0></a>", Waffen[y].text, Waffen[y].text, Waffen[y].text);
						WholeFile += temp;
						Found=true;
					}
					
				if(!Found)
					WholeFile = WholeFile + TableFontColor + "-";
			

				WholeFile = WholeFile + "</th>";

				WholeFile += "</tr>";
			}
		}
		WholeFile = WholeFile + "</table>";
		char temp0[100];

		sprintf(temp0, "Insgesamt %i Logdatei(en) verarbeitet, Minimale Einstellungen : Skill=%i, Kills=%i, Deaths=%i", LogFiles, Requires[0], Requires[1], Requires[2]);//MinSkill, MinKills, MinDeaths);
		WholeFile = WholeFile + "<br><br><br><br><center>" + temp0 + "</center>";
		sprintf(temp0, "Insgesamt %i Spieler, davon %i in der Liste, die Anderen %i waren zu schlecht", RankedPlayers + UnRankedPlayers, RankedPlayers, UnRankedPlayers);
		WholeFile = WholeFile + "<center>" + temp0 + "</center>";
		WholeFile = WholeFile + "<center>� Benjamin Held, HeldenStats Ver.:1.04</center></body>";
		char a[100];

		sprintf(a , "%i", WholeFile.size());
		HTMLDatei.writeBlock(WholeFile.c_str(), WholeFile.size());
		HTMLDatei.close();
	}

}
void Spieler::WriteSpielerFiles(const char *Pfad)
{
	char Path[200];
	QFile HTMLDatei;
	string WholeFile = "";


	//Hier werden die einzelnen SpielerDateien geschrieben, f�r jeden Spieler EINE!
	for(int z = 0; z < AnzahlSpieler; z++)
	{
		int Element = Sortierung[0][z];
		if(Rang[Element] != -1)
		{
			//sprintf(Path, "%sspieler/%s.html", Pfad, SpielerNamen[Element].c_str());
			sprintf(Path, "%sspieler/%i.html", Pfad, Rang[Element]);
			HTMLDatei.setName(Path);
			if(!HTMLDatei.open(IO_WriteOnly))
			{
				char Nachricht[200];
				sprintf(Nachricht, "Fehler beim �ffnen der Datei : %s", Path);
				throw MyException(Nachricht);
			}
			WholeFile = "";
			WholeFile = WholeFile + "<html>" + "<head><title>Individuelle Statistiken</title>"
				"<link rel=stylesheet type=\"text/css\" href=\"../style.css\"></head>";
			char temp[100], TSkill[10];
			sprintf(temp, "%i", Skill[Element]);
			sprintf(TSkill, "%i", TeamSkill[Element]);
			WholeFile = WholeFile + "<body>" + "<h1 align=center>" + SpielerNamen[Element].c_str() + ", Skill : "
				"" + temp + ", TeamSkill : " + TSkill + "</h1>";
			sprintf(temp, "%i",	Rang[Element]);
			WholeFile = WholeFile + "<h1 align=center><u>Rang : " + temp + "</u></h1>" + "<table" + TableSettings + "align=center>";


			WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + ">"
				"<th>" + TableCaptionColor + "Waffe"
				"</th><th>" + TableCaptionColor + "Kills"
				"</th><th>" + TableCaptionColor + "% von allen Kills"
				//"</th><th><font color=" + FarbNamen[5] + ">%"
				"</th><th>" + TableCaptionColor + "Deaths</i>"
				"</th><th>" + TableCaptionColor + "Lebensenergie abgezogen</i>"
				"</th><th>" + TableCaptionColor + "R�stung abgezogen</i></th></tr>";
		
			//Waffen sortieren!
			int y;
			vector<int> WaffenSortierung(WEAPONANZAHL);
			vector<int> Weapons(WEAPONANZAHL);
			//Kills der Waffen von Spieler z in Waffen reinschreiben und dann sortieren
			for(y = 0; y < WEAPONANZAHL; y++)
				Weapons[y] = Kills[Element][y];
			Sortiere(WaffenSortierung, Weapons, WEAPONANZAHL);

			string TextFarbe = "";
			TextFarbe = TextFarbe + TableFontColor;

			for(y = 0; y < WEAPONANZAHL; y++)
			{
				int WElement = WaffenSortierung[y];
				char temp2[200];

				char AktFarbe[100];
				sprintf(AktFarbe, "%s", (y+1) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());



				sprintf(temp2, "<a href=\"../weapons/%s.html\"><img src=\"../images/weapons/%s.gif\" alt=\"%s\" border=0></a>", Waffen[WElement].text, Waffen[WElement].text, Waffen[WElement].text);
				WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + "><th>" + temp2 + "</th>";

				sprintf(temp2, "%i", Kills[Element][WElement]);			
				WholeFile = WholeFile + "<th>" + TextFarbe + temp2 + "</th>";
    	
				if(Actions[Element][0] != 0)
				{
					int KillspInsgKills = (100.0 * Kills[Element][WElement]) / Actions[Element][0];
      	
					sprintf(temp2, "<img src=\"../images/balken.gif\" width=%i height=10 alt=\"%i%%\">%s%i%%", BalkenBreite / 100 * KillspInsgKills, KillspInsgKills, TextFarbe.c_str(), KillspInsgKills);
				}
				else
					sprintf(temp, "%s0%%", TextFarbe.c_str());
				WholeFile = WholeFile + "<th width=250 align=left>" + temp2 + "</th>";

				/*sprintf(temp2, "%f", (100.0 * Kills[z][z]) / TotalKills[z]);
				WholeFile = WholeFile + "<th>" + temp2 + "</th>";*/

				sprintf(temp2, "%i", Deaths[Element][WElement]);			
				WholeFile = WholeFile + "<th>" + TextFarbe + temp2 + "</th>";
			
				sprintf(temp2, "%i", DamageHealths[Element][WElement]);			

				WholeFile = WholeFile + "<th>" + TextFarbe + temp2 + "</th>";
			
				sprintf(temp2, "%i", DamageArmor[Element][WElement]);				
				WholeFile = WholeFile + "<th>" + TextFarbe + temp2 + "</th>" + "</tr>";
			}
//		}
			WholeFile = WholeFile + "</table><br>" ;
			WholeFile = WholeFile + "<table" + TableSettings + "align=center>";
			WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + ">"
				"<th>" + TableCaptionColor + "Aktion"
				"<th>" + TableCaptionColor + "Anzahl";

			char temp2[200];


/*		sprintf(temp2, "%s%i", TextFarbe.c_str(), Actions[Element][0]);			
			WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[1] + ""
				"><th>" + TextFarbe + "Kills</th><th>" + temp2 + "</th>" + "</tr>\n";

			sprintf(temp2, "%s%i", TextFarbe.c_str(), Actions[Element][1]);			
			WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[0] + ""
				"><th>" + TextFarbe + "Deaths</th><th>" + temp2 + "</th>" + "</tr>\n";*/

			sprintf(temp2, "%s%f", TextFarbe.c_str(), KDRate[Element]);			
			WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[1] + ""
				"><th>" + TextFarbe + "KDRate</th><th>" + temp2 + "</th>" + "</tr>\n";

			int Aktion;


		
			for(Aktion = 0; Aktion < AKTIONENANZAHL; Aktion++)
			{
				char AktFarbe[100];
				sprintf(AktFarbe, "%s", (Aktion+1) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());
				sprintf(temp2, "%i", Actions[Element][Aktion]);	
			

				WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + "><th>" + ""
					"" + TextFarbe + Aktionen[Aktion].AnzeigeText + "</th>"
					"<th>" + TextFarbe + temp2 + "</th>" + "</tr>\n";



			}

			for(Aktion = 0; Aktion < FLOATAKTIONENANZAHL; Aktion++)
			{
				char AktFarbe[100];
				sprintf(AktFarbe, "%s", (Aktion) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());
				sprintf(temp2, "%f", FloatActions[Element][Aktion]);	

    	
				WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + "><th>" + ""
					"" + TextFarbe + FloatAktionen[Aktion].AnzeigeText + "</th>"
					"<th>" + TextFarbe + temp2 + "</th>" + "</tr>\n";
			}
			WholeFile = WholeFile + "</table>";

			//Player vs Player Statistiken
			if(MaxPvsPCount > 0)
			{
				WholeFile = WholeFile + "<h1 align=center>Spieler gegen	Spielerstatistiken</h1>";
				WholeFile = WholeFile + "<table" + TableSettings + "align=center>";
				WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + ">"
					"<th>" + TableCaptionColor + "Name</th></font>"
					"<th>" + TableCaptionColor + "Sie t�teten Ihn</font></th>"
					"<th>" + TableCaptionColor + "Er t�tete Sie</font></th>"
					"<th>" + TableCaptionColor + "KDRate</font></th></tr>";
				
				for(int i = 0; i < PvsPCount[Element]; i++)
				{
					int PvsP = i;
					
					char AktFarbe[100];
					sprintf(AktFarbe, "%s", (i) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());
				
					if(IsRanked(SpielerNamen[PvsPIndex[Element][PvsP]].c_str()))
						sprintf(temp2, "<a href=\"%i.html\">%s</a>", Rang[PvsPIndex[Element][PvsP]], SpielerNamen[PvsPIndex[Element][PvsP]].c_str());
					else
						sprintf(temp2, "%s%s", TableFontColor.c_str(), SpielerNamen[PvsPIndex[Element][PvsP]].c_str());
					WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + "><th>" + ""
					"" + TextFarbe + temp2 + "</th>";

				
					sprintf(temp2, "%i", PvsPKills[Element][PvsP]);
					WholeFile = WholeFile + "<th>" + TextFarbe + temp2 + "</th>";
				
					sprintf(temp2, "%i", PvsPDeaths[Element][PvsP]);
					WholeFile = WholeFile + "<th>" + TextFarbe + temp2 + "</th>";
								
					if(PvsPDeaths[Element][PvsP] != 0 && (float) PvsPKills[Element][PvsP] / PvsPDeaths[Element][PvsP] != 0)
						sprintf(temp2, "%f", (float) PvsPKills[Element][PvsP] / (float) PvsPDeaths[Element][PvsP]);
					else
						sprintf(temp2, "%s-", TableFontColor.c_str());				
					
					WholeFile = WholeFile + "<th>" + TextFarbe + temp2 + "</th></tr>";
					
				}
				WholeFile = WholeFile + "</table>";
			}
			WholeFile = WholeFile + "</body>" + "</html>";
			HTMLDatei.writeBlock(WholeFile.c_str(), WholeFile.size());
			HTMLDatei.close();
		}
	}	

}
void Spieler::WriteWeaponFiles(const char *Pfad)
{
	char Path[200];
	QFile HTMLDatei;
	string WholeFile = "";



	//Die einzelnen WaffenDateien schreiben
	for(int z = 0; z < WEAPONANZAHL; z++)
	{
		sprintf(Path, "%sweapons/%s.html", Pfad, Waffen[z].text);
		HTMLDatei.setName(Path);
		if(!HTMLDatei.open(IO_WriteOnly))
		{
			char Nachricht[200];
			sprintf(Nachricht, "Fehler beim �ffnen der Datei : %s", Path);
			throw MyException(Nachricht);
		}
		WholeFile = "";
		WholeFile = WholeFile + "<html>" + "<head><link rel=stylesheet type=\"text/css\" href=\"../style.css\"></head>" + "<body>";

		char Heading[100];

		sprintf(Heading, "<h1 align=center><img src=\"../images/weapons/%s.gif\">%s<img src=\"../images/weapons/%s.gif\"></h1>", Waffen[z].text, Waffen[z].text, Waffen[z].text);
		WholeFile = WholeFile + Heading;

		WholeFile = WholeFile + "<table" + TableSettings + "align=center>";
		WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + ">"
			"<th>" + TableCaptionColor + "Name"
			"</th><th>" + TableCaptionColor + "Kills</th></tr>";
		
		//Hier wird sortiert
		vector<int> WaffenKills(AnzahlSpieler);
		vector<int> ReihenFolge(AnzahlSpieler);
		int y;
		for(y = 0; y < AnzahlSpieler; y++)
		{
			WaffenKills[y] = Kills[y][z];
		}
		Sortiere(ReihenFolge, WaffenKills, AnzahlSpieler);
		//Sortierung steht jetzt in ReihenFolge
		for(y = 0; y < AnzahlSpieler; y++)
		{
			int Element = ReihenFolge[y];
			char temp[100] ;

			if(WaffenKills[Element] > 0)
			{

				string TextFarbe = "";
				TextFarbe = TextFarbe + TableFontColor;

				sprintf(temp, "%s%i", TextFarbe.c_str(), WaffenKills[Element]);

				char AktFarbe[100];
				sprintf(AktFarbe, "%s", (y+1) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());

				if(IsRanked(SpielerNamen[Element].c_str()))
				{
					char temp2[10];
					sprintf(temp2, "%i", Rang[Element]);
					WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + "><th>" 
						"" + TextFarbe +  "<a href=\"../spieler/" + temp2 + ".html\">" + SpielerNamen[Element].c_str() + "</a>"
						"</th>";
				}
				else
				{
					WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + "><th>" + TextFarbe + ""
						"" + SpielerNamen[Element].c_str() + "</th>";
				}
				WholeFile = WholeFile + "<th>" + temp + "</th>" + "</tr>";

			}
		}
		WholeFile = WholeFile + "</table>" + "</body>" + "</html>";
		HTMLDatei.writeBlock(WholeFile.c_str(), WholeFile.size());
		HTMLDatei.close();
	}
}

void Spieler::WriteAwardsFile(const char *Pfad)

{
	char Path[200];
	QFile HTMLDatei;
	string WholeFile = "";

	//AwardsDatei schreiben
	sprintf(Path, "%sawards.html", Pfad);
	HTMLDatei.setName(Path);
	if(!HTMLDatei.open(IO_WriteOnly))
	{
		throw MyException("Fehler beim �ffnen der AwardsDatei!");
	}
	WholeFile = "";
	WholeFile = WholeFile + "<html>" + "<head><link rel=stylesheet type=\"text/css\" href=\"style.css\"></head>" + "<body>"; 
	WholeFile = WholeFile + "<h1 align=center>Auszeichnungen</h1><br>";
	//Ab hier werden die einzelen Aktionen in eine Tabelle geschrieben
	int z;
	char temp[100], temp2[100], Name[100], InsgString[100];
	int Zahl, FarbModulo;

/*	char *Captions[] = {"Allgemein", "Counter-Terroristen", "Terroristen"};
	char *StatusString[] = {"Positiv", "Negativ"};*/
	string Captions[] = {"Allgemein", "Counter-Terroristen", "Terroristen"};
	string StatusString[] = {"Positiv", "Negativ"};


	for(int Tabelle = 0; Tabelle < 3; Tabelle++)
	{
		//WholeFile = WholeFile + "<table border=0 cellspacing=0 align=center bgcolor=" + FarbNamen[4] + ">";
		WholeFile = WholeFile + "<table" + TableSettings + "align=center width=90%>";
		WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + ">"
			"<th colspan=4 align=center>" + TableCaptionColor + Captions[Tabelle] + "</font></th></tr>";

		FarbModulo = 0;

		for(int Status = 0; Status < 2; Status++)
		{
			//siehe Zeile vor der Deklaration von Aktionen
			Zahl = pow(2, Tabelle + 2) + Status + 1;
			WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + ">"
				"<th colspan=4 align=center>" + TableCaptionColor + StatusString[Status] + "</font></th></tr>";

			WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + "><th>" + TableCaptionColor + "Aktion</font></th>"
				"<th>" + TableCaptionColor + "Insgesamt</font></th>"
				"<th>" + TableCaptionColor + "Am Meisten</font></th>"
				"<th>" + TableCaptionColor + "Spieler</font></th></tr>";

			for(z = 0; z < AKTIONENANZAHL; z++)
			{
				if(Aktionen[z].Status == Zahl)
				{
					sprintf(temp, "%i", NumAward[z]);
					strcpy(Name, PlayerAward[z].c_str());
					if(Aktionen[z].ShowTotal)
					{
						sprintf(InsgString, "%i", CountofAction[z]);
					}
					else
						sprintf(InsgString, "---");
					//Wenn noch keiner diese Aktion ausgef�hrt hat
					if(NumAward[z] <= 0)
					{
						strcpy(temp2, "---"); 

					}
					else
					{
						if(IsRanked(Name))
						{
							int Index = WelcherSpieler(Name);
							sprintf(temp2, "<a href=\"spieler/%i.html\">%s</a>", Rang[Index], Name);
						}
						else
							sprintf(temp2, "%s", Name);
					}
					
					char AnzeigeText[300];

					//Wenn Awarddateien erstellt werden, muss ein Link angezeigt werden!					
					if(WriteAwards)
						sprintf(AnzeigeText, "<a href=\"awards/%i.html\">%s</a>", z+1, Aktionen[z].AnzeigeText);
					else
						sprintf(AnzeigeText, "%s", Aktionen[z].AnzeigeText);
					
					char AktFarbe[100];
					sprintf(AktFarbe, "%s", (FarbModulo+1) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());

					WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + "><th>" + TableFontColor + ""
						"" + AnzeigeText + "</th>";
						
					WholeFile = WholeFile + "<th>" + TableFontColor + ""
						"" + InsgString + "</th>";

					WholeFile = WholeFile + "<th>" + TableFontColor + ""
						"" + temp + "</th>";

					WholeFile = WholeFile + "<th>" + TableFontColor + ""
						"" + temp2 + "</th>" + "</tr>";

					FarbModulo++;
				}
			}

			for(z = 0; z < FLOATAKTIONENANZAHL; z++)
			{
				if(FloatAktionen[z].Status == Zahl)
				{
					sprintf(temp, "%f", FloatNumAward[z]);
					strcpy(Name, FloatPlayerAward[z].c_str());
					if(FloatAktionen[z].ShowTotal)
					{
						sprintf(InsgString, "%f", FloatCountofAction[z]);

					}
					else
						sprintf(InsgString, "---");
					//Wenn noch keiner diese Aktion ausgef�hrt hat
					if(FloatNumAward[z] <= 0)
					{
						strcpy(temp2, "---"); 
					}
					else
					{
						if(IsRanked(Name))
						{
							int Index = WelcherSpieler(Name);
							sprintf(temp2, "<a href=\"spieler/%i.html\">%s</a>", Rang[Index], Name);
						}
						else
							sprintf(temp2, "%s", Name);
					}


					char AnzeigeText[300];
					//Wenn Awarddateien erstellt werden, muss ein Link angezeigt werden!					
					if(WriteAwards)
						sprintf(AnzeigeText, "<a href=\"awards/%i.html\">%s</a>", AKTIONENANZAHL + z + 1, FloatAktionen[z].AnzeigeText);
					else
						sprintf(AnzeigeText, "%s", FloatAktionen[z].AnzeigeText);
						
						
					char AktFarbe[100];
					sprintf(AktFarbe, "%s", (FarbModulo+1) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());

					WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + "><th>" + TableFontColor + ""
						"" + AnzeigeText + "</th>";

					WholeFile = WholeFile + "<th>" + TableFontColor + "" 
						"" + InsgString + "</th>";

					WholeFile = WholeFile + "<th>" + TableFontColor + ""
						"" + temp + "</th>";

					WholeFile = WholeFile + "<th>" + TableFontColor + ""
						"" + temp2 + "</th>" + "</tr>";
	
					FarbModulo++;
				}

			}

			WholeFile = WholeFile + "<br>";
		}
		WholeFile = WholeFile + "</table>";
	}
	WholeFile = WholeFile + "</body>" + "</html>";
	HTMLDatei.writeBlock(WholeFile.c_str(), WholeFile.size());
	HTMLDatei.close();
}

void Spieler::WriteMapLinksFile(const char *Pfad)
{
	char Path[200];
	QFile HTMLDatei;
	string WholeFile = "";

	//MapVerweiseDatei schreiben
	sprintf(Path, "%smaplinks.html", Pfad);
	HTMLDatei.setName(Path);
	if(!HTMLDatei.open(IO_WriteOnly))
	{
		throw MyException("Fehler beim �ffnen der MapLinksDatei!");
	}
	WholeFile = WholeFile + "<html>" + "<head>"
		"<link rel=stylesheet type=\"text/css\" href=\"style.css\"></head><body>";

	WholeFile = WholeFile + "<center>Maps</center><br>";

	WholeFile = WholeFile + "<center><a href=\"mapoverview.html\" target=\"HauptFenster\">�bersicht</a></center><br>";
	for(int z = 0; z < MapCount; z++)
	{
		char Anzeige[300];

		sprintf(Anzeige, "<center><a href=\"maps/%i.html\" target=\"HauptFenster\">%s</a></center>", z+1, MapNames[z].c_str());

		WholeFile = WholeFile + Anzeige + "<br>";
	}
	WholeFile = WholeFile + "</body>" + "</html>";

	HTMLDatei.writeBlock(WholeFile.c_str(), WholeFile.size());
	HTMLDatei.close();
}

void Spieler::WriteNoMaps(const char *Pfad)
{
	char Path[200];
	QFile HTMLDatei;
	string WholeFile = "";

	//WaffenDatei schreiben
	sprintf(Path, "%smapindex.html", Pfad);
	HTMLDatei.setName(Path);
	if(!HTMLDatei.open(IO_WriteOnly))
	{
		throw MyException("Fehler beim �ffnen der weaponDatei!");
	}
	WholeFile = WholeFile + "<html>" + "<head><title>Keine Mapstatistiken</title>"
		"<link rel=stylesheet type=\"text/css\" href=\"style.css\"></head><body>";
		
	WholeFile = WholeFile + "<center><h1>Die Mapstatistiken wurden ausgestellt!</h1></center>";
	
	WholeFile = WholeFile + "</body>" + "</html>";
	HTMLDatei.writeBlock(WholeFile.c_str(), WholeFile.size());
	HTMLDatei.close();
}

void Spieler::WriteWeaponFile(const char *Pfad)
{
	char Path[200], temp[200];
	QFile HTMLDatei;
	string WholeFile = "";

	//WaffenDatei schreiben
	sprintf(Path, "%sweapon.html", Pfad);
	HTMLDatei.setName(Path);
	if(!HTMLDatei.open(IO_WriteOnly))
	{
		throw MyException("Fehler beim �ffnen der weaponDatei!");
	}
	WholeFile = WholeFile + "<html>" + "<head><title>Waffen</title>"
		"<link rel=stylesheet type=\"text/css\" href=\"style.css\"></head><body>";
	sprintf(temp, "<center>Es wurden insgesamt %i Kills gemacht!</center>", InsgKills);
	WholeFile = WholeFile + "<h1 align=center>Waffen</h1>" + temp + "<table" + TableSettings + "align=center>";

	WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + ">"
		"<th><font color=" + FarbNamen[5] + ">Waffe</font>"

		"</th><th>" + TableCaptionColor + "Insgesamt</font>"
		"</th><th>" + TableCaptionColor + "% von allen Kills</font>"
		"</th><th>" + TableCaptionColor + "Am Meisten</font>"
		"</th><th>" + TableCaptionColor + "% von der Waffe</font>"
		"</th><th>" + TableCaptionColor + "Spieler</font></th></tr>";
	//Ist f�r die Sortierung zust�ndig
/*	vector<int> WaffenKills(WEAPONANZAHL);
	WaffenKills.resize(WEAPONANZAHL);
	for(int z = 0; z < WEAPONANZAHL; z++)
	{
		WaffenKills[z] = MostWeaponKills(Waffen[z].text);
	}*/
	vector<int> WaffenSortierung;
	WaffenSortierung.resize(WEAPONANZAHL);
	Sortiere(WaffenSortierung, WaffenKills, WEAPONANZAHL);
	//Bis hier wird sortiert!


	for(int z = 0; z < WEAPONANZAHL; z++)
	{
		//In Element steht immer das "richtige" Element der Sortierung
		int Element = WaffenSortierung[z];		
		char temp[100], temp2[100], temp3[200], temp4[200], MostKillsName[100];

		//Z�hlt die insgesamten Kills der Waffe
		int MaxKills=0;
		for(int y = 0; y < AnzahlSpieler; y++)
			if(Kills[y][Element] > 0)
				MaxKills += Kills[y][Element];
		//�berpr�ft ob ein Kill mit der Waffe gemacht wurde!
		//Wenn nicht dann wird "Kein Kill" angezeigt
		char TextFarbe[100];

		sprintf(TextFarbe, "%s", TableFontColor.c_str());


		sprintf(temp2, "<a href=\"weapons/%s.html\"><img src=\"images/weapons/%s.gif\" border=0 align=left></a>", Waffen[Element].text, Waffen[Element].text);
		if(MostWeaponKills(Waffen[Element].text, MostKillsName) > 0)
		{
			sprintf(temp, "%s%i", TextFarbe, MaxKills);
			sprintf(temp3, "%s%i", TextFarbe, MostWeaponKills(Waffen[Element].text, MostKillsName));
			if(IsRanked(MostKillsName))
			{
				int WelcherS;
				WelcherS = WelcherSpieler(MostKillsName);
				sprintf(temp4, "<a href=\"spieler/%i.html\">%s</a>", Rang[WelcherS], MostKillsName);
			}
			else
				sprintf(temp4, "%s%s", TableFontColor.c_str(), MostKillsName);
		}
		else
		{
			sprintf(temp, "%s---", TextFarbe);
			sprintf(temp3, "%s---", TextFarbe);
			sprintf(temp4, "%s---", TextFarbe);
		}

		char AktFarbe[100];
		sprintf(AktFarbe, "%s", (z+1) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());
		//Welche Waffe
		WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + "><th>" + temp2 + "</th>";
		
		//Wieviele Kills insgesamt mit der Waffe
		WholeFile = WholeFile + "<th>" + temp + "</th>";
	
		//Balkengrafik
		if(InsgKills != 0 && MaxKills != 0)
		{
			int MaxperKills = (100 * MaxKills) / InsgKills;
			sprintf(temp, "<img src=\"images/balken.gif\" width=%i height=10 alt=\"%i%%\">%s%i%%", BalkenBreite / 100 * MaxperKills, MaxperKills, TableFontColor.c_str(), MaxperKills);
		}
		else
			sprintf(temp, "%s0%%", TextFarbe);
		WholeFile = WholeFile + "<th width=250 align=left>" + temp + "</th>";

		//Wieviele Kills am Meisten mit der Waffe
		WholeFile = WholeFile + "<th>" + temp3 + "</th>";
				
		//Balkengrafik
		if(MaxKills != 0 && MostWeaponKills(Waffen[Element].text) != 0)
		{
			int WeaponperKill = (100 * MostWeaponKills(Waffen[Element].text)) / MaxKills;
			sprintf(temp, "<img src=\"images/balken.gif\" width=%i height=10 alt=\"%i%%\">%s%i%%", BalkenBreite / 100 * WeaponperKill, WeaponperKill, TableFontColor.c_str(), WeaponperKill);

		}
		else
			sprintf(temp, "%s0%%", TextFarbe);
		WholeFile = WholeFile + "<th width=250 align=left>" + temp + "</th>";

		//Spielername
		WholeFile = WholeFile + "<th>" + temp4 + "</th>" + "</tr>";
	}

	WholeFile = WholeFile + "</table>" + "</body>" + "</html>";
	HTMLDatei.writeBlock(WholeFile.c_str(), WholeFile.size());
	HTMLDatei.close();

}

void Spieler::WriteMapOverViewFile(const char *Pfad)
{
	char Path[200];
	QFile HTMLDatei;
	string WholeFile = "";


	//Overview schreiben
	sprintf(Path, "%smapoverview.html", Pfad);
	HTMLDatei.setName(Path);
	if(!HTMLDatei.open(IO_WriteOnly))
	{
		cout << "Fehler beim �ffnen der CSSDatei!";
		throw MyException("Fehler beim �ffnen der CSSDatei!");
	}
	WholeFile = WholeFile + "<html>" + "<head><title>Waffen</title>"
		"<link rel=stylesheet type=\"text/css\" href=\"style.css\"></head><body>";

	WholeFile = WholeFile + "<h1 align=center>�bersicht</h1>";
	WholeFile = WholeFile + "<center><h3>Folgende Maps wurden gespielt :<br><br>";

	for(int z = 0; z < MapCount; z++)
	{
		char Spielzeit[20], TeamSpieler[200];
		int Index = WelcherSpieler(MapAwardsPlayer[z][0].c_str());

		sprintf(Spielzeit, "%i", MapPlayedTime[z]);
		
		//Pr�fen ob der Spieler geranked ist, wenn ja dann mit Link schreiben sonst ohne
		if(IsRanked(MapAwardsPlayer[z][0].c_str()))
			sprintf(TeamSpieler, "<a href=\"spieler/%i.html\" target=\"Haupt\">%s</a>", Rang[Index], MapAwardsPlayer[z][0].c_str());
		else
			sprintf(TeamSpieler, "%s", MapAwardsPlayer[z][0].c_str());			
		WholeFile = WholeFile + MapNames[z] + ", " + Spielzeit + " Minuten, Bester Teamspieler : " + TeamSpieler + "<br>";
	}
	WholeFile = WholeFile + "</h3>";

	WholeFile = WholeFile + "</body>" + "</html>";
	HTMLDatei.writeBlock(WholeFile.c_str(), WholeFile.size());
	HTMLDatei.close();
}

void Spieler::WriteCSSFile(const char *Pfad)
{
	char Path[200];
	QFile HTMLDatei;
	string WholeFile = "";

	//QMessageBox::information(0, "HeldenStats", FarbNamen[1]);
	//CSSDatei schreiben
	sprintf(Path, "%sstyle.css", Pfad);
	HTMLDatei.setName(Path);
	if(!HTMLDatei.open(IO_WriteOnly))
	{
		cout << "Fehler beim �ffnen der CSSDatei!";
		throw MyException("Fehler beim �ffnen der CSSDatei!");
	}
	
	WholeFile = WholeFile + "body  { background-color:" + FarbNamen[2] + ""
		";color:" + FarbNamen[7] +  ";" + "font-family:" + FarbNamen[12] + ";"
		"font-style:" + FarbNamen[22] + ";"
		"font-size:" + FarbNamen[17] + "mm}\n"
		"a:link, a:visited { text-decoration: none; color:" + FarbNamen[8] + ";"
		"font-weight:bold;"
		"font-family:" + FarbNamen[13] + ";"
		"font-style:" + FarbNamen[23] + ";"
		"font-size:" + FarbNamen[18] + "mm}\n"
		"a:active, a:hover { text-decoration: overline underline; color:" + FarbNamen[9] + "; font-weight:bold;\n"
		"font-family:" + FarbNamen[14] + ";"
		"font-style:" + FarbNamen[24] + ";"
		"font-size:" + FarbNamen[19] + "mm}\n"
		"tr, td, th {color:" + FarbNamen[6] + ";" + "font-family:" + FarbNamen[11] + ";" + "font-size:" + FarbNamen[16] + "mm;}\n";
	WholeFile = WholeFile + ".captionfont{color:" + FarbNamen[5] + ";" + "font-family:" + FarbNamen[10] + ";" + "font-size:" + FarbNamen[15] + "mm;}";



	HTMLDatei.writeBlock(WholeFile.c_str(), WholeFile.size());
	HTMLDatei.close();

}

void Spieler::WriteAwardFiles(const char *Pfad)
{
	char Path[200];
	QFile HTMLDatei;
	string WholeFile = "";

	for(int z = 0; z < AKTIONENANZAHL + FLOATAKTIONENANZAHL; z++)
	{
		//MapFiles schreiben
		sprintf(Path, "%sawards/%i.html", Pfad, z+1);
		HTMLDatei.setName(Path);
		if(!HTMLDatei.open(IO_WriteOnly))
		{
			char Nachricht[300];


			sprintf(Nachricht, "Fehler beim �ffnen von %s", Path);
			throw MyException(Nachricht);
		}
		WholeFile = "";
		WholeFile = WholeFile + "<html>" + "<head><link rel=stylesheet type=\"text/css\" href=\"../style.css\"></head>" + "<body>";
		
		
		//F�r die Sortierung
		vector<int> IntSort(AnzahlSpieler);
		vector<float> FloatSort(AnzahlSpieler);
		
		//Hier steht dann die Sortierung drin
		vector<int> ReihenFolge(AnzahlSpieler);
				
		if(z < AKTIONENANZAHL)
		{
			WholeFile = WholeFile + "<center><h2>" + Aktionen[z].AnzeigeText + "<h2>";
			//Sortieren
			for(int zaehler = 0; zaehler < AnzahlSpieler; zaehler++)
				IntSort[zaehler] = Actions[zaehler][z];
				
			Sortiere(ReihenFolge, IntSort, AnzahlSpieler);
		}
		else
		{
			WholeFile = WholeFile + "<center><h2>" + FloatAktionen[z - AKTIONENANZAHL].AnzeigeText + "<h2>";
			//Sortieren
			for(int zaehler = 0; zaehler < AnzahlSpieler; zaehler++)
				FloatSort[zaehler] = FloatActions[zaehler][z - AKTIONENANZAHL];
				
			Sortiere(ReihenFolge, &FloatSort, AnzahlSpieler);
		}
		
		WholeFile = WholeFile + "<table" + TableSettings + "align=center>";
		WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + ">"	
			"<th>" + TableCaptionColor + "Spieler</font></th>"
			"<th>" + TableCaptionColor + "Anzahl</font></th></tr>";

			
		char Anzahl[20], Spieler[200];
		char AktFarbe[100];
		bool UnderZero;
		
		for(int y = 0; y < AnzahlSpieler; y++)
		{
			int Index = ReihenFolge[y];
			
			sprintf(AktFarbe, "%s", (y+1) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());
			
			strcpy(Anzahl, "0");			
			UnderZero = true;
						
			if(z < AKTIONENANZAHL)
			{
				//IntAktion
				if(Actions[Index][z] > 0)
				{
					sprintf(Anzahl, "%i", Actions[Index][z]);				
					UnderZero = false;
				}
			}

			else
			{

				//FloatAktion
				if(FloatActions[Index][z - AKTIONENANZAHL] > 0)
				{
					sprintf(Anzahl, "%f", FloatActions[Index][z - AKTIONENANZAHL]);				
					UnderZero = false;
				}
			
			}

			if(!UnderZero)
			{
				WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + ">";
				if(IsRanked(SpielerNamen[Index].c_str()))
				{
					sprintf(Spieler, "<a href=\"../spieler/%i.html\">%s</a>", Rang[Index], SpielerNamen[Index].c_str());
				}
				else
					sprintf(Spieler, "%s", SpielerNamen[Index].c_str());
				WholeFile = WholeFile + "<th>" + Spieler + "</th>"; 				
				WholeFile = WholeFile + "<th>" + Anzahl + "</th></tr>";				
			}
		}
		   	
		WholeFile = WholeFile + "</body></html>";
		HTMLDatei.writeBlock(WholeFile.c_str(), WholeFile.size());
		HTMLDatei.close();
	}
}

void Spieler::WriteMapFiles(const char *Pfad)
{
	char Path[200];
	QFile HTMLDatei;
	string WholeFile = "";

	for(int z = 0; z < MapCount; z++)
	{
		//MapFiles schreiben
		sprintf(Path, "%smaps/%i.html", Pfad, z+1);
		HTMLDatei.setName(Path);
		if(!HTMLDatei.open(IO_WriteOnly))
		{
			char Nachricht[300];
			sprintf(Nachricht, "Fehler beim �ffnen von %s", Path);
			throw MyException(Nachricht);
		}
		WholeFile = "";
		WholeFile = WholeFile + "<html>" + "<head><link rel=stylesheet type=\"text/css\" href=\"../style.css\"></head>" + "<body>";

		char temp2[100];

		sprintf(temp2, "%i", MapPlayedTime[z]);

		WholeFile = WholeFile + "<h1 align=center>" + MapNames[z] + ", Spielzeit in Minuten: " + temp2 + "</h1>\n";			
		

		int Zaehler = 0;
		//Tabelle f�r die Counter
		WholeFile = WholeFile + "<table" + TableSettings + "align=center width=70%>";
		WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + "><th colspan=4 align=center>" + TableCaptionColor + "Antiterroristen</font></th></tr>";
		WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + ">"	
			"<th>" + TableCaptionColor + "Aktion</font></th>"
			"<th>" + TableCaptionColor + "Insgesamt</font></th>"
			"<th>" + TableCaptionColor + "Am Meisten</font></th>"
			"<th>" + TableCaptionColor + "Spieler</font></th></tr>";
		int y;
		for(y = 0; y < MAPAKTIONENANZAHL; y++)
		{
			if(MapAktionen[y].Status == 1)
			{
				char AktFarbe[100];
				char temp[10];
				sprintf(AktFarbe, "%s", (Zaehler+1) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());

				WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + ">";

				//Aktionentext
				WholeFile = WholeFile + "<th>" + MapAktionen[y].AnzeigeText + "</th>";

				//Insgesamte Anzahl der Aktion
				if(MapAktionen[y].ShowTotal)
					sprintf(temp, "%i", MapAwardsInsg[z][y]);
				else
					sprintf(temp, "---");
				WholeFile = WholeFile + "<th>" + temp + "</th>";			

				//Meiste Ausf�hrung der Aktion
				sprintf(temp, "%i", MapAwardsNum[z][y]);
				WholeFile = WholeFile + "<th>" + temp + "</th>";			

				//Spieler mit der meisten ausf�hrung

				char temp2[100];

				if(MapAwardsNum[z][y] <= 0)
				{
					strcpy(temp2, "---"); 

				}
				else
				{
					if(IsRanked(MapAwardsPlayer[z][y].c_str()))
					{
						int Index = WelcherSpieler(MapAwardsPlayer[z][y].c_str());
						sprintf(temp2, "<a href=\"../spieler/%i.html\" target=\"Haupt\">%s</a>", Rang[Index], MapAwardsPlayer[z][y].c_str());
					}
					else
						sprintf(temp2, "%s", MapAwardsPlayer[z][y].c_str());
				}
				WholeFile = WholeFile + "<th>" + temp2 + "</th></tr>";			
				Zaehler++;
			}
		
		}
		WholeFile = WholeFile + "</table>";
		
		//Tabelle f�r die Terrors
//		WholeFile = WholeFile + "<h3 align=center>Terroristen</h3>";		
		WholeFile = WholeFile + "<table" + TableSettings + "align=center width=70%>";
		WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + "><th colspan=4 align=center>" + TableCaptionColor + "Terroristen</font></th></tr>";
		WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + ">"	
			"<th>" + TableCaptionColor + "Aktion</font></th>"
			"<th>" + TableCaptionColor + "Insgesamt</font></th>"
			"<th>" + TableCaptionColor + "Am Meisten</font></th>"
			"<th>" + TableCaptionColor + "Spieler</font></th></tr>";
	
		for(y = 0; y < MAPAKTIONENANZAHL; y++)
		{
			if(MapAktionen[y].Status == 2)
			{
				char AktFarbe[100];
				char temp[10];
				sprintf(AktFarbe, "%s", (Zaehler+1) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());
				WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + ">";

				//Aktionentext
				WholeFile = WholeFile + "<th>" + MapAktionen[y].AnzeigeText + "</th>";


				//Insgesamte Anzahl der Aktion

				if(MapAktionen[y].ShowTotal)
					sprintf(temp, "%i", MapAwardsInsg[z][y]);
				else
					sprintf(temp, "---");
				WholeFile = WholeFile + "<th>" + temp + "</th>";			

				//Meiste Ausf�hrung der Aktion
				sprintf(temp, "%i", MapAwardsNum[z][y]);
				WholeFile = WholeFile + "<th>" + temp + "</th>";			

				//Spieler mit der meisten ausf�hrung
				char temp2[100];

				if(MapAwardsNum[z][y] <= 0)
				{
					strcpy(temp2, "---"); 

				}
				else

				{
					if(IsRanked(MapAwardsPlayer[z][y].c_str()))
					{
						int Index = WelcherSpieler(MapAwardsPlayer[z][y].c_str());
						sprintf(temp2, "<a href=\"../spieler/%i.html\">%s</a>", Rang[Index], MapAwardsPlayer[z][y].c_str());
					}
					else
						sprintf(temp2, "%s", MapAwardsPlayer[z][y].c_str());
				}
				WholeFile = WholeFile + "<th>" + temp2 + "</th></tr>";			
				Zaehler++;
			}
		}
		WholeFile = WholeFile + "</table>";
		
		//Tabelle f�r Allgemein
//		WholeFile = WholeFile + "<h3 align=center>Allgemein</h3>";		
		WholeFile = WholeFile + "<table" + TableSettings + "align=center width=70%>";
		WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + "><th colspan=4 align=center>" + TableCaptionColor + "Allgemein</font></th></tr>";
		WholeFile = WholeFile + "<tr bgcolor=" + FarbNamen[3] + ">"	
			"<th>" + TableCaptionColor + "Aktion</font></th>"
			"<th>" + TableCaptionColor + "Insgesamt</font></th>"
			"<th>" + TableCaptionColor + "Am Meisten</font></th>"
			"<th>" + TableCaptionColor + "Spieler</font></th></tr>";
	
		for(y = 0; y < MAPAKTIONENANZAHL; y++)
		{

			if(MapAktionen[y].Status == 0)
			{
				char AktFarbe[100];
				char temp[10];
				sprintf(AktFarbe, "%s", (Zaehler+1) % 2 ? FarbNamen[0].c_str() : FarbNamen[1].c_str());
				WholeFile = WholeFile + "<tr bgcolor=" + AktFarbe + ">";

				//Aktionentext
				WholeFile = WholeFile + "<th>" + MapAktionen[y].AnzeigeText + "</th>";

				//Insgesamte Anzahl der Aktion
				if(MapAktionen[y].ShowTotal)
					sprintf(temp, "%i", MapAwardsInsg[z][y]);
				else
					sprintf(temp, "---");
				WholeFile = WholeFile + "<th>" + temp + "</th>";			

				//Meiste Ausf�hrung der Aktion
				sprintf(temp, "%i", MapAwardsNum[z][y]);
				WholeFile = WholeFile + "<th>" + temp + "</th>";			

				//Spieler mit der meisten ausf�hrung
				char temp2[100];

				if(MapAwardsNum[z][y] <= 0)
				{
					strcpy(temp2, "---"); 

				}
				else
				{
					if(IsRanked(MapAwardsPlayer[z][y].c_str()))
					{
						int Index = WelcherSpieler(MapAwardsPlayer[z][y].c_str());
						sprintf(temp2, "<a href=\"../spieler/%i.html\">%s</a>", Rang[Index], MapAwardsPlayer[z][y].c_str());
					}
					else
						sprintf(temp2, "%s", MapAwardsPlayer[z][y].c_str());
				}
				WholeFile = WholeFile + "<th>" + temp2 + "</th></tr>";			

				Zaehler++;
			}
		}
		
		WholeFile = WholeFile + "</body></html>";
		HTMLDatei.writeBlock(WholeFile.c_str(), WholeFile.size());
		HTMLDatei.close();
	}
}

void Spieler::SortierenachSkill()
{
	if(AnzahlSpieler != 0)
	{
		int z;
		
		//Platz fuer die "wirkliche" Sortierung reservieren
		Sortierung.resize(SortCount);
		for(z = 0; z < SortCount; z++)
			Sortierung[z].resize(AnzahlSpieler);		
			
		
		int NotRankedPlayersCount = 0;
	
		//Speichert die INDEXE der nichtgerankten Spieler
		vector <int> NotRankedPlayers(AnzahlSpieler);
	
		RankedPlayers = 0;
	
		//Speichert die INDEXE der gerankten Spieler
		OnlyRankedPlayers.resize(AnzahlSpieler);
		//Die Schleife pr�ft welche Spieler in die Wertung mitaufgenommen werden
		//und speichert dann den Index des Spielers in OnlyRankedPlayers;
		for(z = 0; z < AnzahlSpieler; z++)
		{
			bool Error = false;
			
			if(!RequiresIgnore[3])
				if(RankedPlayers > Requires[3] - 1)
					break;
				
			if(!RequiresIgnore[0])
				if(Skill[z] < Requires[0])
					Error=true;
				
			if(!RequiresIgnore[1])
				if(Actions[z][0] < Requires[1])
					Error=true;
				
			if(!RequiresIgnore[2])
				if(Actions[z][1] < Requires[2])
					Error=true;
			//Wenn die Nametags den Namen ausschlie�en

			for(int y = 0; y < NotUsedNamesCount; y++)
				if((NotUsedNames[y].find(SpielerNamen[z].c_str(), 0)) != -1)

					Error = true;
				
			if(!Error)
			{
				OnlyRankedPlayers[RankedPlayers] = z;
				RankedPlayers++;
			} 	
			else
			{
				UnRankedPlayers++;
				if(DeleteUnrankedPeople == 1)
				{
/*					NotRankedPlayers[NotRankedPlayersCount] = z;
					NotRankedPlayersCount++;*/
					DeletePlayer(z);
					z--;
				}	
			}
		}
		
		//Alle Spieler l�schen die nicht den Anforderungen entsprechen
/*		if(DeleteUnrankedPeople == 1)

		{
			for(z = NotRankedPlayersCount - 1; z >= 0; z--)
				DeletePlayer(NotRankedPlayers[z]);
		}*/
		//Die Vektoren Kills, Deaths, Bilanz erstellen
		vector<int> KillsVec(AnzahlSpieler);
		vector<int> DeathsVec(AnzahlSpieler);
		vector<int> BilanzVec(AnzahlSpieler);
    for(z = 0; z < AnzahlSpieler; z++)
    {
			KillsVec[z] = Actions[z][0];
			DeathsVec[z] = Actions[z][1];
			BilanzVec[z] = Actions[z][0] - Actions[z][1];
    }
//		KillsVec[1] = -5;
				
		//Zeiger auf die einzelnen Vektor erstellen, die sortiert werden muessen
/*		vector <float> **ToSort;
		
		ToSort = new vector <float> *[sizeof(vector <float> *) * SortCount];
		ToSort[0] = (vector <float> *)&Skill;
		ToSort[1] = (vector <float> *)&KillsVec;
		ToSort[2] = (vector <float> *)&DeathsVec;
//		ToSort[3] = &KDRate;
		ToSort[3] = (vector <float> *)&BilanzVec;
		ToSort[4] = (vector <float> *)&TeamSkill;*/
		
		vector <int> **ToSort;
		ToSort = new vector <int> *[sizeof(vector <int> *) * SortCount];

		ToSort[0] = &Skill;
		ToSort[1] = &KillsVec;
		ToSort[2] = &DeathsVec;
		ToSort[3] = &BilanzVec;
		ToSort[4] = &TeamSkill;
		
		//Eigentlich muesste SortNames[0] "Skill_Sortierung" heissen, aber als erste Datei wird spieler.html aufgerufen
		//und ich bin zu faul, das zu aendern :-))
		SortNames[0] = "spieler";
		SortNames[1] = "Kills_Sortierung";
		SortNames[2] = "Deaths_Sortierung";
		SortNames[3] = "Bilanz_Sortierung";
		SortNames[4] = "TeamSkill_Sortierung";

		SortNames[5] = "KDRate_Sortierung";
		
		vector <int> TempSortierung(AnzahlSpieler);
		for(z = 0; z < SortCount; z++)
		{
			//Sortieren und die INDEXE in TempSortierung speichern
//			Sortiere(TempSortierung, *(ToSort[z]), AnzahlSpieler);
			if(z < SortCount - 1)
				Sortiere(TempSortierung, *(ToSort[z]), AnzahlSpieler);
			else				
				Sortiere(TempSortierung, &KDRate, AnzahlSpieler);
			Sortierung[z] = TempSortierung;
		}		
		

/*		for(z = 0; z < RankedPlayers; z++)
			Rang[Sortierung[0][z]] = z+1;*/
		int RangTemp = 1;
		for(z = 0; z < AnzahlSpieler; z++)
		{
			if(IsRanked(SpielerNamen[Sortierung[0][z]].c_str() ) )		

			{
				Rang[Sortierung[0][z]] = RangTemp;						
				RangTemp++;
			}
			else
				Rang[Sortierung[0][z]] = -1;
		}
	}
	else
		throw MyException("Es ist kein Spieler vorhanden in Ihren Logdateien!");
}

bool Spieler::CheckForPics(char *Buffer)

{
	char Bild[500];
	char *Path;

	Path = new char[strlen(ImagePath) +2];
	strcpy(Path, ImagePath);

	if(Path[strlen(Path)-1] != '/')
	{
		strcat(Path, "/");
		//Path[strlen(Path)] = '\0';
	}
	for(int z = 0; z < WEAPONANZAHL; z++)
	{
		sprintf(Bild, "%simages/weapons/%s.gif", Path, Waffen[z].text);
		if(!QFile::exists(Bild))
		{
			strcpy(Buffer, Bild);
			delete[] Path;
			return false;
		}
	}

	for(unsigned int y = 0; y < sizeof(Bilder) / sizeof(string); y++)
	{
		char temp[400];


		sprintf(temp, "%s%s", Path, Bilder[y].c_str());
		if(!QFile::exists(temp ))
		{
			strcpy(Buffer, temp);
			delete[] Path;
			return false;
		}
	}
	delete[] Path;
	return true;
}

void Spieler::CopyPics(const char *Pfad)
{
	unsigned int z;
	char Output[300], Input[300];

	try
	{
		for(z = 0; z < (unsigned) WEAPONANZAHL; z++)
		{
			sprintf(Output, "%simages/weapons/%s.gif", Pfad, Waffen[z].text);
			sprintf(Input, "%simages/weapons/%s.gif", ImagePath, Waffen[z].text);

			FileCopy(Output, Input);
		}

		for(z = 0; z < sizeof(Bilder) / sizeof(string); z++)
		{
			sprintf(Output, "%s%s", Pfad, Bilder[z].c_str());
			sprintf(Input, "%s%s", ImagePath, Bilder[z].c_str());
			//QMessageBox::information(0, Output, Input);
			FileCopy(Output, Input);
		}
	}
	catch(MyException)
	{
		throw;
	}
	//sprintf(Path, "%s/%s", (QDir::currentDirPath()).latin1(), Bilder[0].c_str());
}

void FileCopy(char *OutName, char *InName)
{
	char Out[300] ="", In[300]="";

	unsigned int z;
	for(z = 0; z < strlen(OutName); z++)
		Out[z] = toupper(OutName[z]);

	for(z = 0; z < strlen(InName); z++)
		In[z] = toupper(InName[z]);

	if(strcmp(Out, In) != 0)
	{
		QFile Output(OutName), Input(InName);


		if(!Input.open(IO_ReadOnly))
		{
			char temp[500];

			sprintf(temp, "Fehler beim �ffnen der Input-Datei : %s", InName);
			throw MyException(temp);
		}

		if(!Output.open(IO_WriteOnly))
		{
			char temp[500];

			sprintf(temp, "Fehler beim �ffnen der Output-Datei : %s", OutName);
			throw MyException(temp);
		}
		
		char Buffer[1001];

		while(!Input.atEnd())
		{
			if(Input.readBlock(Buffer, 1000) == -1)
				throw MyException("Fehler beim Lesen");
			if(Output.writeBlock(Buffer, 1000) == -1)
				throw MyException("Fehler beim Schreiben");
		}

		Input.close();
		Output.close();
	}
}

bool Spieler::IsRanked(const char *Player)
{
	int Index = WelcherSpieler(Player);
	
	for(int z=0; z < RankedPlayers; z++)
	{
		/*if(strcmp(Player, SpielerNamen[Sortierung[Wonach][z]].c_str()) == 0)
			return true;*/
			if(OnlyRankedPlayers[z] == Index)
				return true;
	}
	return false;

}

void Spieler::AddPlayedTime(const char *Name, int Seconds)
{
	int NameID= WelcherSpieler(Name);

	if(NameID == -1)
	{
		NeuerSpieler(Name);
		NameID = WelcherSpieler(Name);
	}
	PlayedTime[NameID] += Seconds;
}

void Spieler::AddPlayedTimeOnMap(int Seconds)
{
	if(ShowMaps)
		MapPlayedTime[CurrentMap] += Seconds / 60;
	InsgSpielZeit += Seconds;
}

void Spieler::SetCurrentMap(const char *MapName)
{
	int MapID = WelcheMap(MapName);

	if(MapID == -1)
	{
		NewMap(MapName);
		MapID = WelcheMap(MapName);
	}
	CurrentMap = MapID;


}

void Spieler::NewMap(const char *Map)
{
	if(ShowMaps)
	{
		if(MapCount == SpaceForMaps)
		{
			//Neuen Speicher reservieren
			int z;

		
			SpaceForMaps += NEWMAPSPACE;
			MapNames.resize(SpaceForMaps);
		
			MapAwardsInsg.resize(SpaceForMaps);
			MapActions.resize(SpaceForMaps);
			MapPlayedTime.resize(SpaceForMaps);
			MapRounds.resize(SpaceForMaps);
			MapCTWins.resize(SpaceForMaps);
			MapTSWins.resize(SpaceForMaps);
		
			for(z = SpaceForMaps - NEWMAPSPACE; z < SpaceForMaps; z++)
			{
				MapAwardsInsg[z].resize(MAPAKTIONENANZAHL);
				MapActions[z].resize(ReservedSpaceForSpielerNamen);
				for(int y=0; y < ReservedSpaceForSpielerNamen; y++)
				{
					MapActions[z][y].resize(MAPAKTIONENANZAHL);
					MapActions[z][y][0] = 100;
				}
			}
		}
		MapNames[MapCount] = Map;
		MapCount++;
	}
}

void Spieler::SetPvsPCount(int Count)
{
	MaxPvsPCount = Count;
	PvsPCount.resize(ANFANGSNAMEN);
	PvsPKills.resize(ANFANGSNAMEN, vector<int>(MaxPvsPCount));
	PvsPDeaths.resize(ANFANGSNAMEN, vector<int>(MaxPvsPCount));
	//Hat die Indexe der Gegner(f�r die Spielernamen)
	PvsPIndex.resize(ANFANGSNAMEN, vector<int>(MaxPvsPCount));
	for(int z=0; z < ANFANGSNAMEN; z++)
		for(int y=0; y < MaxPvsPCount; y++)
			PvsPIndex[z][y] = -1;
}

void Spieler::NewPvsPKills(int Killer, int Opfer, int n)
{
	if(MaxPvsPCount > 0)
	{
		bool OpferFound = false, KillerFound = false;
		int z;

		//Suchen ob das Opfer schon vorhanden ist
		for(z = 0; z < PvsPCount[Killer]; z++)
		{
			//Wenn es vorhanden ist, dann Kills erh�hen und schleife verlassen
			if(PvsPIndex[Killer][z] == Opfer)
			{
				PvsPKills[Killer][z] += n;
				OpferFound = true;
				break;
			}
		}

		//Pr�fen ob das Opfer schon gefunden wurde
		//Wenn nicht dann pr�fen ob wir noch mehr Gegner in die Statistik aufnehmen k�nnen
		if(!OpferFound && PvsPCount[Killer] < MaxPvsPCount)
		{
			//Den Index auf das Opfer setzen, damit er n�chtes mal gefunden wird
			PvsPIndex[Killer][PvsPCount[Killer]] = Opfer;
			PvsPKills[Killer][PvsPCount[Killer]] += n;
			PvsPCount[Killer]++;
		}




		//Das ganze nochmal machen aber diesmal f�r das Opfer...

		//Suchen ob der Killer schon vorhanden ist
		for(z = 0; z < PvsPCount[Opfer]; z++)
		{
			//Wenn er vorhanden ist, dann Deaths erh�hen und schleife verlassen
			if(PvsPIndex[Opfer][z] == Killer)
			{
				PvsPDeaths[Opfer][z] += n;
				KillerFound = true;
				break;
			}
		}

		//Pr�fen ob das Opfer schon gefunden wurde
		//Wenn nicht dann pr�fen ob wir noch mehr Gegner in die Statistik aufnehmen k�nnen
		if(!KillerFound && PvsPCount[Opfer] < MaxPvsPCount)
		{
			//Den Index auf den Killer setzen, damit er n�chtes mal gefunden wird
			PvsPIndex[Opfer][PvsPCount[Opfer]] = Killer;
			PvsPDeaths[Opfer][PvsPCount[Opfer]] += n;
			PvsPCount[Opfer]++;
		}
  }

}

void Spieler::NewRound()
{
	if(ShowMaps)
		MapRounds[CurrentMap]++;
	InsgRunden++;
}

void Spieler::NameChange(const char *Name, const char *ZuName)
{
	int SpielerID = WelcherSpieler(Name);
	int ZuSpielerID = WelcherSpieler(ZuName);
	
	if(SpielerID == -1)
	{
		if(ZuSpielerID == -1)
		{
			ZuSpielerID = NeuerSpieler(ZuName);
		}
	}
	else
	{
		if(ZuSpielerID == -1)
			SpielerNamen[SpielerID] = ZuName;
	}
}

void Spieler::SetNameTagCount(int Count)
{
	NotUsedNamesCount = Count;
	NotUsedNames.resize(Count);
}

void Spieler::NewNameTag(const char *Tag, int Index)
{
	NotUsedNames[Index].setPattern(Tag);
}

void Spieler::CTWin()
{
	int WelcheA = WelcheAktion("CTWin");
	
	CountofAction[WelcheA] += 1;
	if(ShowMaps)
		MapCTWins[CurrentMap] += 1;
}
void Spieler::TSWin()
{
	int WelcheA = WelcheAktion("TSWin");
	
	CountofAction[WelcheA] += 1;
	if(ShowMaps)
		MapTSWins[CurrentMap] += 1;

}

void Spieler::NewDamage(const char *Name, const char *Weapon, int Healths, int Armor, int KillerTeam, int OpferTeam)
{
	if(ShowDamage == 1)
	{
		int SpielerID = WelcherSpieler(Name);
		int WeaponID = WelcheWaffe(Weapon);
	
		if(SpielerID == -1)
		{
			NeuerSpieler(Name);

			SpielerID = WelcherSpieler(Name);
		}

		if(WeaponID == -1)
		{
			char Nachricht[500];
			sprintf(Nachricht, "Die angeforderte Kill-Abfrage konnte nicht best�tigt werden, da die Waffe: %s nicht existiert!", Weapon);
			throw MyException(Nachricht);
		}
		if(KillerTeam == OpferTeam)
		{
			Healths = Healths * -1;		
			Armor = Armor * -1;		
		}
		
		DamageHealths[SpielerID][WeaponID] += Healths;
		DamageArmor[SpielerID][WeaponID] += Armor;

		NewAction(Name, "DamageHealths", Healths); 

		NewAction(Name, "DamageArmor", Armor); 
	}
}

void Spieler::DeletePlayer(int Index)
{
		int y, z;
		
		
		Actions.erase(Actions.begin() + Index);
		DamageArmor.erase(DamageArmor.begin() + Index);
		DamageHealths.erase(DamageHealths.begin() + Index);
		Deaths.erase(Deaths.begin() + Index);
		DeathsStreakTmp.erase(DeathsStreakTmp.begin() + Index);

		FloatActions.erase(FloatActions.begin() + Index);
		KDRate.erase(KDRate.begin() + Index);
		KillStreakTmp.erase(KillStreakTmp.begin() + Index);
		Kills.erase(Kills.begin() + Index);
		for(y = 0; y < MapCount; y++)
			MapActions[y].erase(MapActions[y].begin() + Index);
		PlayedTime.erase(PlayedTime.begin() + Index);
				
		PvsPCount.erase(PvsPCount.begin() + Index);
		PvsPIndex.erase(PvsPIndex.begin() + Index);
		PvsPDeaths.erase(PvsPDeaths.begin() + Index);		
		PvsPKills.erase(PvsPKills.begin() + Index);		
		
		for(z = 0; z < AnzahlSpieler; z++)
		{
			for(y = 0; y < PvsPCount[z]; y++)
			{
				bool Deleted=false;
				if(PvsPIndex[z][y] == Index)
				{
					PvsPIndex[z].erase(PvsPIndex[z].begin() + y);
					PvsPKills[z].erase(PvsPKills[z].begin() + y);
					PvsPDeaths[z].erase(PvsPDeaths[z].begin() + y);
					PvsPCount[z]--;		
					y--;			
					Deleted=true;
				}
				if(!Deleted)
				{
					if(PvsPIndex[z][y] > Index)
						PvsPIndex[z][y]--;					
				}
			}
		}
		Skill.erase(Skill.begin() + Index);
		SpielerNamen.erase(SpielerNamen.begin() + Index);
		TeamSkill.erase(TeamSkill.begin() + Index);
		AnzahlSpieler--;
}

void Spieler::MapsOn()
{
	ShowMaps = true;
	if(ShowMaps)
	{
		SpaceForMaps = ANFANGSMAPS;
		MapActions.resize(ANFANGSMAPS);
		MapAwardsInsg.resize(ANFANGSMAPS);
		MapPlayedTime.resize(ANFANGSMAPS);
		MapRounds.resize(ANFANGSMAPS);
		MapCTWins.resize(ANFANGSMAPS);
		MapTSWins.resize(ANFANGSMAPS);

		for(int z = 0; z < ANFANGSMAPS; z++)
		{
			MapAwardsInsg[z].resize(MAPAKTIONENANZAHL);
			MapActions[z].resize(ANFANGSNAMEN);	
			for(int y = 0; y < ANFANGSNAMEN; y++)
			{
				MapActions[z][y].resize(MAPAKTIONENANZAHL);
				//TeamSkill auf 100 setzen
				MapActions[z][y][0] = 100;
			}

		}
		MapNames.resize(ANFANGSMAPS, "");
		CurrentMap = 0;
		//MapNames[0] = "Nicht angegeben";
		MapCount = 0;
	}
}
void Spieler::DeleteUnranked()
{
	DeleteUnrankedPeople = 1;
}

void Spieler::NewCombinePlayers(const char *BaseName, const char *JoinName)
{
	BasePlayers.push_back(BaseName);
	JoinPlayers.push_back(JoinName);
	CombineCount++;
}

#define SPIELER_CPP
#endif
