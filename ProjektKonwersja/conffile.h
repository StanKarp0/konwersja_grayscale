#ifndef CONFREADER_H
#define CONFREADER_H

#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include "conversions.h"

struct ConfFile {
    static QDomDocument readConf(const QString filename, int &result);
    static void saveConf(const QDomDocument &doc, const QString filename);
    static bool validateConf(const QDomDocument &doc);
};

#endif // CONFREADER_H
