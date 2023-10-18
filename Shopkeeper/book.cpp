#include "book.h"

Book::Book(QObject *parent)
    : QObject{parent}
{
    qInfo() << "book创建！";
}

QString Book::ISBN() const
{
    return m_ISBN;
}

void Book::setISBN(const QString &newISBN)
{
    m_ISBN = newISBN;
}

QString Book::name() const
{
    return m_name;
}

void Book::setName(const QString &newName)
{
    m_name = newName;
}

QString Book::author() const
{
    return m_author;
}

void Book::setAuthor(const QString &newAuthor)
{
    m_author = newAuthor;
}

qreal Book::price() const
{
    return m_price;
}

void Book::setPrice(qreal newPrice)
{
    m_price = newPrice;
}

qint32 Book::count() const
{
    return m_count;
}

void Book::setCount(qint32 newCount)
{
    m_count = newCount;
}

QString Book::profile() const
{
    return m_profile;
}

void Book::setProfile(const QString &newProfile)
{
    m_profile = newProfile;
}

QDate Book::time() const
{
    return m_time;
}

void Book::setTime(const QDate &newTime)
{
    m_time = newTime;
}

//qint64 Book::userId() const
//{
//    return m_userId;
//}

//void Book::setUserId(qint64 newUserId)
//{
//    m_userId = newUserId;
//}

Book::~Book()
{
    qInfo() <<"book销毁中……";
}

QString Book::type() const
{
    return m_type;
}

void Book::setType(const QString &newType)
{
    m_type = newType;
}



//Book::Book(const QString &ISBN, const QString &name, const QString &author, const QDate &time, const QString &type, qreal price, qint32 count, const QString &profile, qint64 userId, QObject *parent) : QObject(parent),
//    m_ISBN(ISBN),
//    m_name(name),
//    m_author(author),
//    m_time(time),
//    m_type(type),
//    m_price(std::move(price)),
//    m_count(std::move(count)),
//    m_profile(profile),
//    m_userId(std::move(userId))
//{}

Book::Book(const QString &ISBN, const QString &name, const QString &author, const QDate &time, const QString &type, qreal price, qint32 count, const QString &profile, QObject *parent) : QObject(parent),
    m_ISBN(ISBN),
    m_name(name),
    m_author(author),
    m_time(time),
    m_type(type),
    m_price(std::move(price)),
    m_count(std::move(count)),
    m_profile(profile)
{}
