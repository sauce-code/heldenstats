#ifndef MyHeldenStats_hpp
#define MyHeldenStats_hpp

#include "HeldenStatsDialog.hpp"

#include <vector>
#include <string.h>

#include <QCheckBox>

using std::vector;
using std::string;


class MyHeldenStats : public HeldenStats

{

  Q_OBJECT

private :
	char ConfigDir[200];
	QString OutputDir;
	QString InputDir;

	void ReadDirs();
	void WriteDirs();
	vector<QLineEdit *> Farben;
	vector<QLineEdit *> Voraussetzungen;
	vector<QCheckBox *> RequireCheck;

	void timerEvent ( QTimerEvent * );
	bool Working;
	bool ExitWhenRdy;
	//int FarbAnzahl;
public:
	
	/*MyHeldenStats( QWidget* parent = 0, const char* name = 0,
		bool modal = FALSE, WFlags f = 0 )
		: HeldenStats( parent, name, modal, f ) {ReadDirs();}*/
	MyHeldenStats( QWidget* parent = 0, const char* name = 0,
	bool modal = FALSE, WFlags f = 0 );
	MyHeldenStats::~MyHeldenStats();
	void SetOptions(bool Exit, bool Messages);
	void NewLog(const char *Log);	
	void SetOutputDir(const char *Output);
public slots:

    virtual void Combine();
    virtual void CreateHTML();
    virtual void DelFiles();
    virtual void DeleteAllNameTags();
    virtual void DeleteCombinedPlayers();
    virtual void DeleteNameTag();
    virtual void NewNameTag();
    virtual void ResetColors();
    virtual void SaveColors();
    virtual void SaveNameTags();
    virtual void SavePlayers();
    virtual void SelectLogDir();
    virtual void SelectLogFiles();
    virtual void SelectOutputDir();
    virtual void TimerEnabled();
    virtual void ClearCombinedPlayers();


};

#endif

