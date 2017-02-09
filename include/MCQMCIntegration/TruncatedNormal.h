#pragma once
#ifndef MCQMC_INTEGRATION_TRUNCATED_NORMAL_H
#define MCQMC_INTEGRATION_TRUNCATED_NORMAL_H
/**
 * @file TruncatedNormal.h
 *
 * @brief Calculate Truncated Multivalual Normal Distribution
 *
 * @author Zdravko I. Botev (original R version)
 * @author Shinsuke Mori (port to C++)
 * @author Makoto Matsumoto
 * @author Mutsuo Saito (little bit modification for publish)
 *
 * Copyright (C) 2015 Zdravko I. Botev.
 *
 * Copyright (C) 2017 Shinsuke Mori, Makoto Matsumoto, Mutsuo Saito
 * and Hiroshima University.
 * All rights reserved.
 *
 * The GPL ver.3 is applied to this software, see
 * COPYING
 */

#include <MCQMCIntegration/DigitalNet.h>
#include <vector>
#include <inttypes.h>

namespace MCQMCIntegration {

    /**
     * structure of the result of truncatedNormal.
     */
    struct TruncatedNormalResult {
        double probability;     /// estimated value of probability
                                /// Pr(@c lower < X < @c upper).
        double absoluteError;   /// absolute error.
        double relativeError;   /// relative error.
        double upperBound;      /// theoretical upper bound on true
                                /// Pr(@c lower < X < @c upper).
        bool success;           /// calculation success or not.
    };

    /**
     * compute Multivariate Normal Distribution by Quasi Monte-Carlo method.
     *
     * computes an estimator and a deterministic upper bound of the
     * probability P r(@c lower < X < @c upper), where X is a
     * zero-mean multivariate normal vector with covariance matrix Σ,
     * that is, X is drawn from N(0, Σ) infinite values for vectors @c
     * upper and @c lower are accepted; Monte Carlo method uses sample
     * size n;
     *
     * @note parameter @c dn, digital net should have dimension s =
     * lower.size - 1.
     *
     * @param[in] lower lower truncation limit.
     * @param[in] upper upper truncation limit.
     * @param[in] sigma covariance matrix of N(0, Σ)
     * @param[in] number Monte Carlo simulation effort — the larger the n,
     * the smaller the relative error of the estimator.
     * @param[in,out] dn digital net.
     * @param[in] probability expected probability such that the
     * result is in the range [p-σ, p+σ].
     * @return estimated value of probability and other information.
     */
    TruncatedNormalResult truncatedNormal(
        const std::vector<double>& lower,
        const std::vector<double>& upper,
        const std::vector< std::vector<double> >& sigma,
        uint64_t number,
        DigitalNet<uint64_t>& dn,
        double probability);

    /**
     * compute Multivariate Normal Distribution by Quasi Monte-Carlo method.
     *
     * computes an estimator and a deterministic upper bound of the
     * probability P r(@c lower < X < @c upper), where X is a
     * zero-mean multivariate normal vector with covariance matrix Σ,
     * that is, X is drawn from N(0, Σ) infinite values for vectors @c
     * upper and @c lower are accepted; Monte Carlo method uses sample
     * size @c number;
     *
     * @c dnid is one of
     * @li @c DigitalNet::digital_net_id::NXLW
     * @li @c DigitalNet::digital_net_id::SOLW Sobol Low WAFOM
     *
     * @c probability shoud be one of {0.95, 0.99, 0.999, 0.9999}
     *
     * @param[in] lower lower truncation limit.
     * @param[in] upper upper truncation limit.
     * @param[in] sigma covariance matrix of N(0, Σ)
     * @param[in] number Monte Carlo simulation effort — the larger
     * the @c number, the smaller the relative error of the estimator.
     * @param[in] dnid digital netid.
     * @param[in] m F2 dimention of element of digital net.
     * @param[in] probability expected probability such that the
     * result is in the range [p - @c absoluteError, p + @c absoluteError].
     * @return estimated value of probability and other information.
     */
    TruncatedNormalResult truncatedNormal(
        const std::vector<double>& lower,
        const std::vector<double>& upper,
        const std::vector< std::vector<double> >& sigma,
        uint64_t number,
        DigitalNet<uint64_t>::digital_net_id dnid
        = DigitalNet<uint64_t>::digital_net_id::NXLW,
        uint32_t m = 10,
        double probability = 0.99);

    /**
     * compute Multivariate Normal Distribution by Monte-Carlo method.
     *
     * computes an estimator and a deterministic upper bound of the
     * probability P r(@c lower < X < @c upper), where X is a
     * zero-mean multivariate normal vector with covariance matrix Σ,
     * that is, X is drawn from N(0, Σ) infinite values for vectors @c
     * upper and @c lower are accepted; Monte Carlo method uses sample
     * size @c number;
     *
     * @c dnid is one of
     * @li @c DigitalNet::digital_net_id::NXLW
     * @li @c DigitalNet::digital_net_id::SOLW Sobol Low WAFOM
     * @li @c DigitalNet::digital_net_id::RANDOM Monte-Carlo method
     *
     * @c probability shoud be one of {0.95, 0.99, 0.999, 0.9999}
     *
     * @param[in] lower lower truncation limit.
     * @param[in] upper upper truncation limit.
     * @param[in] sigma covariance matrix of N(0, Σ)
     * @param[in] trialNumber Monte Carlo simulation effort — the larger
     * the @c number, the smaller the relative error of the estimator.
     * @param[in] sampleNumber sample number per a trial.
     * @param[in] probability expected probability such that the
     * result is in the range [p - @c absoluteError, p + @c absoluteError].
     * @return estimated value of probability and other information.
     */
    TruncatedNormalResult truncatedNormalMC(
        const std::vector<double>& lower,
        const std::vector<double>& upper,
        const std::vector< std::vector<double> >& sigma,
        uint32_t trialNumber,
        uint32_t sampleNumber,
        double probability = 0.99);

}
#endif // MCQMC_INTEGRATION_TRUNCATED_NORMAL_H
