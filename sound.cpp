//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#include "sound.hpp"

dsplab::sound::Sound::Sound() {

    Sound::data = nullptr;
    Sound::length = 0u;
    Sound::time = 0.0;
    Sound::quantization_bit = 0;
    Sound::sampling_frequency = 0u;
#if defined(__GNUG__) && (__GNUC__ >= 9 && __GNUC_MINOR__ >= 2) 
    std::random_device hd;
    Sound::seed = hd();
#elif defined(_MSC_VER) && _MSC_VER >= 1910
    std::random_device hd;
    Sound::seed = hd();
#else
    Sound::seed = (unsigned int)std::time(nullptr);
#endif
    mtrnd = new std::mt19937(seed);
}

dsplab::sound::Sound::Sound(unsigned int seed) {
    
    Sound::data = nullptr;
    Sound::length = 0u;
    Sound::time = 0.0;
    Sound::quantization_bit = 0;
    Sound::sampling_frequency = 0u;
    Sound::seed = seed;
    mtrnd = new std::mt19937(seed);
}

dsplab::sound::Sound::Sound(const Sound& copy) {
    Copy(copy);
}

void dsplab::sound::Sound::operator=(const Sound& copy) {

    delete Sound::mtrnd;
    Sound::mtrnd = nullptr;
    Copy(copy);   
}

void dsplab::sound::Sound::Copy(const Sound& copy) {

    Sound::length = copy.length;
    Sound::time = copy.time;
    Sound::quantization_bit = copy.quantization_bit;
    Sound::sampling_frequency = copy.sampling_frequency;
    Sound::seed = copy.seed;

    unsigned int i;
    if (nullptr != copy.data) {
        Sound::data = new double[Sound::length];
        for (i = 0u; i < Sound::length; i++) Sound::data[i] = copy.data[i];
    }
    else Sound::data = nullptr;

    mtrnd = new std::mt19937(seed);
}

dsplab::sound::Sound::~Sound() {

    Clear();
    delete Sound::mtrnd;
    Sound::mtrnd = nullptr;
}

bool dsplab::sound::Sound::ReadWAV(const char* filename) {

    if (!ReadWAV(filename, this, 1)) return false;
    return true;
}

bool dsplab::sound::Sound::ReadCSV(const char* filename, unsigned int sampling_frequency) {

    if (nullptr != data) return false;
    if (nullptr == filename) return false;
    if (NULL == filename) return false;

    FILE* fp = nullptr;
    unsigned int cnt = 0u;
    unsigned int i = 0u;
    double buff = 0.0;

    fp = std::fopen(filename, "r");
    if (nullptr == fp) return false;

    while (EOF != std::fscanf(fp, "%lf,%lf", &buff, &buff)) cnt++;

    Sound::length = cnt;
    Sound::sampling_frequency = sampling_frequency;
    Sound::time = length / (double)sampling_frequency; 
    Sound::data = new double[cnt];
    std::fseek(fp, 0, SEEK_SET);
    
    for (i = 0u; i < Sound::length; i++) std::fscanf(fp, "%lf,%lf", &buff, &Sound::data[i]);

    std::fclose(fp);
    fp = nullptr;

    return true;
}

bool dsplab::sound::Sound::ReadDAT(const char* filename, short int quantization_bit, unsigned int sampling_frequency) {

   if (!ReadDAT(filename, this, 1, quantization_bit, sampling_frequency)) return false;
   return false;
}

bool dsplab::sound::Sound::WriteWAV(const char* filename, short int quantization_bit) {

    if (!WriteWAV(filename, this, 1, quantization_bit)) return false;
    return true;
}

bool dsplab::sound::Sound::WriteCSV(const char* filename, short int quantization_bit) {

    if (nullptr == filename) return false;
    if (NULL == filename) return false;
    if (nullptr == Sound::data) return false;
    
    signed char c = 0;
    short int s = 0u;
    unsigned int i = 0u;
    double sample_per_second = time / length;
    double time = 0.0;
    FILE* fp = nullptr;

    fp = std::fopen(filename, "w");
    if (nullptr == fp) return false;
    
    if (8 == quantization_bit) {
        HardClipping(*this, std::numeric_limits<signed char>::lowest(), std::numeric_limits<signed>::max());
        Rounding(*this);
        for (i = 0u; i < Sound::length; i++) {
            time = i * sample_per_second;
            c = (signed char)Sound::data[i];
            std::fprintf(fp, "%16.15lf %d\n", time, c);
        }
    }
    else if (16 == quantization_bit) {
        HardClipping(*this, std::numeric_limits<short int>::lowest(), std::numeric_limits<short int>::max());
        Rounding(*this);
        for (i = 0u; i < Sound::length; i++) {
            time = i * sample_per_second;
            s = (short int)Sound::data[i];
            std::fprintf(fp, "%16.15lf,%d\n", time, s);
        }
    }
    else {
         for (i = 0u; i < Sound::length; i++) {
            time = i * sample_per_second;
            std::fprintf(fp, "%16.15lf,%16.15lf\n", time, Sound::data[i]);
        }
    }
    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::sound::Sound::WriteDAT(const char* filename, short int quantization_bit) {

   if (!WriteDAT(filename, this, 1, quantization_bit)) return false;
   return true;
}

double& dsplab::sound::Sound::operator[](unsigned int sample) {
    
    static double buff;
    buff = 0.0;
    if (nullptr == Sound::data) return buff;
    if (sample >= Sound::length) return buff;
    return Sound::data[sample];
}

const double& dsplab::sound::Sound::operator[](unsigned int sample) const {
    
    static double buff;
    buff = 0.0;
    if (nullptr == Sound::data) return buff;
    if (sample >= Sound::length) return buff; 
    return Sound::data[sample];
}

bool dsplab::sound::Sound::GenerateUniform(double min, double max, double time, unsigned int sampling_frequency) {

    if (time <= 0.0) return false;
    if (0u == sampling_frequency) return false;
    if (min > max) return false;
    if (nullptr != Sound::data) return false;

    Sound::length = (unsigned int)(time * sampling_frequency);
    if (0u == Sound::length) return false;
    Sound::time = time;
    Sound::sampling_frequency = sampling_frequency;

    unsigned int i;
    std::uniform_real_distribution<double> distribution(min, max);
    Sound::data = new double[Sound::length];

    for (i = 0u; i < Sound::length; i++) Sound::data[i] = distribution(*Sound::mtrnd);
    return true;
}

bool dsplab::sound::Sound::GenerateNormal(double mean, double standard_deviation, double time, unsigned int sampling_frequency) {

    if (time <= 0.0) return false;
    if (0u == sampling_frequency) return false;
    if (nullptr != Sound::data) return false;

    Sound::length = (unsigned int)(sampling_frequency * time);
    if (0u == Sound::length) return false;
    Sound::time = time;
    Sound::sampling_frequency = sampling_frequency;

    unsigned int i;
    std::uniform_real_distribution<double> distribution(mean, standard_deviation);
    Sound::data = new double[Sound::length];
    
    for (i = 0u; i < Sound::length; i++) Sound::data[i] = distribution(*Sound::mtrnd);
    return true;
}

bool dsplab::sound::Sound::GenerateSine(double amplitude, double phase, double frequency, double time, unsigned int sampling_frequency) {

    if (time <= 0.0) return false;
    if (0u == sampling_frequency) return false;
    if (nullptr != Sound::data) return false;

    Sound::length = (unsigned int)(sampling_frequency * time);
    if (0u == Sound::length) return false;
    Sound::time = time;
    Sound::sampling_frequency = sampling_frequency;
    
    unsigned int i;
    Sound::data = new double[Sound::length];

    for (i = 0u; i < Sound::length; i++) Sound::data[i] = amplitude * std::sin(2.0 * constants::PI * frequency * i / (double)sampling_frequency - phase);
    return true;
}

bool dsplab::sound::Sound::GenerateCosine(double amplitude, double phase, double frequency, double time, unsigned int sampling_frequency) {

    if (time <= 0.0) return false;
    if (0u == sampling_frequency) return false;
    if (nullptr != Sound::data) return false;

    Sound::length = (unsigned int)(sampling_frequency * time);
    if (0u == Sound::length) return false;
    Sound::time = time;
    Sound::sampling_frequency = sampling_frequency;
    
    unsigned int i;
    Sound::data = new double[Sound::length];

    for (i = 0u; i < Sound::length; i++) Sound::data[i] = amplitude * std::cos(2.0 * constants::PI * frequency * i / (double)sampling_frequency - phase);
    return true;
}

bool dsplab::sound::Sound::GenerateSilence(double time, unsigned int sampling_frequency) {

    if (time <= 0.0) return false;
    if (0u == sampling_frequency) return false;
    if (nullptr != Sound::data) return false;

    Sound::length = (unsigned int)(sampling_frequency * time);
    if (0u == Sound::length) return false;
    Sound::time = time;
    Sound::sampling_frequency = sampling_frequency;
    
    unsigned int i;
    Sound::data = new double[Sound::length];

    for (i = 0u; i < Sound::length; i++) Sound::data[i] = 0.0;
    return true;
}

bool dsplab::sound::Sound::GenerateImpulse(double amplitude, double time, unsigned int sampling_frequency) {

    if (time <= 0.0) return false;
    if (0u == sampling_frequency) return false;
    if (nullptr != Sound::data) return false;

    Sound::length = (unsigned int)(sampling_frequency * time);
    if (0u == Sound::length) return false;
    Sound::time = time;
    Sound::sampling_frequency = sampling_frequency;

    unsigned int i;
    Sound::data = new double[Sound::length];

    Sound::data[0] = amplitude;
    for (i = 1u; i < Sound::length; i++) Sound::data[i] = 0.0;

    return true;
}

bool dsplab::sound::Sound::GenerateStep(double amplitude, double time, unsigned int sampling_frequency) {
    if (time <= 0.0) return false;
    if (0u == sampling_frequency) return false;
    if (nullptr != Sound::data) return false;

    Sound::length = (unsigned int)(sampling_frequency * time);
    if (0u == Sound::length) return false;
    Sound::time = time;
    Sound::sampling_frequency = sampling_frequency;

    unsigned int i;
    Sound::data = new double[Sound::length];

    for (i = 0u; i < Sound::length; i++) Sound::data[i] = amplitude;

    return true;
}

bool dsplab::sound::Sound::GenerateChirp(double amplitude, double phase, double start_frequency, double final_frequency, double time, unsigned int sampling_frequency) {

    if (time <= 0.0) return false;
    if (0u == sampling_frequency) return false;
    if (nullptr != Sound::data) return false;

    Sound::length = (unsigned int)(sampling_frequency * time);
    if (0u == Sound::length) return false;
    Sound::time = time;
    Sound::sampling_frequency = sampling_frequency;

    unsigned int i;
    double k = (final_frequency - start_frequency) / time;
    double t = 0.0;

    Sound::data = new double[Sound::length];
    for (i = 0u; i < Sound::length; i++) {
        t = i / (double)sampling_frequency;
        Sound::data[i] = amplitude * std::sin(dsplab::constants::DOUBLE_PI * (start_frequency * t + k / 2.0 * t * t) - phase);
    }
    return true;
}

bool dsplab::sound::Sound::HardClipping(Sound& sound, double threshold_min, double threshold_max) {

    if (threshold_min >= threshold_max) return false;
    if (nullptr == sound.data) return false;
    if (0u == sound.length) return false;

    unsigned int i;
    for (i = 0u; i < sound.length; i++) {
        if (threshold_max < sound.data[i]) sound.data[i] = threshold_max;
        else if (threshold_min > sound.data[i]) sound.data[i] = threshold_min;
    }
    return true;
}

bool dsplab::sound::Sound::Rounding(Sound& sound) {

    if (nullptr == sound.data) return false;
    if (0u == sound.length) return false;

    unsigned int i;
    for (i = 0u; i < sound.length; i++) sound.data[i] = std::floor(sound.data[i] + 0.5);
    return true;
}

bool dsplab::sound::Sound::Gain(Sound& sound, double gain) {

    if (nullptr == sound.data) return false;
    if (0u == sound.length) return false;

    unsigned int i;
    for (i = 0u; i < sound.length; i++) sound.data[i] *= gain;
    return true;
}

bool dsplab::sound::Sound::Bias(Sound& sound, double bias) {
    
    if (nullptr == sound.data) return false;
    if (0u == sound.length) return false;

    unsigned int i;
    for (i = 0u; i < sound.length; i++) sound.data[i] += bias;
    return true;
}

bool dsplab::sound::Sound::AntiPhase(Sound& sound) {

    if (nullptr == sound.data) return false;
    if (0u == sound.length) return false;

    unsigned int i;
    for (i = 0u; i < sound.length; i++) sound.data[i] = -sound.data[i];
    return true;
}

bool dsplab::sound::Sound::Reverse(Sound& sound) {

    if (nullptr == sound.data) return false;
    if (0u == sound.length) return false;

    unsigned int i;
    unsigned int correspond_index;
    double buffer = 0.0;
    correspond_index = sound.length - 1u;
    for (i = 0u; i < (sound.length >> 1u); i++) {
        buffer = sound.data[i];
        sound.data[i] = sound.data[correspond_index];
        sound.data[correspond_index] = buffer;
        correspond_index--;
    }
    return true;
}

bool dsplab::sound::Sound::ReadDAT(const char* filename, Sound* sound, short int channel, short int quantization_bit, unsigned int sampling_frequency) {

    //error check
    short int i;
    if (channel <= 0) return false;
    if (0 == sampling_frequency) return false;
    if (nullptr == sound) return false;
    if (NULL == sound) return false;
    if (nullptr == filename) return false;
    if (NULL == filename) return false;
    for (i = 0u; i < channel; i++) {
        if (nullptr != sound[i].data) return false;
    }
    switch (quantization_bit) {
        case 8 : break;
        case 16 : break;
        default : return false;
    }

    unsigned char c = 0; //8bit buff
    short int s = 0; //16bit buff
    unsigned int j; // loop count
    unsigned int length_all = 0u;
    FILE* fp = nullptr;

    //file open & read
    fp = std::fopen(filename, "rb");
    if (nullptr == fp) return false;
    
    if (8 == quantization_bit) {

        //length count
        while (1 == std::fread(&c, sizeof(unsigned char), 1, fp)) length_all++;
        if (0u == length_all) {
            std::fclose(fp);
            fp = nullptr;
            return false;
        }
        if (0 != std::fseek(fp, 0, SEEK_SET)) {
            std::fclose(fp);
            fp = nullptr;
            return false;
        }

        //new 
        sound->length = length_all / channel;
        sound->time = sound->length / sampling_frequency;
        sound->sampling_frequency = sampling_frequency;
        sound->quantization_bit = quantization_bit;
        sound->data = new double[sound->length];
        for (i = 1; i < channel; i++) {
            sound[i].length = sound->length;
            sound[i].time = sound->time;
            sound[i].sampling_frequency = sampling_frequency;
            sound[i].quantization_bit = quantization_bit;
            sound[i].data = new double[sound[i].length];
        }

        //read
        for (j = 0u; j < sound->length; j++) {
            for (i = 0; i < channel; i++) {
                sound[i].data[j] = 0.0;
                if (1 != std::fread(&c, sizeof(unsigned char), 1, fp)) continue;
                sound[i].data[j] = (double)c;
                sound[i].data[j] -= std::numeric_limits<signed char>::max(); 
            } 
        }
    }
    else if (16 == quantization_bit) {

        //length count
        while (1 == std::fread(&s, sizeof(short int), 1, fp)) length_all++;
        if (0u == length_all) {
            std::fclose(fp);
            fp = nullptr;
            return false;
        }
        if (0 != std::fseek(fp, 0, SEEK_SET)) {
            std::fclose(fp);
            fp = nullptr;
            return false;
        }

        //new 
        sound->length = length_all / channel;
        sound->time = sound->length / sampling_frequency;
        sound->sampling_frequency = sampling_frequency;
        sound->quantization_bit = quantization_bit;
        sound->data = new double[sound->length];
        for (i = 1; i < channel; i++) {
            sound[i].length = sound->length;
            sound[i].time = sound->time;
            sound[i].sampling_frequency = sampling_frequency;
            sound[i].quantization_bit = quantization_bit;
            sound[i].data = new double[sound[i].length];
        }

        //read
        for (j = 0u; j < sound->length; j++) {
            for (i = 0; i < channel; i++) {
                sound[i].data[j] = 0.0;
                if (1 != std::fread(&s, sizeof(short int), 1, fp)) continue;
                sound[i].data[j] = (double)s; 
            } 
        }
    }
    
    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::sound::Sound::WriteDAT(const char* filename, Sound* sound, short int channel, short int quantization_bit) {

    //error check
    short int i;
    if (channel <= 0) return false;
    if (nullptr == sound) return false;
    if (NULL == sound) return false;
    if (nullptr == filename) return false;
    if (NULL == filename) return false;
    if (nullptr == sound->data) return false; 
    for (i = 1u; i < channel; i++) {
        if (nullptr == sound[i].data) return false;
        if (sound[i].length != sound->length) return false;
    }
    switch (quantization_bit) {
        case 8 : break;
        case 16 : break;
        default : return false;
    }

    unsigned char c = 0; //8bit buff
    short int s = 0; //16bit buff
    unsigned int j; // loop count
    FILE* fp = nullptr;

    //file open & read
    fp = std::fopen(filename, "wb");
    if (nullptr == fp) return false;

    //8[bit]
    if (8 == quantization_bit) {

        for (i = 0; i < channel; i++) {
            HardClipping(sound[i], std::numeric_limits<signed char>::lowest() + 1, std::numeric_limits<signed char>::max());
            Rounding(sound[i]);
        }
        for (j = 0u; j < sound->length; j++) {
            for (i = 0; i < channel; i++) {
                sound[i].data[j] += std::numeric_limits<signed char>::max();
                c = (unsigned char)sound[i].data[j];
                std::fwrite(&c, sizeof(unsigned char), 1, fp);
            }
        }
    }
    else if (16 == quantization_bit) {

        for (i = 0; i < channel; i++) {
            HardClipping(sound[i], std::numeric_limits<short int>::lowest(), std::numeric_limits<short int>::max());
            Rounding(sound[i]);
        }
        for (j = 0u; j < sound->length; j++) {
            for (i = 0; i < channel; i++) {
                s = (short int)sound[i].data[j];
                std::fwrite(&s, sizeof(short int), 1, fp);
            }
        }
    }
    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::sound::Sound::ReadWAV(const char* filename, Sound* sound, short int channel) {

    short int i;
    if (channel <= 0) return false;
    if (nullptr == sound) return false;
    if (NULL == sound) return false;
    if (nullptr == filename) return false;
    if (NULL == filename) return false;
    for (i = 0u; i < channel; i++) {
        if (nullptr != sound[i].data) return false;
    }

    FILE* fp = nullptr;
	unsigned int j;
	char riff_chunk_ID[4];
	unsigned int riff_chunk_size;
	char riff_form_type[4];
	char fmt_chunk_ID[4];
	unsigned int fmt_chunk_size;
	short int fmt_wave_format_type;
	short int fmt_channel;
	unsigned int fmt_samples_per_sec;
	unsigned int fmt_bytes_per_sec;
	short int fmt_block_size;
	short int fmt_bits_per_sample;
	char data_chunk_ID[4];
	unsigned int data_chunk_size;
	short int s;
    unsigned char c;

    fp = std::fopen(filename, "rb");
	if (nullptr == fp) return false;
	
	std::fread(riff_chunk_ID, 1, 4, fp);
	std::fread(&riff_chunk_size, 4, 1, fp);
	std::fread(riff_form_type, 1, 4, fp);
	std::fread(fmt_chunk_ID, 1, 4, fp);
	std::fread(&fmt_chunk_size, 4, 1, fp);
	std::fread(&fmt_wave_format_type, 2, 1, fp);
	std::fread(&fmt_channel, 2, 1, fp);
	std::fread(&fmt_samples_per_sec, 4, 1, fp);
	std::fread(&fmt_bytes_per_sec, 4, 1, fp);
	std::fread(&fmt_block_size, 2, 1, fp);
	std::fread(&fmt_bits_per_sample, 2, 1, fp);
	std::fread(data_chunk_ID, 1, 4, fp);
	std::fread(&data_chunk_size, 4, 1, fp);

	sound->sampling_frequency = fmt_samples_per_sec;
	sound->quantization_bit = fmt_bits_per_sample;
    sound->length = data_chunk_size / (sound->quantization_bit / 8) / channel;
    if (0u == sound->length) return false;
    sound->time = sound->length / (double)sound->sampling_frequency;
    sound->data = new double[sound->length];
    for (i = 1; i < channel; i++) {
        sound[i].length = sound->length;
        sound[i].time = sound->time;
        sound[i].sampling_frequency = sound->sampling_frequency;
        sound[i].quantization_bit = sound->quantization_bit;
        sound[i].data = new double[sound[i].length];
    }
    
    if (8 == sound->quantization_bit) {

        //read
        for (j = 0u; j < sound->length; j++) {
            for (i = 0; i < channel; i++) {
                sound[i].data[j] = 0.0;
                if (1 != std::fread(&c, sizeof(unsigned char), 1, fp)) continue;
                sound[i].data[j] = (double)c;
                sound[i].data[j] -= std::numeric_limits<signed char>::max(); 
            } 
        }
    }
    else if (16 == sound->quantization_bit) {

        //read
        for (j = 0u; j < sound->length; j++) {
            for (i = 0; i < channel; i++) {
                sound[i].data[j] = 0.0;
                if (1 != std::fread(&s, sizeof(short int), 1, fp)) continue;
                sound[i].data[j] = (double)s; 
            } 
        }
    }

	std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::sound::Sound::WriteWAV(const char* filename, Sound* sound, short int channel, short int quantization_bit) {

    short int i;
    if (channel <= 0) return false;
    if (nullptr == sound) return false;
    if (NULL == sound) return false;
    if (nullptr == filename) return false;
    if (NULL == filename) return false;
    if (nullptr == sound->data) return false; 
    for (i = 1u; i < channel; i++) {
        if (nullptr == sound[i].data) return false;
        if (sound[i].length != sound->length) return false;
    }
    switch (quantization_bit) {
        case 8 : break;
        case 16 : break;
        default : return false;
    }

    FILE* fp = nullptr;
	unsigned int j;
	char riff_chunk_ID[4];
	unsigned int riff_chunk_size;
	char riff_form_type[4];
	char fmt_chunk_ID[4];
	unsigned int fmt_chunk_size;
	short int fmt_wave_format_type;
	short int fmt_channel;
	unsigned int fmt_samples_per_sec;
	unsigned int fmt_bytes_per_sec;
	short int fmt_block_size;
	short int fmt_bits_per_sample;
	char data_chunk_ID[4];
	unsigned int data_chunk_size;
	short int s;
    unsigned char c;

    fmt_block_size = quantization_bit / 8 * channel;
    data_chunk_size = sound->length * fmt_block_size;
	riff_chunk_ID[0] = 'R';
	riff_chunk_ID[1] = 'I';
	riff_chunk_ID[2] = 'F';
	riff_chunk_ID[3] = 'F';
	riff_chunk_size = 36 + data_chunk_size;
	riff_form_type[0] = 'W';
	riff_form_type[1] = 'A';
	riff_form_type[2] = 'V';
	riff_form_type[3] = 'E';

	fmt_chunk_ID[0] = 'f';
	fmt_chunk_ID[1] = 'm';
	fmt_chunk_ID[2] = 't';
	fmt_chunk_ID[3] = ' ';
	fmt_chunk_size = 16;
	fmt_wave_format_type = 1;
	fmt_channel = channel;
	fmt_samples_per_sec = sound->sampling_frequency;
	fmt_bytes_per_sec = sound->sampling_frequency * fmt_block_size;
	fmt_bits_per_sample = quantization_bit;

	data_chunk_ID[0] = 'd';
	data_chunk_ID[1] = 'a';
	data_chunk_ID[2] = 't';
	data_chunk_ID[3] = 'a';

    fp = std::fopen(filename, "wb");
    if (nullptr == fp) return false;

	std::fwrite(riff_chunk_ID, 1, 4, fp);
	std::fwrite(&riff_chunk_size, 4, 1, fp);
	std::fwrite(riff_form_type, 1, 4, fp);
	std::fwrite(fmt_chunk_ID, 1, 4, fp);
	std::fwrite(&fmt_chunk_size, 4, 1, fp);
	std::fwrite(&fmt_wave_format_type, 2, 1, fp);
	std::fwrite(&fmt_channel, 2, 1, fp);
	std::fwrite(&fmt_samples_per_sec, 4, 1, fp);
	std::fwrite(&fmt_bytes_per_sec, 4, 1, fp);
	std::fwrite(&fmt_block_size, 2, 1, fp);
	std::fwrite(&fmt_bits_per_sample, 2, 1, fp);
	std::fwrite(data_chunk_ID, 1, 4, fp);
	std::fwrite(&data_chunk_size, 4, 1, fp);

    //8[bit]
    if (8 == quantization_bit) {

        for (i = 0; i < channel; i++) {
            HardClipping(sound[i], std::numeric_limits<signed char>::lowest() + 1, std::numeric_limits<signed char>::max());
            Rounding(sound[i]);
        }
        for (j = 0u; j < sound->length; j++) {
            for (i = 0; i < channel; i++) {
                sound[i].data[j] += std::numeric_limits<signed char>::max();
                c = (unsigned char)sound[i].data[j];
                std::fwrite(&c, sizeof(unsigned char), 1, fp);
            }
        }
    }
    else if (16 == quantization_bit) {

        for (i = 0; i < channel; i++) {
            HardClipping(sound[i], std::numeric_limits<short int>::lowest(), std::numeric_limits<short int>::max());
            Rounding(sound[i]);
        }
        for (j = 0u; j < sound->length; j++) {
            for (i = 0; i < channel; i++) {
                s = (short int)sound[i].data[j];
                std::fwrite(&s, sizeof(short int), 1, fp);
            }
        }
    }
    
	std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::sound::Sound::IsEmpty() {
    if (Sound::data == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

void dsplab::sound::Sound::Clear() {

    delete[] Sound::data;
    Sound::data = nullptr;
    Sound::length = 0u;
    Sound::time = 0.0;
    Sound::quantization_bit = 0;
    Sound::sampling_frequency = 0u;
}

double dsplab::sound::Sound::CalculateSpeedOfSound(double degree_celsius) {
    if (-273.15 > degree_celsius) return 0.0;
    return 20.055 * std::sqrt(degree_celsius + 273.15);
}