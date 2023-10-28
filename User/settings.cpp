#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject{parent}
{
    settings = new QSettings(
                             "UWlab","bookStore",this);
//    settings->setValue("username","UWillno");
//    qInfo() << settings->value("username").toString();

    setId(settings->value("id").toLongLong());
    setName(settings->value("name").toString());
    setPassword(settings->value("password").toString());

    connect(this,&Settings::idChanged,this,[&]{
        settings->setValue("id",id());
    });
    connect(this,&Settings::nameChanged,this,[&]{
        settings->setValue("name",name());
    });
    connect(this,&Settings::passwordChanged,this,[&]{
        settings->setValue("password",password());
    });


}

QString Settings::password() const
{
    return m_password;
}

void Settings::setPassword(const QString &newPassword)
{
    if (m_password == newPassword)
        return;
    m_password = newPassword;
    emit passwordChanged();
}

void Settings::resetPassword()
{
    setPassword({}); // TODO: Adapt to use your actual default value
}

QString Settings::name() const
{
    return m_name;
}

void Settings::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

void Settings::resetName()
{
    setName({}); // TODO: Adapt to use your actual default value
}

qint64 Settings::id() const
{
    return m_id;
}

void Settings::setId(qint64 newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

void Settings::resetId()
{
    setId({}); // TODO: Adapt to use your actual default value
}

void Settings::reset()
{
    resetPassword();
    resetName();
    resetId();
}


