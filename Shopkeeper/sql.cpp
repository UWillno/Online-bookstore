#include "sql.h"

Sql::Sql(QObject *parent)
    : QObject{parent}
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("");
    m_db.setPort(3306);
    m_db.setDatabaseName("bookstore");
    m_db.setUserName("root");
    m_db.setPassword("123456");
    m_db.open();
    initBookModel();
    initAccountModel();
    initUserModel();
    //    connect(this,&Sql::inNewBookSucceed,this,&Sql::addAccount);

}

void Sql::inNewBook(const Book &book)
{
    //    qInfo() << book.ISBN() << book.name() << book.author()
    //            <<book.time().toString("yyyyMMdd") <<book.type() <<book.count()
    //            <<book.price() <<book.profile();
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("INSERT INTO book VALUES (:isbn,:name,:author,:time,:type,:count,:price,:profile);");
    query.bindValue(":isbn",book.ISBN());
    query.bindValue(":name",book.name());
    query.bindValue(":author",book.author());
    query.bindValue(":time",book.time().toString("yyyyMMdd"));
    query.bindValue(":type",book.type());
    query.bindValue(":count",book.count());
    query.bindValue(":price",book.price());
    query.bindValue(":profile",book.profile());
    query.exec();
    //    qInfo () << commitDB(&query);
    commitDB(&query)?
        emit inNewBookSucceed(book):
        emit inNewBookFailed();
}

void Sql::inOldBook(const Book &book)
{
    QSqlQuery query  = QSqlQuery(m_db);
    query.prepare("UPDATE book SET count = count + :count WHERE ISBN = :ISBN;");
    query.bindValue(":ISBN",book.ISBN());
    query.bindValue(":count",book.count());
    query.exec();
    query.numRowsAffected() !=0 ? emit inNewBookSucceed(book):
        emit inNewBookFailed();

}

//void Sql::addAccount(const Book &book)
//{
//    QSqlQuery query = QSqlQuery(m_db);
//    query.prepare("INSERT INTO account VALUES (NULL,:ISBN,:delta,NOW());");
//    query.bindValue(":ISBN",book.ISBN());
//    query.bindValue(":delta",book.count());
////    query.bindValue(":userId",book.userId());
//    query.exec();
//}

bool Sql::commitDB(QSqlQuery *query)
{
    if (query->isActive())
    {
        m_db.commit();
        return true;
    }
    else
    {
        m_db.rollback();
        return false;
    }
}

void Sql::selectAllBooks()
{
    booksModel->select();
    //    emit selectAllBooksFinished();
}

void Sql::selectAllAccounts()
{
    accoutModel->select();
    //    accoutModel->insertColumn(4);
    //    accoutModel->setHeaderData(4, Qt::Horizontal, "操作");
    //    emit selectAllAccountFinished();
}

void Sql::selectAllUsers()
{
    userModel->select();
}

void Sql::postNews(const QString &news)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("INSERT INTO news VALUES (NULL,NOW(),:news);");
    query.bindValue(":news",news);
    query.exec();
    commitDB(&query)?
        emit postNewsSucceed():
        emit postNewsFailed();

}

void Sql::initBookModel()
{
    booksModel =new QSqlTableModel(this,m_db);
    booksModel->setTable("book");
    booksModel->setHeaderData(0, Qt::Horizontal, "ISBN");
    booksModel->setHeaderData(1, Qt::Horizontal, "书名");
    booksModel->setHeaderData(2, Qt::Horizontal, "作者");
    booksModel->setHeaderData(3, Qt::Horizontal, "出版时间");
    booksModel->setHeaderData(4, Qt::Horizontal, "类型");
    booksModel->setHeaderData(5, Qt::Horizontal, "库存");
    booksModel->setHeaderData(6, Qt::Horizontal, "价格");
    booksModel->setHeaderData(7, Qt::Horizontal, "简介");
    connect(this,&Sql::inNewBookSucceed,this,&Sql::selectAllBooks);
    //    selectAllBooks();
}

void Sql::initAccountModel()
{
    accoutModel =new QSqlTableModel(this,m_db);
    accoutModel->setTable("account");
    accoutModel->setHeaderData(0, Qt::Horizontal, "id");
    accoutModel->setHeaderData(1, Qt::Horizontal, "ISBN");
    accoutModel->setHeaderData(2, Qt::Horizontal, "进出量");
    accoutModel->setHeaderData(3, Qt::Horizontal, "入账时间");
    connect(this,&Sql::inNewBookSucceed,this,&Sql::selectAllAccounts);
}

void Sql::initUserModel()
{
    userModel =new QSqlTableModel(this,m_db);
    userModel->setTable("user");
    userModel->setHeaderData(0, Qt::Horizontal, "手机号");
    userModel->setHeaderData(1, Qt::Horizontal, "用户名");
    userModel->setHeaderData(2, Qt::Horizontal, "密码");
}



