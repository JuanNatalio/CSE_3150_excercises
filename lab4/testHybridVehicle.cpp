#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "HybridVehicle.h"
#include <cmath>

TEST_CASE("GasolineVehicle - Basic Functionality")
{
    GasolineVehicle gasVehicle;

    SUBCASE("Default constructor initializes to 0")
    {
        CHECK(gasVehicle.getMPG() == 0.0);
    }

    SUBCASE("Set and get MPG")
    {
        gasVehicle.setMPG(30.0);
        CHECK(gasVehicle.getMPG() == 30.0);
    }

    SUBCASE("Calculate cost per mile")
    {
        gasVehicle.setMPG(25.0);
        double costPerGallon = 3.00;
        double costPerMile = gasVehicle.calcCostPerMileGas(costPerGallon);
        CHECK(costPerMile == doctest::Approx(0.12).epsilon(0.01));
    }

    SUBCASE("Zero MPG returns 0 cost")
    {
        gasVehicle.setMPG(0.0);
        CHECK(gasVehicle.calcCostPerMileGas(3.00) == 0.0);
    }
}

TEST_CASE("GasolineVehicle - Parameterized Constructor")
{
    GasolineVehicle gasVehicle(35.0);
    CHECK(gasVehicle.getMPG() == 35.0);
}

TEST_CASE("ElectricVehicle - Basic Functionality")
{
    ElectricVehicle evVehicle;

    SUBCASE("Default constructor initializes to 0")
    {
        CHECK(evVehicle.getElectricMiles() == 0.0);
        CHECK(evVehicle.getTotalkWh() == 0.0);
    }

    SUBCASE("Set and get electric miles")
    {
        evVehicle.setElectricMiles(100.0);
        CHECK(evVehicle.getElectricMiles() == 100.0);
    }

    SUBCASE("Set and get total kWh")
    {
        evVehicle.setTotalkWh(50.0);
        CHECK(evVehicle.getTotalkWh() == 50.0);
    }

    SUBCASE("Calculate MPGe")
    {
        evVehicle.setElectricMiles(300.0);
        evVehicle.setTotalkWh(70.0);
        double mpge = evVehicle.calcMPGe();

        CHECK(mpge == doctest::Approx(144.43).epsilon(0.01));
    }

    SUBCASE("Zero kWh returns 0 MPGe")
    {
        evVehicle.setElectricMiles(300.0);
        evVehicle.setTotalkWh(0.0);
        CHECK(evVehicle.calcMPGe() == 0.0);
    }

    SUBCASE("Calculate cost per mile electric")
    {
        evVehicle.setElectricMiles(200.0);
        evVehicle.setTotalkWh(50.0);
        double costPerKwh = 0.20;
        double costPerMile = evVehicle.calcCostPerMileElectric(costPerKwh);

        CHECK(costPerMile == doctest::Approx(0.05).epsilon(0.01));
    }
}

TEST_CASE("ElectricVehicle - Parameterized Constructor")
{
    ElectricVehicle evVehicle(250.0, 60.0);
    CHECK(evVehicle.getElectricMiles() == 250.0);
    CHECK(evVehicle.getTotalkWh() == 60.0);
}

TEST_CASE("HybridVehicle - Multi-Inheritance")
{
    HybridVehicle hybrid;

    SUBCASE("Default constructor")
    {
        CHECK(hybrid.getMPG() == 0.0);
        CHECK(hybrid.getElectricMiles() == 0.0);
        CHECK(hybrid.getTotalkWh() == 0.0);
    }

    SUBCASE("Access GasolineVehicle methods")
    {
        hybrid.setMPG(40.0);
        CHECK(hybrid.getMPG() == 40.0);
    }

    SUBCASE("Access ElectricVehicle methods")
    {
        hybrid.setElectricMiles(150.0);
        hybrid.setTotalkWh(45.0);
        CHECK(hybrid.getElectricMiles() == 150.0);
        CHECK(hybrid.getTotalkWh() == 45.0);
    }

    SUBCASE("Calculate MPGe from inherited method")
    {
        hybrid.setElectricMiles(300.0);
        hybrid.setTotalkWh(70.0);
        double mpge = hybrid.calcMPGe();
        CHECK(mpge == doctest::Approx(144.43).epsilon(0.01));
    }
}

TEST_CASE("HybridVehicle - Parameterized Constructor")
{
    HybridVehicle hybrid(35.0, 300.0, 70.0);
    CHECK(hybrid.getMPG() == 35.0);
    CHECK(hybrid.getElectricMiles() == 300.0);
    CHECK(hybrid.getTotalkWh() == 70.0);
}

TEST_CASE("HybridVehicle - Cost Per Mile Calculations")
{
    HybridVehicle hybrid;

    SUBCASE("Cost per mile using gas price (based on MPGe)")
    {
        hybrid.setElectricMiles(300.0);
        hybrid.setTotalkWh(70.0);
        double costOfOneGallon = 3.10;
        double avgCostPerMile = hybrid.costPerMile(costOfOneGallon);

        CHECK(avgCostPerMile == doctest::Approx(0.02146).epsilon(0.001));
    }

    SUBCASE("Cost per mile electric mode")
    {
        hybrid.setElectricMiles(200.0);
        hybrid.setTotalkWh(50.0);
        double costPerKwh = 0.24;
        double costPerMile = hybrid.costPerMile(costPerKwh, true);

        CHECK(costPerMile == doctest::Approx(0.06).epsilon(0.01));
    }
}

TEST_CASE("Real-world Example - From Lab Instructions")
{
    HybridVehicle aHybrid;

    double miles = 300;
    aHybrid.setElectricMiles(miles);
    aHybrid.setTotalkWh(70.0);

    double MPGe = aHybrid.calcMPGe();
    CHECK(MPGe == doctest::Approx(144.43).epsilon(0.01));

    double costOfOneGallon = 3.10;
    double averageCostPerMile = aHybrid.costPerMile(costOfOneGallon);
    CHECK(averageCostPerMile == doctest::Approx(0.02146).epsilon(0.001));
}

TEST_CASE("Connecticut Electricity Cost Example")
{
    HybridVehicle hybrid;
    hybrid.setElectricMiles(100.0);
    hybrid.setTotalkWh(33.7);

    double mpge = hybrid.calcMPGe();
    CHECK(mpge == doctest::Approx(100.0).epsilon(0.1));

    double costPerKwh = 0.24;
    double costOfGallonEquivalent = 33.7 * costPerKwh;
    CHECK(costOfGallonEquivalent == doctest::Approx(8.088).epsilon(0.01));
}

TEST_CASE("Edge Cases")
{
    SUBCASE("Zero electric miles")
    {
        ElectricVehicle ev;
        ev.setElectricMiles(0.0);
        ev.setTotalkWh(50.0);
        CHECK(ev.calcCostPerMileElectric(0.24) == 0.0);
    }

    SUBCASE("Very high efficiency")
    {
        ElectricVehicle ev;
        ev.setElectricMiles(500.0);
        ev.setTotalkWh(30.0);
        double mpge = ev.calcMPGe();
        CHECK(mpge > 500.0);
    }
}
