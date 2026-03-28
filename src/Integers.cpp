//
//  Integers.cpp
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
#include "Integers.h"
#include "Fractions.h"

using namespace std;

void styleIntegers()
{
    cout << ".aa {\n";
    if (g_events)
    {
        cout << "    pointer-events: fill;\n";
        cout << "    cursor: crosshair;\n";
    }
    
    cout << "    fill-opacity: 0.05;\n";
    cout << "    stroke-width: 2;\n";
    cout << "    stroke-opacity: 0.5;\n";
    cout << "}\n";
    
    for (int i = 0; i < g_maxExponentInteger; ++i)
    {
        cout << ".aa" << i << " {\n";
        cout << "}\n";
    }
    
    cout << ".a {\n";
    if (g_events)
    {
        cout << "    pointer-events: fill;\n";
        cout << "    cursor: crosshair;\n";
    }
    cout << "}\n";
    
    cout << ".integerLabel {\n";
    cout << "    font-family: \"Noto Serif\", serif;\n";
    cout << "    font-size: 30px;\n";

    cout << "    text-anchor: middle;\n";

    cout << "    stroke: white;\n";
    cout << "    stroke-linecap: round;\n";
    cout << "    stroke-linejoin: round;\n";
    cout << "    stroke-width: 3px;\n";
    cout << "    paint-order: stroke fill;\n";
    cout << "}\n";
    
    cout << ".smallLabelRight {\n";
    cout << "    font-family: \"Noto Serif\", serif;\n";
    cout << "    font-size: 14px;\n";

    cout << "    text-anchor: start;\n";

    cout << "    stroke: white;\n";
    cout << "    stroke-linecap: round;\n";
    cout << "    stroke-linejoin: round;\n";
    cout << "    stroke-width: 1.5px;\n";
    cout << "    paint-order: stroke fill;\n";
    cout << "}\n";
    
    cout << ".smallLabelLeft {\n";
    cout << "    font-family: \"Noto Serif\", serif;\n";
    cout << "    font-size: 14px;\n";

    cout << "    text-anchor: end;\n";

    cout << "    stroke: white;\n";
    cout << "    stroke-linecap: round;\n";
    cout << "    stroke-linejoin: round;\n";
    cout << "    stroke-width: 1.5px;\n";
    cout << "    paint-order: stroke fill;\n";
    cout << "}\n";
}

void styleMetric()
{
    cout << ".aa {\n";
    if (g_events)
    {
        cout << "    pointer-events: fill;\n";
        cout << "    cursor: crosshair;\n";
    }
    
    cout << "    fill-opacity:" << g_integerBallOpacity << ";\n";
    cout << "}\n";
    
    // for (int i = 0; i < g_maxExponentInteger; ++i)
    // {
    //     cout << ".aa" << i << " {\n";
    //     cout << "}\n";
    // }
    
    cout << ".aa0 {\n";
    cout << "    fill: #7288cf;\n";
    cout << "    stroke: #0a1855;\n";
    cout << "    stroke-width: 3;\n";
    cout << "    stroke-opacity: 1;\n";
    cout << "}\n";
    
    cout << ".aa1 {\n";
    cout << "    fill: #98b9d8;\n";
    cout << "    stroke: #0a1855;\n";
    cout << "    stroke-width: 1.5;\n";
    cout << "    stroke-opacity: 1;\n";
    cout << "}\n";
    
    cout << ".aa2 {\n";
    cout << "    fill: #badfe4;\n";
    cout << "    stroke: #0a1855;\n";
    cout << "    stroke-width: 0.75;\n";
    cout << "    stroke-opacity: 1;\n";
    cout << "}\n";
    
    cout << ".a {\n";
    
    // cout << "    fill-opacity:" << g_integerBallOpacity << ";\n";
    cout << "    stroke: #0a1855;\n";
    cout << "    stroke-width: 0.375;\n";
    cout << "    stroke-opacity: 1;\n";
    cout << "    fill-opacity: 1;\n";
    cout << "    fill: #eff8f7;\n";
    // cout << "    stroke-width: 0;\n";

    if (g_events)
    {
        cout << "    pointer-events: fill;\n";
        cout << "    cursor: crosshair;\n";
    }
    cout << "}\n";
    
    cout << ".integerLabel {\n";
    cout << "    font-family: \"Noto Serif\", serif;\n";
    cout << "    font-size: 31px;\n";

    cout << "    text-anchor: middle;\n";

    cout << "    fill: black;\n";
    cout << "    fill-opacity: 1;\n";
    // cout << "    stroke: white;\n";
    // cout << "    stroke-linecap: round;\n";
    // cout << "    stroke-linejoin: round;\n";
    cout << "    stroke-width: 0;\n";
    // cout << "    paint-order: stroke fill;\n";
    cout << "}\n";
    
    cout << ".smallLabelRight {\n";
    cout << "    font-family: \"Noto Serif\", serif;\n";
    cout << "    font-size: 14px;\n";

    cout << "    text-anchor: start;\n";

    cout << "    stroke: white;\n";
    cout << "    stroke-linecap: round;\n";
    cout << "    stroke-linejoin: round;\n";
    cout << "    stroke-width: 1.5px;\n";
    cout << "    paint-order: stroke fill;\n";
    cout << "}\n";
    
    cout << ".smallLabelLeft {\n";
    cout << "    font-family: \"Noto Serif\", serif;\n";
    cout << "    font-size: 14px;\n";

    cout << "    text-anchor: end;\n";

    cout << "    stroke: white;\n";
    cout << "    stroke-linecap: round;\n";
    cout << "    stroke-linejoin: round;\n";
    cout << "    stroke-width: 1.5px;\n";
    cout << "    paint-order: stroke fill;\n";
    cout << "}\n";
}

void printAdicTitle(int value, int power)
{
    int modulus = powi(prime, power);
    
    std::cout << "<title>";
    if (value != 0)
    {
        if (value * 2 < modulus)
        {
            std::cout << value;
        }
        else
        {
            std::cout << value - modulus;
        }
        
        std::cout << " + ";
    }
    
    if (power != 0) std::cout << modulus;
    
    std::cout << "Z"; //&#x2124; would be double-struck
    if (prime <= 9)
    {
        std::cout << "&#x208" << prime << ";";
    }
    else
    {
        std::cout << "_" << prime;
    }
    
    std::cout << " = {...";
    
    for (int i = power - 1; i >= 0; --i)
    {
        int mod = powi(prime, i);
        std::cout << (value / mod) % prime;
    }
    
    std::cout << "}</title>";
}

void recursiveDraw(comp center, double offset, double scale, int value, int power)
{
    indent::space();
    std::cout << "<g "
    << "id=\"a_" << value << "_" << power << "\""
    << ">";
    
    {
        indent inGroup;
        
        printAdicTitle(value, power);
        
        std::cout << "\n";
        
        double stroke = g_integerBallStroke;
        double radius = stroke + scale / (1.0 - g_scale) * g_integerBallOverflow;
        
        indent::space();
        std::cout << "<circle "
        << "id=\"aa_" << value << "_" << power << "\" "
        << "cx=\"" << center.getre() << "\" "
        << "cy=\"" << center.getim() << "\" "
        << "r=\"" << radius << "\" "
        << "class=\"aa aa" << power << "\" "
        << "/>\n";
        
        double newScale = scale * g_scale;
        double newRadius = stroke + newScale / (1.0 - g_scale) * g_integerBallOverflow;
        
        bool fRecursive = (power + 1 < g_maxExponentInteger);
        
        for (int d = 0; d < prime; ++d)
        {
            double newOffset = (offset + d) / prime;
//          double newOffset = ((double)d) / prime;
            comp newCenter = center + circ (newOffset) * scale;
            
            int newValue = value + powi(prime, power) * d;
            
            if (fRecursive)
            {
                recursiveDraw(newCenter, newOffset, newScale, newValue, power + 1);
            }
            else
            {
                indent::space();
                std::cout << "<circle "
                << "id=\"a_" << newValue << "_" << power + 1<< "\" "
                << "cx=\"" << newCenter.getre() << "\" "
                << "cy=\"" << newCenter.getim() << "\" "
                << "r=\"" << newRadius << "\" "
                << "class=\"a\""
                <<">";
                
                printAdicTitle(newValue, power + 1);
                
                std::cout << "</circle>\n";
                
                if (g_integerBallLabels) {
                    double x = newCenter.getre();
                    double y = newCenter.getim() + 10.5;

                    auto balanced = (newValue > powi(prime, power + 1) / 2.0) ? (newValue - powi(prime, power + 1)) : newValue;

                    std::cout << "<text x=\"" << x << "\" y=\"" << y << "\" class=\"integerLabel\" ";
                    // printFillValue(0.0, 80);
                    if (abs(balanced) >= 10) {
                        std:cout << "letter-spacing=\"-2.5px\"";
                    }
                    std::cout << ">";
                    std::cout << balanced;
                    std::cout << "</text>\n";
                }
            }
        }
    }
    
    indent::space();
    std::cout << "</g>\n";
}

void drawIntegers(comp center, double scale)
{
    indent::space();
    std::cout << "<g "
    << "id=\"IntegerRoot\" "
    << "fill=\"black\" stroke=\"none\"";
    
    if (g_events)
    {
        cout << " onmouseover=\"hover_a_start(evt)\" onmouseout=\"hover_a_stop(evt)\"";
    }
    
    cout << ">";
    
    {
        indent inIntegers;
        
        recursiveDraw(center, 0, scale, 0, 0);
    }
    
    indent::space();
    std::cout << "</g>\n";
}

comp getPoint(comp center, double scale, int value, int power)
{
    comp point = center;
    for (int i = 1; i <= power; ++i)
    {
        point += circ((double)value / pow((double)prime, i)) * pow(g_scale, i-1) * scale;
    }
    
    return point;
}

