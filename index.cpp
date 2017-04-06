#include "index.h"
#include "ui_index.h"
#include <qmessagebox.h>
#include "booker.h"
#include "login.h"
#include <vector>
#include <utility>
#include <QDebug>
index::index(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::index)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    ui->_15->setVisible(false);
    ui->_25->setVisible(false);
    ui->_35->setVisible(false);
    ui->_45->setVisible(false);
    //ui->button_search->setShortcut(Qt::Key_Enter); no work
    prevRecordNum = -1;
    nowRecordNum = -1;

    bookinformation = new bookImformation(this);
    connect(this,SIGNAL(send(QString , QString ,
                                  QString, QString)),bookinformation,SLOT(receive(QString , QString ,
                                                                               QString, QString)));
}


void index::showagain(){
    this->show();
}

int index::getRadioButton() {
    if (ui->radio_ISBN->isChecked()) {
        return 1;
    }else if (ui->radio_book->isChecked()){
        return 2;
    }else {
        return -1;
    }
}

index::~index()
{
    delete ui;
}

// ui显示书籍信息
void index::printBookList(Datastore::Book **list){
    int i = 0;
    newVt.clear();
    vt.clear();
    clear();
    prevRecordNum = nowRecordNum = -1;
    if(list[0] == NULL){
        //QMessageBox::warning(this,tr("Success"),tr("NO DATA"),QMessageBox::Yes);
        //ui->waring->setText(s2q("没有查询到相关信息"));
        ui->waring->setText("没有查询到相关信息");
        return;
    }

    while (list[i] != nullptr){
        vt.push_back(list[i]);
        i++;
    }
    for (auto i = vt.begin(); i != vt.end();) {
        auto j = i;
        for (; j != vt.end() && strcmp((*i)->ISBN,(*j)->ISBN)==0; j++);
        newVt.push_back(make_pair(*i, distance(i, j)));
        i = j;
    }

    qDebug("YESYEESSSS %d %d",vt.size(), newVt.size());
    int ii = 0;
    nowCnt = 0;
    while(ii < newVt.size() && ii < 4){
        int i = ii%4+1;
        string tmp1 = "_";tmp1+=char('0'+i);tmp1+="1";
        string x1;
        x1 += newVt[ii].first->bookName;
        QLabel * label1 = findChild<QLabel*>(s2q(tmp1));
        label1->setText(s2q(x1));
        label1->adjustSize();

        string tmp2 = "_";tmp2+=char('0'+i);tmp2+="2";
        string x2;
        x2+=newVt[ii].first->ISBN;
        QLabel * label2 = findChild<QLabel*>(s2q(tmp2));
        label2->setText(s2q(x2));
        label2->adjustSize();

        string tmp3 = "_";tmp3+=char('0'+i);tmp3+="3";
        string x3 = newVt[ii].first->bookAuthor;
        QLabel * label3 = findChild<QLabel*>(s2q(tmp3));
        label3->setText(s2q(x3));
        label3->adjustSize();

        string tmp4 = "_";tmp4+=char('0'+i);tmp4+="4";
        string x4 = newVt[ii].first->bookPublish;
        QLabel * label4 = findChild<QLabel*>(s2q(tmp4));
        label4->setText(s2q(x4));
        label4->adjustSize();

        string tmp5 = "_";tmp5+=char('0'+i);tmp5+="5";
        string x5;
        x5+=char( '0' + newVt[ii].second );x5+="本馆藏";
        QPushButton * pushbotton5 = findChild<QPushButton*>(s2q(tmp5));
        pushbotton5->setVisible(true);
        pushbotton5->setText(s2q(x5));

        ii++;
        nowCnt++;
    }
    nowRecordNum = nowCnt;
}
// 搜索按钮的响应事件
void index::on_button_search_clicked()
{
    ui->waring->clear();
    Datastore::Book**  bookList;
    QString s = ui->text_search->text();
    string str =  q2s(s);
    //qDebug("%s",str.c_str());
    if (str.size() == 0) {
        //QMessageBox::warning(this,tr("Success"),tr("search text is illegal"),QMessageBox::Yes);
        //ui->waring->setText(s2q("请输入查找关键字"));
        ui->waring->setText("请输入查找关键字");
        return;
    }
    if (!(str.size() >= 0 && str.size() <= 20)) {
        //QMessageBox::warning(this,tr("Success"),tr("search text is illegal"),QMessageBox::Yes);
        //ui->waring->setText(s2q("请输入20内的查找关键字"));
        ui->waring->setText("请输入20内的查找关键字");
        return;
    }
    int flag = getRadioButton();
    if (flag == -1) {
        //QMessageBox::warning(this,tr("Success"),tr("radio button is illegal"),QMessageBox::Yes);
        //ui->waring->setText(s2q("请选择搜索范围"));
        ui->waring->setText("请选择搜索范围");
        return;
    }

    if (flag == 1) {
        if (!isbnCheck(str)) {
            //QMessageBox::warning(this,tr("Success"),tr("isbn is illegal"),QMessageBox::Yes);
            //ui->waring->setText(s2q("请输入正确的ISBN号"));
            ui->waring->setText("请输入正确的ISBN号");
            return;
        }
        bookList = Booker::IsbnFindBook(str);
    }else {
        bookList = Booker::AnythingFindBook(str);
    }

    ui->page_next->setStyleSheet("QPushButton:hover{background:qlineargradient(spread:pad, x1:0.505682, y1:0, x2:0.539773, y2:1, stop:0 rgba(255, 208, 32, 255), stop:1 rgba(255, 196, 19, 255));color:#c97002;border-radius:5;border:#E79F14;}QPushButton:!hover{background-color:#ffbb07;color:#c97002;border-radius:5;}");

    ui->page_prev->setStyleSheet("QPushButton:hover{background:qlineargradient(spread:pad, x1:0.505682, y1:0, x2:0.539773, y2:1, stop:0 rgba(255, 208, 32, 255), stop:1 rgba(255, 196, 19, 255));color:#c97002;border-radius:5;border:#E79F14;}QPushButton:!hover{background-color:#ffbb07;color:#c97002;border-radius:5;}");


    printBookList(bookList);


}

void index::on_button_tologin_clicked()
{
    //hide();
    log=new login(this);
    log->show();
    this->hide();

}
void index::clear() {
    ui->_11->clear();
    ui->_12->clear();
    ui->_13->clear();
    ui->_14->clear();
    ui->_15->setVisible(false);
    ui->_21->clear();
    ui->_22->clear();
    ui->_23->clear();
    ui->_24->clear();
    ui->_25->setVisible(false);
    ui->_31->clear();
    ui->_32->clear();
    ui->_33->clear();
    ui->_34->clear();
    ui->_35->setVisible(false);
    ui->_41->clear();
    ui->_42->clear();
    ui->_43->clear();
    ui->_44->clear();
    ui->_45->setVisible(false);
}

void index::on_page_next_clicked()
{
    if(nowCnt >= newVt.size()){
        //QMessageBox::warning(this,tr("Success"),tr("already last page"),QMessageBox::Yes);
        ui->page_next->setStyleSheet("background-color:#DADADA;border-radius:5;color:#fafafa");
        ui->waring_2->setText(s2q("已经是最后一页了"));
        return;
    }

    ui->page_prev->setStyleSheet("QPushButton:hover{background:qlineargradient(spread:pad, x1:0.505682, y1:0, x2:0.539773, y2:1, stop:0 rgba(255, 208, 32, 255), stop:1 rgba(255, 196, 19, 255));color:#c97002;border-radius:5;border:#E79F14;}QPushButton:!hover{background-color:#ffbb07;color:#c97002;border-radius:5;}");

    prevRecordNum = nowRecordNum;
    clear();
    int tmpi = 0;
    int pre_x = nowCnt;
    while(nowCnt < newVt.size() && tmpi < 4) {
        int i = (nowCnt % 4) + 1;
        string tmp1 = "_";tmp1+=char('0'+i);tmp1+="1";
        string x1;
        x1 += newVt[nowCnt].first->bookName;
        QLabel * label1 = findChild<QLabel*>(s2q(tmp1));
        label1->setText(s2q(x1));
        //label1->adjustSize();

        string tmp2 = "_";tmp2+=char('0'+i);tmp2+="2";
        string x2;
        x2+=newVt[nowCnt].first->ISBN;
        QLabel * label2 = findChild<QLabel*>(s2q(tmp2));
        label2->setText(s2q(x2));
        //label2->adjustSize();

        string tmp3 = "_";tmp3+=char('0'+i);tmp3+="3";
        string x3 = newVt[nowCnt].first->bookAuthor;
        QLabel * label3 = findChild<QLabel*>(s2q(tmp3));
        label3->setText(s2q(x3));
        //label3->adjustSize();

        string tmp4 = "_";tmp4+=char('0'+i);tmp4+="4";
        string x4 = newVt[nowCnt].first->bookPublish;
        QLabel * label4 = findChild<QLabel*>(s2q(tmp4));
        label4->setText(s2q(x4));
        //label4->adjustSize();

        string tmp5 = "_";tmp5+=char('0'+i);tmp5+="5";
        string x5;
        x5+=char( '0' + newVt[nowCnt].second );x5+="本馆藏";
        QPushButton * pushbotton5 = findChild<QPushButton*>(s2q(tmp5));
        pushbotton5->setVisible(true);
        pushbotton5->setText(s2q(x5));
        tmpi++;
        nowCnt++;
    }
    int now_x = nowCnt;
    nowRecordNum = now_x - pre_x;
}

void index::on_page_prev_clicked()
{
    if (prevRecordNum < 4) {
        //QMessageBox::warning(this,tr("Success"),tr("already first page"),QMessageBox::Yes);
        ui->page_prev->setStyleSheet("background-color:#DADADA;border-radius:5;color:#fafafa");
        ui->waring_2->setText(s2q("已经是第一页了"));
        return;
    }
    ui->page_next->setStyleSheet("QPushButton:hover{background:qlineargradient(spread:pad, x1:0.505682, y1:0, x2:0.539773, y2:1, stop:0 rgba(255, 208, 32, 255), stop:1 rgba(255, 196, 19, 255));color:#c97002;border-radius:5;border:#E79F14;}QPushButton:!hover{background-color:#ffbb07;color:#c97002;border-radius:5;}");
    clear();
    nowRecordNum = 4;
    nowCnt -= nowRecordNum;
    nowCnt -= 4;
    if (nowCnt >= 4) prevRecordNum = 4;
    else prevRecordNum = nowCnt;
    int tmpi = 0;
    int pre_x = nowCnt;
    while(nowCnt < newVt.size() && tmpi < 4) {
        int i = (nowCnt % 4) + 1;
        string tmp1 = "_";tmp1+=char('0'+i);tmp1+="1";
        string x1;
        x1 += newVt[nowCnt].first->bookName;
        QLabel * label1 = findChild<QLabel*>(s2q(tmp1));
        label1->setText(s2q(x1));
        //label1->adjustSize();

        string tmp2 = "_";tmp2+=char('0'+i);tmp2+="2";
        string x2;
        x2+=newVt[nowCnt].first->ISBN;
        QLabel * label2 = findChild<QLabel*>(s2q(tmp2));
        label2->setText(s2q(x2));
        //label2->adjustSize();

        string tmp3 = "_";tmp3+=char('0'+i);tmp3+="3";
        string x3 = newVt[nowCnt].first->bookAuthor;
        QLabel * label3 = findChild<QLabel*>(s2q(tmp3));
        label3->setText(s2q(x3));
        //label3->adjustSize();

        string tmp4 = "_";tmp4+=char('0'+i);tmp4+="4";
        string x4 = newVt[nowCnt].first->bookPublish;
        QLabel * label4 = findChild<QLabel*>(s2q(tmp4));
        label4->setText(s2q(x4));
        //label4->adjustSize();

        string tmp5 = "_";tmp5+=char('0'+i);tmp5+="5";
        string x5;
        x5+=char( '0' + newVt[nowCnt].second );x5+="本馆藏";
        QPushButton * pushbotton5 = findChild<QPushButton*>(s2q(tmp5));
        pushbotton5->setVisible(true);
        pushbotton5->setText(s2q(x5));
        tmpi++;
        nowCnt++;
    }
    int now_x = nowCnt;
    nowRecordNum = now_x - pre_x;
}

void index::on_button_exit_clicked()
{
    exit(0);
}

void index::on__15_clicked()
{
    qDebug("ok simida 15");
    emit send(this->ui->_11->text(), this->ui->_12->text(),
              this->ui->_13->text(), this->ui->_14->text());
    bookinformation->show();
}

void index::on__25_clicked()
{
    qDebug("ok simida 25");
    emit send(this->ui->_21->text(), this->ui->_22->text(),
              this->ui->_23->text(), this->ui->_24->text());
    bookinformation->show();
}


void index::on__35_clicked()
{
    qDebug("ok simida 35");
    emit send(this->ui->_31->text(), this->ui->_32->text(),
              this->ui->_33->text(), this->ui->_34->text());
    bookinformation->show();
}

void index::on__45_clicked()
{
    qDebug("ok simida 45");
    emit send(this->ui->_41->text(), this->ui->_42->text(),
              this->ui->_43->text(), this->ui->_44->text());
    bookinformation->show();
}

