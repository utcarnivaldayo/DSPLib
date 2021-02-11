//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#ifndef _DSPLAB_SOUND_HPP_
#define _DSPLAB_SOUND_HPP_
#include <cstdio>
#include <cmath>
#include <random>
#include <limits>
#include "constants.hpp"
#if defined(__GNUG__) && (__GNUC__ >= 9 && __GNUC_MINOR__ >= 2) 
#elif defined(_MSC_VER) && _MSC_VER >= 1910
#pragma warning(disable:4996)
#else
#include <ctime>
#endif 

namespace dsplab {

    namespace sound {

        class Sound {

            private:
                double* data;
                unsigned int length;
                double time;
                short int quantization_bit;
                unsigned int sampling_frequency;
                unsigned int seed;
                std::mt19937* mtrnd;

            public:
                Sound();
                ~Sound();
                Sound(unsigned int seed);
                Sound(const Sound& copy);
                void operator=(const Sound& copy);
                
                //Read Write file
                bool ReadWAV(const char* filename);
                bool WriteWAV(const char* filename, short int quantization_bit);
                bool ReadDAT(const char* filename, short int quantization_bit, unsigned int sampling_frequency);
                bool WriteDAT(const char* filename, short int quantization_bit);
                bool ReadCSV(const char* filename, unsigned int sampling_frequency);
                bool WriteCSV(const char* filename, short int quantization_bit);
                
                //get
                inline unsigned int GetLength() const {return length;}
                inline short int GetQuantizationBit() const {return quantization_bit;}
                inline unsigned int GetSamplingFrequency() const {return sampling_frequency;}
                inline double GetTime() const {return time;}
                double& operator[](unsigned int sample);
                const double& operator[](unsigned int sample) const;
                
                //generator
                bool GenerateUniform(double min, double max, double time, unsigned int sampling_frequency);
                bool GenerateNormal(double mean, double standard_deviation, double time, unsigned int sampling_frequency);
                bool GenerateSine(double amplitude, double phase, double frequency, double time, unsigned int sampling_frequency);
                bool GenerateCosine(double amplitude, double phase, double frequency, double time, unsigned int sampling_frequency);
                bool GenerateSilence(double time, unsigned int sampling_frequency);
                bool GenerateImpulse(double amplitude, double time, unsigned int sampling_frequency);
                bool GenerateStep(double amplitude, double time, unsigned int sampling_frequency);
                bool GenerateChirp(double amplitude, double phase, double start_frequency, double final_frequency, double time, unsigned int sampling_frequency);
                //bool GenerateSquare(double amplitude, double phase, double frequency, double time, unsigned int sampling_frequency);
                //bool GenerateTriangle(double amplitude, double phase, double frequency, double time, unsigned int sampling_frequency);

                void Clear();
                bool IsEmpty();

                static bool HardClipping(Sound& sound, double threshold_min, double threshold_max);
                static bool Rounding(Sound& sound);
                static bool Gain(Sound& sound, double gain);
                static bool Bias(Sound& sound, double bias);
                static bool AntiPhase(Sound& sound);
                static bool NoiseGate(Sound& sound, double threshold, double ratio);
                static bool Reverse(Sound& sound);
                static bool ReadWAV(const char* filename, Sound* sound, short int channel);
                static bool ReadDAT(const char* filename, Sound* sound, short int channel, short int quantization_bit, unsigned int sampling_frequency);
                static bool WriteWAV(const char* filename, Sound* sound, short int channel, short int quantization_bit);
                static bool WriteDAT(const char* filename, Sound* sound, short int channel, short int quantization_bit);
                static double CalculateSpeedOfSound(double degree_celsius);

            private:
                void Copy(const Sound& copy);
        };
    }
}
#endif 