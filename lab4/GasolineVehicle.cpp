#include "GasolineVehicle.h"

GasolineVehicle::GasolineVehicle() : mpg(0.0) {}

GasolineVehicle::GasolineVehicle(double mpg) : mpg(mpg) {}

void GasolineVehicle::setMPG(double mpg)
{
    this->mpg = mpg;
}

double GasolineVehicle::getMPG() const
{
    return mpg;
}

double GasolineVehicle::calcCostPerMileGas(double costPerGallon) const
{
    if (mpg == 0.0)
    {
        return 0.0;
    }
    return costPerGallon / mpg;
}
