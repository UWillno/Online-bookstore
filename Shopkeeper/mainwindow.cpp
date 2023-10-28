#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QContextMenuEvent>
#include <QMenu>
#include <QCursor>
#include <QInputDialog>
#include <QModelIndex>
#define SQL Singleton<Sql>::GetInstance()

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    settings = new QSettings("bookstore.ini",QSettings::IniFormat,this);
    ui->textEdit_storeProfile->setHtml(settings->value("profile").toString());
    SQL.storeProfile = settings->value("profile").toString();
    ui->tableView_books->setModel(SQL.booksModel);
    ui->tableView_stock->setModel(SQL.booksModel);
    ui->tableView_account->setModel(SQL.accoutModel);
    ui->tableView_user->setModel(SQL.userModel);
    ui->treeView->setModel(SQL.commentTreeModel);
//    QObject::connect(&SQL,&Sql::selectAllBooksFinished,this,[&]{
//        ui->tableView_books->setModel(SQL.booksModel);
//        ui->tableView_stock->setModel(SQL.booksModel);
//    });
    ui->tableView_account->hideColumn(0);
//    QObject::connect(&SQL,&Sql::selectAllAccountFinished,this,[&]{
//        ui->tableView_account->setModel(SQL.accoutModel);
//    });

    QObject::connect(this,&MainWindow::inNewBookSignal,&SQL,&Sql::inNewBook);
    QObject::connect(this,&MainWindow::ioBookSignal,&SQL,&Sql::inOldBook);
    QObject::connect(&SQL,&Sql::inNewBookSucceed,this,[&]{
        showInfoDialog("进书成功！");
        ui->lineEdit_ISBN->clear();
        ui->lineEdit_author->clear();
        ui->lineEdit_name->clear();
        ui->textEdit_profile->clear();
        //……
    });
    QObject::connect(&SQL,&Sql::inNewBookFailed,this,[&]{
        showInfoDialog("进书失败！");
    });

    QObject::connect(&SQL,&Sql::postNewsFailed,this,[&]{
        showInfoDialog("信息发布失败");
    });
    QObject::connect(&SQL,&Sql::postNewsSucceed,this,[&]{
        showInfoDialog("信息发布成功");
        ui->textEdit_news->clear();
    });
//    SQL.selectAllBooks();
//    SQL.selectAllAccounts();
    QObject::connect(SQL.booksModel,&QSqlTableModel::dataChanged,this,[&]{
        //避免重复提交
        if (!SQL.isSubmitting) {  // 检查是否已经在提交中
            SQL.isSubmitting = true;  // 设置提交标志
            if (SQL.booksModel->submitAll()) {
                showInfoDialog("修改成功！");
            } else {
                         SQL.booksModel->revertAll();
                showInfoDialog("修改失败!");
            }
            SQL.isSubmitting = false;  // 重置提交标志
        }
        });
    QObject::connect(SQL.accoutModel,&QSqlTableModel::beforeUpdate,this,[&]{
        //避免重复提交
        if (!SQL.isSubmitting) {  // 检查是否已经在提交中
            SQL.isSubmitting = true;  // 设置提交标志
            if (SQL.accoutModel->submitAll()) {
                showInfoDialog("修改成功！");
            } else {
                SQL.accoutModel->revertAll();
                showInfoDialog("修改失败!");
            }
            SQL.isSubmitting = false;  // 重置提交标志
        }
    });

    QObject::connect(&SQL,&Sql::insertCommentSucceed,this,[&]{
        showInfoDialog("回复留言成功！");
        SQL.selectAllcomments();
    });
    QObject::connect(&SQL,&Sql::insertCommentFailed,this,[&]{
         showInfoDialog("回复留言失败！");
    });
    SQL.selectAllcomments();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_inBook_clicked()
{
    if(ui->lineEdit_ISBN->text().isEmpty()) return;
    if(ui->check_newbook->isChecked()){
        Book book;
        foreach(QRadioButton* rb, ui->groupBox->findChildren<QRadioButton*>()){
            if(rb->isChecked())
            {
                qInfo()<< rb->text();
                book.setType(rb->text());
                break;
            }
        }
        book.setName(ui->lineEdit_name->text());
        book.setAuthor(ui->lineEdit_author->text());
        book.setISBN(ui->lineEdit_ISBN->text());
        book.setCount(ui->spinBox->value());
        book.setPrice(ui->doubleSpinBox->value());
        book.setTime(ui->dateEdit->date());
        //        book.setProfile(ui->textEdit_profile->toHtml()); //可以改成html的
        book.setProfile(ui->textEdit_profile->toPlainText());
        emit inNewBookSignal(book);
    }else {
        Book book;
        book.setISBN(ui->lineEdit_ISBN->text());
        book.setCount(ui->spinBox->value());
        emit ioBookSignal(book);
    }
}

void MainWindow::showInfoDialog(const QString &info)
{
    QMessageBox::information(this,"提示",info);
}


void MainWindow::on_pushButton_commit_clicked()
{
  SQL.booksModel->submit()?
        showInfoDialog("提交成功！") : showInfoDialog("提交失败！");
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
  if(index == 4)
        SQL.selectAllAccounts();
  else if(index == 1 || index==2) {
        SQL.selectAllBooks();
  }else if(index == 3 )
        SQL.selectAllUsers();
  else if(index == 0) SQL.selectAllcomments();

}


void MainWindow::on_pushButton_delete_clicked()
{

  if(!ui->tableView_account->selectionModel()->hasSelection())
        showInfoDialog("未选中行！");
  else{
        foreach (QModelIndex index , ui->tableView_account->selectionModel()->selectedRows()) {
            SQL.accoutModel->removeRow(index.row());
        }
        showInfoDialog("删除成功！");
        SQL.selectAllAccounts();
  }
}


void MainWindow::on_pushButton_clicked()
{
  settings->setValue("profile",ui->textEdit_storeProfile->toHtml());
  SQL.storeProfile = ui->textEdit_storeProfile->toHtml();
  showInfoDialog("书店简介修改成功！");
}


void MainWindow::on_pushButton_news_clicked()
{
  SQL.postNews(ui->textEdit_news->toHtml());
}




void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
  QModelIndex index = ui->treeView->indexAt(pos);
//  qInfo()<<index;
   QMenu contextMenu(ui->treeView);
  if(index.isValid()){

        QAction *action1 = contextMenu.addAction("回复");
        QAction *action2 = contextMenu.addAction("修改");
        QAction *action3= contextMenu.addAction("删除");
        QVariantList data = ui->treeView->model()->data(index,Qt::UserRole).value<QVariantList>();
        connect(action1,&QAction::triggered,this,[&]{
//      qint32 parentId =
            qint32 row = data[1].toModelIndex().row();
            qint32 replyId = SQL.commentModel->index(row,4).data().toInt();
            QString content = QInputDialog::getText(this,"回复","请输入");
            if(replyId == 0){
                qint32 id = SQL.commentModel->index(row,0).data().toInt();
                SQL.insertComment(id,content);
            }else{
              SQL.insertComment(replyId,content);
            }
            });
        connect(action2,&QAction::triggered,this,[&]{
                      QString newContent = QInputDialog::getText(this,"修改留言","请输入",QLineEdit::Normal,data.at(0).toString());
                        if(!newContent.isEmpty()){
                           SQL.commentModel->setData(data[1].toModelIndex(),newContent);
                            if(SQL.commentModel->submit()){
                               showInfoDialog("修改成功！");
                               SQL.selectAllcomments();
                        }else
                            showInfoDialog("修改失败");
                        }

 });
        connect(action3,&QAction::triggered,this,[&]{
             SQL.commentModel->removeRow(data[1].toModelIndex().row());
            if(SQL.commentModel->submit()){
                            showInfoDialog("删除成功！");
                SQL.selectAllcomments();}
            else
                showInfoDialog("删除失败");
        });

  }else{
        QAction *action4= contextMenu.addAction("全部展开");
        QAction *action5= contextMenu.addAction("全部收缩");
        connect(action4,&QAction::triggered,ui->treeView,&QTreeView::expandAll);
        connect(action5,&QAction::triggered,ui->treeView,&QTreeView::collapseAll);

  }
  contextMenu.exec(QCursor::pos());
}


