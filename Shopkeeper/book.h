#ifndef BOOK_H
#define BOOK_H

#include <QDateTime>
#include <QObject>

class Book : public QObject
{
    Q_OBJECT
public:
    explicit Book(QObject *parent = nullptr);
    Book(const QString &ISBN, const QString &name, const QString &author, const QDate &time, const QString &type, qreal price, qint32 count, const QString &profile, QObject *parent = nullptr);
//    Book(const QString &ISBN, const QString &name, const QString &author, const QDate &time, const QString &type, qreal price, qint32 count, const QString &profile, qint64 userId, QObject *parent = nullptr);

    QString ISBN() const;
    void setISBN(const QString &newISBN);

    QString name() const;
    void setName(const QString &newName);

    QString author() const;
    void setAuthor(const QString &newAuthor);

    qreal price() const;
    void setPrice(qreal newPrice);

    qint32 count() const;
    void setCount(qint32 newCount);

    QString profile() const;
    void setProfile(const QString &newProfile);

    QDate time() const;
    void setTime(const QDate &newTime);

//    qint64 userId() const;
//    void setUserId(qint64 newUserId);

    ~Book();

    QString type() const;
    void setType(const QString &newType);

signals:

private:
    QString m_ISBN;
    QString m_name;
    QString m_author;
    QDate m_time;
    QString m_type;
    qreal m_price;
    qint32 m_count;
    QString m_profile;
//    qint64 m_userId = 44910244;
};

#endif // BOOK_H
