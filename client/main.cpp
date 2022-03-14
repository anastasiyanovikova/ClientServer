#include "client.h"

#include <QApplication>
#include<QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCommandLineParser parser;
    parser.setApplicationDescription("Справка о параметрах запуска приложения");
    parser.addHelpOption();
    QCommandLineOption portOption(QStringList()<<"p"<<"port",".");
    parser.addOption(portOption);

    parser.process(a);
    qDebug()<<parser.isSet(portOption)<<parser.positionalArguments();
    QStringList args = parser.positionalArguments();

    if(parser.isSet("p"))
    {
        Client client;
        client.setWindowTitle(QString("Client port [%1]").arg(args.at(0)));
        client.startNetworking(args.at(0).toUInt());
        client.show();
        return a.exec();
    }
    else
    {
        Client client;
        client.setWindowTitle(QString("Client port 34567"));
        client.startNetworking(34567);
        client.show();
        return a.exec();
    }

}
