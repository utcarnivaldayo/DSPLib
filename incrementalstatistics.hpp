//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#ifndef _DSPLAB_INCREMENTALSTATISTICS_HPP_
#define _DSPLAB_INCREMENTALSTATISTICS_HPP_
#if defined(_MSC_VER) && _MSC_VER >= 1910
#pragma warning(disable:4996)
#endif
#include <cmath>

namespace dsplab {

    namespace math {

        class IncrementalStatistics {
        
            private:
                double mean;
                double m2;
                double c_mean;
                double c_m2;
                unsigned int n;
    
            public:
                IncrementalStatistics();
                ~IncrementalStatistics();
                double Variance() const { return m2 / n;}
                double UnbiasVariance() const { return  n > 1u ? m2 / (n - 1u) : 0.0;}
                double StandardDeviation() const { return std::sqrt(m2 / n); }
                double UnbiasStandardDeviation() const { return n > 1u ? std::sqrt(m2 / (n - 1u)) : 0.0; }
                double Mean() const { return mean;}
                unsigned int Size() const { return n;}
                void AddSample(double sample);
                void Clear();
            
            private:
                void Kahan(double sample, double& sum, double& c);
        };
    }
}
#endif