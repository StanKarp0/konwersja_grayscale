#include "conffile.h"


QDomDocument ConfFile::readConf(const QString filename, int &result){
    //TODO odczytywanie konfiguracji
    QDomDocument doc;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
        std::cout << "can't open file";
        result = 0;
    }
    if (!doc.setContent(&file)) {
        file.close();
        std::cout << "can't set content file";
        result = 0;
    }
    file.close();
    /*QDomElement root = doc.createElement("conversion");
    root.setAttribute("merge",60);
    doc.appendChild(root);
    root.appendChild(GrayscaleGimpConv(-1,1,0.5).toXml(doc));*/
    return doc;
}

void ConfFile::saveConf(const QDomDocument &doc, const QString filename){
    //TODO zapisywanie konfuiguracji
    //QFile file(filename);
    /*QFile file(filename);
    file.open(QIODevice::WriteOnly);
    //file.open(filename, QIODevice::WriteOnly);
    file.write(doc.toString(), qstrlen(doc.toString()));        // write to stderr
    file.close();*/
    QFile data(filename);
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        //out << "Result: " << qSetFieldWidth(10) << left << 3.14 << 2.7;
        out << doc.toString();
        // writes "Result: 3.14      2.7       "
    }
    data.close();
}
bool ConfFile::validateConf(const QDomDocument &doc) {
    return true;
}
