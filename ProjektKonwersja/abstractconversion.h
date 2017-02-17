#ifndef ABSTRACTCONVERSION_H
#define ABSTRACTCONVERSION_H

#include <QImage>
#include <QColor>
#include <QDomElement>

#include <cmath>
#include <iostream>
#include <vector>

/**
 * @brief The AbstractConversion struct
 * Klasa abstrakcyjna AbstractConversion zapewnia interfejs dla klas
 * zapewniających konwersję kolorów.
 */
struct AbstractConversion {

    virtual ~AbstractConversion() {}

    /**
     * @brief map Metoda zapewnia konwersje z jednego koloru na drugi.
     * @param c Kolor wejściowy.
     * @return Kolor wyjściowy.
     */
    virtual QColor map(const QColor &c) const = 0;

    /**
     * @brief copy Wykonuje kopie obiektu.
     * @return Metoda zwraca wskaźnik na zaalokowany wskaźnik. Samodzielna dealokacja.
     */
    virtual AbstractConversion* copy() const = 0;

    /**
     * @brief toXml Przetwarza obiekt do postaci xml.
     * @param doc Dokument w którym stworzony ma być xml.
     * @return Element xml z danymi potrzebnymi do odtworzenia obiektu.
     */
    virtual QDomElement toXml(QDomDocument &doc) const = 0;

    /**
     * @brief toRange Realizuje funkcję r(x) = {x dla x>l i x<u; l dla x<l; u dla x>u}
     * @param value Argument x funkcji.
     * @param l Dolna granica.
     * @param u Górna granica.
     * @return Wynik funkcji.
     */
    static double toRange(const double value, const double l, const double u);
};

#endif // ABSTRACTCONVERSION_H
