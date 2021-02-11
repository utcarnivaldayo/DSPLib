#include "incrementalstatistics.hpp"

dsplab::math::IncrementalStatistics::IncrementalStatistics() {
    Clear();
}

dsplab::math::IncrementalStatistics::~IncrementalStatistics() {
    Clear();
}

void dsplab::math::IncrementalStatistics::Clear() {
    
    mean = 0.0;
    m2 = 0.0;
    c_mean = 0.0;
    c_m2 = 0.0;
    n = 0u;
}

//Welford's online algorithm
void dsplab::math::IncrementalStatistics::AddSample(double sample) {
    
    n++;
    double delta = sample - mean;
    Kahan(delta / n, mean, c_mean);
    double delta2 = sample - mean;
    Kahan(delta * delta2, m2, c_m2);
}

//Kahan summation algorithm
void dsplab::math::IncrementalStatistics::Kahan(double sample, double& sum, double& c) {

    double y = sample - c;
    double t = sum + y;
    c = (t - sum) - y;
    sum = t;
}
