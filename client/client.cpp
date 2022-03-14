#include "client.h"
#include "ui_client.h"
#include<QUdpSocket>
#include <QAbstractSocket>
#include<QFileDialog>
#include <QMessageBox>

Client::Client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    socket=nullptr;
    ui->choose_btn->setStyleSheet("padding: 3px;");
    QObject::connect (ui->choose_btn, &QPushButton::clicked, this, &Client::onChooseButton);
    QObject::connect( ui->send_btn, &QPushButton::clicked, this, &Client::sendImage);
    ui->send_btn->setEnabled(false);
}

Client::~Client()
{
    delete ui;
}

//Установка соединения
void Client::startNetworking(int port)
{
    socket = new QUdpSocket(this);
    socketPort=port;
    socket->bind(socketPort,QAbstractSocket::ShareAddress|QAbstractSocket::ReuseAddressHint);

}

//Отправка картинки
void Client::sendImage()
{
    QByteArray d=encodeImage(img);
    socket->writeDatagram(d,QHostAddress::Broadcast,socketPort);
}

//Кодирование картинки для отправки
QByteArray Client::encodeImage(const QPixmap &img)
{
    QByteArray d;
    QDataStream st(&d,QIODevice::WriteOnly);
    st<<img;
    return d;
}

//Выбор файла с картинкой
void Client::onChooseButton()
{
    QString fileName = QFileDialog::getOpenFileName (this,
        tr ("Выбор картинки"), "/home", tr ("Files (*.jpeg *.jpg *.png )"));
    if(fileName!="")
    {
        img.load(fileName);
        img=img.scaled(600,600,Qt::AspectRatioMode::KeepAspectRatio);
        ui->label->setPixmap(img);
        ui->send_btn->setEnabled(true);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText ("Картинка не выбрана");
        msgBox.setIcon (QMessageBox::Critical);
        msgBox.exec ();
    }

}


