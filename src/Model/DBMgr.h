#ifndef DBMGR_H
#define DBMGR_H

#include <QSqlDatabase>


namespace MyNote {

struct User {
    int Id;
    QString Name;
    QString Avatar;
    QString Passwd;
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



private:
    QSqlDatabase db;
};

}


#endif // DBMGR_H
