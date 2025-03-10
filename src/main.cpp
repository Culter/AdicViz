//
//  main.cpp
//  NewIll
//
//  Created by Christopher Culter on 1/22/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "Comp.h"
#include "Svg.h"
#include "Settings.h"

#include "Integers.h"
#include "Fractions.h"
#include "BarChart.h"

using namespace std;

void drawLine(comp integerCenter, comp fractionCenter, comp offset, double integerScale, double fractionScale, int integerValue, int integerExponent);
void drawLineWithColor(comp integerCenter, comp fractionCenter, comp offset, double integerScale, double fractionScale, int integerValue, int integerExponent);


void drawLine(comp integerCenter, comp fractionCenter, comp offset, double integerScale, double fractionScale, int integerValue, int integerExponent)
{
    comp integer = getPoint(integerCenter, integerScale, integerValue, integerExponent);
    
    indent::space();
    cout << "<path fill=\"none\" stroke=\"gray\" d=\"";
    cout << "M" << integer.getre() << "," << integer.getim() << " ";
    
    integer += offset;
    cout << "L" << integer.getre() << "," << integer.getim() << " ";
    cout << "L" << fractionCenter.getre() << "," << fractionCenter.getim() << " ";
    cout << "\" />\n";
}

void drawLineWithColor(comp integerCenter, comp fractionCenter, comp offset, double integerScale, double fractionScale, int integerValue, int integerExponent)
{
    drawLine(integerCenter, fractionCenter, offset, integerScale, fractionScale, integerValue, integerExponent);
    drawPruferColored(fractionCenter, fractionScale, integerValue, g_maxExponentFraction);
}

int main (int argc, const char * argv[])
{    
    ofstream outFile("LocalAutoGenerated.svg");
    cout.rdbuf(outFile.rdbuf());
    
    g_events = false;
    g_maxExponentInteger = 8;
    g_maxExponentFraction = 6;
    g_scale = 1.0 / (1.0 + 1.0 / (sin(pi / prime)));
    
    cout << setprecision(6);
    
    preamble(400, 400);
    {
        indent inSvg;
        
        if (g_events)
        {
            beginScript();
            insertScript();
            endScript();
        }
        
        beginDefs();
        {
            indent inDefs;
            
            beginStyle();
            styleIntegers();
            //stylePrufer();
            styleBars();
            endStyle();
            
            //definePrufer();
        }
        
        endDefs();
        
//        drawBars(comp(125, 150), 3);
      
        drawIntegers(comp(200, 200), 180 * (1.0 - g_scale));
        //drawPrufer(comp(600, 200), 180);
        
//        comp center(300, 300);
        //double integerScale = 180 * (1.0 - g_scale);
        
        //2
        /*
        drawLineWithColor(center, center + circ( 6.0/13.0) * 240, comp(0, 0), integerScale, 50,   1+4+16+64+256+1024,  10);
        drawLineWithColor(center, center + circ(-6.0/13.0) * 240, comp(0, 0), integerScale, 50, -(1+4+16+64+256+1024), 10);
        
        drawLineWithColor(center, center + circ( 5.0/13.0) * 240, comp(0, 0), integerScale, 50,   1+8+64+512,  10);
        drawLineWithColor(center, center + circ(-5.0/13.0) * 240, comp(0, 0), integerScale, 50, -(1+8+64+512), 10);
        
        drawLineWithColor(center, center + circ( 4.0/13.0) * 240, comp(0, 0), integerScale, 50,  1, 10);
        drawLineWithColor(center, center + circ(-4.0/13.0) * 240, comp(0, 0), integerScale, 50, -1, 10);
        
        drawLineWithColor(center, center + circ( 3.0/13.0) * 240, comp(60, 0), integerScale, 50, -3, 10);
        drawLineWithColor(center, center + circ(-3.0/13.0) * 240, comp(60, 0), integerScale, 50,  3, 10);
        
        drawLineWithColor(center, center + circ( 2.0/13.0) * 240, comp(0, 0), integerScale, 50,  2, 10);
        drawLineWithColor(center, center + circ(-2.0/13.0) * 240, comp(0, 0), integerScale, 50, -2, 10);
        
        drawLineWithColor(center, center + circ( 1.0/13.0) * 240, comp(0, 0), integerScale, 50,  4, 10);
        drawLineWithColor(center, center + circ(-1.0/13.0) * 240, comp(0, 0), integerScale, 50, -4, 10);
        
        drawLineWithColor(center, center + circ(0.0) * 240, comp(0, 0), integerScale, 50, 0, g_maxExponent);
        */
        
        //3
        /*
        drawLineWithColor(center, center + circ( 6.0/13.0) * 240, comp(0, 0), integerScale, 50, -(powi(3, 10) - 1) / 4, 9);
        drawLineWithColor(center, center + circ(-6.0/13.0) * 240, comp(0, 0), integerScale, 50,  (powi(3, 10) - 1) / 4, 9);
        
        drawLineWithColor(center, center + circ( 5.0/13.0) * 240, comp(0, 0), integerScale, 50,  (powi(3, 10) - 1) / 2, 9);
        drawLineWithColor(center, center + circ(-5.0/13.0) * 240, comp(0, 0), integerScale, 50, -(powi(3, 10) - 1) / 2, 9);
        
        drawLineWithColor(center, center + circ( 4.0/13.0) * 240, comp(0, 0), integerScale, 50,  (powi(3, 10) - 1) / 8, 9);
        drawLineWithColor(center, center + circ(-4.0/13.0) * 240, comp(0, 0), integerScale, 50, -(powi(3, 10) - 1) / 8, 9);
        
        drawLineWithColor(center, center + circ( 3.0/13.0) * 240, comp(0, 0), integerScale, 50,  1, 10);
        drawLineWithColor(center, center + circ(-3.0/13.0) * 240, comp(0, 0), integerScale, 50, -1, 10);
        
        drawLineWithColor(center, center + circ( 2.0/13.0) * 240, comp(0, 0), integerScale, 50,  3, 10);
        drawLineWithColor(center, center + circ(-2.0/13.0) * 240, comp(0, 0), integerScale, 50, -3, 10);
        
        drawLineWithColor(center, center + circ( 1.0/13.0) * 240, comp(0, 0), integerScale, 50,  9, 10);
        drawLineWithColor(center, center + circ(-1.0/13.0) * 240, comp(0, 0), integerScale, 50, -9, 10);
        
        drawLineWithColor(center, center + circ(0.0) * 240, comp(0, 0), integerScale, 50, 0, 10);
        
        drawIntegers(center, integerScale);
         */
        
    }
    
	postamble();
}














