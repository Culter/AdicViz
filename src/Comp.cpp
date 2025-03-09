//
//  Comp.cpp
//  NewIll
//
//  Created by Christopher Culter on 2/9/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "Comp.h"

comp::comp (void) { re = 0.0; im = 0.0; }
comp::comp (double a, double b) { re = a; im = b; }
comp comp::operator+ (const comp & p) const { return comp (re+p.re, im+p.im); }
comp comp::operator- (const comp & p) const { return comp (re-p.re, im-p.im); }
comp comp::operator* (const comp & p) const { return comp (re*p.re - im*p.im, re*p.im + im*p.re); }
comp comp::operator* (double m) const { return comp (re*m, im*m); }
comp comp::operator+= (const comp & p) { return (*this = *this + p); }
comp comp::operator-= (const comp & p) { return (*this = *this - p); }
comp comp::operator*= (double m) { return (*this = *this * m); }
comp comp::operator- (void) const { return comp (-re, -im); }
double comp::norm (void) const { return sqrt (re*re + im*im); }

double comp::getre (void) const { return re; }
double comp::getim (void) const { return im; }

comp circ(double frac)
{
	double angle = 2.0*pi*frac;
	return comp (cos(angle), -sin(angle));
}

int ord(int i)
{
    if (i == 0) return -1;
    
    int value = 0;
    while (i % prime == 0)
    {
        i /= prime;
        ++value;
    }
    
    return value;
}

int powi(int base, unsigned int exp)
{
    return (int)pow((double)base, (int)exp);
}