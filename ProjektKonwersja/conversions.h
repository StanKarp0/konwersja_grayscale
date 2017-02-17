#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <QDomElement>
#include "abstractconversion.h"
#include <cmath>

/**
 * @brief The GrayscaleGimpConv class
 * Klasa zapewnia konwersję obrazu do odcieni szarości. Wynik Konwersji wzorowany na zaimplementownaej
 * w programi Gimp. Funkcja f(x,l,u) zdefiniowana jako f(x,l,u) = {x dla x>l i x<u; l dla x<l; u dla x>u}.
 * Wartość nowego koloru to r = g = b =f((r_w * red + g_w * green + b_w * blue) / (f(r_w,0,1) + f(g_w,0,1) + f(b_w,0,1)),0,255),
 * gdzie r_w, g_w, b_w - kolejne wagi kolorów RGB z przedziału -2 ... 2, red, green, blue - stare watości kolorów RGB,
 * r, g, b - nowe wartości RGB.
 */
class GrayscaleGimpConv: public AbstractConversion {
public:
    GrayscaleGimpConv(const double r, const double g, const double b);
    virtual QColor map(const QColor &c) const;
    virtual AbstractConversion* copy() const {return new GrayscaleGimpConv(_r, _g, _b);}
    virtual QDomElement toXml(QDomDocument &doc) const;
private:
    const double _r, _g, _b, _sum;
};

/**
 * @brief The GrayscaleNormConv class
 * Klasa zapewnia konwersja do odcieni szarości.
 * Funkcja f(x,l,u) zdefiniowana jako f(x,l,u) = {x dla x>l i x<u; l dla x<l; u dla x>u}.
 * Nowy kolor RGB (r,g,b) dla r = g = b = f(r_w * red + g_w * green + b_w * blue,0,255), gdzie
 * gdzie r_w, g_w, b_w - kolejne wagi kolorów RGB z przedziału -2 ... 2, red, green, blue - stare watości kolorów RGB
 */
class GrayscaleNormConv: public AbstractConversion {
public:
    GrayscaleNormConv(const double r, const double g, const double b);
    virtual QColor map(const QColor &c) const;
    virtual AbstractConversion* copy() const {return new GrayscaleNormConv(_r, _g, _b);}
    virtual QDomElement toXml(QDomDocument &doc) const;
private:
    const double _r, _g, _b;
};

/**
 * @brief The DuotoneConv class
 */
class DuotoneConv: public AbstractConversion{
public:
    DuotoneConv(const double hue);
    virtual QColor map(const QColor &c) const;
    virtual AbstractConversion* copy() const {return new DuotoneConv(_hue);}
    virtual QDomElement toXml(QDomDocument &doc) const;
private:
    const double _hue;
};

/**
 * @brief The ReverseDuotoneConv class
 */
class ReverseDuotoneConv: public AbstractConversion{
public:
    ReverseDuotoneConv(const double hue);
    virtual QColor map(const QColor &c) const;
    virtual AbstractConversion* copy() const {return new ReverseDuotoneConv(_hue);}
    virtual QDomElement toXml(QDomDocument &doc) const;
private:
    const double _hue;
};

/**
 * @brief The RangeConv class
 */
class RangeConv: public AbstractConversion{
public:
    RangeConv(const double hue1, const double t, const AbstractConversion &a);
    virtual ~RangeConv();
    virtual QColor map(const QColor &c) const;
    virtual AbstractConversion* copy() const {return new RangeConv(_hue1, _t, *_a);}
    virtual QDomElement toXml(QDomDocument &doc) const;
private:
    const double _hue1, _t;
    const AbstractConversion *_a;
};

/**
 * @brief The MonoRangeConv class
 */
class MonoRangeConv: public AbstractConversion {
public:
    MonoRangeConv(const double hue1, const double t, const AbstractConversion &a);
    virtual ~MonoRangeConv();
    virtual QColor map(const QColor &c) const;
    virtual AbstractConversion* copy() const {return new MonoRangeConv(_hue1, _t, *_a);}
    virtual QDomElement toXml(QDomDocument &doc) const;
private:
    const double _hue1, _t;
    const AbstractConversion *_a;
};

#endif // CONVERSIONS_H
