#include "tcpset.h"
#include "ui_tcpset.h"
#include <QDebug>
#include <QMessageBox>

tcpset::tcpset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tcpset)
{
    ui->setupUi(this);
    _ip="";
    _port=0;
    setFixedSize(width(),height());
    connect(ui->OKButton,SIGNAL(on_OKButton_clicked(bool)),this,SLOT(close()));
}

tcpset::~tcpset()
{
    delete ui;
}

QString &tcpset::getIP()
{
    return _ip;
}

short &tcpset::getPort()
{
    return _port;
}

bool tcpset::IPchecked(QString &ip, short &port){
    bool legal=false;
    int count=0;
    qDebug()<<ip.size();
    for(int i=0;i<ip.size();++i){
        qDebug()<<ip[i]<<" ";
       if(ip[i]=='.'){//统计点
           count++;
           continue;
       }
       else if(ip[i]>='0'&&ip[i]<='9')
            continue;
        else if(ip[i]==' '){
           legal=false;
           return legal;
       }
       else{
           legal=false;
           return legal;
       }
    }
    qDebug()<<"cout:"<<count<<";"<<port;
    if(count==3&&port)
        legal=true;
    return legal;
}

void tcpset::on_OKButton_clicked(bool checked)
{
    if(!checked){
        _ip=ui->IPEdit->text();
        _port=ui->PORTEdit->text().toInt();
    }
     if(!IPchecked(_ip,_port)){
        _ip="";
        _port=0;
        QMessageBox::information(NULL,"error!","invalid address!",QMessageBox::Yes,QMessageBox::Yes);
    }
//    close();

//    qDebug()<<_ip;
//    qDebug()<<_port;
}
