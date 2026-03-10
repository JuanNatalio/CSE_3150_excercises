#ifndef ELECTRIC_VEHICLE_H
#define ELECTRIC_VEHICLE_H

class ElectricVehicle
{
private:
    double electricMiles;
    double totalkWh;

    static constexpr double KWH_PER_GALLON = 33.7;

public:
    ElectricVehicle();
    ElectricVehicle(double electricMiles, double totalkWh);

    void setElectricMiles(double miles);
    double getElectricMiles() const;

    void setTotalkWh(double kWh);
    double getTotalkWh() const;

    double calcMPGe() const;

    double calcCostPerMileElectric(double costPerKwh) const;
};

#endif
