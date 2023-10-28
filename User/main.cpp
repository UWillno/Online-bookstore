#include "settings.h"

#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    int fontId = QFontDatabase::addApplicationFont(":/NotoSansSC-Regular.otf");
    QFontDatabase::addApplicationFont(":/NotoSansSC-Bold.otf");

    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    //    qDebug()<<"fontfamilies:"<<fontId;
    if (fontFamilies.size() > 0)
    {
        QFont font;
        font.setFamily(fontFamilies[0]);//设置全局字体
        app.setFont(font);
    }
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    Settings ss;
    engine.rootContext()->setContextProperty("ss",&ss);
    engine.loadFromModule("User", "Main");

    return app.exec();
}
