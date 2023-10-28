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
    initCommentModel();
    timer.setInterval(10000);
    connect(&timer,&QTimer::timeout,this,[&]{
        selectAllBooks();
        selectAllAccounts();
//        selectAllNews();
        selectAllUsers();
        selectAllcomments();
    });
    timer.start();

    //    connect(this,&Sql::inNewBookSucceed,this,&Sql::addAccount);
    //    connect(commentTreeModel,&QStandardItemModel::dataChanged,this,[&](const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles){
    //        qInfo() << topLeft;
    //        qInfo() << bottomRight;
    //        qInfo() << roles;
    //    });

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

bool Sql::sellBook(const Book &book)
{
    QSqlQuery query  = QSqlQuery(m_db);
    query.prepare("UPDATE book SET count = count + :count WHERE ISBN = :ISBN;");
    query.bindValue(":ISBN",book.ISBN());
    query.bindValue(":count",book.count());
    query.exec();
    return query.numRowsAffected() !=0;
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

void Sql::selectAllcomments()
{
    if(commentModel->select()){
        commentTreeModel->clear();
        commentTreeModel->setHorizontalHeaderLabels(QStringList("留言"));
        QHash<qint32,QStandardItem*> itemMap;
        QStandardItem* rootItem = commentTreeModel->invisibleRootItem();
        //    cModel->select();
        for (int row = 0; row <commentModel->rowCount(); ++row) {
            qint32 id = commentModel->index(row,0).data().toInt();
            qint32 replyId = commentModel->index(row,4).data().toInt();
            QString content = commentModel->index(row,3).data().toString();
            QString name = commentModel->index(row,2).data().toString();
            QStandardItem* item = new QStandardItem(content + "\t"+name);
            QVariantList data;
            data << content << commentModel->index(row,3);
            item->setData(data,Qt::UserRole); // 存储评论的 ID，以便稍后引用
            if(replyId == 0){
                itemMap[id] = item;
            }else if (itemMap.contains(replyId)){
                itemMap[replyId]->appendRow(item);
            }else{

            }
        }
        rootItem->appendRows(itemMap.values());
    }
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

void Sql::insertComment(const qint32 &id, const QString &content)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("INSERT INTO comment VALUES (NULL,44910244,NULL,:content,:id);");
    query.bindValue(":id",id);
    query.bindValue(":content",content);
    query.exec();
    commitDB(&query)?
        emit insertCommentSucceed() : emit insertCommentFailed();

}

bool Sql::addUser(const qint64 &id, const QString &name, const QString &password)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("INSERT INTO `user` VALUES(:id,:name,:password);");
    query.bindValue(":id",id);
    query.bindValue(":name",name);
    query.bindValue(":password",password);
    query.exec();
    return commitDB(&query);
}

bool Sql::changeUserPassword(const qint64 &id, const QString &newPassword,const QString &oldPassword)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("UPDATE `user` SET `password` = :newPassword WHERE id = :id AND `password` = :oldPassword;");
    query.bindValue(":id",id);
    query.bindValue(":newPassword",newPassword);
    query.bindValue(":oldPassword",oldPassword);
    query.exec();
    return query.numRowsAffected()!=0;
}

bool Sql::changeUserName(const qint64 &id, const QString &password,const QString &name)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("UPDATE `user` SET `name` = :name WHERE id = :id AND `password` = :password;");
    query.bindValue(":id",id);
    query.bindValue(":password",password);
    query.bindValue(":name",name);
    query.exec();
    return query.numRowsAffected()!=0;
}

QString Sql::login(const qint64 &id, const QString &password)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("SELECT name FROM `user` WHERE id = :id AND password = :password;");
    query.bindValue(":id",id);
    query.bindValue(":password",password);
    query.exec();
    if(query.next())
        return query.value(0).toString();
    return "";
}

QJsonArray Sql::selectAllNews()
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("SELECT * FROM `news` ORDER BY time DESC;");
    query.exec();
    QJsonArray array;
    while(query.next()){
        QJsonObject object;
        object.insert("id",query.value(0).toInt());
        object.insert("time",query.value(1).toDateTime().toString("yyyy-MM-dd"));
        object.insert("content",query.value(2).toString());
        array.append(object);
    }
    return array;
}

QJsonArray Sql::selectCommentByUserId(const qint64 &userId)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("SELECT * FROM `comment` WHERE userId = :userId ORDER BY id DESC;");
    query.bindValue(":userId",userId);
    query.exec();
    QJsonArray array {};
    while(query.next()){
        QJsonObject object;
        qint64 id = query.value(0).toLongLong();
//        qInfo() <<"id" << id;
        object.insert("id",id);
        object.insert("userId",query.value(1).toLongLong());
        object.insert("name",query.value(2).toString());
        object.insert("content",query.value(3).toString());
        object.insert("reply",selectCommentByReplyId(id));
        array.append(object);
        qInfo() << object;
    }
    return array;
}

QJsonArray Sql::selectCommentByReplyId(const qint64 &replyId)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("SELECT * FROM `comment` WHERE replyId = :replyId ORDER BY id DESC;");
    query.bindValue(":replyId",replyId);
    query.exec();
    QJsonArray array {};
    while(query.next()){
        QJsonObject object;
        object.insert("id",query.value(0).toLongLong());
        object.insert("userId",query.value(1).toLongLong());
        object.insert("name",query.value(2).toString());
        object.insert("content",query.value(3).toString());
        array.append(object);
    }
    return array;
}

bool Sql::insertUserComment(const qint64 &userId, const QString &content)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("INSERT `comment` VALUES (NULL,:userId,NULL,:content,NULL)");
    query.bindValue(":userId",userId);
    query.bindValue(":content",content);
    query.exec();
    return query.numRowsAffected() !=0;

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

void Sql::initCommentModel()
{
    commentModel =new QSqlTableModel(this,m_db);
    commentModel->setTable("comment");
    commentTreeModel = new QStandardItemModel(this);
}



