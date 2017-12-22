#include <QApplication>
#include "../logging.h"
#include "test.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QString path_to_log("/Users/mac/Documents/Technopark/RhytmGame/Rhythm_game/client/logs/mylogs.log");
    Logging::setUpSettings(path_to_log);

    test();

    return a.exec();

}
