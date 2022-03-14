#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include<QPixmap>
class QUdpSocket;


QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QWidget
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();
    void startNetworking(int port=34567);


public slots:
    void sendImage();



private:
    Ui::Client *ui;
    QUdpSocket *socket;
    quint16 socketPort;
    QPixmap img;
    QByteArray encodeImage(const QPixmap &img);


private slots:
    void onChooseButton();

};
#endif // CLIENT_H
