#include "abstractconversion.h"

double AbstractConversion::toRange(const double value, const double l, const double u){
    return std::max(l,std::min(value,u));
}
