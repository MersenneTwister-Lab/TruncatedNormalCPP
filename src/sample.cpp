/**
 * @file sample.cpp
 *
 * @brief A test program of TruncatedNormal
 *
 * @author Shinsuke Mori (Hiroshima University)
 * @author Makoto Matsumoto (Hiroshima University)
 * @author Mutsuo Saito
 *
 * Copyright (C) 2017 Shinsuke Mori, Makoto Matsumoto, Mutsuo Saito
 * and Hiroshima University.
 * All rights reserved.
 *
 * The GPL ver.3 is applied to this software, see
 * COPYING
 */
#include <MCQMCIntegration/TruncatedNormal.h>
#include <MCQMCIntegration/DigitalNet.h>
#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <cerrno>
#include <getopt.h>

//#define DEBUG 1
//#include <MCQMCIntegration/TruncatedNormal.h>

using namespace std;
using namespace MCQMCIntegration;

namespace {
    // parameter example
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

    struct cmd_option {
        bool qmc;
//        bool number;
//        DigitalNet<uint64_t>::digital_net_id digitalNet;
    };

    bool parse(cmd_option& opt, int argc, char * argv[]);
    void show_error_message(string& pgm);
    void qmc(const vector<double>& lower,
             const vector<double>& upper,
             const vector< vector<double> >& sigma);
    void mc(const vector<double>& lower,
            const vector<double>& upper,
            const vector< vector<double> >& sigma);
}

int main(int argc, char *argv[])
{
    cmd_option opt;
    if (!parse(opt, argc, argv)) {
        return -1;
    }
    // prepare integration area.
    vector<double> lower(LOWER, LOWER+s);
    vector<double> upper(UPPER, UPPER+s);
    vector< vector<double> > sigma(s);
    for (uint32_t i = 0; i < s; i++) {
        for (uint32_t j = 0; j < s; j++) {
            sigma[i].push_back(SIGMA[i][j]);
        }
    }
#if defined(DEBUG)
    cout << "lower:" << endl;
    for (uint32_t i = 0; i < s; i++) {
        cout << lower[i] << " ";
    }
    cout << endl;
    cout << "upper:" << endl;
    for (uint32_t i = 0; i < s; i++) {
        cout << upper[i] << " ";
    }
    cout << endl;
    cout << "sigma:" << endl;
    for (uint32_t i = 0; i < s; i++) {
        for (uint32_t j = 0; j < s; j++) {
            cout << sigma[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
#endif

    if (opt.qmc) {
        qmc(lower, upper, sigma);
    } else {
        mc(lower, upper, sigma);
    }
    return 0;
}

namespace {

    void qmc(const vector<double>& lower,
             const vector<double>& upper,
             const vector< vector<double> >& sigma)
    {
#if defined(DEBUG)
        cout << "start qmc" << endl;
#endif
        DigitalNet<uint64_t>::digital_net_id id =
            DigitalNet<uint64_t>::digital_net_id::NXLW;
        //DigitalNet<uint64_t> digitalNet(id, s - 1, 10);
#if defined(DEBUG)
        //digitalNet.showStatus(cout);
        cout << "before truncatedNormal" << endl;
#endif
        const TruncatedNormalResult result
            = truncatedNormal(lower,
                              upper,
                              sigma,
                              10000, // number of samples
                              id, // NXLW
                              10,
//                              digitalNet, // NXLW
                              0.99);
#if defined(DEBUG)
        cout << "after truncatedNormal" << endl;
#endif
        if (!result.success) {
            cout << "calculation failed" << endl;
            return;
        }
        cout << "probability:" << result.probability << endl;
        cout << "absoluteError:" << result.absoluteError << endl;
        cout << "relativeError:" << result.relativeError << endl;
        cout << "theoreticalUpperBound:" << result.upperBound << endl;
    }

    void mc(const vector<double>& lower,
            const vector<double>& upper,
            const vector< vector<double> >& sigma)
    {
        const TruncatedNormalResult result
            = truncatedNormalMC(lower,
                                upper,
                                sigma,
                                10000, // number of trials.
                                1000, // number of samples per a trial.
                                0.99);
        if (!result.success) {
            cout << "calculation failed" << endl;
            return;
        }
        cout << "probability:" << result.probability << endl;
        cout << "absoluteError:" << result.absoluteError << endl;
        cout << "relativeError:" << result.relativeError << endl;
        cout << "theoreticalUpperBound:" << result.upperBound << endl;
    }

    bool parse(cmd_option& opt, int argc, char * argv[])
    {
        opt.qmc = true;
        static struct option longopts[] = {
            {"qmc", no_argument, NULL, 'q'},
            {"mc", no_argument, NULL, 'm'},
            {NULL, 0, NULL, 0}};
        string pgm = argv[0];
        int c;
        bool error = false;
        errno = 0;
        for (;;) {
            if (error) {
                break;
            }
            c = getopt_long(argc, argv, "?qm", longopts, NULL);
            if (c < 0) {
                break;
            }
            switch (c) {
            case 'q':
                opt.qmc = true;
                break;
            case 'm':
                opt.qmc = false;
                break;
            case '?':
            default:
                error = true;
                break;
            }
        }
        if (error) {
            show_error_message(pgm);
            return false;
        }
        return true;
    }

    void show_error_message(string& pgm)
    {
        cout << pgm << " [-q] [-m]" << endl;
        cout << "\t--qmc, -q\tcalculate sample by QMC. (default)" << endl;
        cout << "\t--mc, -m\tcalculate sample by MC." << endl;
    }

}
