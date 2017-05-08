#ifndef TCPSET_H
#define TCPSET_H

#include <QDialog>
#include <QString>

namespace Ui {
class tcpset;
}

class tcpset : public QDialog
{
    Q_OBJECT

public:
    explicit tcpset(QWidget *parent = 0);
    ~tcpset();
public:
    QString& getIP();
    short& getPort();
private:
    bool IPchecked(QString& ip,short& port);
private slots:
    void on_OKButton_clicked(bool checked);

private:
    Ui::tcpset *ui;
    QString _ip;
    short _port;
};

#endif // TCPSET_H
