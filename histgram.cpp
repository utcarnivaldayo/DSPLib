//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#include "histgram.hpp"

dsplab::math::Histgram::Histgram() {

    max = 0.0;
    min = 0.0;
    bin_width = 0.0;
    histgram = nullptr;
    bins = nullptr;
    sample_size = 0u;
    number_of_bins = 0u;
}

dsplab::math::Histgram::~Histgram() {
    Clear();
}

dsplab::math::Histgram::Histgram(const Histgram& copy) {
    Copy(copy);
}

void dsplab::math::Histgram::operator=(const Histgram& copy) {
    Copy(copy);
}

void dsplab::math::Histgram::Copy(const Histgram& copy) {

    this->max = copy.max;
    this->min = copy.min;
    this->bin_width = copy.bin_width;
    this->sample_size = copy.sample_size;
    this->number_of_bins = copy.number_of_bins;

    if (nullptr != histgram) {
        this->histgram = new unsigned int[this->number_of_bins];
        this->bins = new double[this->number_of_bins + 1u];
        for (unsigned int i = 0u; i < this->number_of_bins; i++) {
            this->histgram[i] = copy.histgram[i];
            this->bins[i] = copy.bins[i];
        }
        this->bins[this->number_of_bins] = copy.bins[this->number_of_bins];
    }
}

bool dsplab::math::Histgram::SetHistgram(double min, double max, unsigned int number_of_bins) {

    if (nullptr != histgram) return false;
    if (min >= max) return false;
    if (number_of_bins < 2u) return false;

    this->min = min;
    this->max = max;
    this->number_of_bins = number_of_bins;
    this->bin_width = (this->max - this->min) / (double)number_of_bins;
    this->histgram = new unsigned int[this->number_of_bins];
    this->bins = new double[this->number_of_bins + 1u];

    for (unsigned int i = 0u; i < this->number_of_bins; i++) {
        histgram[i] = 0u;
        bins[i] = min + bin_width * i;
    }
    bins[this->number_of_bins] = max + std::numeric_limits<double>::epsilon();
    return true;
}

bool dsplab::math::Histgram::AddSample(double &sample) {

    if (min > sample || sample > max) return false;
    if (nullptr == histgram) return false;

    for (unsigned int i = 0u; i < number_of_bins; i++) {
        if (bins[i] <= sample && sample < bins[i + 1]) {
            histgram[i]++;
        }
    }
    sample_size++;
    return true;
}

const unsigned int& dsplab::math::Histgram::operator[](unsigned int bin) const {
    
    static unsigned int buff;
    buff = 0u;
    if (nullptr == histgram) return buff;
    if (bin >= number_of_bins) return buff;
    return histgram[bin];
}

double dsplab::math::Histgram::Mean() {

    if (nullptr == histgram) return 0.0;
    
    double mean = 0.0;

    for (unsigned int i = 0u; i < number_of_bins; i++) {
        mean += (bins[i + 1] - bins[i]) / 2.0 * histgram[i];
    }
    mean /= (double)sample_size;
    return mean;
}

void dsplab::math::Histgram::Clear() {
    max = 0.0;
    min = 0.0;
    bin_width = 0.0;
    sample_size = 0u;
    number_of_bins = 0u;

    delete[] histgram;
    histgram = nullptr;

    delete[] bins;
    bins = nullptr;
}

bool dsplab::math::Histgram::IsEmpty() {

    if (nullptr == histgram) return true;
    else return false;
}
