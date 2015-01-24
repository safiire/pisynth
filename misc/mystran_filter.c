//// LICENSE TERMS: Copyright 2012 Teemu Voipio 
// 
// You can use this however you like for pretty much any purpose, 
// as long as you don't claim you wrote it. There is no warranty. 
// 
// Distribution of substantial portions of this code in source form 
// must include this copyright notice and list of conditions. 
// 

//  This comes from here:
//  http://www.kvraudio.com/forum/viewtopic.php?t=349859&start=0&postdays=0&postorder=asc&highlight=

// input delay and state for member variables 
double z1; 
double s[4] = { 0, 0, 0, 0 }; 

// tanh(x)/x approximation, flatline at very high inputs 
// so might not be safe for very large feedback gains 
// [limit is 1/15 so very large means ~15 or +23dB] 
double tanhXdX(double x) 
{ 
    double a = x*x; 
    // IIRC I got this as Pade-approx for tanh(sqrt(x))/sqrt(x) 
    return ((a + 105)*a + 945) / ((15*a + 420)*a + 945); 
} 

// cutoff as normalized frequency (eg 0.5 = Nyquist) 
// resonance from 0 to 1, self-oscillates at settings over 0.9 
void transistorLadder( 
    double cutoff, double resonance, 
    double * in, double * out, unsigned nsamples) 
{ 
    // tuning and feedback 
    double f = tan(M_PI * cutoff); 
    double r = (40.0/9.0) * resonance; 

    for(unsigned n = 0; n < nsamples; ++n) 
    { 
        // input with half delay, for non-linearities 
        double ih = 0.5 * (in[n] + zi); zi = in[n]; 

        // evaluate the non-linear gains 
        double t0 = tanhXdX(ih - r * s[3]); 
        double t1 = tanhXdX(s[0]); 
        double t2 = tanhXdX(s[1]); 
        double t3 = tanhXdX(s[2]); 
        double t4 = tanhXdX(s[3]); 

        // g# the denominators for solutions of individual stages 
        double g0 = 1 / (1 + f*t1), g1 = 1 / (1 + f*t2); 
        double g2 = 1 / (1 + f*t3), g3 = 1 / (1 + f*t4); 
        
        // f# are just factored out of the feedback solution 
        double f3 = f*t3*g3, f2 = f*t2*g2*f3, f1 = f*t1*g1*f2, f0 = f*t0*g0*f1; 

        // solve feedback 
        double y3 = (g3*s[3] + f3*g2*s[2] + f2*g1*s[1] + f1*g0*s[0] + f0*in[n]) / (1 + r*f0); 

        // then solve the remaining outputs (with the non-linear gains here) 
        double xx = t0*(in[n] - r*y3); 
        double y0 = t1*g0*(s[0] + f*xx); 
        double y1 = t2*g1*(s[1] + f*y0); 
        double y2 = t3*g2*(s[2] + f*y1); 

        // update state 
        s[0] += 2*f * (xx - y0); 
        s[1] += 2*f * (y0 - y1); 
        s[2] += 2*f * (y1 - y2); 
        s[3] += 2*f * (y2 - t4*y3); 

        out[n] = y3; 
    } 
} 
