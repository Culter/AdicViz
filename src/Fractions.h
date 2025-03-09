//
//  Fractions.h
//  NewIll
//
//  Created by Christopher Culter on 2/9/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef NewIll_Fractions_h
#define NewIll_Fractions_h

double rCurve(double i);
double rCurvePrime(double i);
comp pruferCurve(double fraction, double t, double halfWidth);
comp pruferDerivative(double fraction, double t, double halfWidth);

void printPrufer(int value, int power);

void stylePrufer();
void definePrufer();
void drawPrufer(comp center, double scale);

void drawPruferColored(comp center, double scale, int value, int power);

#endif
