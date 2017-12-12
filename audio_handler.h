#ifndef AUDIOHANDLER_HPP
#define AUDIOHANDLER_HPP
#include <vector>
#include <array>
#include <string>
const unsigned SPECHEIGHT = 1000;	// height (changing requires palette adjustments too)
const unsigned BANDS = 3;
const double TDIFF = 50; // setup update timer (20hz)

class AudioHandler{
public:
    AudioHandler(const std::string& filename);
    ~AudioHandler();
    void parse();
private:
    class Private;
    Private* private_group;
};

#endif // AUDIOHANDLER_HPP
