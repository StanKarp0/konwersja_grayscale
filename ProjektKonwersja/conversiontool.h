#ifndef CONVERSIONTOOL_H
#define CONVERSIONTOOL_H

#include <QImage>
#include <QDomDocument>
#include "abstractconversion.h"

class ConversionTool {
public:
    ConversionTool(const double merge);
    ConversionTool(const ConversionTool& ct);
    ~ConversionTool();
    QImage operator()(const QImage& src) const;
    ConversionTool& add(const AbstractConversion &a);
    QDomDocument document() const;
private:
    QColor conversion(const QColor c) const;
    std::vector<AbstractConversion*> chain;
    const double _merge;
};

#endif // CONVERSIONTOOL_H
