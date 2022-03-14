#include "server.h"
#include "ui_server.h"
#include <QUdpSocket>
#include <QTime>

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    socket = nullptr;
    ui->lineEdit->setReadOnly(true);
}

Server::~Server()
{
    delete ui;
}

//Установка соединения
void Server::startNetworking(int port)
{
    socket = new QUdpSocket(this);
    socketPort=port;
    socket->bind(socketPort,QAbstractSocket::ShareAddress|QAbstractSocket::ReuseAddressHint);
    connect(socket,SIGNAL(readyRead()),this,SLOT(processPendingDatagramms()));
}

//Отображение полученной картинки
void Server::showImage(const QPixmap &img)
{
    ui->label->setPixmap(img);
    QTime t=QTime::currentTime();
    ui->lineEdit->setText(QString("Время получения картинки %1").arg(t.toString()));
}

//Обработка получения датаграммы
void Server::processPendingDatagramms()
{
    QByteArray buf;
    while(socket->hasPendingDatagrams())
    {
        buf.resize(socket->pendingDatagramSize());
        socket->readDatagram(buf.data(),buf.size());
        QPixmap p = decodeImage(buf);
        showImage(p);
    }
}

//Декодирование полученного сообщения
QPixmap Server::decodeImage(const QByteArray &ba) const
{
    QDataStream stream(ba);
    QPixmap img;
    stream>>img;
    return img;
}

