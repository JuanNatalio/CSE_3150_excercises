#ifndef HYBRID_VEHICLE_H
#define HYBRID_VEHICLE_H

#include "GasolineVehicle.h"
#include "ElectricVehicle.h"

class HybridVehicle : public GasolineVehicle, public ElectricVehicle
{
public:
    HybridVehicle();
    HybridVehicle(double mpg, double electricMiles, double totalkWh);

    double costPerMile(double costOfOneGallon) const;

    double costPerMile(double costPerKwh, bool isElectric) const;
};

#endif
