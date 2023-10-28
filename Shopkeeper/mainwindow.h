#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "singleton.h"
#include <QMainWindow>
#include "book.h"
#include "sql.h"
#include <QMessageBox>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSettings *settings;

signals:
    void inNewBookSignal(Book &book); // 进新书信号
    void ioBookSignal(Book &book); // 进/出(旧)书信号

private slots:
    void on_pushButton_inBook_clicked();
    void showInfoDialog(const QString &info);

    void on_pushButton_commit_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_delete_clicked();
    void on_pushButton_clicked();

    void on_pushButton_news_clicked();


    void on_treeView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    bool flag = true;

    // QWidget interface

};
#endif // MAINWINDOW_H
