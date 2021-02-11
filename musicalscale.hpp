//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------
#ifndef DSPLAB_MUSICALSCALE_HPP_
#define DSPLAB_MUSICALSCALE_HPP_
#include <cmath>

namespace dsplab {

    namespace sound {
        
        class MusicalScale {

            private:

                //0
                double A0_;
                double As0_;
                double B0_;

                //1
                double C1_;
                double Cs1_;
                double D1_;
                double Ds1_;
                double E1_;
                double F1_;
                double Fs1_;
                double G1_;
                double Gs1_;
                double A1_;
                double As1_;
                double B1_;

                //2
                double C2_;
                double Cs2_;
                double D2_;
                double Ds2_;
                double E2_;
                double F2_;
                double Fs2_;
                double G2_;
                double Gs2_;
                double A2_;
                double As2_;
                double B2_;

                //3
                double C3_;
                double Cs3_;
                double D3_;
                double Ds3_;
                double E3_;
                double F3_;
                double Fs3_;
                double G3_;
                double Gs3_;
                double A3_;
                double As3_;
                double B3_;

                //4
                double C4_;
                double Cs4_;
                double D4_;
                double Ds4_;
                double E4_;
                double F4_;
                double Fs4_;
                double G4_;
                double Gs4_;
                double A4_;
                double As4_;
                double B4_;

                //5
                double C5_;
                double Cs5_;
                double D5_;
                double Ds5_;
                double E5_;
                double F5_;
                double Fs5_;
                double G5_;
                double Gs5_;
                double A5_;
                double As5_;
                double B5_;

                //6
                double C6_;
                double Cs6_;
                double D6_;
                double Ds6_;
                double E6_;
                double F6_;
                double Fs6_;
                double G6_;
                double Gs6_;
                double A6_;
                double As6_;
                double B6_;

                //7
                double C7_;
                double Cs7_;
                double D7_;
                double Ds7_;
                double E7_;
                double F7_;
                double Fs7_;
                double G7_;
                double Gs7_;
                double A7_;
                double As7_;
                double B7_;

                //8
                double C8_;
            
            public:
                MusicalScale();
                ~MusicalScale();

                //0
                inline double A0() const {return A0_;}
                inline double As0() const {return As0_;}
                inline double B0() const {return B0_;}

                //1
                inline double C1() const {return C1_;}                
                inline double Cs1() const {return Cs1_;}
                inline double D1() const {return D1_;}               
                inline double Ds1() const {return Ds1_;}
                inline double E1() const {return E1_;}
                inline double F1() const {return F1_;}
                inline double Fs1() const {return Fs1_;}                
                inline double G1() const {return G1_;}
                inline double Gs1() const {return Gs1_;}
                inline double A1() const {return A1_;}
                inline double As1() const {return As1_;}
                inline double B1() const {return B1_;}

                //2
                inline double C2() const {return C2_;}                
                inline double Cs2() const {return Cs2_;}
                inline double D2() const {return D2_;}               
                inline double Ds2() const {return Ds2_;}
                inline double E2() const {return E2_;}
                inline double F2() const {return F2_;}
                inline double Fs2() const {return Fs2_;}                
                inline double G2() const {return G2_;}
                inline double Gs2() const {return Gs2_;}
                inline double A2() const {return A2_;}
                inline double As2() const {return As2_;}
                inline double B2() const {return B2_;}

                //3
                inline double C3() const {return C3_;}                
                inline double Cs3() const {return Cs3_;}
                inline double D3() const {return D3_;}               
                inline double Ds3() const {return Ds3_;}
                inline double E3() const {return E3_;}
                inline double F3() const {return F3_;}
                inline double Fs3() const {return Fs3_;}                
                inline double G3() const {return G3_;}
                inline double Gs3() const {return Gs3_;}
                inline double A3() const {return A3_;}
                inline double As3() const {return As3_;}
                inline double B3() const {return B3_;}

                //4
                inline double C4() const {return C4_;}                
                inline double Cs4() const {return Cs4_;}
                inline double D4() const {return D4_;}               
                inline double Ds4() const {return Ds4_;}
                inline double E4() const {return E4_;}
                inline double F4() const {return F4_;}
                inline double Fs4() const {return Fs4_;}                
                inline double G4() const {return G4_;}
                inline double Gs4() const {return Gs4_;}
                inline double A4() const {return A4_;}
                inline double As4() const {return As4_;}
                inline double B4() const {return B4_;}

                //5
                inline double C5() const {return C5_;}                
                inline double Cs5() const {return Cs5_;}
                inline double D5() const {return D5_;}               
                inline double Ds5() const {return Ds5_;}
                inline double E5() const {return E5_;}
                inline double F5() const {return F5_;}
                inline double Fs5() const {return Fs5_;}                
                inline double G5() const {return G5_;}
                inline double Gs5() const {return Gs5_;}
                inline double A5() const {return A5_;}
                inline double As5() const {return As5_;}
                inline double B5() const {return B5_;}

                //6
                inline double C6() const {return C6_;}                
                inline double Cs6() const {return Cs6_;}
                inline double D6() const {return D6_;}               
                inline double Ds6() const {return Ds6_;}
                inline double E6() const {return E6_;}
                inline double F6() const {return F6_;}
                inline double Fs6() const {return Fs6_;}                
                inline double G6() const {return G6_;}
                inline double Gs6() const {return Gs6_;}
                inline double A6() const {return A6_;}
                inline double As6() const {return As6_;}
                inline double B6() const {return B6_;}

                //7
                inline double C7() const {return C7_;}                
                inline double Cs7() const {return Cs7_;}
                inline double D7() const {return D7_;}               
                inline double Ds7() const {return Ds7_;}
                inline double E7() const {return E7_;}
                inline double F7() const {return F7_;}
                inline double Fs7() const {return Fs7_;}                
                inline double G7() const {return G7_;}
                inline double Gs7() const {return Gs7_;}
                inline double A7() const {return A7_;}
                inline double As7() const {return As7_;}
                inline double B7() const {return B7_;}

                //8
                inline double C8() const {return C8_;}

                bool SetMusicalScale(double concert_pitch);

        };
    }
}
#endif