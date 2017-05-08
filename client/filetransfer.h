#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include "tcpset.h"
namespace Ui {
class FileTransfer;
}

class FileTransfer : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileTransfer(QWidget *parent = 0);
    ~FileTransfer();
private:
    void setfixed();
    void setoption();
    void initloadingbar(int value,int range,bool vis=false);
    void setselectbt();
private slots:
    void _setting_clicked();
//    void on_selectpathbtn_clicked();
    void select_clicked();
//    void calcel_clicked();
private:
    Ui::FileTransfer *ui;
    QMenuBar* _set;
    QMenu* _option;
    QAction* _setting;
    QAction* _about;

    tcpset* _ts;
};

#endif // FILETRANSFER_H
