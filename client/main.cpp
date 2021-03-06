#include <QApplication>
#include "logging.h"
#include "test.h"
#include "configvalues.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    if (argc < 2) {
        qDebug() << "The path to the configuration file is not specified";
        return 0;
    }

    std::string path = argv[1];

    if (ConfigValues::setupConfigs(path) == false){
        return 0;
    }

    Logging::setUpSettings(ConfigValues::log_file_path);

    test();

    return a.exec();

}
