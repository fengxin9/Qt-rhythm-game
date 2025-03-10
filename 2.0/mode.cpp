#include "mode.h"
#include "ui_mode.h"
#include "gamewindow.h"
#include "QMessageBox"

mode::mode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mode)
{
    ui->setupUi(this);
    this->setFixedSize(1800,1300);
}

mode::~mode()
{
    delete ui;
}

int flag=0;
void mode::on_radioButton_toggled(bool checked)
{
    if(checked)
    flag=1;
}

void mode::on_radioButton_2_toggled(bool checked)
{
    if(checked)
        flag=2;
}

void mode::on_pushButton_clicked()
{
    if(flag==1){
        this->close();
        g=new gamewindow;
        g->show();
        QMessageBox::information(this,"教程","键盘A,S,K,L分别控制从左到右的轨道");
    }
    //打开谱面1
    else
       {
        if(flag==2){
            QMessageBox::information(this,"提示","未完待续");
        }
        //谱面2未完待续
        else{
            QMessageBox::information(this,"提示","请选择音乐！");
        }
        //未选择
    }
}


