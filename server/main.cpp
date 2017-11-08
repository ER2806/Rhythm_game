#include <QApplication>
#include <server.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Server serv(getPort());
    return a.exec();

}
