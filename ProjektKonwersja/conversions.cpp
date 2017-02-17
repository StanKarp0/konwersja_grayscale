#include "conversions.h"
#include <iostream>

//////////////////////////////////
GrayscaleGimpConv::GrayscaleGimpConv(const double r, const double g, const double b)
    :_r(r), _g(g), _b(b),_sum(toRange(r, 0., 1.) + toRange(g, 0., 1.) + toRange(b, 0., 1.)){
}
QColor GrayscaleGimpConv::map(const QColor &c) const {
    int val = toRange((c.red() * _r + c.green() * _g + c.blue() * _b)/_sum, 0., 255.);
    return QColor(val, val, val, c.alpha());
}
QDomElement GrayscaleGimpConv::toXml(QDomDocument &doc) const {
    QDomElement node = doc.createElement("grayscale");
    node.setAttribute("n",0);
    node.setAttribute("red",_r*100);
    node.setAttribute("green",_g*100);
    node.setAttribute("blue",_b*100);
    return node;
}
///////////////////////////////////
GrayscaleNormConv::GrayscaleNormConv(const double r, const double g, const double b)
    :_r(r), _g(g), _b(b){
}
QColor GrayscaleNormConv::map(const QColor &c) const {
    int val = toRange(c.red() * _r + c.green() * _g + c.blue() * _b, 0., 255.);
    return QColor(val, val, val, c.alpha());
}
QDomElement GrayscaleNormConv::toXml(QDomDocument &doc) const {
    QDomElement node = doc.createElement("grayscale");
    node.setAttribute("n",1);
    node.setAttribute("red",_r*100);
    node.setAttribute("green",_g*100);
    node.setAttribute("blue",_b*100);
    return node;
}
///////////////////////////////////
DuotoneConv::DuotoneConv(const double hue):_hue(hue){}
QColor DuotoneConv::map(const QColor &c) const {
    QColor s = c;
    s.setHsl(_hue, 255 - s.lightness(), s.lightness(), s.alpha());
    return s;
}
QDomElement DuotoneConv::toXml(QDomDocument &doc) const {
    QDomElement node = doc.createElement("duotone");
    node.setAttribute("n",1);
    node.setAttribute("hue",_hue);
    return node;
}
//////////////////////////////////
ReverseDuotoneConv::ReverseDuotoneConv(const double hue):_hue(hue){}
QColor ReverseDuotoneConv::map(const QColor &c) const {
    QColor s = c;
    s.setHsl(_hue, s.lightness(), s.lightness(), s.alpha());
    return s;
}
QDomElement ReverseDuotoneConv::toXml(QDomDocument &doc) const {
    QDomElement node = doc.createElement("duotone");
    node.setAttribute("n",2);
    node.setAttribute("hue",_hue);
    return node;
}
//////////////////////////////////
RangeConv::RangeConv(const double hue1, const double t, const AbstractConversion &a):_hue1(hue1), _t(t), _a(a.copy()){}
RangeConv::~RangeConv(){
    delete _a;
}
QColor RangeConv::map(const QColor &c) const {
    QColor n = c;
    double s = _t * 360.;
    double rAbs = fabs(c.hue() - _hue1);
    double r = std::min(rAbs,360. - rAbs);
    if(r < s) {
        double v = (s - r)/s;
        n.setHsl(c.hue(), c.saturation() * v, c.lightness());
        return n;
    }
    return _a->map(c);
}
QDomElement RangeConv::toXml(QDomDocument &doc) const {
    QDomElement node = doc.createElement("range");
    node.setAttribute("n",1);
    node.setAttribute("hue",_hue1);
    node.setAttribute("tol",_t*100);
    return node;
}
///////////////////////////////////
MonoRangeConv::MonoRangeConv(const double hue1, const double t, const AbstractConversion &a):_hue1(hue1), _t(t), _a(a.copy()){}
MonoRangeConv::~MonoRangeConv(){
    delete _a;
}
QColor MonoRangeConv::map(const QColor &c) const {
    QColor n = c;
    double s = _t * 360.;
    double rAbs = fabs(c.hue() - _hue1);
    double r = std::min(rAbs,360. - rAbs);
    if(r < s) {
        double v = (s - r)/s;
        n.setHsl(_hue1, c.saturation() * v, c.lightness());
        return n;
    }
    return _a->map(c);
}
QDomElement MonoRangeConv::toXml(QDomDocument &doc) const {
    QDomElement node = doc.createElement("range");
    node.setAttribute("n",2);
    node.setAttribute("hue",_hue1);
    node.setAttribute("tol",_t*100);
    return node;
}
