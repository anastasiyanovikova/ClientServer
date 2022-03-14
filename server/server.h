#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

class QUdpSocket;
QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();
    void startNetworking(int port=34567);

public slots:
    void showImage(const QPixmap &img);
    void processPendingDatagramms();


private:
    Ui::Server *ui;
    QUdpSocket *socket;
    quint16 socketPort;
    QPixmap decodeImage(const QByteArray&ba) const;
};
#endif // SERVER_H
