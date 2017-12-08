#include <QApplication>
#include <server.h>
#include "logging.h"
#include "utils/networkutils.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Logging log;
    log.setUpSettings();
    Server serv(getPort());
    serv.run();
    return a.exec();

}
