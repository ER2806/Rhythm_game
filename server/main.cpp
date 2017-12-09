#include <QApplication>
#include <server.h>
#include "logging.h"
#include "utils/networkutils.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Logging::setUpSettings();
    Server serv(getPort());

    try {
        serv.run();
    } catch(std::logic_error& ex) {
        LOG(ERROR) << ex.what();
    }

    return a.exec();

}
