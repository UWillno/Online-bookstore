#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QHttpServer>
#include "sql.h"
#include "singleton.h"
#include <QtConcurrent>

class HttpServer : public QObject
{
    Q_OBJECT
public:
    explicit HttpServer(QObject *parent = nullptr);
    void routeAllBooks();
    void routeUserManagement();
    void routeBuyBook();
    void routeStoreInfo();
    void routeComment();

signals:




private:
    QHttpServer httpServer;
};

#endif // HTTPSERVER_H
