#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    Q_PROPERTY(QString password READ password WRITE setPassword RESET resetPassword NOTIFY passwordChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName RESET resetName NOTIFY nameChanged FINAL)
    Q_PROPERTY(qint64 id READ id WRITE setId RESET resetId NOTIFY idChanged FINAL)
    QString password() const;
    void setPassword(const QString &newPassword);
    void resetPassword();

    QString name() const;
    void setName(const QString &newName);
    void resetName();

    qint64 id() const;
    void setId(qint64 newId);
    void resetId();


public slots:
    void reset();
signals:


    void passwordChanged();

    void nameChanged();



    void idChanged();

private:
    QSettings *settings;

    qint64 m_id = 0;
    QString m_name = "";
    QString m_password = "";

};

#endif // SETTINGS_H
