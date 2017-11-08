#include <QApplication>
#include "client.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client(getIpAddr(), getPort());
    QString name("shape2.wav");
    quint8 error_code = 0;
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 1){
            client.getTrackFromServer(error_code, name);
            if (error_code != 0)
                std::cout << "Error response" << std::endl;
        }
        else
            client.getPlaylistFromServer(error_code);

        delay(1000);
    }

    std::cout << "all_ok" << std::endl;
    return a.exec();
}
