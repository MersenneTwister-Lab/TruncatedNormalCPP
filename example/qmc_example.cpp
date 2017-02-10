#include <MCQMCIntegration/TruncatedNormal.h>
#include <MCQMCIntegration/DigitalNet.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;
using namespace MCQMCIntegration;

const uint32_t s = 5;
double LOWER[5] = {-INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY};
double UPPER[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
double SIGMA[5][5] = {
    {1.666667e+00, 8.333333e-01, 8.333333e-01, 8.333333e-01, 8.333333e-01},
    {8.333333e-01, 1.666667e+00, 8.333333e-01, 8.333333e-01, 8.333333e-01},
    {8.333333e-01, 8.333333e-01, 1.666667e+00, 8.333333e-01, 8.333333e-01},
    {8.333333e-01, 8.333333e-01, 8.333333e-01, 1.666667e+00, 8.333333e-01},
    {8.333333e-01, 8.333333e-01, 8.333333e-01, 8.333333e-01, 1.666667e+00}
};

int main()
{
    // prepare integration area.
    vector<double> lower(LOWER, LOWER+s);
    vector<double> upper(UPPER, UPPER+s);
    vector< vector<double> > sigma(s);
    for (uint32_t i = 0; i < s; i++) {
        for (uint32_t j = 0; j < s; j++) {
            sigma[i].push_back(SIGMA[i][j]);
        }
    }

    // QMC
    DigitalNet<uint64_t>::digital_net_id id =
        DigitalNet<uint64_t>::digital_net_id::NXLW;
    const TruncatedNormalResult result
        = truncatedNormal(lower,
                          upper,
                          sigma,
                          10000, // number of samples
                          id,    // Low WAFOM Niederreiter-Xing
                          10,    // 2^10 points in digital net point set.
                          0.99);
    if (!result.success) {
        cout << "calculation failed" << endl;
        return -1;
    }
    // show result
    cout << "probability:" << result.probability << endl;
    cout << "absoluteError:" << result.absoluteError << endl;
    cout << "relativeError:" << result.relativeError << endl;
    cout << "theoreticalUpperBound:" << result.upperBound << endl;
    return 0;
}
