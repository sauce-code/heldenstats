/****************************************************************************
** MyHeldenStats meta object code from reading C++ file 'MyHeldenStatsDialog.hpp'
**
** Created: Sat Oct 27 18:40:10 2001
**      by: The Qt MOC ($Id: //depot/qt/main/src/moc/moc.y#178 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_MyHeldenStats
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 8
#elif Q_MOC_OUTPUT_REVISION != 8
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "MyHeldenStatsDialog.hpp"

#include <QMetaObject>
#include <QApplication>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *MyHeldenStats::className() const
{
    return "MyHeldenStats";
}

QMetaObject *MyHeldenStats::metaObj = 0;

void MyHeldenStats::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(HeldenStats::className(), "HeldenStats") != 0 )
	badSuperclassWarning("MyHeldenStats","HeldenStats");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION
QString MyHeldenStats::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("MyHeldenStats",s);
}

#endif // QT_NO_TRANSLATION
QMetaObject* MyHeldenStats::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) HeldenStats::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void(MyHeldenStats::*m1_t0)();
    typedef void(MyHeldenStats::*m1_t1)();
    typedef void(MyHeldenStats::*m1_t2)();
    typedef void(MyHeldenStats::*m1_t3)();
    typedef void(MyHeldenStats::*m1_t4)();
    typedef void(MyHeldenStats::*m1_t5)();
    typedef void(MyHeldenStats::*m1_t6)();
    typedef void(MyHeldenStats::*m1_t7)();
    typedef void(MyHeldenStats::*m1_t8)();
    typedef void(MyHeldenStats::*m1_t9)();
    typedef void(MyHeldenStats::*m1_t10)();
    typedef void(MyHeldenStats::*m1_t11)();
    typedef void(MyHeldenStats::*m1_t12)();
    typedef void(MyHeldenStats::*m1_t13)();
    typedef void(MyHeldenStats::*m1_t14)();
    typedef void(MyHeldenStats::*m1_t15)();
    m1_t0 v1_0 = Q_AMPERSAND MyHeldenStats::Combine;
    m1_t1 v1_1 = Q_AMPERSAND MyHeldenStats::CreateHTML;
    m1_t2 v1_2 = Q_AMPERSAND MyHeldenStats::DelFiles;
    m1_t3 v1_3 = Q_AMPERSAND MyHeldenStats::DeleteAllNameTags;
    m1_t4 v1_4 = Q_AMPERSAND MyHeldenStats::DeleteCombinedPlayers;
    m1_t5 v1_5 = Q_AMPERSAND MyHeldenStats::DeleteNameTag;
    m1_t6 v1_6 = Q_AMPERSAND MyHeldenStats::NewNameTag;
    m1_t7 v1_7 = Q_AMPERSAND MyHeldenStats::ResetColors;
    m1_t8 v1_8 = Q_AMPERSAND MyHeldenStats::SaveColors;
    m1_t9 v1_9 = Q_AMPERSAND MyHeldenStats::SaveNameTags;
    m1_t10 v1_10 = Q_AMPERSAND MyHeldenStats::SavePlayers;
    m1_t11 v1_11 = Q_AMPERSAND MyHeldenStats::SelectLogDir;
    m1_t12 v1_12 = Q_AMPERSAND MyHeldenStats::SelectLogFiles;
    m1_t13 v1_13 = Q_AMPERSAND MyHeldenStats::SelectOutputDir;
    m1_t14 v1_14 = Q_AMPERSAND MyHeldenStats::TimerEnabled;
    m1_t15 v1_15 = Q_AMPERSAND MyHeldenStats::ClearCombinedPlayers;
    QMetaData *slot_tbl = QMetaObject::new_metadata(16);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(16);
    slot_tbl[0].name = "Combine()";
    slot_tbl[0].ptr = *((QMember*)&v1_0);
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "CreateHTML()";
    slot_tbl[1].ptr = *((QMember*)&v1_1);
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "DelFiles()";
    slot_tbl[2].ptr = *((QMember*)&v1_2);
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "DeleteAllNameTags()";
    slot_tbl[3].ptr = *((QMember*)&v1_3);
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "DeleteCombinedPlayers()";
    slot_tbl[4].ptr = *((QMember*)&v1_4);
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "DeleteNameTag()";
    slot_tbl[5].ptr = *((QMember*)&v1_5);
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "NewNameTag()";
    slot_tbl[6].ptr = *((QMember*)&v1_6);
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "ResetColors()";
    slot_tbl[7].ptr = *((QMember*)&v1_7);
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "SaveColors()";
    slot_tbl[8].ptr = *((QMember*)&v1_8);
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "SaveNameTags()";
    slot_tbl[9].ptr = *((QMember*)&v1_9);
    slot_tbl_access[9] = QMetaData::Public;
    slot_tbl[10].name = "SavePlayers()";
    slot_tbl[10].ptr = *((QMember*)&v1_10);
    slot_tbl_access[10] = QMetaData::Public;
    slot_tbl[11].name = "SelectLogDir()";
    slot_tbl[11].ptr = *((QMember*)&v1_11);
    slot_tbl_access[11] = QMetaData::Public;
    slot_tbl[12].name = "SelectLogFiles()";
    slot_tbl[12].ptr = *((QMember*)&v1_12);
    slot_tbl_access[12] = QMetaData::Public;
    slot_tbl[13].name = "SelectOutputDir()";
    slot_tbl[13].ptr = *((QMember*)&v1_13);
    slot_tbl_access[13] = QMetaData::Public;
    slot_tbl[14].name = "TimerEnabled()";
    slot_tbl[14].ptr = *((QMember*)&v1_14);
    slot_tbl_access[14] = QMetaData::Public;
    slot_tbl[15].name = "ClearCombinedPlayers()";
    slot_tbl[15].ptr = *((QMember*)&v1_15);
    slot_tbl_access[15] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"MyHeldenStats", "HeldenStats",
	slot_tbl, 16,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}
