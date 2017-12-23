#include <QApplication>
#include "logging.h"
#include "test.h"
#include "configvalues.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QString path_to_log("/Users/mac/Documents/Technopark/RhytmGame/Rhythm_game/client/logs/mylogs.log");
    Logging::setUpSettings(path_to_log);
    std::string path_to_config("/Users/mac/Documents/Technopark/RhytmGame/Rhythm_game/client/config.json");
    if (!ConfigValues::setupConfigs(path_to_config)) {
        return 0;
    }
    test();

    return a.exec();

}
