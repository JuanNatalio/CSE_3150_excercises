#include "HybridVehicle.h"

HybridVehicle::HybridVehicle()
    : GasolineVehicle(), ElectricVehicle() {}

HybridVehicle::HybridVehicle(double mpg, double electricMiles, double totalkWh)
    : GasolineVehicle(mpg), ElectricVehicle(electricMiles, totalkWh) {}

double HybridVehicle::costPerMile(double costOfOneGallon) const
{
    double mpge = calcMPGe();

    if (mpge == 0.0)
    {
        return 0.0;
    }

    return costOfOneGallon / mpge;
}

double HybridVehicle::costPerMile(double costPerKwh, bool isElectric) const
{
    if (isElectric)
    {
        return calcCostPerMileElectric(costPerKwh);
    }
    else
    {
        double costPerGallon = costPerKwh * 33.7;
        return calcCostPerMileGas(costPerGallon);
    }
}
