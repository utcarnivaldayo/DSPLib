//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------
#include "musicalscale.hpp"

dsplab::sound::MusicalScale::MusicalScale() {
    SetMusicalScale(440.0);
}

dsplab::sound::MusicalScale::~MusicalScale() {}

bool dsplab::sound::MusicalScale::SetMusicalScale(double concert_pitch) {

    if (concert_pitch <= 0.0) {
        return false;
    }

    A4_ = concert_pitch;

    A0_ = A4_ / 16.0;
    A1_ = A4_ / 8.0;
    A2_ = A4_ / 4.0;
    A3_ = A4_ / 2.0;
    A5_ = A4_ * 2.0;
    A6_ = A4_ * 4.0;
    A7_ = A4_ * 8.0;

    //0
    As0_ = A0_ * std::pow(2.0, 1.0 / 12.0);
    B0_ = A0_ * std::pow(2.0, 2.0 / 12.0);

    //1
    C1_ = A1_ * std::pow(2.0, -9.0 / 12.0);
    Cs1_ = A1_ * std::pow(2.0, -8.0 / 12.0);
    D1_ = A1_ * std::pow(2.0, -7.0 / 12.0);
    Ds1_ = A1_ * std::pow(2.0, -6.0 / 12.0);
    E1_ = A1_ * std::pow(2.0, -5.0 / 12.0);
    F1_ = A1_ * std::pow(2.0, -4.0 / 12.0);
    Fs1_ = A1_ * std::pow(2.0, -3.0 / 12.0);
    G1_ = A1_ * std::pow(2.0, -2.0 / 12.0);
    Gs1_ = A1_ * std::pow(2.0, -1.0 / 12.0);
    As1_ = A1_ * std::pow(2.0, 1.0 / 12.0);
    B1_ = A1_ * std::pow(2.0, 2.0 / 12.0);

    //2
    C2_ = A2_ * std::pow(2.0, -9.0 / 12.0);
    Cs2_ = A2_ * std::pow(2.0, -8.0 / 12.0);
    D2_ = A2_ * std::pow(2.0, -7.0 / 12.0);
    Ds2_ = A2_ * std::pow(2.0, -6.0 / 12.0);
    E2_ = A2_ * std::pow(2.0, -5.0 / 12.0);
    F2_ = A2_ * std::pow(2.0, -4.0 / 12.0);
    Fs2_ = A2_ * std::pow(2.0, -3.0 / 12.0);
    G2_ = A2_ * std::pow(2.0, -2.0 / 12.0);
    Gs2_ = A2_ * std::pow(2.0, -1.0 / 12.0);
    As2_ = A2_ * std::pow(2.0, 1.0 / 12.0);
    B2_ = A2_ * std::pow(2.0, 2.0 / 12.0);

    //3
    C3_ = A3_ * std::pow(2.0, -9.0 / 12.0);
    Cs3_ = A3_ * std::pow(2.0, -8.0 / 12.0);
    D3_ = A3_ * std::pow(2.0, -7.0 / 12.0);
    Ds3_ = A3_ * std::pow(2.0, -6.0 / 12.0);
    E3_ = A3_ * std::pow(2.0, -5.0 / 12.0);
    F3_ = A3_ * std::pow(2.0, -4.0 / 12.0);
    Fs3_ = A3_ * std::pow(2.0, -3.0 / 12.0);
    G3_ = A3_ * std::pow(2.0, -2.0 / 12.0);
    Gs3_ = A3_ * std::pow(2.0, -1.0 / 12.0);
    As4_ = A4_ * std::pow(2.0, 1.0 / 12.0);
    B4_ = A4_ * std::pow(2.0, 2.0 / 12.0);

    //4
    C4_ = A4_ * std::pow(2.0, -9.0 / 12.0);
    Cs4_ = A4_ * std::pow(2.0, -8.0 / 12.0);
    D4_ = A4_ * std::pow(2.0, -7.0 / 12.0);
    Ds4_ = A4_ * std::pow(2.0, -6.0 / 12.0);
    E4_ = A4_ * std::pow(2.0, -5.0 / 12.0);
    F4_ = A4_ * std::pow(2.0, -4.0 / 12.0);
    Fs4_ = A4_ * std::pow(2.0, -3.0 / 12.0);
    G4_ = A4_ * std::pow(2.0, -2.0 / 12.0);
    Gs4_ = A4_ * std::pow(2.0, -1.0 / 12.0);
    As4_ = A4_ * std::pow(2.0, 1.0 / 12.0);
    B4_ = A4_ * std::pow(2.0, 2.0 / 12.0);

    //5
    C5_ = A5_ * std::pow(2.0, -9.0 / 12.0);
    Cs5_ = A5_ * std::pow(2.0, -8.0 / 12.0);
    D5_ = A5_ * std::pow(2.0, -7.0 / 12.0);
    Ds5_ = A5_ * std::pow(2.0, -6.0 / 12.0);
    E5_ = A5_ * std::pow(2.0, -5.0 / 12.0);
    F5_ = A5_ * std::pow(2.0, -4.0 / 12.0);
    Fs5_ = A5_ * std::pow(2.0, -3.0 / 12.0);
    G5_ = A5_ * std::pow(2.0, -2.0 / 12.0);
    Gs5_ = A5_ * std::pow(2.0, -1.0 / 12.0);
    As5_ = A5_ * std::pow(2.0, 1.0 / 12.0);
    B5_ = A5_ * std::pow(2.0, 2.0 / 12.0);

    //6
    C6_ = A6_ * std::pow(2.0, -9.0 / 12.0);
    Cs6_ = A6_ * std::pow(2.0, -8.0 / 12.0);
    D6_ = A6_ * std::pow(2.0, -7.0 / 12.0);
    Ds6_ = A6_ * std::pow(2.0, -6.0 / 12.0);
    E6_ = A6_ * std::pow(2.0, -5.0 / 12.0);
    F6_ = A6_ * std::pow(2.0, -4.0 / 12.0);
    Fs6_ = A6_ * std::pow(2.0, -3.0 / 12.0);
    G6_ = A6_ * std::pow(2.0, -2.0 / 12.0);
    Gs6_ = A6_ * std::pow(2.0, -1.0 / 12.0);
    As6_ = A6_ * std::pow(2.0, 1.0 / 12.0);
    B6_ = A6_ * std::pow(2.0, 2.0 / 12.0);

    //7
    C7_ = A7_ * std::pow(2.0, -9.0 / 12.0);
    Cs7_ = A7_ * std::pow(2.0, -8.0 / 12.0);
    D7_ = A7_ * std::pow(2.0, -7.0 / 12.0);
    Ds7_ = A7_ * std::pow(2.0, -6.0 / 12.0);
    E7_ = A7_ * std::pow(2.0, -5.0 / 12.0);
    F7_ = A7_ * std::pow(2.0, -4.0 / 12.0);
    Fs7_ = A7_ * std::pow(2.0, -3.0 / 12.0);
    G7_ = A7_ * std::pow(2.0, -2.0 / 12.0);
    Gs7_ = A7_ * std::pow(2.0, -1.0 / 12.0);
    As7_ = A7_ * std::pow(2.0, 1.0 / 12.0);
    B7_ = A7_ * std::pow(2.0, 2.0 / 12.0);

    //8
    C8_ = A7_ * std::pow(2.0, 3.0 / 12.0);
    return true;
}