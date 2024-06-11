#ifndef DBMGR_H
#define DBMGR_H

#include <QSqlDatabase>


namespace MyNote {

struct User {
    int Id;
    QString Name;
    QString Avatar;
    QString Passwd;
    int SettingId;
};

struct Note {
    int Id;
    QString Name;
    int Type;	// 笔记类型：文件笔记
    QString CreateTime;
    QString UpdateTime;
    QString Path;
};

struct Setting {
    int Id;
    QString Name;
    int IsOpenLastNote;
    int IsAutoLogin;
};

class DBMgr {
public:
    static DBMgr *GetInstance();
    ~DBMgr();

    void InitDB();
    void Open();
    void Close();

    int UserAdd(User *user);
    int UserUpdate();
    int UserDel();
    int UserQuery();


    int NoteAdd();

    Setting GetCurSetting();



private:
    QSqlDatabase db;
};

}


#endif // DBMGR_H
