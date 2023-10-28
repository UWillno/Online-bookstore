#include "httpserver.h"
#include "mainwindow.h"
//#include<QHttpServerRequest>
#include <QJsonArray>
#include <QJsonObject>
#include "singleton.h"
#include "sql.h"
#include <QSqlRecord>
#define booksModel Singleton<Sql>::GetInstance().booksModel

HttpServer::HttpServer(QObject *parent)
    : QObject{parent}
{
    httpServer.listen(QHostAddress::Any,4444);
    //    httpServer.afterRequest()
    httpServer.afterRequest([](QHttpServerResponse &&resp) {
        resp.setHeader("Access-Control-Allow-Origin","*");
        return std::move(resp);
    });
    routeUserManagement();
    routeAllBooks();
    routeBuyBook();
    routeStoreInfo();
    routeComment();
}

void HttpServer::routeAllBooks()
{
    httpServer.route("/allBooks", [] {
        QJsonObject json;
        qint32 rowCount = booksModel->rowCount();
        QJsonArray jArray,yArray,qArray;
        for (int row = 0; row < rowCount; ++row) {
            QSqlRecord record = booksModel->record(row);
            Book book;
            book.setISBN(record.value(0).toString());
            book.setName(record.value(1).toString());
            book.setAuthor(record.value(2).toString());
            book.setTime(record.value(3).toDate());
            book.setType(record.value(4).toString());
            book.setCount(record.value(5).toInt());
            book.setPrice(record.value(6).toReal());
            book.setProfile(record.value(7).toString());
            QJsonObject object;
            object.insert("ISBN",book.ISBN());
            object.insert("name",book.name());
            object.insert("author",book.author());
            object.insert("time",book.time().toString("yyyy-MM-dd"));
            object.insert("count",book.count());
            object.insert("price",book.price());
            object.insert("profile",book.profile());
            if(book.type() == "计算机")
            {
                jArray.append(object);
            }else if(book.type() == "英语") {
                yArray.append(object);
            }else{
                qArray.append(object);
            }
        }
        json.insert("计算机",jArray);
        json.insert("英语",yArray);
        json.insert("其它",qArray);

        return json;
    });
}

void HttpServer::routeUserManagement()
{
    httpServer.route("/signUp", [](const QHttpServerRequest &request) {
//        qInfo() << ;
        QJsonObject data = QJsonDocument::fromJson(request.body()).object();
        qint64 id = data.value("id").toInteger();
        QString name = data.value("name").toString();
        QString password = data.value("password").toString();
        if(id==0 || name.isEmpty() || password.isEmpty())
            return "";
        return QtConcurrent::run([&]
                              (){
                return Singleton<Sql>::GetInstance().addUser(id,name,password);
               }).result()? "success" :"";
    });


    httpServer.route("/login",[](const QHttpServerRequest &request) {
//        qInfo() << ;
        QJsonObject data = QJsonDocument::fromJson(request.body()).object();
        qint64 id = data.value("id").toInteger();
        QString password = data.value("password").toString();
        if(id==0  || password.isEmpty())
            return QString("");
        return QtConcurrent::run([&]
                              (){
                return Singleton<Sql>::GetInstance().login(id,password);
               }).result();
    });

    httpServer.route("/changePassword",[](const QHttpServerRequest &request) {

        QJsonObject data = QJsonDocument::fromJson(request.body()).object();
        qint64 id = data.value("id").toInteger();
        QString newPassword = data.value("newPassword").toString();
        QString oldPassword = data.value("oldPassword").toString();
        qInfo() << data;
        if(id==0  || oldPassword.isEmpty() || newPassword.isEmpty())
            return "";
        return QtConcurrent::run([&]
                                 (){
                                     return Singleton<Sql>::GetInstance().changeUserPassword(id,newPassword,oldPassword);
               }).result() ? "success" : "";
    });

    httpServer.route("/changeName",[](const QHttpServerRequest &request) {

        QJsonObject data = QJsonDocument::fromJson(request.body()).object();
        qint64 id = data.value("id").toInteger();
        QString password = data.value("password").toString();
        QString name = data.value("name").toString();
        qInfo() << data;
        if(id==0  || password.isEmpty() || name.isEmpty())
            return "";
        return QtConcurrent::run([&]
                                 (){
                                     return Singleton<Sql>::GetInstance().changeUserName(id,password,name);
                                 }).result() ? "success" : "";
    });
}

void HttpServer::routeBuyBook()
{
    httpServer.route("/buyBook",[](const QHttpServerRequest &request) {
        QJsonObject data = QJsonDocument::fromJson(request.body()).object();
        qint64 id = data.value("id").toInteger();
        QString password = data.value("password").toString();
//        if()
        bool ok = QtConcurrent::run([&]
                                    (){
                                        return Singleton<Sql>::GetInstance().login(id,password);
                  }).result().isEmpty();
        if(ok) return "";
        Book book;
        book.setISBN(data.value("isbn").toString());
        book.setCount(data.value("count").toInt());
        return QtConcurrent::run([&]
                                 (){return Singleton<Sql>::GetInstance().sellBook(book);}).result()
        ? "success" : "";
    });
}

void HttpServer::routeStoreInfo()
{
    httpServer.route("/storeInfo",[](){
        QJsonObject json;
        json.insert("profile",Singleton<Sql>::GetInstance().storeProfile);
//        return json;
        QJsonArray array = QtConcurrent::run([&]
                          (){return Singleton<Sql>::GetInstance().selectAllNews();}).result();
        json.insert("news",array);
        return json;
    });
}

void HttpServer::routeComment()
{
    httpServer.route("/insertComment",[](const QHttpServerRequest &request) {
        QJsonObject data = QJsonDocument::fromJson(request.body()).object();
        qint64 id = data.value("id").toInteger();
        QString password = data.value("password").toString();
        QString content = data.value("content").toString();
        if(id ==0 || password.isEmpty() || content.isEmpty())
            return "";
        if(!QtConcurrent::run([&]
                              (){return Singleton<Sql>::GetInstance().login(id,password);}).result().isEmpty())

            return QtConcurrent::run([&](){return Singleton<Sql>::GetInstance().insertUserComment(id,content);}).result() ? "success": "";
        else{
            return "";

        }

        });

    httpServer.route("/selectComments/",[](qint64 id){
        qInfo()<< id;
       return QtConcurrent::run([&](){return Singleton<Sql>::GetInstance().selectCommentByUserId(id);}).result();

    });

}

