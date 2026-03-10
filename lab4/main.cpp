#include <iostream>
#include "HybridVehicle.h"

int main()
{

    HybridVehicle aHybrid;

    double miles = 300;
    aHybrid.setElectricMiles(miles);
    aHybrid.setTotalkWh(70.0);

    double MPGe = aHybrid.calcMPGe();
    std::cout << "MPGe (Miles Per Gallon Equivalent): " << MPGe << std::endl;

    double costOfOneGallon = 3.10;
    double averageCostPerMile = aHybrid.costPerMile(costOfOneGallon);
    std::cout << "Average cost per mile (using gas price): $" << averageCostPerMile << std::endl;

    double costPerKwh = 0.24;
    double costPerMileElectric = aHybrid.calcCostPerMileElectric(costPerKwh);
    std::cout << "Cost per mile (using electricity): $" << costPerMileElectric << std::endl;

    double gasolineEquivalentCost = costPerKwh * 33.7;
    std::cout << "\nFor comparison:" << std::endl;
    std::cout << "Cost of 1 gallon equivalent of electricity: $" << gasolineEquivalentCost << std::endl;
    std::cout << "Cost of 1 gallon of gasoline: $" << costOfOneGallon << std::endl;

    std::cout << "\n--- Testing Gasoline Vehicle Features ---" << std::endl;
    aHybrid.setMPG(35.0);
    double gasCostPerMile = aHybrid.calcCostPerMileGas(costOfOneGallon);
    std::cout << "Cost per mile (gasoline mode, 35 MPG): $" << gasCostPerMile << std::endl;

    return 0;
}
