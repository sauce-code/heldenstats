#include <string>
#include <vector>
#include <qregexp.h>

using std::string;
using std::vector;

const int ANFANGSNAMEN = 200, NEWSPACE = 200, WEAPONANZAHL = 24, AKTIONENANZAHL = 35, FLOATAKTIONENANZAHL = 9;
const int FarbAnzahl = 28, RequiresCount = 4, ANFANGSMAPS = 10, MAPAKTIONENANZAHL = 22, NEWMAPSPACE = 10;
//Speichert die Anzahl der Sortierungen, die man für Write Player File braucht, um die Spieler
//Einmal nach Kills, Deaths, KDRate... sortieren zu können
const int SortCount = 6;

const string Colors[] = {"#001525", "#002232", "black", "#141432", "black", "green", "white",
"white", "yellow", "white",//0-9 = Farben
"Courier", "Courier", "Times New Roman", "Courier", "Courier",//10-14 = Schriftart
"4", "4", "4", "4", "4", //15-19 = Schriftgröße
"normal","normal","normal","normal","normal", "#333333", "1", "2"//20-24 = Schriftstyle(normal/italic)
};
/* 
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
*/

struct WAFFEN
{
	const char *text ;
	long style ;
};
extern WAFFEN Waffen[];

struct AKTIONEN
{
	const char *text ;
	long style ;
	const char *AnzeigeText ;
	bool ShowTotal;
	int TeamSkill;
	//Zeigt an ob es Allgemein oder zu TS oder zu CT gehört
	int Status;
};
extern AKTIONEN Aktionen[];

struct FLOATAKTIONEN
{
	const char *text ;
	long style ;
	const char *AnzeigeText ;
	bool ShowTotal;
	//Zeigt an ob es Allgemein oder zu TS oder zu CT gehört
	int Status;
};
extern FLOATAKTIONEN FloatAktionen[];

struct MAPAKTIONEN
{
	const char *text ;
	long style ;
	const char *AnzeigeText ;
	bool ShowTotal;
	int TeamSkill;
	//Zeigt an ob es Allgemein oder zu TS oder zu CT gehört
	int Status;
};
extern MAPAKTIONEN MapAktionen[];

/*struct Map
{
	int AnzahlMaps;
	int ***Kills; //Kills per Map per Weapon  per Player-> ***
	string *MapNamen;

};*/

class Spieler
{
private :
	//Platform spezifisch : anderes Image Verzeichnis für Linux benutzen
	char ImagePath[201];

	int InsgKills;
	int AnzahlSpieler;
	int ReservedSpaceForSpielerNamen;

	int InsgSpielZeit;
	int InsgRunden;
	int UnRankedPlayers;
	//Der erste Vektor beinhaltet immer die Spieleranzahl, der zweite dann die Waffenanzahl/Aktionenanzahl
	vector <vector<int> >Kills;
	vector <vector<int> >Deaths;
	vector <vector<int> >Actions;
	vector <vector<float> > FloatActions;
	vector <string> SpielerNamen;
	/*Was man für die Schadensanzeige braucht :*/
	vector <vector<int> > DamageHealths;
	vector <vector<int> > DamageArmor;
	bool ShowDamage;
	/*Bis hier hin*/
	vector <int> Skill;
	vector <float> KDRate;
	//Steht die Sortierung der Spieler drin, für die Kills, Deaths, KDRate... siehe SortCount oben
	vector <vector<int> > Sortierung;
	vector <int> KillStreakTmp;
	vector <int> DeathsStreakTmp;
	vector <int> Rang;
	vector <int> PlayedTime;
	//Speichert die insgesamten Kills jeder Waffe
	vector <int> WaffenKills;
	//Speichert welcher Spieler welchen Award hat
	vector <string> PlayerWeaponKill;
	//Speichert die Kills die der SPieler hat
	vector <int> NumWeaponKill;

	//Speichert den Namen der einen Award hat
	vector <string> PlayerAward;
	//Speichert die Anzahl mit der der Spieler den Award hat
	vector <int> NumAward;
	//Insgesamte Ausführung einer Action
	vector <int> CountofAction;
	
	//Speichert den Namen der einen Award hat(für die Floataktionen)
	vector <string> FloatPlayerAward;
	//Speichert die Anzahl mit der der Spieler den Award hat(für die Floataktionen)
	vector <float> FloatNumAward;
	//Insgesamte Ausführung einer Action
	vector <float> FloatCountofAction;

	int RankedPlayers;
	//beeinhaltet die Indexe der gerankten Spieler
	vector <int> OnlyRankedPlayers;
	int LogFiles;
	//Wenn es 0 ist werden nicht gerankte Spieler nicht gelöscht und in der Statistik ohne Link geschrieben
	//Wenn es 1 ist werden nicht gerankte Spieler gelöscht und sind somit nicht in der Statistik vorhanden
	//In beiden Fällen wird keine eigene Spielerdatei von einem nicht gerankten Spieler erstellt.
	int DeleteUnrankedPeople;
	//Alles was in der Player vs Player Statistik gebraucht wird!
	//Die aktuelle Anzahl der Gegner, von den einzelnen Spielern
	vector <int> PvsPCount;
	vector <vector<int> > PvsPKills;
	vector <vector<int> > PvsPDeaths;
	//Hat die Indexe der Gegner(für die Spielernamen)
	vector <vector<int> >PvsPIndex;
	int MaxPvsPCount;
	void NewPvsPKills(int Killer, int Opfer, int n);

	vector<int> TeamSkill;

	void ReserveNewSpaceForSpielerNamen();
	//Ist eine generische Funktion, die ZuSortieren, sortiert in Output schreibt
	void Sortiere(vector<int> &Output, vector<int> &ZuSortieren, int Anzahl);
	void Sortiere(vector<int> &Output, vector<float> *ZuSortieren, int Anzahl);
	//Findet die Höchste Anzahl eines vectors raus und schreibt den Namen in Player
	int Most(vector<int> &Highest, char *Player, int Element);
	//Findet die Höchste Anzahl eines vectors raus und schreibt den Namen in Player
	float Most(vector<float> &Highest, char *Player, int Element);



	int Addiere(vector<int> ZuAddieren, int Anzahl);
	void WriteIndexFile(const char *Pfad);
	void WriteSpielerFile(const char *Pfad);
	void WriteSpielerFiles(const char *Pfad);
	void WriteAwardsFile(const char *Pfad);
	void WriteTitelFile(const char *Pfad);
	void WriteWeaponFiles(const char *Pfad);
	void WriteWeaponFile(const char *Pfad);
	void WriteCSSFile(const char *Pfad);
	void WriteMapFiles(const char *Pfad);
	void WriteMapIndexFile(const char *Pfad);
	void WriteMapLinksFile(const char *Pfad);
	void WriteMapOverViewFile(const char *Pfad);
	void WriteAwardFiles(const char *Pfad);
	void WriteNoMaps(const char *Pfad);
	bool WriteAwards;
	
	void CopyPics(const char *Pfad);
	bool IsRanked(const char *Player);
	string FarbNamen[FarbAnzahl];
	string TableSettings;
	string TableFontColor;
	string TableCaptionColor;
	vector<int> Requires;
	vector<bool> RequiresIgnore;

	//Alles für die Maps
	vector <string> MapNames;
	int MapCount, CurrentMap, SpaceForMaps;
	int WelcheMap(const char *Map);
	bool ShowMaps;
	//MapAktionen speichert die Aktionen von den Spielern auf den Maps
	vector <vector<vector<int> > > MapActions;
	vector <vector<int> > MapAwardsNum;
	vector <vector<int> > MapAwardsInsg;
	vector <vector<string> > MapAwardsPlayer;
	vector <int> MapPlayedTime;
	vector <int> MapRounds;
	vector <int> MapCTWins;
	vector <int> MapTSWins;

	void NewMap(const char *Map);

	//Speichert die NamenTags, die NICHT benutzt werden dürfen
	vector <QRegExp> NotUsedNames;
	int NotUsedNamesCount;
	
	//Speichert die Namen der Sortierungen, z.B; KillsSortierung oder SkillSortierung
	vector<string> SortNames;
	
	void SortierenachSkill();
	void DeletePlayer(int Index);
	
	//Wird benötigt damit man Spieler zusammenfügen kann, das ganze passiert unter WelcherSpieler
	vector <string> BasePlayers;
	vector <string> JoinPlayers;
	int CombineCount;
	
public :
	Spieler();
	~Spieler();
	//int WriteMapFile(char *Pfad);
	inline int WelcherSpieler(const char *Name);
	inline int NeuerSpieler(const char *Name);
	inline void GetSpieler(char *Buffer, int Welcher);
	void NewKills(const char *Killer, const char *Opfer, int KillerTeam, int OpferTeam, const char *Weapon, int n);
	int GetKills(char *Player, char *Weapon);
	//Liefert den Index der Waffe zurück
	inline int WelcheWaffe(const char *Waffe);
	//Liefert den Index der Aktion zurück
	inline int WelcheAktion(const char *Aktion);
	inline int WelcheMapAktion(const char *MapAktion);
	inline int WelcheFloatAktion(const char *Aktion);

	void CoutAllPlayers();
	//Schreibt alle Spieler als HTML Dateien mit allen bekannten Angaben, einer eigenen
	//Awards, PlayerRanks und Index-Datei
	void WritePlayerHTML(const char *Pfad, int Logdateien);
	//void SortierenachKDRate();
	//Liefert die meisten Kills dieser Waffe zurück und schreibt den Namen in Player
	int MostWeaponKills(const char *Weapon);
	int MostWeaponKills(const char *Weapon, char *Player);
	inline void NewAction(const char *Player, const char *Action, int n);
	bool CheckForPics(char *Buffer);
	//void SetMinimum(int K, int D, int Sk, int KD){MinKills = K; MinDeaths = D; MinSkill = Sk; MinKD = KD;}
	void SetColor(const char *Farbe, int Index){FarbNamen[Index] = Farbe;}
	void AddPlayedTime(const char *Name, int Seconds);
	void SetRequires(int Require, int Index){Requires[Index] = Require;}
	void SetRequiresCheck(bool Require, int Index){RequiresIgnore[Index] = Require;}
	void SetCurrentMap(const char *MapName);
	void SetPvsPCount(int Count);
	void AddPlayedTimeOnMap(int Seconds);
	void NewRound();
	void NameChange(const char *Name, const char *ZuName);
	void SetNameTagCount(int Count);
	void NewNameTag(const char *Tag, int Index);
	void CTWin();
	void TSWin();
	void NewDamage(const char *Name, const char *Weapon, int Healths, int Armor, int KillerTeam, int OpferTeam);
	void MapsOn();
	void DeleteUnranked();
	void NewCombinePlayers(const char *BaseName, const char *JoinName);
};

