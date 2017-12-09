#include <QApplication>
#include "logging.h"
#include "test.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logging::setUpSettings();

    test();

    return a.exec();
}
