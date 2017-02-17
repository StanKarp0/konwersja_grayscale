#include "conversiontool.h"

ConversionTool::ConversionTool(const double merge):_merge(merge){
}
ConversionTool::ConversionTool(const ConversionTool& ct):_merge(ct._merge){
    for(std::vector<AbstractConversion*>::const_iterator i = ct.chain.begin(); i != ct.chain.end(); i++) {
        chain.push_back((*i)->copy());
    }
}

QImage ConversionTool::operator()(const QImage& src) const{
    QImage dst = src.convertToFormat(src.hasAlphaChannel() ? QImage::Format_ARGB32 : QImage::Format_RGB32);
    unsigned int *data = (unsigned int*)dst.bits();
    int pixelCount = dst.width() * dst.height();
    const double l = 1 - _merge, p = _merge;
    for(int i = 0; i < pixelCount; ++i) {
        QColor oc(*data);
        QColor nc = conversion(oc);
        *data = qRgba(oc.red() * l + nc.red() * p, oc.green() * l + nc.green() * p, oc.blue() * l + nc.blue() * p, oc.alpha());
        ++data;
    }
    return dst;
}
ConversionTool::~ConversionTool(){
    for(std::vector<AbstractConversion*>::iterator i = chain.begin(); i != chain.end(); i++) {
        delete (*i);
    }
}

ConversionTool& ConversionTool::add(const AbstractConversion &a) {
    chain.push_back(a.copy());
    return *this;
}
QColor ConversionTool::conversion(const QColor c) const {
    QColor temp = c;

    for(std::vector<AbstractConversion*>::const_iterator i = chain.begin(); i != chain.end(); i++) {
        temp = (*i)->map(temp);
    }
    return temp;
}
QDomDocument ConversionTool::document() const {
    QDomDocument doc;
    QDomElement root = doc.createElement("conversion");
    root.setAttribute("merge",_merge*100);
    doc.appendChild(root);
    for(std::vector<AbstractConversion*>::const_iterator i = chain.begin(); i != chain.end(); i++) {
        root.appendChild((*i)->toXml(doc));
    }
    return doc;
}
