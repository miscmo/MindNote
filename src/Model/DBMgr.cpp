#include "DBMgr.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

namespace MyNote {

DBMgr *DBMgr::GetInstance() {
    static DBMgr mgr;

    return &mgr;
}

void DBMgr::InitDB() {

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("MyNoteDB.db");
        db.setUserName("myNote666");
        db.setPassword("142995");
    }

    db.open();

    // create table
    QSqlQuery sql_query;
    QString create_sql = "create table user (id int primary key, name varchar(255), avatar varchar(255), passwd varchar(255))";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table user." << sql_query.lastError();
    }
}

void DBMgr::Open() {
    db.open();
}

void DBMgr::Close() {
    db.close();
}

int DBMgr::UserAdd(User *user) {
    if (!db.isOpen()) {
        qDebug() << "Error: Failed to connect database" << db.lastError() << Qt::endl;
        return -1;
    }

    QSqlQuery sql_query;

    QString insert_sql = "insert into user (name, avatar, passwd) values (?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(user->Name);
    sql_query.addBindValue(user->Avatar);
    sql_query.addBindValue(user->Passwd);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
        return -1;
    }

    return 0;
}

DBMgr::~DBMgr() {
    Close();
}

}
