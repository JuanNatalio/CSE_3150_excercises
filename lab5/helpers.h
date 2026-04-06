#ifndef HELPERS_H
#define HELPERS_H

#include <vector>

using namespace std;

double calculateVectorMagnitude(vector<double> vec);
double calculateVectorDotProduct(vector<double> vec1, vector<double> vec2);
double getAlpha(double dotProduct, double magnitude1, double magnitude2);

#endif