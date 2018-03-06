#include "delay.h"

void delay(int msec_to_wait) {

    QTime dieTime= QTime::currentTime().addMSecs(msec_to_wait);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}
