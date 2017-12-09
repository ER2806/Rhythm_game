#ifndef LOGGING_H
#define LOGGING_H
#include "libs/easylogging++.h"
#include <string>
#include <QDate>

class Logging {
public:
    Logging() = default;
    ~Logging() = default;

    static void setUpSettings() {
        el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "/Users/mac/Documents/Technopark/RhytmGame/Rhythm_game/client/logs/mylogs.log");
        el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%level %datetime{%H:%m:%s} (%func): %msg");
        /* Выключаем выдачу на стандартный поток  */
        el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
        /* Включаем флаг цветной печати */
        el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
        /* Ставим флаг для переключения журналов по размеру файла */
        el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);
        /* Ставим проговое значение на размер файла в 1MB*/
        el::Loggers::reconfigureAllLoggers(el::ConfigurationType::MaxLogFileSize, "8388608");
        /* Передаем callback на переключение файлов */
        el::Helpers::installPreRollOutCallback(LogsRollout);
    }

    static void LogsRollout(const char* fname, size_t fsize)
    {
        /* Допишем к имени файла текущую дату*/
        std::string fileName = fname;
        size_t position = fileName.find(".");
        std::string extractName = (std::string::npos == position)? fileName : fileName.substr(0, position);
        extractName = extractName + "_" +  ((QDate::currentDate()).toString("dd_MM_yyyy")).toStdString() + ".log";

        /* Старый фал журнала уже закрыт, переименуем его */
        int status = rename(fname, extractName.c_str());
        if(status)
        {
            /* Не смогли переименовать */
        }
    }

};

#endif // LOGGING_H
