//
//  Comp.h
//  NewIll
//
//  Created by Christopher Culter on 2/9/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <cmath>

#ifndef NewIll_Comp_h
#define NewIll_Comp_h

#ifndef pi
#define pi 3.14159265359
#endif

#define prime 3

class comp {
public:
    comp (void);
    comp (double a, double b);
    
    comp operator+ (const comp & p) const;
    comp operator- (const comp & p) const;
    comp operator* (const comp & p) const;
    comp operator* (double m) const;
    comp operator+= (const comp & p);
    comp operator-= (const comp & p);
    comp operator*= (double m);
    comp operator- (void) const;
    double norm (void) const;
    
    double getre (void) const;
    double getim (void) const;
    void draw (void);
    
    void reflectthru (const comp & p);
protected:
    double re, im;
};

comp circ(double frac);
int ord(int i);

int powi(int base, unsigned int exp);

#endif
