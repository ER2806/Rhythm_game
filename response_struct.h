#ifndef RESPONSE_STRUCT_H
#define RESPONSE_STRUCT_H

#include <QByteArray>
#include <QDataStream>

struct ResponseStruct {
    quint8 comand;
    QByteArray data;
};

inline QDataStream& operator<<(QDataStream& out, const ResponseStruct& str)
{
    out << str.comand;
    out << str.data;
    return out;
}

inline QDataStream& operator>>(QDataStream& out, ResponseStruct& str)
{
    out >> str.comand;
    out >> str.data;
    return out;
}

#endif // RESPONSE_STRUCT_H
