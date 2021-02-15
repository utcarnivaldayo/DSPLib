//------------------------------------------------------------------------------
//
//          The file is part of the DSPLAB Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#ifndef _DSPLAB_VECTOR_HPP_
#define _DSPLAB_VECTOR_HPP_
#include <cmath>
#include <cstdio>
#include <complex>
#if defined(_MSC_VER) && _MSC_VER >= 1910
#pragma warning(disable:4996)
#endif

namespace dsplab {
    
    namespace math {
        
        class Vector {
            private:
                Vector(){}
                Vector(const Vector &copy){}
                ~Vector(){}
                Vector &operator=(const Vector &copy) { return *this; }
            
            public:
                static bool Zero(double *vector, unsigned int length);
                static bool Zero(std::complex<double> *vector, unsigned int length);
                static bool One(double *vector, unsigned int length);
                static bool One(std::complex<double> *vector, unsigned int length);
                static bool Add(double *output, double *vector_a, double *vector_b, unsigned int length);
                static bool Add(double *vector_a, double *vector_b, unsigned int length);
                static bool Add(double *output, double *vector, double scalar, unsigned int length);
                static bool Add(double *vector, double scalar, unsigned int length);
                static bool Add(std::complex<double> *output, std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length);
                static bool Add(std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length);
                static bool Add(std::complex<double> *output, std::complex<double> *vector, std::complex<double> scalar, unsigned int length);
                static bool Add(std::complex<double> *vector, std::complex<double> scalar, unsigned int length);
                static bool Substract(double *output, double *vector_a, double *vector_b, unsigned int length);
                static bool Substract(double *vector_a, double *vector_b, unsigned int length);
                static bool Substract(double *output, double *vector, double scalar, unsigned int length);
                static bool Substract(double *vector, double scalar, unsigned int length);
                static bool Substract(std::complex<double> *output, std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length);
                static bool Substract(std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length);
                static bool Substract(std::complex<double> *output, std::complex<double> *vector, std::complex<double> scalar, unsigned int length);
                static bool Substract(std::complex<double> *vector, std::complex<double> scalar, unsigned int length);
                static bool Scalar(double *output, double *vector_a, double *vector_b, unsigned int length);
                static bool Scalar(double *vector_a, double *vector_b, unsigned int length);
                static bool Scalar(double *output, double *vector, double scalar, unsigned int length);
                static bool Scalar(double *vector, double scalar, unsigned int length);
                static bool Scalar(std::complex<double> *output, std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length);
                static bool Scalar(std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length);
                static bool Scalar(std::complex<double> *output, std::complex<double> *vector, std::complex<double> scalar, unsigned int length);
                static bool Scalar(std::complex<double> *vector, std::complex<double> scalar, unsigned int length);
                static double Inner(double *vector_a, double *vector_b, unsigned int length);
                static std::complex<double> Inner(std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length);
                static double SquareSum(double *vector, unsigned int length);
                static double SquareSum(std::complex<double> *vector, unsigned int length);
                static double L2(double *vector, unsigned int length);
                static double L2(std::complex<double> *vector, unsigned int length);
                static double L1(double *vector, unsigned int length);
                static double L1(std::complex<double>*vector, unsigned int length);
                static bool Print(double *vector, unsigned int length);
                static bool Print(std::complex<double> *vector, unsigned int length);
                static bool Write(const char* filename, double *vector, unsigned int length);
                static bool Write(const char* filename, std::complex<double> *vector, unsigned int length);
                //static double Lp(double *vector, unsigned int length, unsigned int p);
                //static double LInfinity(double *vector, unsigned int length);

        };
    }
}
#endif