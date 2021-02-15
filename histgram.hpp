//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#ifndef _DSPLAB_HISTGRAM_HPP_
#define _DSPLAB_HISTGRAM_HPP_
#include <limits>

namespace dsplab {
    
    namespace math {

        class Histgram {
            private:
                double max;
                double min;
                double bin_width;
                unsigned int *histgram;
                double *bins;
                unsigned int sample_size;
                unsigned int number_of_bins;

            public:
                Histgram();
                ~Histgram();
                Histgram(const Histgram& copy);
                void operator=(const Histgram& copy);
                bool SetHistgram(double min, double max, unsigned int bins);
                inline double GetMax() const { return max; }
                inline double GetMin() const { return min; }
                inline double GetBinWidth() const { return bin_width; }
                inline unsigned int GetSampleSize() const { return sample_size; }
                inline unsigned int GetNumberOfBins() const { return number_of_bins; }
                bool AddSample(double &sample);
                const unsigned int& operator[](unsigned int bin) const;
                double Mean();
                void Clear();
                bool IsEmpty();

            private:
                void Copy(const Histgram &copy);
        };
    }
}
#endif