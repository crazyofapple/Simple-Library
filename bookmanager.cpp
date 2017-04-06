#include "bookmanager.h"
#include "ui_bookmanager.h"
#include "data.h"
#include "booker.h"
#include <sstream>
#include <iomanip>
#include <QMessageBox>
#include "myuser.h"
#pragma execution_character_set("utf-8")
bookManager::bookManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookManager)
{
    ui->setupUi(this);
    ui->label_31->setVisible(false);
    ui->label_32->setVisible(false);
    ui->label_33->setVisible(false);
    ui->label_34->setVisible(false);
    ui->label_35->setVisible(false);
    ui->label_36->setVisible(false);
    ui->label_37->setVisible(false);
    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);
    ui->label_13->setVisible(false);
    ui->pushButton_14->setVisible(false);
    ui->pushButton_15->setVisible(false);
    ui->pushButton_16->setVisible(false);
    ui->low_1->setVisible(false);
    ui->low_2->setVisible(false);
    ui->low_3->setVisible(false);
    ui->low_4->setVisible(false);
    ui->low_5->setVisible(false);
    flag = 0;
}

bookManager::~bookManager()
{
    delete ui;
}

void bookManager::on_pushButton_addBook_clicked()
{
    string bookName = _trim(q2s(ui->lineEdit_2->text()));\
    string bookAuthor = _trim(q2s(ui->lineEdit_3->text()));
    string bookPublish = _trim(q2s(ui->lineEdit_4->text()));
    string ISBN = _trim(q2s(ui->lineEdit_5->text()));
    string bookPrice = _trim(q2s(ui->lineEdit_6->text()));
    int bookID = -1;
    if(!ui->label_32->isVisible() && !ui->label_33->isVisible() &&
            !ui->label_34->isVisible() && !ui->label_35->isVisible() &&
            !ui->label_36->isVisible() && bookName.length() > 0 &&
            bookAuthor.length() > 0 && bookPublish.length() > 0 &&
            ISBN.length() > 0 && bookPrice.length() > 0) {
        qDebug("ok");
        if ((bookID = Booker::AddBook(ISBN,bookName,bookAuthor,bookPublish,atof(bookPrice.c_str()))) != -1) {
            QMessageBox::warning(this,tr("Success"),tr("Add book ok!"),QMessageBox::Yes);
            std::stringstream stream;std::string ans;stream<<setw(10) <<setfill('0') << bookID;
            stream>>ans;
            string tmp; tmp+="ADD SUCCESS, ";tmp+="BOOK ID: ";tmp+=_trim(ans);
            qDebug("%s   ------  %s",ans.c_str(), tmp.c_str());
            qDebug("%d",bookID);
            ui->label_37->setVisible(true);
            ui->label_37->setText(s2q(tmp));
            ui->label_37->adjustSize();

        }else{
            // NO ACTION
            QMessageBox::warning(this,tr("Success"),tr("Add book fail!"),QMessageBox::Yes);
        }
    }else{
        // NO ACTION
        QMessageBox::warning(this,tr("Success"),tr("input illegal"),QMessageBox::Yes);
    }
}

// book name
void bookManager::on_lineEdit_2_editingFinished()
{
    QString str = ui->lineEdit_2->text();
    string s = _trim(q2s(str));
    // 书名合法性及合理性判断
    if (s.size() > 0 && s.size() < LEN_BOOK_NAME) {
        ui->label_32->setVisible(false);
    }else {
        ui->label_32->setVisible(true);
    }
}
// book author
void bookManager::on_lineEdit_3_editingFinished()
{
    QString str = ui->lineEdit_3->text();
    string s = _trim(q2s(str));
    // 作者合法性及合理性判断
    if (s.size() > 0 && s.size() < LEN_BOOK_AUTHOR) {
        ui->label_33->setVisible(false);
    }else {
        ui->label_33->setVisible(true);
    }
}
// book publisher
void bookManager::on_lineEdit_4_editingFinished()
{
    QString str = ui->lineEdit_4->text();
    string s = _trim(q2s(str));
    // 出版社合法性及合理性判断
    if (s.size() > 0 && s.size() < LEN_BOOK_PUBLISHER) {
        ui->label_34->setVisible(false);
    }else {
        ui->label_34->setVisible(true);
    }
}
// ISBN
void bookManager::on_lineEdit_5_editingFinished()
{
    QString str = ui->lineEdit_5->text();
    if (isbnCheck(_trim((q2s(str))))) {
        ui->label_35->setVisible(false);
    }else {
        ui->label_35->setVisible(true);
    }
}
// book price
void bookManager::on_lineEdit_6_editingFinished()
{
    QString str = ui->lineEdit_6->text();
    string s = _trim(q2s(str));
    // 书籍价格判断
    if (s.size() > 0 && isNumber(s.c_str())) {
        ui->label_36->setVisible(false);
    }else {
        ui->label_36->setVisible(true);
    }
}


void bookManager::on_lineEdit_6_textChanged(const QString &arg1)
{
    ui->label_37->setVisible(false);
    QString str = ui->lineEdit_6->text();
    string s = _trim(q2s(str));
    // 书籍价格判断
    if (s.size() > 0 && isNumber(s.c_str())) {
        ui->label_36->setVisible(false);
    }else {
        ui->label_36->setVisible(true);
    }
}

void bookManager::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->label_37->setVisible(false);
    QString str = ui->lineEdit_2->text();
    string s = _trim(q2s(str));
    // 书名合法性及合理性判断
    if (s.size() > 0 && s.size() < LEN_BOOK_NAME) {
        ui->label_32->setVisible(false);
    }else {
        ui->label_32->setVisible(true);
    }
}

void bookManager::on_lineEdit_3_textChanged(const QString &arg1)
{
    ui->label_37->setVisible(false);
    QString str = ui->lineEdit_3->text();
    string s = _trim(q2s(str));
    // 作者合法性及合理性判断
    if (s.size() > 0 && s.size() < LEN_BOOK_AUTHOR) {
        ui->label_33->setVisible(false);
    }else {
        ui->label_33->setVisible(true);
    }
}

void bookManager::on_lineEdit_4_textChanged(const QString &arg1)
{
    ui->label_37->setVisible(false);
    QString str = ui->lineEdit_4->text();
    string s = _trim(q2s(str));
    // 出版社合法性及合理性判断
    if (s.size() > 0 && s.size() < LEN_BOOK_PUBLISHER) {
        ui->label_34->setVisible(false);
    }else {
        ui->label_34->setVisible(true);
    }
}

void bookManager::on_lineEdit_5_textChanged(const QString &arg1)
{
    ui->label_37->setVisible(false);
    QString str = ui->lineEdit_5->text();
    if (isbnCheck(_trim(q2s(str)))) {
        ui->label_35->setVisible(false);
    }else {
        ui->label_35->setVisible(true);
    }
}

int getNumber(const std::string& str){
    try
    {
        std::size_t lastChar;
        int result = std::stoi(str, &lastChar, 10);
        if (lastChar == str.size()){
            return result;
        }else {
            return -1;
        }
    }
    catch (std::invalid_argument&)
    {
        return -1;
    }
    catch (std::out_of_range&)
    {
        return -1;
    }
}
void bookManager::clear() {
    ui->label_31->setVisible(false);
    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);
    ui->label_13->setVisible(false);
    ui->pushButton_14->setVisible(false);
    ui->pushButton_15->setVisible(false);
    ui->pushButton_16->setVisible(false);
    ui->low_1->setVisible(false);
    ui->low_2->setVisible(false);
    ui->low_3->setVisible(false);
    ui->low_4->setVisible(false);
    ui->low_5->setVisible(false);
}
// low widget myshow
void bookManager::myshow() {
    ui->low_1->setVisible(true);
    ui->low_2->setVisible(true);
    ui->low_3->setVisible(true);
    ui->low_4->setVisible(false);
    ui->low_5->setVisible(true);
    // 互斥
    ui->pushButton_14->setEnabled(false);
    ui->pushButton_15->setEnabled(false);
    ui->pushButton_16->setEnabled(false);
}
// 搜索按钮事件处理
void bookManager::on_pushButton_clicked()
{
    clear();
    QString s = ui->lineEdit_1->text();
    string str = _trim(q2s(s));
    if (str.length() == 0) {
        QMessageBox::warning(this,tr("Success"),tr("no letter input"),QMessageBox::Yes);
        return;
    }
    if (str.length() > 10) {
        QMessageBox::warning(this,tr("Success"),tr("illegal input"),QMessageBox::Yes);
        return;
    }
    ID = getNumber(str);
    if (ID <= 0) {
        QMessageBox::warning(this,tr("Success"),tr("illegal input"),QMessageBox::Yes);
        return;
    }

    Datastore::Book*  book = Booker::IDFindBook(ID);

    if (book == nullptr) {
        ui->label_31->setVisible(true);
    }else {
        ui->label_11->setVisible(true);
        string tmp = "ISBN: ";
        tmp+=book->ISBN;
        ui->label_11->setText(s2q(tmp));
        //ui->label_11->adjustSize();
        ui->label_12->setVisible(true);
        ui->label_12->setText(s2q(book->bookName));
        //ui->label_12->adjustSize();
        ui->label_13->setVisible(true);
        ui->label_13->setText(s2q(book->bookAuthor));
        //ui->label_13->adjustSize();
        if(book->canBorrow)ui->pushButton_14->setVisible(true);
        if(!book->canBorrow)ui->pushButton_15->setVisible(true);
        ui->pushButton_16->setVisible(true);
    }
}
void bookManager::refresh(int flag) {
    if (flag == 1) { // 借阅处理完毕
        ui->low_1->setVisible(false);
        ui->low_2->setVisible(false);
        ui->low_3->setVisible(false);
        ui->low_4->setVisible(false);
        ui->low_5->setVisible(false);
        ui->pushButton_14->setEnabled(true);
        ui->pushButton_14->setVisible(false);// 借阅不可见
        ui->pushButton_15->setEnabled(true);
        ui->pushButton_15->setVisible(true);// 归还可见
        ui->pushButton_16->setEnabled(true);
        ui->pushButton_16->setVisible(true);// 删除可见
    }else if (flag == 2) {
        ui->low_1->setVisible(false);
        ui->low_2->setVisible(false);
        ui->low_3->setVisible(false);
        ui->low_4->setVisible(false);
        ui->low_5->setVisible(false);
        ui->pushButton_14->setEnabled(true);
        ui->pushButton_14->setVisible(true);// 借阅可见
        ui->pushButton_15->setEnabled(true);
        ui->pushButton_15->setVisible(false);// 归还可见
        ui->pushButton_16->setEnabled(true);
        ui->pushButton_16->setVisible(true);// 删除可见
    }else{
        ui->low_1->setVisible(false);
        ui->low_2->setVisible(false);
        ui->low_3->setVisible(false);
        ui->low_4->setVisible(false);
        ui->low_5->setVisible(false);
        ui->pushButton_14->setEnabled(true);
        ui->pushButton_15->setEnabled(true);
        ui->pushButton_16->setEnabled(true);
    }
}

//借阅按钮事件处理
void bookManager::on_pushButton_14_clicked()
{
    myshow();
    flag = 1; // 借阅
}
// 归还事件处理
void bookManager::on_pushButton_15_clicked()
{
    myshow();
    flag = 2;
}
// 用户名是否合法
void bookManager::on_low_2_textChanged(const QString &arg1)
{
    QString str = ui->low_2->text();
    string s = _trim(q2s(str));
    // 用户名合法性判断
    if (s.size() > 0 && s.size() < LEN_USER_NAME && isEmailAddress(s2q(s))) {
        Datastore::User * user = UserManager::SelectUser(s);
        if (user == nullptr) {
            ui->low_4->setVisible(true);
            return;
        }else {
            ui->low_4->setVisible(false);
        }
    }else {
        ui->low_4->setVisible(true);
    }
}

void bookManager::on_low_3_clicked()
{
    string userName = _trim(q2s(ui->low_2->text()));
    if (!ui->low_4->isVisible() && userName.length() > 0) {
        if (flag == 1)
        {
            if (Booker::BrowseBook(userName, ID)) {
                QMessageBox::warning(this,tr("Success"),tr("borrow ok!"),QMessageBox::Yes);
                refresh(1);
            }else {
                QMessageBox::warning(this,tr("Success"),tr("borrow wrong! BUG"),QMessageBox::Yes);
            }
        }else if (flag == 2){
            qDebug("flag = 2 ok\n");
            //1正常还书,0超期还书,-1还书失败
            int ok = Booker::ReturnBook(userName, ID);
            qDebug("%d\n",ok);
            if ( ok != -1) {
                QMessageBox::warning(this,tr("Success"),tr("return ok!"),QMessageBox::Yes);
                refresh(2);
            }else {
                QMessageBox::warning(this,tr("Success"),tr("this book guoqi"),QMessageBox::Yes);
            }
        }
        else {
            QMessageBox::warning(this,tr("Success"),tr("something wrong in flag"),QMessageBox::Yes);
        }
    }else {
        QMessageBox::warning(this,tr("Success"),tr("illegal input"),QMessageBox::Yes);
    }
    flag = 0;
}


void bookManager::on_low_5_clicked()
{
    refresh(-1);
    flag = 0;
}
//删除事件处理
void bookManager::on_pushButton_16_clicked()
{
    QMessageBox message(QMessageBox::Warning,"Information","Really to delete this book?",QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::Yes)
    {
        if (Booker::DeleteBook(ID)) {
            QMessageBox::warning(this,tr("Success"),tr("delete ok"),QMessageBox::Yes);
            on_pushButton_clicked();
        }else {
            QMessageBox::warning(this,tr("Success"),tr("delete error"),QMessageBox::Yes);
        }
    }
    else
    {
        // do nothing
    }

}

