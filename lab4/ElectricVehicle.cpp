#include "ElectricVehicle.h"

ElectricVehicle::ElectricVehicle() : electricMiles(0.0), totalkWh(0.0) {}

ElectricVehicle::ElectricVehicle(double electricMiles, double totalkWh)
    : electricMiles(electricMiles), totalkWh(totalkWh) {}

void ElectricVehicle::setElectricMiles(double miles)
{
    this->electricMiles = miles;
}

double ElectricVehicle::getElectricMiles() const
{
    return electricMiles;
}

void ElectricVehicle::setTotalkWh(double kWh)
{
    this->totalkWh = kWh;
}

double ElectricVehicle::getTotalkWh() const
{
    return totalkWh;
}

double ElectricVehicle::calcMPGe() const
{
    if (totalkWh == 0.0)
    {
        return 0.0;
    }
    return (electricMiles / totalkWh) * KWH_PER_GALLON;
}

double ElectricVehicle::calcCostPerMileElectric(double costPerKwh) const
{
    if (electricMiles == 0.0)
    {
        return 0.0;
    }
    return (totalkWh * costPerKwh) / electricMiles;
}
