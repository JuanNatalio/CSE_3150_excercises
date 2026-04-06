#include "helpers.h"
#include <cmath>

double calculateVectorMagnitude(vector<double> vec)
{
    double sum = 0.0;
    for (double num : vec)
    {
        sum += num * num;
    }

    return sqrt(sum);
};

double calculateVectorDotProduct(vector<double> vec1, vector<double> vec2)
{
    double dotProduct = 0.0;
    for (int i = 0; i < vec1.size(); i++)
    {
        dotProduct += vec1[i] * vec2[i];
    }
    return dotProduct;
};

double getAlpha(double dotProduct, double magnitude1, double magnitude2)
{
    return acos(dotProduct / (magnitude1 * magnitude2));
};
