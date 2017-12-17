#include "test.h"

void test() {

    Client client(getIpAddr(), getPort());
    std::string name("shape.wav");
    std::string name2("test");
    quint8 error_code = 0;

    std::cout << client.getTrackFromServer(error_code, name) << std::endl;
    if (error_code) {
        std::cout << "err_code =" <<  error_code << std::endl;
        error_code = 0;
    }

    std::cout << client.getParsedTrackFromServer(error_code, name2) << std::endl;
    if (error_code) {
        std::cout << "err_code =" <<  error_code << std::endl;
        error_code = 0;
    }

    std::vector<std::string> res =  client.getPlaylistFromServer(error_code);
    for (auto i: res){
        std::cout << i << std::endl;
    }

    std::cout << "all_ok" << std::endl;


}
