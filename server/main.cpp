#include <QApplication>
#include <server.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Server serv(getPort());
    serv.run();
    return a.exec();

}
