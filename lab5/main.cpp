#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "helpers.h"

using namespace std;

struct PairResult
{
    int firstIndex;
    int secondIndex;
    double alpha;

    bool operator<(const PairResult &other) const
    {
        return alpha < other.alpha;
    }
};

int main()
{
    ifstream inputFile("vectors.txt");
    if (!inputFile)
    {
        cerr << "Unable to open vectors.txt" << endl;
        return 1;
    }

    vector<vector<double>> vectors;
    string line;

    while (getline(inputFile, line))
    {
        istringstream lineStream(line);
        vector<double> currentVector;
        double value;

        while (lineStream >> value)
        {
            currentVector.push_back(value);
        }

        if (!currentVector.empty())
        {
            vectors.push_back(currentVector);
        }
    }

    if (vectors.size() < 2)
    {
        cerr << "Need at least two vectors in vectors.txt" << endl;
        return 1;
    }

    const size_t dimension = vectors.front().size();
    for (const vector<double> &currentVector : vectors)
    {
        if (currentVector.size() != dimension)
        {
            cerr << "All vectors must have the same number of components" << endl;
            return 1;
        }
    }

    vector<PairResult> results;

    for (size_t i = 0; i < vectors.size(); ++i)
    {
        for (size_t j = i + 1; j < vectors.size(); ++j)
        {
            double magnitude1 = calculateVectorMagnitude(vectors[i]);
            double magnitude2 = calculateVectorMagnitude(vectors[j]);

            if (magnitude1 == 0.0 || magnitude2 == 0.0)
            {
                cerr << "Zero-length vectors are not allowed" << endl;
                return 1;
            }

            double dotProduct = calculateVectorDotProduct(vectors[i], vectors[j]);
            double alpha = getAlpha(dotProduct, magnitude1, magnitude2);

            results.push_back({static_cast<int>(i), static_cast<int>(j), alpha});
        }
    }

    sort(results.begin(), results.end());

    cout << fixed << setprecision(6);
    for (const PairResult &result : results)
    {
        cout << "Vector " << result.firstIndex << " and Vector " << result.secondIndex
             << " | alpha = " << result.alpha << endl;
    }

    return 0;
}