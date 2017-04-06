#include "tmp.h"
#include "ui_tmp.h"

tmp::tmp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tmp)
{
    ui->setupUi(this);
}

tmp::~tmp()
{
    delete ui;
}

void tmp::on_pushButton_clicked()
{

}

void tmp::on_pushButton_2_clicked()
{

}
