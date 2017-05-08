#include "filetransfer.h"
#include "ui_filetransfer.h"
#include "filetcpset.h"
#include <QMenu>
#include "tcpset.h"
#include <QFileDialog>
#include <QDebug>

FileTransfer::FileTransfer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileTransfer)
{
    ui->setupUi(this);
    setfixed();
    setoption();
    initloadingbar(0,1000);
    setselectbt();
    connect(_setting,SIGNAL(triggered(bool)),this,SLOT(_setting_clicked()));
    connect(ui->selectpathbtn,SIGNAL(clicked(bool)),this,SLOT(select_clicked()));
    connect(ui->cancelbtn,SIGNAL(clicked(bool)),this,SLOT(close()));
}

FileTransfer::~FileTransfer()
{
    delete ui;
}

void FileTransfer::setfixed(){
    setFixedSize(width(),height());
}
void FileTransfer::setoption(){
     _set=ui->menuBar;
     _option=new QMenu("option");

     QString s_="setting";
     _setting=new QAction(s_,this);
     _option->addAction(_setting);

     s_="about";
     _about=new QAction(s_,this);
     _option->addAction(_about);

     _set->addMenu(_option);
}

void FileTransfer::initloadingbar(int value,int range, bool vis)
{
    ui->downloadBar->setValue(value);
    ui->downloadBar->setRange(0,range);
    ui->downloadBar->setTextVisible(vis);

}

void FileTransfer::setselectbt()
{

}


void FileTransfer::_setting_clicked(){
    if(!_ts){
        _ts=new tcpset();
        //_ts->setWindowFlags(Qt::SubWindow);
        //_ts->show();
        _ts->exec();//屏蔽其他窗口
    }
}

//void FileTransfer::on_selectpathbtn_clicked()
//{
//    ui->filenameEdit->setText(QFileDialog::getExistingDirectory(this));
//    //QFileDialog::getOpenFileName(this);
//}

void FileTransfer::select_clicked()
{
    ui->filenameEdit->setText(QFileDialog::getExistingDirectory(this));
}


