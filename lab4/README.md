# Compile for main

g++ -std=c++11 -o hybrid_demo main.cpp GasolineVehicle.cpp ElectricVehicle.cpp HybridVehicle.cpp

# Run main

./hybrid_demo

# Compile for tests

g++ -std=c++11 -o testHybridVehicle testHybridVehicle.cpp GasolineVehicle.cpp ElectricVehicle.cpp HybridVehicle.cpp

# Run tests

./testHybridVehicle
