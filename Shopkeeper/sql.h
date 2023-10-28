#ifndef SQL_H
#define SQL_H

#include "book.h"


#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTreeView>
#include <QStandardItemModel>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>
class Sql : public QObject
{
    Q_OBJECT
public:
    explicit Sql(QObject *parent = nullptr);
    QSqlTableModel *booksModel,*accoutModel,*userModel,*commentModel;
    QStandardItemModel *commentTreeModel;
    bool isSubmitting = false;
    QString storeProfile;

signals:
    void inNewBookSucceed(const Book &book);
    void inNewBookFailed();
    void selectAllBooksFinished();
    void selectAllAccountFinished();
    void selectAllUsersFinished();
    void postNewsSucceed();
    void postNewsFailed();
    void insertCommentSucceed();
    void insertCommentFailed();

public slots:
    void inNewBook(const Book &book); // 进新书
    void inOldBook(const Book &book); //进旧书
    bool sellBook(const Book &book);
    //    void addAccount(const Book &book); //计入账目 改用数据库触发器实现
    bool commitDB(QSqlQuery *query);
    void selectAllBooks();
    void selectAllcomments();
    void selectAllAccounts();
    void selectAllUsers();
    void postNews(const QString &news);
    void insertComment(const qint32 &id,const QString &content);

    bool addUser(const qint64 &id,const QString &name,const QString &password);
    bool changeUserPassword(const qint64 &id,const QString &newPassword,const QString &oldPassword);
    bool changeUserName(const qint64 &id,const QString &password ,const QString &name);
    QString login(const qint64& id,const QString &password);
    QJsonArray selectAllNews();
    QJsonArray selectCommentByUserId(const qint64 &userId);
    QJsonArray selectCommentByReplyId(const qint64 &replyId);
    bool insertUserComment(const qint64 &userId,const QString &content);
private:
    void initBookModel();
    void initAccountModel();
    void initUserModel();
    void initCommentModel();
    QSqlDatabase m_db;
    QTimer timer;


    //    QTable
};

#endif // SQL_H
