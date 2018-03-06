#ifndef CONFIGVALUES_H
#define CONFIGVALUES_H

#include <string>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <iostream>
#include <QDebug>

class ConfigValues
{
public:
    ConfigValues() = default;

    static bool setupConfigs(std::string& path_to_config);

    static int port;
    static QString host;
    static QString music_path;
    static QString parsed_music_path;
    static QString log_file_path;

};


#endif // CONFIGVALUES_H
