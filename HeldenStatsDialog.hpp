/****************************************************************************
** Form interface generated from reading ui file 'Helden~1.ui'
**
** Created: Sat Oct 27 18:40:07 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef HELDENSTATS_H
#define HELDENSTATS_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QListBox;
class QListBoxItem;
class QProgressBar;
class QPushButton;
class QTabWidget;
class QWidget;

class HeldenStats : public QDialog
{ 
    Q_OBJECT

public:
    HeldenStats( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~HeldenStats();

    QTabWidget* Einstellungen;
    QWidget* Allgemein;
    QGroupBox* GroupBox1;
    QListBox* LogDateienListe;
    QPushButton* OutputDirButton;
    QPushButton* SelectLogFilesButton;
    QPushButton* PushButton6;
    QProgressBar* ProgressBar;
    QLineEdit* TimerTime;
    QPushButton* PushButton7;
    QLabel* TextLabel3;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* CurrentDirLabel;
    QLabel* TextLabel1_7;
    QLabel* TimerLabel;
    QPushButton* PushButton4;
    QCheckBox* CheckTimer;
    QLabel* TextLabel7;
    QWidget* Farben;
    QGroupBox* GroupBox2;
    QPushButton* ColorSave;
    QPushButton* ColorDefault;
    QGroupBox* GroupBox5;
    QLineEdit* FontColor;
    QLineEdit* FontStyle;
    QLineEdit* HoverLinkColor;
    QLineEdit* LinkFontStyle;
    QLineEdit* HoverLinkFontStyle;
    QLineEdit* LinkColor;
    QLineEdit* HTMLBG;
    QLineEdit* LinkFont;
    QLineEdit* HoverLinkFont;
    QLineEdit* FontSize;
    QLineEdit* LinkFontSize;
    QLineEdit* HoverLinkSize;
    QLineEdit* Font;
    QLabel* TextLabel6;
    QLabel* TextLabel3_2;
    QLabel* TextLabel1_3;
    QLabel* TextLabel2_4;
    QGroupBox* GroupBox4;
    QLineEdit* EvenBG;
    QLineEdit* TableFontStyle;
    QLineEdit* TableCaptionStyle;
    QLineEdit* TableCaptionFont;
    QLineEdit* TableFont;
    QLineEdit* TableFontColor;
    QLineEdit* TableBorderSize;
    QLineEdit* TableBG;
    QLineEdit* TableCaptionBG;
    QLineEdit* TableCellSpacingSize;
    QLineEdit* TableCaptionColor;
    QLineEdit* TableBorderColor;
    QLineEdit* TableCaptionSize;
    QLineEdit* TableFontSize;
    QLineEdit* UnEvenBG;
    QLabel* TextLabel1_2;
    QLabel* TextLabel2_3;
    QLabel* TextLabel5;
    QLabel* TextLabel2_2;
    QLabel* TextLabel1_5;
    QLabel* TextLabel4;
    QLabel* TextLabel1_8;
    QLabel* TextLabel1_8_2;
    QLabel* TextLabel5_3;
    QLabel* TextLabel6_3;
    QLabel* TextLabel7_2;
    QLabel* TextLabel8;
    QWidget* Voraussetzungen;
    QGroupBox* GroupBox6;
    QLineEdit* MaxPlayers;
    QLineEdit* MaxPvsP;
    QLabel* TextLabel2_5;
    QLabel* TextLabel1_4;
    QLabel* TextLabel1_6;
    QCheckBox* CheckPlayers;
    QGroupBox* GroupBox9;
    QLineEdit* MinSkill;
    QLineEdit* MinKills;
    QLineEdit* MinDeaths;
    QLabel* TextLabel4_2;
    QLabel* TextLabel5_2;
    QLabel* TextLabel6_2;
    QCheckBox* CheckDeaths;
    QCheckBox* CheckKills;
    QCheckBox* CheckSkill;
    QLabel* TextLabel3_3;
    QPushButton* PushButton16;
    QWidget* Names;
    QGroupBox* GroupBox7;
    QLabel* TextLabel2_6;
    QLabel* TextLabel1_9;
    QPushButton* KillNames;
    QPushButton* KillCurrentName;
    QPushButton* SaveNames;
    QPushButton* EingabeButton;
    QLineEdit* NameEdit;
    QListBox* Namen;
    QWidget* Sonstiges;
    QGroupBox* GroupBox8;
    QLabel* TextLabel1_10;
    QLabel* TextLabel2_2_2;
    QCheckBox* HideMaps;
    QCheckBox* DeleteUnranked;
    QWidget* CombinePage;
    QGroupBox* GroupBox9_2;
    QLabel* TextLabel2_7;
    QLineEdit* JoinPlayer;
    QLineEdit* BasePlayer;
    QLabel* TextLabel3_4;
    QPushButton* SavePlayersButton;
    QPushButton* DeleteCombinedPlayersButton;
    QPushButton* ClearCombinedPlayersButton;
    QListBox* CombinedPlayers;
    QLabel* TextLabel1_11;
    QPushButton* CombineButton;

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

protected:
    bool event( QEvent* );
};

#endif // HELDENSTATS_H
