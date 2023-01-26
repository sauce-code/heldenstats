/****************************************************************************
** Form implementation generated from reading ui file 'Helden~1.ui'
**
** Created: Sat Oct 27 18:40:08 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "HeldenStatsDialog.hpp"

/*
#include <qcheckbox.h>
#include <q3groupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <q3listbox.h>
#include <q3progressbar.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
*/
#include <QCheckBox>
#include <Q3GroupBox>
#include <QLabel>
#include <QLineEdit>
#include <Q3ListBox>
#include <Q3ProgressBar>
#include <QPushButton>
#include <QTabWidget>
#include <QWidget>
#include <QLayout>
#include <QVariant>
#include <QToolTip>
#include <Q3WhatsThis>

/* 
 *  Constructs a HeldenStats which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
HeldenStats::HeldenStats( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "HeldenStats" );
    resize( 688, 542 ); 
    setProperty( "caption", tr( "HeldenStats" ) );

    Einstellungen = new QTabWidget( this, "Einstellungen" );
    Einstellungen->setGeometry( QRect( 0, 0, 690, 540 ) ); 

    Allgemein = new QWidget( Einstellungen, "Allgemein" );

    GroupBox1 = new QGroupBox( Allgemein, "GroupBox1" );
    GroupBox1->setGeometry( QRect( 0, 0, 700, 410 ) ); 
    GroupBox1->setProperty( "title", tr( "Einstellungen" ) );

    LogDateienListe = new QListBox( GroupBox1, "LogDateienListe" );
    LogDateienListe->setGeometry( QRect( 10, 180, 500, 131 ) ); 

    OutputDirButton = new QPushButton( GroupBox1, "OutputDirButton" );
    OutputDirButton->setGeometry( QRect( 10, 120, 190, 40 ) ); 
    OutputDirButton->setProperty( "text", tr( QString::fromUtf8( "Outputverzeichnis auswählen" ) ) );

    SelectLogFilesButton = new QPushButton( GroupBox1, "SelectLogFilesButton" );
    SelectLogFilesButton->setGeometry( QRect( 10, 50, 191, 40 ) ); 
    SelectLogFilesButton->setProperty( "text", tr( QString::fromUtf8( "Logdateien auswählen" ) ) );
    SelectLogFilesButton->setProperty( "on", QVariant( FALSE, 0 ) );
    SelectLogFilesButton->setProperty( "on", QVariant( FALSE, 0 ) );

    PushButton6 = new QPushButton( GroupBox1, "PushButton6" );
    PushButton6->setGeometry( QRect( 210, 50, 190, 41 ) ); 
    PushButton6->setProperty( "text", tr( QString::fromUtf8( "Komplettes Verzeichnis auswählen" ) ) );

    ProgressBar = new QProgressBar( GroupBox1, "ProgressBar" );
    ProgressBar->setProperty( "enabled", QVariant( TRUE, 0 ) );
    ProgressBar->setGeometry( QRect( 228, 327, 250, 21 ) ); 
    ProgressBar->setProperty( "totalSteps", 100 );
    ProgressBar->setProperty( "progress", 0 );

    TimerTime = new QLineEdit( GroupBox1, "TimerTime" );
    TimerTime->setGeometry( QRect( 10, 380, 71, 22 ) ); 
    TimerTime->setProperty( "text", tr( "30" ) );

    PushButton7 = new QPushButton( GroupBox1, "PushButton7" );
    PushButton7->setGeometry( QRect( 518, 227, 131, 31 ) ); 
    PushButton7->setProperty( "text", tr( QString::fromUtf8( "Liste löschen" ) ) );

    TextLabel3 = new QLabel( GroupBox1, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 160, 230, 16 ) ); 
    TextLabel3->setProperty( "text", tr( QString::fromUtf8( "Momentan ausgewählte Logdateien :" ) ) );

    TextLabel1 = new QLabel( GroupBox1, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 20, 670, 30 ) ); 
    QFont TextLabel1_font(  TextLabel1->font() );
    TextLabel1_font.setFamily( "Tahoma" );
    TextLabel1->setFont( TextLabel1_font ); 
    TextLabel1->setProperty( "text", tr( QString::fromUtf8( "Drücken Sie auf \"Logdateien auswählen\" und markieren Sie bitte die Logdateien oder benutzen Sie den Knopf\n \"Komplettes Verzeichnis auswählen\", um alle Logdateien aus einem Verzeichnis umzuwandeln." ) ) );

    TextLabel2 = new QLabel( GroupBox1, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 100, 550, 16 ) ); 
    QFont TextLabel2_font(  TextLabel2->font() );
    TextLabel2_font.setFamily( "Tahoma" );
    TextLabel2->setFont( TextLabel2_font ); 
    TextLabel2->setProperty( "autoMask", QVariant( FALSE, 0 ) );
    TextLabel2->setProperty( "text", tr( QString::fromUtf8( "Bitte das Verzeichnis auswählen, in welches die HTML Dateien geschrieben werden sollen!" ) ) );
    TextLabel2->setProperty( "textFormat", (int)QLabel::AutoText );
    TextLabel2->setProperty( "alignment", int( QLabel::AlignVCenter | QLabel::AlignLeft ) );

    CurrentDirLabel = new QLabel( GroupBox1, "CurrentDirLabel" );
    CurrentDirLabel->setGeometry( QRect( 210, 120, 300, 50 ) ); 
    QFont CurrentDirLabel_font(  CurrentDirLabel->font() );
    CurrentDirLabel_font.setFamily( "Tahoma" );
    CurrentDirLabel->setFont( CurrentDirLabel_font ); 
    CurrentDirLabel->setProperty( "mouseTracking", QVariant( FALSE, 0 ) );
    CurrentDirLabel->setProperty( "autoMask", QVariant( FALSE, 0 ) );
    CurrentDirLabel->setProperty( "frameShape", (int)QLabel::NoFrame );
    CurrentDirLabel->setProperty( "text", tr( QString::fromUtf8( "Aktuelles Verzeichnis : noch kein Verzeichnis gewählt" ) ) );
    CurrentDirLabel->setProperty( "textFormat", (int)QLabel::AutoText );
    CurrentDirLabel->setProperty( "scaledContents", QVariant( FALSE, 0 ) );
    CurrentDirLabel->setProperty( "alignment", int( QLabel::WordBreak | QLabel::AlignVCenter | QLabel::AlignLeft ) );

    TextLabel1_7 = new QLabel( GroupBox1, "TextLabel1_7" );
    TextLabel1_7->setGeometry( QRect( 10, 360, 660, 21 ) ); 
    QFont TextLabel1_7_font(  TextLabel1_7->font() );
    TextLabel1_7_font.setFamily( "Tahoma" );
    TextLabel1_7->setFont( TextLabel1_7_font ); 
    TextLabel1_7->setProperty( "text", tr( QString::fromUtf8( "Hier können Sie einen Timer einrichten, der nach n Minuten die angegeben Logdateien umwandelt." ) ) );

    TimerLabel = new QLabel( GroupBox1, "TimerLabel" );
    TimerLabel->setGeometry( QRect( 210, 380, 410, 21 ) ); 
    QFont TimerLabel_font(  TimerLabel->font() );
    TimerLabel_font.setFamily( "Tahoma" );
    TimerLabel->setFont( TimerLabel_font ); 
    TimerLabel->setProperty( "text", tr( "Der Timer ist nicht aktiviert." ) );

    PushButton4 = new QPushButton( GroupBox1, "PushButton4" );
    PushButton4->setGeometry( QRect( 10, 320, 191, 40 ) ); 
    PushButton4->setProperty( "text", tr( "Los : HTML-Dateien erstellen" ) );

    CheckTimer = new QCheckBox( GroupBox1, "CheckTimer" );
    CheckTimer->setGeometry( QRect( 90, 381, 110, 20 ) ); 
    QFont CheckTimer_font(  CheckTimer->font() );
    CheckTimer_font.setFamily( "Tahoma" );
    CheckTimer->setFont( CheckTimer_font ); 
    CheckTimer->setProperty( "text", tr( "Timer aktivieren" ) );

    TextLabel7 = new QLabel( Allgemein, "TextLabel7" );
    TextLabel7->setGeometry( QRect( 10, 420, 380, 90 ) ); 
    QFont TextLabel7_font(  TextLabel7->font() );
    TextLabel7_font.setFamily( "Tahoma" );
    TextLabel7->setFont( TextLabel7_font ); 
    TextLabel7->setProperty( "text", tr( QString::fromUtf8( "Version 1.04 © Benjamin Held benjamin.held@gmx.de\nProgrammierer : Benjamin Held\nGrafiker : Ansgar Heidemann\nEine Beschreibung gibts in der readme.html" ) ) );
    Einstellungen->insertTab( Allgemein, tr( "Allgemein" ) );

    Farben = new QWidget( Einstellungen, "Farben" );

    GroupBox2 = new QGroupBox( Farben, "GroupBox2" );
    GroupBox2->setGeometry( QRect( 0, 0, 700, 510 ) ); 
    GroupBox2->setProperty( "title", tr( "Farben" ) );

    ColorSave = new QPushButton( GroupBox2, "ColorSave" );
    ColorSave->setGeometry( QRect( 10, 460, 144, 26 ) ); 
    ColorSave->setProperty( "text", tr( "Einstellungen speichern" ) );

    ColorDefault = new QPushButton( GroupBox2, "ColorDefault" );
    ColorDefault->setGeometry( QRect( 170, 460, 148, 26 ) ); 
    ColorDefault->setProperty( "text", tr( "Default wieder herstellen" ) );

    GroupBox5 = new QGroupBox( GroupBox2, "GroupBox5" );
    GroupBox5->setGeometry( QRect( 10, 300, 680, 140 ) ); 
    GroupBox5->setProperty( "title", tr( "In den HTML Dateien" ) );

    FontColor = new QLineEdit( GroupBox5, "FontColor" );
    FontColor->setGeometry( QRect( 160, 50, 100, 22 ) ); 
    FontColor->setProperty( "text", tr( "white" ) );

    FontStyle = new QLineEdit( GroupBox5, "FontStyle" );
    FontStyle->setGeometry( QRect( 450, 50, 90, 22 ) ); 
    FontStyle->setProperty( "text", tr( "normal" ) );

    HoverLinkColor = new QLineEdit( GroupBox5, "HoverLinkColor" );
    HoverLinkColor->setGeometry( QRect( 160, 110, 100, 22 ) ); 
    HoverLinkColor->setProperty( "text", tr( "white" ) );

    LinkFontStyle = new QLineEdit( GroupBox5, "LinkFontStyle" );
    LinkFontStyle->setGeometry( QRect( 450, 80, 90, 22 ) ); 
    LinkFontStyle->setProperty( "text", tr( "normal" ) );

    HoverLinkFontStyle = new QLineEdit( GroupBox5, "HoverLinkFontStyle" );
    HoverLinkFontStyle->setGeometry( QRect( 450, 110, 90, 22 ) ); 
    HoverLinkFontStyle->setProperty( "text", tr( "normal" ) );

    LinkColor = new QLineEdit( GroupBox5, "LinkColor" );
    LinkColor->setGeometry( QRect( 160, 80, 100, 22 ) ); 
    LinkColor->setProperty( "text", tr( "yellow" ) );

    HTMLBG = new QLineEdit( GroupBox5, "HTMLBG" );
    HTMLBG->setGeometry( QRect( 160, 20, 100, 22 ) ); 
    HTMLBG->setProperty( "text", tr( "black" ) );

    LinkFont = new QLineEdit( GroupBox5, "LinkFont" );
    LinkFont->setGeometry( QRect( 270, 80, 101, 22 ) ); 
    LinkFont->setProperty( "text", tr( "Courier" ) );

    HoverLinkFont = new QLineEdit( GroupBox5, "HoverLinkFont" );
    HoverLinkFont->setGeometry( QRect( 270, 110, 101, 22 ) ); 
    HoverLinkFont->setProperty( "text", tr( "Courier" ) );

    FontSize = new QLineEdit( GroupBox5, "FontSize" );
    FontSize->setGeometry( QRect( 380, 50, 60, 22 ) ); 
    FontSize->setProperty( "text", tr( "4" ) );

    LinkFontSize = new QLineEdit( GroupBox5, "LinkFontSize" );
    LinkFontSize->setGeometry( QRect( 380, 80, 60, 22 ) ); 
    LinkFontSize->setProperty( "text", tr( "4" ) );

    HoverLinkSize = new QLineEdit( GroupBox5, "HoverLinkSize" );
    HoverLinkSize->setGeometry( QRect( 380, 110, 60, 22 ) ); 
    HoverLinkSize->setProperty( "text", tr( "4" ) );

    Font = new QLineEdit( GroupBox5, "Font" );
    Font->setGeometry( QRect( 270, 50, 100, 22 ) ); 
    Font->setProperty( "text", tr( "Times New Roman" ) );

    TextLabel6 = new QLabel( GroupBox5, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 10, 50, 110, 16 ) ); 
    QFont TextLabel6_font(  TextLabel6->font() );
    TextLabel6_font.setFamily( "Tahoma" );
    TextLabel6->setFont( TextLabel6_font ); 
    TextLabel6->setProperty( "text", tr( "Schrift :" ) );

    TextLabel3_2 = new QLabel( GroupBox5, "TextLabel3_2" );
    TextLabel3_2->setGeometry( QRect( 10, 20, 140, 16 ) ); 
    QFont TextLabel3_2_font(  TextLabel3_2->font() );
    TextLabel3_2_font.setFamily( "Tahoma" );
    TextLabel3_2->setFont( TextLabel3_2_font ); 
    TextLabel3_2->setProperty( "text", tr( "Hintergrund :" ) );

    TextLabel1_3 = new QLabel( GroupBox5, "TextLabel1_3" );
    TextLabel1_3->setGeometry( QRect( 10, 80, 110, 16 ) ); 
    QFont TextLabel1_3_font(  TextLabel1_3->font() );
    TextLabel1_3_font.setFamily( "Tahoma" );
    TextLabel1_3->setFont( TextLabel1_3_font ); 
    TextLabel1_3->setProperty( "text", tr( "Link :" ) );

    TextLabel2_4 = new QLabel( GroupBox5, "TextLabel2_4" );
    TextLabel2_4->setGeometry( QRect( 10, 110, 150, 16 ) ); 
    QFont TextLabel2_4_font(  TextLabel2_4->font() );
    TextLabel2_4_font.setFamily( "Tahoma" );
    TextLabel2_4->setFont( TextLabel2_4_font ); 
    TextLabel2_4->setProperty( "text", tr( QString::fromUtf8( "Link beim drübergehen :" ) ) );

    GroupBox4 = new QGroupBox( GroupBox2, "GroupBox4" );
    GroupBox4->setGeometry( QRect( 10, 20, 680, 280 ) ); 
    GroupBox4->setProperty( "title", tr( "In den Tabellen" ) );

    EvenBG = new QLineEdit( GroupBox4, "EvenBG" );
    EvenBG->setGeometry( QRect( 160, 100, 100, 22 ) ); 
    EvenBG->setProperty( "text", tr( "#002232" ) );

    TableFontStyle = new QLineEdit( GroupBox4, "TableFontStyle" );
    TableFontStyle->setGeometry( QRect( 450, 190, 90, 22 ) ); 
    TableFontStyle->setProperty( "text", tr( "normal" ) );

    TableCaptionStyle = new QLineEdit( GroupBox4, "TableCaptionStyle" );
    TableCaptionStyle->setGeometry( QRect( 450, 160, 90, 22 ) ); 
    TableCaptionStyle->setProperty( "text", tr( "normal" ) );

    TableCaptionFont = new QLineEdit( GroupBox4, "TableCaptionFont" );
    TableCaptionFont->setGeometry( QRect( 270, 160, 100, 22 ) ); 
    TableCaptionFont->setProperty( "text", tr( "Courier" ) );

    TableFont = new QLineEdit( GroupBox4, "TableFont" );
    TableFont->setGeometry( QRect( 270, 190, 100, 22 ) ); 
    TableFont->setProperty( "text", tr( "Courier" ) );

    TableFontColor = new QLineEdit( GroupBox4, "TableFontColor" );
    TableFontColor->setGeometry( QRect( 160, 190, 100, 22 ) ); 
    TableFontColor->setProperty( "text", tr( "white" ) );

    TableBorderSize = new QLineEdit( GroupBox4, "TableBorderSize" );
    TableBorderSize->setGeometry( QRect( 380, 220, 61, 22 ) ); 
    TableBorderSize->setProperty( "text", tr( "1" ) );

    TableBG = new QLineEdit( GroupBox4, "TableBG" );
    TableBG->setGeometry( QRect( 160, 40, 100, 22 ) ); 
    TableBG->setProperty( "text", tr( "black" ) );

    TableCaptionBG = new QLineEdit( GroupBox4, "TableCaptionBG" );
    TableCaptionBG->setGeometry( QRect( 160, 130, 100, 22 ) ); 
    TableCaptionBG->setProperty( "text", tr( "#141432" ) );

    TableCellSpacingSize = new QLineEdit( GroupBox4, "TableCellSpacingSize" );
    TableCellSpacingSize->setGeometry( QRect( 380, 250, 60, 22 ) ); 
    TableCellSpacingSize->setProperty( "text", tr( "2" ) );

    TableCaptionColor = new QLineEdit( GroupBox4, "TableCaptionColor" );
    TableCaptionColor->setGeometry( QRect( 160, 160, 101, 22 ) ); 
    TableCaptionColor->setProperty( "text", tr( "green" ) );

    TableBorderColor = new QLineEdit( GroupBox4, "TableBorderColor" );
    TableBorderColor->setGeometry( QRect( 160, 220, 100, 22 ) ); 
    TableBorderColor->setProperty( "text", tr( "#333333" ) );

    TableCaptionSize = new QLineEdit( GroupBox4, "TableCaptionSize" );
    TableCaptionSize->setGeometry( QRect( 380, 160, 60, 22 ) ); 
    TableCaptionSize->setProperty( "text", tr( "4" ) );

    TableFontSize = new QLineEdit( GroupBox4, "TableFontSize" );
    TableFontSize->setGeometry( QRect( 380, 190, 60, 22 ) ); 
    TableFontSize->setProperty( "text", tr( "4" ) );

    UnEvenBG = new QLineEdit( GroupBox4, "UnEvenBG" );
    UnEvenBG->setGeometry( QRect( 160, 70, 100, 22 ) ); 
    UnEvenBG->setProperty( "text", tr( "#001525" ) );

    TextLabel1_2 = new QLabel( GroupBox4, "TextLabel1_2" );
    TextLabel1_2->setGeometry( QRect( 10, 70, 150, 16 ) ); 
    QFont TextLabel1_2_font(  TextLabel1_2->font() );
    TextLabel1_2_font.setFamily( "Tahoma" );
    TextLabel1_2->setFont( TextLabel1_2_font ); 
    TextLabel1_2->setProperty( "text", tr( "Ungerade Tabellenzeilen :" ) );

    TextLabel2_3 = new QLabel( GroupBox4, "TextLabel2_3" );
    TextLabel2_3->setGeometry( QRect( 10, 40, 120, 16 ) ); 
    QFont TextLabel2_3_font(  TextLabel2_3->font() );
    TextLabel2_3_font.setFamily( "Tahoma" );
    TextLabel2_3->setFont( TextLabel2_3_font ); 
    TextLabel2_3->setProperty( "text", tr( "Hintergrund :" ) );

    TextLabel5 = new QLabel( GroupBox4, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 10, 130, 140, 16 ) ); 
    QFont TextLabel5_font(  TextLabel5->font() );
    TextLabel5_font.setFamily( "Tahoma" );
    TextLabel5->setFont( TextLabel5_font ); 
    TextLabel5->setProperty( "text", tr( "Kopfzeilenhintergrund :" ) );

    TextLabel2_2 = new QLabel( GroupBox4, "TextLabel2_2" );
    TextLabel2_2->setGeometry( QRect( 10, 100, 150, 16 ) ); 
    QFont TextLabel2_2_font(  TextLabel2_2->font() );
    TextLabel2_2_font.setFamily( "Tahoma" );
    TextLabel2_2->setFont( TextLabel2_2_font ); 
    TextLabel2_2->setProperty( "text", tr( "Gerade Tabellenzeilen :" ) );

    TextLabel1_5 = new QLabel( GroupBox4, "TextLabel1_5" );
    TextLabel1_5->setGeometry( QRect( 10, 160, 110, 16 ) ); 
    QFont TextLabel1_5_font(  TextLabel1_5->font() );
    TextLabel1_5_font.setFamily( "Tahoma" );
    TextLabel1_5->setFont( TextLabel1_5_font ); 
    TextLabel1_5->setProperty( "text", tr( "Kopfzeile :" ) );

    TextLabel4 = new QLabel( GroupBox4, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 10, 190, 80, 16 ) ); 
    QFont TextLabel4_font(  TextLabel4->font() );
    TextLabel4_font.setFamily( "Tahoma" );
    TextLabel4->setFont( TextLabel4_font ); 
    TextLabel4->setProperty( "text", tr( "Schrift :" ) );

    TextLabel1_8 = new QLabel( GroupBox4, "TextLabel1_8" );
    TextLabel1_8->setGeometry( QRect( 10, 220, 80, 21 ) ); 
    QFont TextLabel1_8_font(  TextLabel1_8->font() );
    TextLabel1_8_font.setFamily( "Tahoma" );
    TextLabel1_8->setFont( TextLabel1_8_font ); 
    TextLabel1_8->setProperty( "text", tr( "Rand :" ) );

    TextLabel1_8_2 = new QLabel( GroupBox4, "TextLabel1_8_2" );
    TextLabel1_8_2->setGeometry( QRect( 10, 250, 170, 21 ) ); 
    QFont TextLabel1_8_2_font(  TextLabel1_8_2->font() );
    TextLabel1_8_2_font.setFamily( "Tahoma" );
    TextLabel1_8_2->setFont( TextLabel1_8_2_font ); 
    TextLabel1_8_2->setProperty( "text", tr( "Abstand zwischen Zellen :" ) );

    TextLabel5_3 = new QLabel( GroupBox4, "TextLabel5_3" );
    TextLabel5_3->setGeometry( QRect( 170, 20, 90, 16 ) ); 
    QFont TextLabel5_3_font(  TextLabel5_3->font() );
    TextLabel5_3_font.setFamily( "Tahoma" );
    TextLabel5_3->setFont( TextLabel5_3_font ); 
    TextLabel5_3->setProperty( "text", tr( "Farbe" ) );

    TextLabel6_3 = new QLabel( GroupBox4, "TextLabel6_3" );
    TextLabel6_3->setGeometry( QRect( 280, 20, 90, 16 ) ); 
    QFont TextLabel6_3_font(  TextLabel6_3->font() );
    TextLabel6_3_font.setFamily( "Tahoma" );
    TextLabel6_3->setFont( TextLabel6_3_font ); 
    TextLabel6_3->setProperty( "text", tr( "Schriftart" ) );

    TextLabel7_2 = new QLabel( GroupBox4, "TextLabel7_2" );
    TextLabel7_2->setGeometry( QRect( 390, 20, 60, 16 ) ); 
    QFont TextLabel7_2_font(  TextLabel7_2->font() );
    TextLabel7_2_font.setFamily( "Tahoma" );
    TextLabel7_2->setFont( TextLabel7_2_font ); 
    TextLabel7_2->setProperty( "text", tr( QString::fromUtf8( "Größe" ) ) );

    TextLabel8 = new QLabel( GroupBox4, "TextLabel8" );
    TextLabel8->setGeometry( QRect( 460, 20, 210, 16 ) ); 
    QFont TextLabel8_font(  TextLabel8->font() );
    TextLabel8_font.setFamily( "Tahoma" );
    TextLabel8->setFont( TextLabel8_font ); 
    TextLabel8->setProperty( "text", tr( "Style(normal / italic)" ) );
    Einstellungen->insertTab( Farben, tr( "Farben" ) );

    Voraussetzungen = new QWidget( Einstellungen, "Voraussetzungen" );

    GroupBox6 = new QGroupBox( Voraussetzungen, "GroupBox6" );
    GroupBox6->setGeometry( QRect( 0, 150, 700, 100 ) ); 
    GroupBox6->setProperty( "title", tr( "Maximale Vorrausetzungen" ) );

    MaxPlayers = new QLineEdit( GroupBox6, "MaxPlayers" );
    MaxPlayers->setGeometry( QRect( 320, 40, 60, 22 ) ); 
    MaxPlayers->setProperty( "text", tr( "100" ) );
    MaxPlayers->setProperty( "maxLength", 5 );

    MaxPvsP = new QLineEdit( GroupBox6, "MaxPvsP" );
    MaxPvsP->setGeometry( QRect( 320, 70, 61, 22 ) ); 
    MaxPvsP->setProperty( "text", tr( "20" ) );

    TextLabel2_5 = new QLabel( GroupBox6, "TextLabel2_5" );
    TextLabel2_5->setGeometry( QRect( 10, 20, 670, 16 ) ); 
    QFont TextLabel2_5_font(  TextLabel2_5->font() );
    TextLabel2_5_font.setFamily( "Tahoma" );
    TextLabel2_5->setFont( TextLabel2_5_font ); 
    TextLabel2_5->setProperty( "text", tr( QString::fromUtf8( "Hier können Sie eine Menge Platz sparen, ein Spieler braucht ungefähr 10 Kilobyte." ) ) );

    TextLabel1_4 = new QLabel( GroupBox6, "TextLabel1_4" );
    TextLabel1_4->setGeometry( QRect( 10, 40, 290, 16 ) ); 
    QFont TextLabel1_4_font(  TextLabel1_4->font() );
    TextLabel1_4_font.setFamily( "Tahoma" );
    TextLabel1_4->setFont( TextLabel1_4_font ); 
    TextLabel1_4->setProperty( "text", tr( "Maximale Spieler :" ) );

    TextLabel1_6 = new QLabel( GroupBox6, "TextLabel1_6" );
    TextLabel1_6->setGeometry( QRect( 10, 70, 310, 21 ) ); 
    QFont TextLabel1_6_font(  TextLabel1_6->font() );
    TextLabel1_6_font.setFamily( "Tahoma" );
    TextLabel1_6->setFont( TextLabel1_6_font ); 
    TextLabel1_6->setProperty( "text", tr( "Maximale Gegner in der Spieler gegen Spielerstatistik :" ) );

    CheckPlayers = new QCheckBox( GroupBox6, "CheckPlayers" );
    CheckPlayers->setGeometry( QRect( 400, 40, 290, 17 ) ); 
    QFont CheckPlayers_font(  CheckPlayers->font() );
    CheckPlayers_font.setFamily( "Tahoma" );
    CheckPlayers->setFont( CheckPlayers_font ); 
    CheckPlayers->setProperty( "text", tr( "Spieleranzahl egal" ) );

    GroupBox9 = new QGroupBox( Voraussetzungen, "GroupBox9" );
    GroupBox9->setGeometry( QRect( 0, 30, 700, 110 ) ); 
    GroupBox9->setProperty( "title", tr( "Minimale Voraussetzungen" ) );

    MinSkill = new QLineEdit( GroupBox9, "MinSkill" );
    MinSkill->setGeometry( QRect( 320, 20, 60, 22 ) ); 
    MinSkill->setProperty( "text", tr( "0" ) );
    MinSkill->setProperty( "maxLength", 4 );

    MinKills = new QLineEdit( GroupBox9, "MinKills" );
    MinKills->setGeometry( QRect( 320, 50, 60, 22 ) ); 
    MinKills->setProperty( "text", tr( "0" ) );
    MinKills->setProperty( "maxLength", 4 );

    MinDeaths = new QLineEdit( GroupBox9, "MinDeaths" );
    MinDeaths->setGeometry( QRect( 320, 80, 61, 22 ) ); 
    MinDeaths->setProperty( "text", tr( "0" ) );
    MinDeaths->setProperty( "maxLength", 4 );

    TextLabel4_2 = new QLabel( GroupBox9, "TextLabel4_2" );
    TextLabel4_2->setGeometry( QRect( 10, 20, 250, 16 ) ); 
    QFont TextLabel4_2_font(  TextLabel4_2->font() );
    TextLabel4_2_font.setFamily( "Tahoma" );
    TextLabel4_2->setFont( TextLabel4_2_font ); 
    TextLabel4_2->setProperty( "text", tr( "Minimaler Skill :" ) );

    TextLabel5_2 = new QLabel( GroupBox9, "TextLabel5_2" );
    TextLabel5_2->setGeometry( QRect( 10, 50, 280, 16 ) ); 
    QFont TextLabel5_2_font(  TextLabel5_2->font() );
    TextLabel5_2_font.setFamily( "Tahoma" );
    TextLabel5_2->setFont( TextLabel5_2_font ); 
    TextLabel5_2->setProperty( "text", tr( "Minimale Kills :" ) );

    TextLabel6_2 = new QLabel( GroupBox9, "TextLabel6_2" );
    TextLabel6_2->setGeometry( QRect( 10, 80, 280, 16 ) ); 
    QFont TextLabel6_2_font(  TextLabel6_2->font() );
    TextLabel6_2_font.setFamily( "Tahoma" );
    TextLabel6_2->setFont( TextLabel6_2_font ); 
    TextLabel6_2->setProperty( "text", tr( "Minimale Deaths :" ) );

    CheckDeaths = new QCheckBox( GroupBox9, "CheckDeaths" );
    CheckDeaths->setGeometry( QRect( 400, 80, 290, 17 ) ); 
    QFont CheckDeaths_font(  CheckDeaths->font() );
    CheckDeaths_font.setFamily( "Tahoma" );
    CheckDeaths->setFont( CheckDeaths_font ); 
    CheckDeaths->setProperty( "text", tr( "Deathsanzahl egal" ) );

    CheckKills = new QCheckBox( GroupBox9, "CheckKills" );
    CheckKills->setGeometry( QRect( 400, 50, 290, 17 ) ); 
    QFont CheckKills_font(  CheckKills->font() );
    CheckKills_font.setFamily( "Tahoma" );
    CheckKills->setFont( CheckKills_font ); 
    CheckKills->setProperty( "text", tr( "Killanzahl egal" ) );

    CheckSkill = new QCheckBox( GroupBox9, "CheckSkill" );
    CheckSkill->setGeometry( QRect( 400, 20, 290, 17 ) ); 
    QFont CheckSkill_font(  CheckSkill->font() );
    CheckSkill_font.setFamily( "Tahoma" );
    CheckSkill->setFont( CheckSkill_font ); 
    CheckSkill->setProperty( "text", tr( "Skill egal" ) );

    TextLabel3_3 = new QLabel( Voraussetzungen, "TextLabel3_3" );
    TextLabel3_3->setGeometry( QRect( 10, 10, 680, 16 ) ); 
    QFont TextLabel3_3_font(  TextLabel3_3->font() );
    TextLabel3_3_font.setFamily( "Tahoma" );
    TextLabel3_3->setFont( TextLabel3_3_font ); 
    TextLabel3_3->setProperty( "text", tr( QString::fromUtf8( "Hier können Sie die Voraussetzungen angeben, damit ein Spieler in die Liste aufgenommen wird!" ) ) );

    PushButton16 = new QPushButton( Voraussetzungen, "PushButton16" );
    PushButton16->setGeometry( QRect( 8, 267, 140, 31 ) ); 
    PushButton16->setProperty( "text", tr( "Einstellungen speichern" ) );
    Einstellungen->insertTab( Voraussetzungen, tr( "Voraussetzungen" ) );

    Names = new QWidget( Einstellungen, "Names" );

    GroupBox7 = new QGroupBox( Names, "GroupBox7" );
    GroupBox7->setGeometry( QRect( 0, 0, 700, 390 ) ); 
    GroupBox7->setProperty( "title", tr( QString::fromUtf8( "Ausschließen" ) ) );

    TextLabel2_6 = new QLabel( GroupBox7, "TextLabel2_6" );
    TextLabel2_6->setGeometry( QRect( 10, 100, 400, 16 ) ); 
    TextLabel2_6->setProperty( "text", tr( "Hier sehen Sie welche namen bis jetzt eingegeben wurden." ) );

    TextLabel1_9 = new QLabel( GroupBox7, "TextLabel1_9" );
    TextLabel1_9->setGeometry( QRect( 10, 20, 590, 50 ) ); 
    TextLabel1_9->setProperty( "text", tr( QString::fromUtf8( "Geben Sie in das Eingabefeld den Namen oder den Namensausdruck ein und drücken Sie auf den Knopf Eingabe. \nAlle Spieler die davon betroffen sind werden nicht in der Spielerstatistik angezeigt. \nInformationen zu den Sonderzeichen die benutzt werden können finden Sie in der readme.html" ) ) );

    KillNames = new QPushButton( GroupBox7, "KillNames" );
    KillNames->setGeometry( QRect( 290, 320, 131, 30 ) ); 
    KillNames->setProperty( "text", tr( QString::fromUtf8( "Liste löschen" ) ) );

    KillCurrentName = new QPushButton( GroupBox7, "KillCurrentName" );
    KillCurrentName->setGeometry( QRect( 120, 320, 160, 30 ) ); 
    KillCurrentName->setProperty( "text", tr( QString::fromUtf8( "Ausgewälte Namen löschen" ) ) );

    SaveNames = new QPushButton( GroupBox7, "SaveNames" );
    SaveNames->setGeometry( QRect( 10, 320, 101, 30 ) ); 
    SaveNames->setProperty( "text", tr( "Namen speichern" ) );

    EingabeButton = new QPushButton( GroupBox7, "EingabeButton" );
    EingabeButton->setGeometry( QRect( 250, 70, 100, 20 ) ); 
    EingabeButton->setProperty( "text", tr( "Eingabe" ) );

    NameEdit = new QLineEdit( GroupBox7, "NameEdit" );
    NameEdit->setGeometry( QRect( 10, 70, 231, 22 ) ); 

    Namen = new QListBox( GroupBox7, "Namen" );
    Namen->setGeometry( QRect( 10, 120, 460, 190 ) ); 
    Namen->setProperty( "selectionMode", (int)QListBox::Extended );
    Einstellungen->insertTab( Names, tr( QString::fromUtf8( "Namen ausschließen" ) ) );

    Sonstiges = new QWidget( Einstellungen, "Sonstiges" );

    GroupBox8 = new QGroupBox( Sonstiges, "GroupBox8" );
    GroupBox8->setGeometry( QRect( 0, 0, 680, 470 ) ); 
    GroupBox8->setProperty( "title", tr( "Sonstige Einstellungen" ) );

    TextLabel1_10 = new QLabel( GroupBox8, "TextLabel1_10" );
    TextLabel1_10->setGeometry( QRect( 10, 20, 660, 40 ) ); 
    TextLabel1_10->setProperty( "text", tr( QString::fromUtf8( "Wenn dieser Haken gesetzt ist, werden Spieler die nicht den Vorrausetzungen entsprechen komplett gelöscht.\nAnsonsten sind sie noch in Auszeichnungen zu sehen, es wird nur keine Spielerdatei erstellt." ) ) );

    TextLabel2_2_2 = new QLabel( GroupBox8, "TextLabel2_2_2" );
    TextLabel2_2_2->setGeometry( QRect( 10, 110, 630, 21 ) ); 
    TextLabel2_2_2->setProperty( "text", tr( QString::fromUtf8( "Wenn Sie die Mapstatistik nicht interessiert, können Sie sie hier ausstellen." ) ) );

    HideMaps = new QCheckBox( GroupBox8, "HideMaps" );
    HideMaps->setGeometry( QRect( 10, 140, 270, 21 ) ); 
    HideMaps->setProperty( "text", tr( "Maps ausschalten" ) );

    DeleteUnranked = new QCheckBox( GroupBox8, "DeleteUnranked" );
    DeleteUnranked->setGeometry( QRect( 10, 70, 330, 21 ) ); 
    DeleteUnranked->setProperty( "text", tr( QString::fromUtf8( "Nicht qualifizierte Spieler löschen" ) ) );
    DeleteUnranked->setProperty( "checked", QVariant( TRUE, 0 ) );
    Einstellungen->insertTab( Sonstiges, tr( "Sonstige Einstellungen" ) );

    CombinePage = new QWidget( Einstellungen, "CombinePage" );

    GroupBox9_2 = new QGroupBox( CombinePage, "GroupBox9_2" );
    GroupBox9_2->setGeometry( QRect( 0, 0, 680, 410 ) ); 
    GroupBox9_2->setProperty( "title", tr( "Spieler kombinieren" ) );

    TextLabel2_7 = new QLabel( GroupBox9_2, "TextLabel2_7" );
    TextLabel2_7->setGeometry( QRect( 150, 80, 20, 21 ) ); 
    TextLabel2_7->setProperty( "text", tr( "+" ) );

    JoinPlayer = new QLineEdit( GroupBox9_2, "JoinPlayer" );
    JoinPlayer->setGeometry( QRect( 170, 80, 130, 22 ) ); 

    BasePlayer = new QLineEdit( GroupBox9_2, "BasePlayer" );
    BasePlayer->setGeometry( QRect( 10, 80, 130, 22 ) ); 

    TextLabel3_4 = new QLabel( GroupBox9_2, "TextLabel3_4" );
    TextLabel3_4->setGeometry( QRect( 20, 110, 330, 21 ) ); 
    TextLabel3_4->setProperty( "text", tr( QString::fromUtf8( "Bis jetzt zusammen gefügte Spieler :" ) ) );

    SavePlayersButton = new QPushButton( GroupBox9_2, "SavePlayersButton" );
    SavePlayersButton->setGeometry( QRect( 10, 360, 101, 31 ) ); 
    SavePlayersButton->setProperty( "text", tr( "Spieler speichern" ) );

    DeleteCombinedPlayersButton = new QPushButton( GroupBox9_2, "DeleteCombinedPlayersButton" );
    DeleteCombinedPlayersButton->setGeometry( QRect( 120, 360, 160, 31 ) ); 
    DeleteCombinedPlayersButton->setProperty( "text", tr( QString::fromUtf8( "Ausgewählte Spieler löschen" ) ) );

    ClearCombinedPlayersButton = new QPushButton( GroupBox9_2, "ClearCombinedPlayersButton" );
    ClearCombinedPlayersButton->setGeometry( QRect( 290, 360, 111, 31 ) ); 
    ClearCombinedPlayersButton->setProperty( "text", tr( QString::fromUtf8( "Liste löschen" ) ) );

    CombinedPlayers = new QListBox( GroupBox9_2, "CombinedPlayers" );
    CombinedPlayers->setGeometry( QRect( 10, 140, 600, 200 ) ); 
    CombinedPlayers->setProperty( "selectionMode", (int)QListBox::Extended );

    TextLabel1_11 = new QLabel( GroupBox9_2, "TextLabel1_11" );
    TextLabel1_11->setGeometry( QRect( 9, 19, 650, 50 ) ); 
    TextLabel1_11->setProperty( "text", tr( QString::fromUtf8( "Falls Sie zwei Spieler zusammenfügen möchten, dann tragen Sie bitte in das erste Eingabefeld den Namen ein, \nder weiterbestehen soll und in das zweite Eingabefeld den Spielernamen, dessen Werte dazuaddiert werden sollen." ) ) );

    CombineButton = new QPushButton( GroupBox9_2, "CombineButton" );
    CombineButton->setGeometry( QRect( 320, 80, 101, 20 ) ); 
    CombineButton->setProperty( "text", tr( "Kombinieren" ) );
    Einstellungen->insertTab( CombinePage, tr( "Spieler kombinieren" ) );

    // signals and slots connections
    connect( SelectLogFilesButton, SIGNAL( clicked() ), this, SLOT( SelectLogFiles() ) );
    connect( OutputDirButton, SIGNAL( clicked() ), this, SLOT( SelectOutputDir() ) );
    connect( PushButton4, SIGNAL( clicked() ), this, SLOT( CreateHTML() ) );
    connect( ColorDefault, SIGNAL( clicked() ), this, SLOT( ResetColors() ) );
    connect( ColorSave, SIGNAL( clicked() ), this, SLOT( SaveColors() ) );
    connect( PushButton6, SIGNAL( clicked() ), this, SLOT( SelectLogDir() ) );
    connect( CheckTimer, SIGNAL( stateChanged(int) ), this, SLOT( TimerEnabled() ) );
    connect( PushButton7, SIGNAL( clicked() ), this, SLOT( DelFiles() ) );
    connect( EingabeButton, SIGNAL( clicked() ), this, SLOT( NewNameTag() ) );
    connect( SaveNames, SIGNAL( clicked() ), this, SLOT( SaveNameTags() ) );
    connect( KillCurrentName, SIGNAL( clicked() ), this, SLOT( DeleteNameTag() ) );
    connect( KillNames, SIGNAL( clicked() ), this, SLOT( DeleteAllNameTags() ) );
    connect( CombineButton, SIGNAL( clicked() ), this, SLOT( Combine() ) );
    connect( SavePlayersButton, SIGNAL( clicked() ), this, SLOT( SavePlayers() ) );
    connect( ClearCombinedPlayersButton, SIGNAL( clicked() ), this, SLOT( ClearCombinedPlayers() ) );
    connect( DeleteCombinedPlayersButton, SIGNAL( clicked() ), this, SLOT( DeleteCombinedPlayers() ) );
    connect( PushButton16, SIGNAL( clicked() ), this, SLOT( SaveColors() ) );

    // tab order
    setTabOrder( ColorDefault, ColorSave );
    setTabOrder( ColorSave, UnEvenBG );
    setTabOrder( UnEvenBG, EvenBG );
    setTabOrder( EvenBG, HTMLBG );
    setTabOrder( HTMLBG, TableBG );
    setTabOrder( TableBG, TableCaptionBG );
    setTabOrder( TableCaptionBG, TableFontColor );
    setTabOrder( TableFontColor, FontColor );
    setTabOrder( FontColor, LinkColor );
    setTabOrder( LinkColor, HoverLinkColor );
    setTabOrder( HoverLinkColor, Einstellungen );
    setTabOrder( Einstellungen, PushButton4 );
    setTabOrder( PushButton4, LogDateienListe );
    setTabOrder( LogDateienListe, OutputDirButton );
    setTabOrder( OutputDirButton, SelectLogFilesButton );
    setTabOrder( SelectLogFilesButton, PushButton6 );
    setTabOrder( PushButton6, MinKills );
    setTabOrder( MinKills, MinDeaths );
    setTabOrder( MinDeaths, MinSkill );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
HeldenStats::~HeldenStats()
{
    // no need to delete child widgets, Qt does it all for us
}

/*  
 *  Main event handler. Reimplemented to handle application
 *  font changes
 */
bool HeldenStats::event( QEvent* ev )
{
    bool ret = QDialog::event( ev ); 
    if ( ev->type() == QEvent::ApplicationFontChange ) {
	QFont TextLabel1_font(  TextLabel1->font() );
	TextLabel1_font.setFamily( "Tahoma" );
	TextLabel1->setFont( TextLabel1_font ); 
	QFont TextLabel2_font(  TextLabel2->font() );
	TextLabel2_font.setFamily( "Tahoma" );
	TextLabel2->setFont( TextLabel2_font ); 
	QFont CurrentDirLabel_font(  CurrentDirLabel->font() );
	CurrentDirLabel_font.setFamily( "Tahoma" );
	CurrentDirLabel->setFont( CurrentDirLabel_font ); 
	QFont TextLabel1_7_font(  TextLabel1_7->font() );
	TextLabel1_7_font.setFamily( "Tahoma" );
	TextLabel1_7->setFont( TextLabel1_7_font ); 
	QFont TimerLabel_font(  TimerLabel->font() );
	TimerLabel_font.setFamily( "Tahoma" );
	TimerLabel->setFont( TimerLabel_font ); 
	QFont CheckTimer_font(  CheckTimer->font() );
	CheckTimer_font.setFamily( "Tahoma" );
	CheckTimer->setFont( CheckTimer_font ); 
	QFont TextLabel7_font(  TextLabel7->font() );
	TextLabel7_font.setFamily( "Tahoma" );
	TextLabel7->setFont( TextLabel7_font ); 
	QFont TextLabel6_font(  TextLabel6->font() );
	TextLabel6_font.setFamily( "Tahoma" );
	TextLabel6->setFont( TextLabel6_font ); 
	QFont TextLabel3_2_font(  TextLabel3_2->font() );
	TextLabel3_2_font.setFamily( "Tahoma" );
	TextLabel3_2->setFont( TextLabel3_2_font ); 
	QFont TextLabel1_3_font(  TextLabel1_3->font() );
	TextLabel1_3_font.setFamily( "Tahoma" );
	TextLabel1_3->setFont( TextLabel1_3_font ); 
	QFont TextLabel2_4_font(  TextLabel2_4->font() );
	TextLabel2_4_font.setFamily( "Tahoma" );
	TextLabel2_4->setFont( TextLabel2_4_font ); 
	QFont TextLabel1_2_font(  TextLabel1_2->font() );
	TextLabel1_2_font.setFamily( "Tahoma" );
	TextLabel1_2->setFont( TextLabel1_2_font ); 
	QFont TextLabel2_3_font(  TextLabel2_3->font() );
	TextLabel2_3_font.setFamily( "Tahoma" );
	TextLabel2_3->setFont( TextLabel2_3_font ); 
	QFont TextLabel5_font(  TextLabel5->font() );
	TextLabel5_font.setFamily( "Tahoma" );
	TextLabel5->setFont( TextLabel5_font ); 
	QFont TextLabel2_2_font(  TextLabel2_2->font() );
	TextLabel2_2_font.setFamily( "Tahoma" );
	TextLabel2_2->setFont( TextLabel2_2_font ); 
	QFont TextLabel1_5_font(  TextLabel1_5->font() );
	TextLabel1_5_font.setFamily( "Tahoma" );
	TextLabel1_5->setFont( TextLabel1_5_font ); 
	QFont TextLabel4_font(  TextLabel4->font() );
	TextLabel4_font.setFamily( "Tahoma" );
	TextLabel4->setFont( TextLabel4_font ); 
	QFont TextLabel1_8_font(  TextLabel1_8->font() );
	TextLabel1_8_font.setFamily( "Tahoma" );
	TextLabel1_8->setFont( TextLabel1_8_font ); 
	QFont TextLabel1_8_2_font(  TextLabel1_8_2->font() );
	TextLabel1_8_2_font.setFamily( "Tahoma" );
	TextLabel1_8_2->setFont( TextLabel1_8_2_font ); 
	QFont TextLabel5_3_font(  TextLabel5_3->font() );
	TextLabel5_3_font.setFamily( "Tahoma" );
	TextLabel5_3->setFont( TextLabel5_3_font ); 
	QFont TextLabel6_3_font(  TextLabel6_3->font() );
	TextLabel6_3_font.setFamily( "Tahoma" );
	TextLabel6_3->setFont( TextLabel6_3_font ); 
	QFont TextLabel7_2_font(  TextLabel7_2->font() );
	TextLabel7_2_font.setFamily( "Tahoma" );
	TextLabel7_2->setFont( TextLabel7_2_font ); 
	QFont TextLabel8_font(  TextLabel8->font() );
	TextLabel8_font.setFamily( "Tahoma" );
	TextLabel8->setFont( TextLabel8_font ); 
	QFont TextLabel2_5_font(  TextLabel2_5->font() );
	TextLabel2_5_font.setFamily( "Tahoma" );
	TextLabel2_5->setFont( TextLabel2_5_font ); 
	QFont TextLabel1_4_font(  TextLabel1_4->font() );
	TextLabel1_4_font.setFamily( "Tahoma" );
	TextLabel1_4->setFont( TextLabel1_4_font ); 
	QFont TextLabel1_6_font(  TextLabel1_6->font() );
	TextLabel1_6_font.setFamily( "Tahoma" );
	TextLabel1_6->setFont( TextLabel1_6_font ); 
	QFont CheckPlayers_font(  CheckPlayers->font() );
	CheckPlayers_font.setFamily( "Tahoma" );
	CheckPlayers->setFont( CheckPlayers_font ); 
	QFont TextLabel4_2_font(  TextLabel4_2->font() );
	TextLabel4_2_font.setFamily( "Tahoma" );
	TextLabel4_2->setFont( TextLabel4_2_font ); 
	QFont TextLabel5_2_font(  TextLabel5_2->font() );
	TextLabel5_2_font.setFamily( "Tahoma" );
	TextLabel5_2->setFont( TextLabel5_2_font ); 
	QFont TextLabel6_2_font(  TextLabel6_2->font() );
	TextLabel6_2_font.setFamily( "Tahoma" );
	TextLabel6_2->setFont( TextLabel6_2_font ); 
	QFont CheckDeaths_font(  CheckDeaths->font() );
	CheckDeaths_font.setFamily( "Tahoma" );
	CheckDeaths->setFont( CheckDeaths_font ); 
	QFont CheckKills_font(  CheckKills->font() );
	CheckKills_font.setFamily( "Tahoma" );
	CheckKills->setFont( CheckKills_font ); 
	QFont CheckSkill_font(  CheckSkill->font() );
	CheckSkill_font.setFamily( "Tahoma" );
	CheckSkill->setFont( CheckSkill_font ); 
	QFont TextLabel3_3_font(  TextLabel3_3->font() );
	TextLabel3_3_font.setFamily( "Tahoma" );
	TextLabel3_3->setFont( TextLabel3_3_font ); 
    }
    return ret;
}

void HeldenStats::Combine()
{
    qWarning( "HeldenStats::Combine(): Not implemented yet!" );
}

void HeldenStats::CreateHTML()
{
    qWarning( "HeldenStats::CreateHTML(): Not implemented yet!" );
}

void HeldenStats::DelFiles()
{
    qWarning( "HeldenStats::DelFiles(): Not implemented yet!" );
}

void HeldenStats::DeleteAllNameTags()
{
    qWarning( "HeldenStats::DeleteAllNameTags(): Not implemented yet!" );
}

void HeldenStats::DeleteCombinedPlayers()
{
    qWarning( "HeldenStats::DeleteCombinedPlayers(): Not implemented yet!" );
}

void HeldenStats::DeleteNameTag()
{
    qWarning( "HeldenStats::DeleteNameTag(): Not implemented yet!" );
}

void HeldenStats::NewNameTag()
{
    qWarning( "HeldenStats::NewNameTag(): Not implemented yet!" );
}

void HeldenStats::ResetColors()
{
    qWarning( "HeldenStats::ResetColors(): Not implemented yet!" );
}

void HeldenStats::SaveColors()
{
    qWarning( "HeldenStats::SaveColors(): Not implemented yet!" );
}

void HeldenStats::SaveNameTags()
{
    qWarning( "HeldenStats::SaveNameTags(): Not implemented yet!" );
}

void HeldenStats::SavePlayers()
{
    qWarning( "HeldenStats::SavePlayers(): Not implemented yet!" );
}

void HeldenStats::SelectLogDir()
{
    qWarning( "HeldenStats::SelectLogDir(): Not implemented yet!" );
}

void HeldenStats::SelectLogFiles()
{
    qWarning( "HeldenStats::SelectLogFiles(): Not implemented yet!" );
}

void HeldenStats::SelectOutputDir()
{
    qWarning( "HeldenStats::SelectOutputDir(): Not implemented yet!" );
}

void HeldenStats::TimerEnabled()
{
    qWarning( "HeldenStats::TimerEnabled(): Not implemented yet!" );
}

void HeldenStats::ClearCombinedPlayers()
{
    qWarning( "HeldenStats::ClearCombinedPlayers(): Not implemented yet!" );
}

