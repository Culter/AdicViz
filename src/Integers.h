//
//  Integers.h
//  NewIll
//
//  Created by Christopher Culter on 2/9/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef NewIll_Integers_h
#define NewIll_Integers_h

void styleIntegers();
void drawIntegers(comp center, double scale);

void printAdicTitle(int value, int power);
void recursiveDraw(comp center, double offset, double scale, int value, int power);

comp getPoint(comp center, double scale, int value, int power);

#endif
