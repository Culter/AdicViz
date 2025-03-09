//
//  Fractions.cpp
//  NewIll
//
//  Created by Christopher Culter on 2/9/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <iomanip>

#include "Svg.h"
#include "Comp.h"
#include "Settings.h"
#include "Fractions.h"

using namespace std;

double g_curvePower = 2.5; //p=3
//double g_curvePower = 4.0; //p=2

void drawPruferVisiblePath(int power, int maxDetail);
void drawPruferBackgroundPath(int power, int maxDetail);

double rCurve(double i)
{
    double x = 1.0 - pow(g_scale, i);
    return pow(x, g_curvePower);
}

double rCurvePrime(double i)
{
    double innerPower = pow(g_scale, i);
    
    return g_curvePower * pow(1.0 - innerPower, g_curvePower - 1.0) * (-log(g_scale)) * innerPower;
}

comp pruferCurve(double fraction, double t, double halfWidth)
{
    return circ(fraction + halfWidth / pow(prime, t)) * rCurve(t);
}

comp pruferDerivative(double fraction, double t, double halfWidth)
{
    double r = rCurve(t);
    double rPrime = rCurvePrime(t);
    
    double theta = fraction + halfWidth / pow(prime, t);
    double thetaPrime = halfWidth * (-log((double)prime) / pow(prime, t)) * 2.0 * pi;
    
    comp angleV = circ(theta);
    
//    comp point = angleV * r;
    comp derivative = comp(rPrime, -r * thetaPrime) * angleV;
    
    return derivative;
}

void printPrufer(int value, int power)
{
    if (value == 0)
    {
        std::cout << "0";
        return;
    }
    
    int max = powi(prime, power);
    
    value = value % max;
    if (value * 2 <= max)
    {
        std::cout << value;
    }
    else
    {
        std::cout << value - max;
    }
    
    std::cout << "/" << max << " = " << "0.";
    
    for (int i = power - 1; i >= 0; --i)
    {
        int mod = powi(prime, i);
        std::cout << (value / mod) % prime;
    }
}

void drawPruferVisiblePath(int power, int maxDetail)
{
    double hw = 0.45;
    double depress = -log(1.0 - hw) / log((double)prime);
    
    int max = powi(prime, power);
    
    //Start at edge
    std::cout << "M1 0";
    
    //Curve back to primary ring
    double stepsize = 1.0;
    for (double i = maxDetail; i >= power; i -= stepsize)
    {
        comp p = pruferCurve(0, i, hw);
        comp control = p + pruferDerivative(0, i, hw) * (stepsize / 3.0);
        
        if (i == maxDetail)
        {
            std::cout << " C1,0";
            std::cout << " " << control.getre() << "," << control.getim();
            std::cout << " " << p.getre() << "," << p.getim();
        }
        else
        {
            std::cout << " S";
            std::cout << " " << control.getre() << "," << control.getim();
            std::cout << " " << p.getre() << "," << p.getim();
        }
    }
    
    if (power >= 1.0)
    {
        //Curve to minimum point
        {
            double nextFraction = 1.0 / max;
            double t1 = power;
            
            comp p1 = pruferCurve(nextFraction, t1, hw - 1.0);
            comp c1 = p1 - pruferDerivative(nextFraction, t1, hw - 1.0) * (depress / 3.0);
            
            double t2 = t1 - depress;
            
            comp p2 = pruferCurve(nextFraction, t2, hw - 1.0);
            comp c2 = p2 + pruferDerivative(nextFraction, t2, hw - 1.0) * (depress / 3.0);
            
            std::cout << " C";
            std::cout << c1.getre() << "," << c1.getim();
            std::cout << " " << c2.getre() << "," << c2.getim();
            std::cout << " " << p2.getre() << "," << p2.getim();
        }
        
        //Curve back to primary ring
        {
            double lastFraction = -1.0 / max;
            double t1 = (double)power - depress;
            
            comp p1 = pruferCurve(lastFraction, t1, 1.0 - hw);
            comp c1 = p1 + pruferDerivative(lastFraction, t1, 1.0 - hw) * (depress / 3.0);
            
            double t2 = power;
            
            comp p2 = pruferCurve(lastFraction, t2, 1.0 - hw);
            comp c2 = p2 - pruferDerivative(lastFraction, t2, 1.0 - hw) * (depress / 3.0);
            
            std::cout << " C";
            std::cout << c1.getre() << "," << c1.getim();
            std::cout << " " << c2.getre() << "," << c2.getim();
            std::cout << " " << p2.getre() << "," << p2.getim();
        }
    }
    
    //Curve back to edge
    for (double i = power; i <= maxDetail; i += stepsize)
    {
        comp p1 = pruferCurve(0, i, -hw);
        comp c1 = p1 + pruferDerivative(0, i, -hw) * (stepsize / 3.0);
        
        comp p2 = pruferCurve(0, i + stepsize, -hw);
        comp c2 = p2 - pruferDerivative(0, i + stepsize, -hw) * (stepsize / 3.0);
        
        if (i == power)
        {
            std::cout << " C";
            std::cout << c1.getre() << "," << c1.getim();
            std::cout << " " << c2.getre() << "," << c2.getim();
            std::cout << " " << p2.getre() << "," << p2.getim();
        }
        else if (i + stepsize <= maxDetail)
        {
            std::cout << " S";
            std::cout << " " << c2.getre() << "," << c2.getim();
            std::cout << " " << p2.getre() << "," << p2.getim();
        }
        else
        {
            std::cout << " S1,0 1,0";
        }
    }
    
    //End visible element
    std::cout << " z";
}

void drawPruferBackgroundPath(int power, int maxDetail)
{
    double hw = 0.45;
    double depress = -log(1.0 - hw) / log((double)prime);
    
    {
        comp e1 = circ( 0.5 / pow((double)prime, maxDetail));
        comp e2 = circ(-0.5 / pow((double)prime, maxDetail));
        
        std::cout << "M" << e1.getre() << " " << e1.getim();
        
        for (double i = maxDetail; i >= power + 1; i -= 1.0)
        {
            comp p1 = pruferCurve(0, i, 0.5);
            std::cout << "L" << p1.getre() << " " << p1.getim();
            
            if (i >= 1.0)
            {
                comp p2 = pruferCurve(0, i - depress, 0.5);
                std::cout << "L" << p2.getre() << " " << p2.getim();
                
                comp p3 = circ(0.5 / pow((double)prime, i - 1)) * rCurve(i - depress);
                std::cout << "L" << p3.getre() << " " << p3.getim();
            }
        }
        
        if (power >= 1.0)
        {
            comp m1 = circ( 0.5 / pow((double)prime, power)) * rCurve(power - 1.0);
            comp m2 = circ(-0.5 / pow((double)prime, power)) * rCurve(power - 1.0);
            
            std::cout << "L" << m1.getre() << " " << m1.getim();
            std::cout << "L" << m2.getre() << " " << m2.getim();
        }
        
        for (double i = power + 1; i <= maxDetail; i += 1.0)
        {
            if (i >= 1.0)
            {
                comp p3 = circ(-0.5 / pow((double)prime, i - 1)) * rCurve(i - depress);
                std::cout << "L" << p3.getre() << " " << p3.getim();
                
                comp p2 = pruferCurve(0, i - depress, -0.5);
                std::cout << "L" << p2.getre() << " " << p2.getim();
            }
            
            comp p1 = pruferCurve(0, i, -0.5);
            std::cout << "L" << p1.getre() << " " << p1.getim();
        }
        
        std::cout << "L" << e2.getre() << " " << e2.getim();
    }
    
    //End background path
    std::cout << " z";
}

void stylePrufer()
{
    cout << ".fracRegion {\n";
    if (g_events)
    {
        cout << "    pointer-events: fill;\n";
        cout << "    cursor: crosshair;\n";
    }
    
    cout << "    visibility: hidden;\n";
    cout << "    fill: none;\n";
    cout << "    stroke: none;\n";
    cout << "}\n";
    
    cout << ".fracVisible {\n";
    if (g_events)
    {
        cout << "    pointer-events: none;\n";
    }
    
    cout << "    stroke-width: 0.01;\n";
    cout << "}\n";
}

void definePrufer()
{
    for (int i = 0; i <= g_maxExponentFraction; ++i)
    {
        indent::space();
        cout << "<g id=\"bb" << i << "\">\n";
        {
            indent inGroup;
            
            indent::space();
            cout << "<path id=\"bbb" << i << "\" class=\"fracRegion\" d=\"";
            drawPruferBackgroundPath(i, g_maxExponentFraction);
            cout << "\" />\n";
            
            indent::space();
            cout << "<path id=\"b" << i << "\" class=\"fracVisible\" d=\"";
            drawPruferVisiblePath(i, g_maxExponentFraction);
            cout << "\" />\n";
        }
        
        indent::space();
        cout << "</g>\n";
    }
}

void drawPrufer(comp center, double scale)
{
    int maxOrd = g_maxExponentFraction;
    
    //Begin transform
    std::cout << "<g id=\"FractionRoot\" transform=\""
    << "translate(" << center.getre() << "," << center.getim() << ")"
    << " "
    << "scale(" << scale << ")\"";
    
    std::cout << " stroke=\"none\" fill=\"gray\"";
    if (g_events)
    {
        std::cout << " onmouseover=\"hover_b_start(evt)\" onmouseout=\"hover_b_stop(evt)\"";
    }
    
    std::cout << ">\n";
    
    {
        indent inFractions;
        
        double limitR = (1.0 - rCurve(maxOrd + 1)) / 2;
                
        indent::space();
        std::cout << "<circle "
        << "id=\"b_Limit\" "
        << "r=\"" << (1.0 - limitR) << "\" "
        << "stroke-width=\"" << limitR * 2.0 << "\" "
        << "stroke=\"gray\" stroke-opacity=\"0.675\" fill=\"white\""
        << "><title>(Unresolved)</title></circle>\n\n";
        
        for (int power = maxOrd; power >= 0; --power)
        {
            //Begin exponent
            indent::space();
            std::cout << "<g id=\"b_X_" << power << "\">\n";
            
            {
                indent inExponent;
                
                int max = powi(prime, power);
                for (int d = 0; d < max; ++d)
                {
                    if ((d % prime) == 0 && power != 0) continue;
                    
                    indent::space();
                    std::cout << "<use xlink:href=\"#bb" << power << "\" "
                    << "id=\"b_" << d << "_" << power << "\" "
                    << "transform=\"rotate(" << -360.0 * d / max << ")\""
                    << "><title>";
                    printPrufer(d, power);
                    std::cout << "</title></use>\n";
                }
            }
            
            //End exponent
            indent::space();
            std::cout << "</g>\n";
        }
    }
    
    //End transform
    indent::space();
    std::cout << "</g>\n";
}

void printFillValue(double angle)
{
    double r = 0;
    double g = 0;
    double b = 0;
    
    if (angle >= 0.0)
    {
        angle = fmod(angle, 1.0);
    }
    else
    {
        angle = 1.0 - fmod(-angle, 1.0);
    }
    
    if (angle < 1.0/3.0)
    {
        r = (angle - 1.0/3.0) / (0.0/3.0 - 1.0/3.0);
        g = (angle - 0.0/3.0) / (1.0/3.0 - 0.0/3.0);
        
        r = sqrt(r);
        g = sqrt(g);
    }
    else if (angle < 2.0/3.0)
    {
        g = (angle - 2.0/3.0) / (1.0/3.0 - 2.0/3.0);
        b = (angle - 1.0/3.0) / (2.0/3.0 - 1.0/3.0);
        
        g = sqrt(g);
        b = sqrt(b);
    }
    else
    {
        b = (angle - 3.0/3.0) / (2.0/3.0 - 3.0/3.0);
        r = (angle - 2.0/3.0) / (3.0/3.0 - 2.0/3.0);
        
        b = sqrt(b);
        r = sqrt(r);
    }
    
    r *= 256;
    g *= 256;
    b *= 256;
    
    cout << "fill=\"rgb(" << (int)r << "," << (int)g << "," << (int)b << ")\"";
}

void drawPruferColored(comp center, double scale, int colorValue, int colorPower)
{
    int maxOrd = g_maxExponentFraction;
    
    //Begin transform
    std::cout << "<g id=\"FractionRoot_" << colorValue << "_" << colorPower << "\" "
    << "transform=\""
    << "translate(" << center.getre() << "," << center.getim() << ") "
    << "scale(" << scale << ")\"";
    
    std::cout << " stroke=\"none\" fill=\"gray\"";
    if (g_events)
    {
        std::cout << " onmouseover=\"hover_b_start(evt)\" onmouseout=\"hover_b_stop(evt)\"";
    }
    
    std::cout << ">\n";
    
    {
        indent inFractions;
        
        double limitR = (1.0 - rCurve(maxOrd + 1)) / 2;
        
        indent::space();
        std::cout << "<circle "
        << "id=\"b_Limit_" << colorValue << "_" << colorPower << "\" "
        << "r=\"" << (1.0 - limitR) << "\" "
        << "stroke-width=\"" << limitR * 2.0 << "\" "
        << "stroke=\"gray\" stroke-opacity=\"0.675\" fill=\"white\""
        << "><title>(Unresolved)</title></circle>\n\n";
        
        for (int power = maxOrd; power >= 0; --power)
        {
            //Begin exponent
            indent::space();
            std::cout << "<g id=\"b_X_" << power << "_" << colorValue << "_" << colorPower << "\">\n";
            
            {
                indent inExponent;
                
                int max = powi(prime, power);
                for (int d = 0; d < max; ++d)
                {
                    if ((d % prime) == 0 && power != 0) continue;
                    
                    indent::space();
                    std::cout << "<use xlink:href=\"#bb" << power << "\" "
                    << "id=\"b_" << d << "_" << power << "_" << colorValue << "_" << colorPower << "\" "
                    << "transform=\"rotate(" << -360.0 * d / max << ")\" ";
                    
                    //Color!
                    double colorFraction = ((double)d / max) * colorValue;
                    printFillValue(colorFraction);
                    
                    cout << "><title>";
                    printPrufer(d, power);
                    std::cout << "</title></use>\n";
                }
            }
            
            //End exponent
            indent::space();
            std::cout << "</g>\n";
        }
    }
    
    //End transform
    indent::space();
    std::cout << "</g>\n";
}









