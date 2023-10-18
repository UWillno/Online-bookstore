#ifndef SQL_H
#define SQL_H

#include "book.h"

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

class Sql : public QObject
{
    Q_OBJECT
public:
    explicit Sql(QObject *parent = nullptr);
    QSqlTableModel *booksModel,*accoutModel,*userModel;
    bool isSubmitting = false;
signals:
    void inNewBookSucceed(const Book &book);
    void inNewBookFailed();
    void selectAllBooksFinished();
    void selectAllAccountFinished();
    void selectAllUsersFinished();
    void postNewsSucceed();
    void postNewsFailed();

public slots:
    void inNewBook(const Book &book); // 进新书
    void inOldBook(const Book &book); //进旧书
    //    void addAccount(const Book &book); //计入账目 改用数据库触发器实现
    bool commitDB(QSqlQuery *query);
    void selectAllBooks();
    void selectAllAccounts();
    void selectAllUsers();
    void postNews(const QString &news);
private:
    void initBookModel();
    void initAccountModel();
    void initUserModel();
    QSqlDatabase m_db;

    //    QTable
};

#endif // SQL_H
