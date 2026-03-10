#ifndef GASOLINE_VEHICLE_H
#define GASOLINE_VEHICLE_H

class GasolineVehicle
{
private:
    double mpg;

public:
    GasolineVehicle();
    GasolineVehicle(double mpg);

    void setMPG(double mpg);
    double getMPG() const;

    double calcCostPerMileGas(double costPerGallon) const;
};

#endif
