#include "server.h"

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
        Server server;
        server.setWindowTitle(QString("Server port [%1]").arg(args.at(0)));
        server.startNetworking(args.at(0).toUInt());
        server.show();
        return a.exec();
    }
    else
    {
        Server server;
        server.setWindowTitle(QString("Server port 34567"));
        server.startNetworking(34567);
        server.show();
        return a.exec();
    }

}
