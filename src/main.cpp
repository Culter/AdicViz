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

void drawLabel(comp integerCenter, double integerScale, int integerValue, string name, double dx, string styleClass, double colorAngle) {
    comp integer = getPoint(integerCenter, integerScale, integerValue, g_maxExponentInteger);
    
    double x = integer.getre() + dx;
    double y = integer.getim() + 5.0;

    std::cout << "<text x=\"" << x << "\" y=\"" << y << "\" class=\"" << styleClass << "\" ";
    printFillValue(colorAngle, 80);
    std::cout << ">";
    std::cout << name;
    std::cout << "</text>\n";
}

void drawLabelAtPoint(comp point, string name, double colorAngle) {    
    double x = point.getre();
    double y = point.getim() + 10.5;

    std::cout << "<text x=\"" << x << "\" y=\"" << y << "\" class=\"integerLabel\"";
    if (colorAngle >= 0.0) {
        std::cout << " ";
        printFillValue(colorAngle, 80);
    }
    std::cout << ">";
    std::cout << name;
    std::cout << "</text>\n";
}

void drawLineWithColor(comp integerCenter, comp fractionCenter, comp offset, double integerScale, double fractionScale, int integerValue, int integerExponent, string name, double colorAngle)
{
    drawLine(integerCenter, fractionCenter, offset, integerScale, fractionScale, integerValue, integerExponent);
    
    comp integer = getPoint(integerCenter, integerScale, integerValue, integerExponent) + offset;
    comp dz = fractionCenter - integer;
    bool labelOnTop = dz.getim() < -abs(dz.getre() / 2);

    comp integerToFractionCenter = fractionCenter - integer;
    comp direction = integerToFractionCenter / integerToFractionCenter.norm();
    double lengthToPerimeter = integerToFractionCenter.norm() - fractionScale;
    double lengthToName = lengthToPerimeter * 0.6;
    comp nameCenter = integer + (direction * lengthToName);
    drawLabelAtPoint(nameCenter, name, colorAngle);

    drawPruferColored(fractionCenter, fractionScale, integerValue, g_maxExponentFraction, labelOnTop);
}

void TwoAdicWithLabels() {
    ofstream outFile("2-adic integers with labels.svg");
    cout.rdbuf(outFile.rdbuf());
    
    g_events = false;
    g_maxExponentInteger = 8;
    g_maxExponentFraction = 6;
    g_integerBallOpacity = 0.05;
    g_integerBallOverflow = 1.0;
    g_scale = 1.0 / (1.0 + 1.0 / (sin(pi / prime)));
    
    cout << setprecision(6);
    
    preamble(600, 600);
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
            stylePrufer();
            styleBars();
            endStyle();
            
            definePrufer();
        }
        
        endDefs();
        
        comp center(300, 300);
        double integerScale = 180 * (1.0 - g_scale);
        double fractionSize = 40;
        double fractionDistance = 246;
        
        drawIntegers(center, integerScale);
        
        drawLineWithColor(center, center + circ( 6.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize,   1+4+16+64+256+1024,  10, "−1⁄3", 0.5);
        drawLineWithColor(center, center + circ(-6.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, -(1+4+16+64+256+1024), 10, "1⁄3", 0.5);
        
        drawLineWithColor(center, center + circ( 5.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize,   1+8+64+512,  10, "−1⁄7", 0.375);
        drawLineWithColor(center, center + circ(-5.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, -(1+8+64+512), 10, "1⁄7", 0.625);
        
        drawLineWithColor(center, center + circ( 4.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize,  1, 10, "1", 0.0);
        drawLineWithColor(center, center + circ(-4.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, -1, 10, "−1", 0.0);
        
        drawLineWithColor(center, center + circ( 3.0/13.0) * fractionDistance, comp(60, 0), integerScale, fractionSize, -3, 10, "−3", 0.0);
        drawLineWithColor(center, center + circ(-3.0/13.0) * fractionDistance, comp(60, 0), integerScale, fractionSize,  3, 10, "3", 0.0);
        
        drawLineWithColor(center, center + circ( 2.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize,  2, 10, "2", 0.0);
        drawLineWithColor(center, center + circ(-2.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, -2, 10, "−2", 0.0);
        
        drawLineWithColor(center, center + circ( 1.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize,  4, 10, "4", 0.0);
        drawLineWithColor(center, center + circ(-1.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, -4, 10, "−4", 0.0);
        
        drawLineWithColor(center, center + circ(0.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, 0, 10, "0", 0.0);
    }
    
	postamble();
}

void ThreeAdicWithLabels() {
    ofstream outFile("3-adic integers with labels.svg");
    cout.rdbuf(outFile.rdbuf());
    
    g_events = false;
    g_maxExponentInteger = 8;
    g_maxExponentFraction = 6;
    g_integerBallOpacity = 0.05;
    g_integerBallOverflow = 1.0;
    g_scale = 1.0 / (1.0 + 1.0 / (sin(pi / prime)));
    
    cout << setprecision(6);
    
    preamble(600, 600);
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
            stylePrufer();
            styleBars();
            endStyle();
            
            definePrufer();
        }
        
        endDefs();
        
//        drawBars(comp(125, 150), 3);
      
        //drawIntegers(comp(200, 200), 180 * (1.0 - g_scale));
        //drawPrufer(comp(600, 200), 180);
        
        comp center(300, 300);
        double integerScale = 180 * (1.0 - g_scale);
        double fractionSize = 40;
        double fractionDistance = 246;
        
        drawIntegers(center, integerScale);

        drawLineWithColor(center, center + circ( 6.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, -(powi(3, 10) - 1) / 4, 9, "1⁄4", -1);
        drawLineWithColor(center, center + circ(-6.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize,  (powi(3, 10) - 1) / 4, 9, "−1⁄4", -1);
        
        drawLineWithColor(center, center + circ( 5.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize,  (powi(3, 10) - 1) / 2, 9, "−1⁄2", 0.5);
        drawLineWithColor(center, center + circ(-5.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, -(powi(3, 10) - 1) / 2, 9, "1⁄2", 0.5);
        
        drawLineWithColor(center, center + circ( 4.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize,  (powi(3, 10) - 1) / 8, 9, "−1⁄8", -1);
        drawLineWithColor(center, center + circ(-4.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, -(powi(3, 10) - 1) / 8, 9, "1⁄8", -1);
        
        drawLineWithColor(center, center + circ( 3.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize,  1, 10, "1", 0.0);
        drawLineWithColor(center, center + circ(-3.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, -1, 10, "−1", 0.0);
        
        drawLineWithColor(center, center + circ( 2.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize,  3, 10, "3", 0.0);
        drawLineWithColor(center, center + circ(-2.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, -3, 10, "−3", 0.0);
        
        drawLineWithColor(center, center + circ( 1.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize,  9, 10, "9", 0.0);
        drawLineWithColor(center, center + circ(-1.0/13.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, -9, 10, "−9", 0.0);
        
        drawLineWithColor(center, center + circ(0.0) * fractionDistance, comp(0, 0), integerScale, fractionSize, 0, 10, "0", 0.0);
        
        const double dx = 2.0;

        drawLabel(center, integerScale, 2, "2", dx, "smallLabelRight", 0.0);
        drawLabel(center, integerScale, -2, "−2", dx, "smallLabelRight", 0.0);
        drawLabel(center, integerScale, 4, "4", dx, "smallLabelRight", 0.0);
        drawLabel(center, integerScale, -4, "−4", dx, "smallLabelRight", 0.0);
        drawLabel(center, integerScale, 6, "6", dx, "smallLabelRight", 0.0);
        drawLabel(center, integerScale, -6, "−6", dx, "smallLabelRight", 0.0);
        drawLabel(center, integerScale, 7, "7", dx, "smallLabelRight", 0.0);
        drawLabel(center, integerScale, -7, "−7", dx, "smallLabelRight", 0.0);
        drawLabel(center, integerScale, 8, "8", dx, "smallLabelRight", 0.0);
        drawLabel(center, integerScale, -8, "−8", dx, "smallLabelRight", 0.0);
        
        drawLabel(center, integerScale, -((powi(3, 10) - 1) / 2) * 3, "3⁄2", -dx, "smallLabelLeft", 0.5);
        drawLabel(center, integerScale, ((powi(3, 10) - 1) / 2) * 3, "−3⁄2", -dx, "smallLabelLeft", 0.5);
        drawLabel(center, integerScale, -((powi(3, 10) - 1) / 2) * 5, "5⁄2", -dx, "smallLabelLeft", 0.5);
        drawLabel(center, integerScale, ((powi(3, 10) - 1) / 2) * 5, "−5⁄2", -dx, "smallLabelLeft", 0.5);
        // drawLabel(center, integerScale, -((powi(3, 10) - 1) / 2) * 15, "15⁄2", -dx, "smallLabelLeft", 0.5);
        // drawLabel(center, integerScale, ((powi(3, 10) - 1) / 2) * 15, "−15⁄2", -dx, "smallLabelLeft", 0.5);
    }
    
	postamble();
}

void ThreeAdicMetric() {
    ofstream outFile("3-adic metric on Z mod 27.svg");
    cout.rdbuf(outFile.rdbuf());
    
    g_maxExponentInteger = 3;
    g_maxExponentFraction = 3;
    g_integerBallOpacity = 1.0;
    g_integerBallOverflow = 1.08;
    // g_integerBallStroke = 8;
    g_integerBallLabels = true;
    g_scale = 0.95 / (1.0 + 1.0 / (sin(pi / prime)));
    
    cout << setprecision(6);
    
    preamble(600, 600);
    {
        indent inSvg;
        
        beginDefs();
        {
            indent inDefs;
            
            beginStyle();
            // styleIntegers();
            styleMetric();
            // stylePrufer();
            // styleBars();
            endStyle();
            
            definePrufer();
        }
        
        endDefs();
        
        comp center(300, 300);
        double integerScale = 270 * (1.0 - g_scale);
        
        drawIntegers(center, integerScale);
    }
    
	postamble();
}

int main (int argc, const char * argv[])
{
    // TwoAdicWithLabels();
    // ThreeAdicWithLabels();
    ThreeAdicMetric();
}














