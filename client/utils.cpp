#include "utils.h"


int getPort() {
    return 8000;
}


QString getIpAddr() {
    return QString("localhost");
}


QString getPathToMusicsFile() {
    return QString ("/Users/mac/Documents/Technopark/RhytmGame/MyServer/client/music/");
}


void delay(int msec_to_wait) {
    QTime dieTime= QTime::currentTime().addMSecs(msec_to_wait);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
