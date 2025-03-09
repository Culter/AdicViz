//
//  BarChart.cpp
//  NewIll
//
//  Created by Christopher Culter on 7/8/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <iomanip>

#include "Svg.h"
#include "Settings.h"
#include "BarChart.h"

using namespace std;

void printBarFill(int power)
{
    double r = 0;
    double g = 0;
    double b = 0;
    
    if (power == 0)
    {
        r = 1.0;
    }
    else
    {
        b = pow(1.0 / power, 0.8);
        g = 1.0 - b;
        
        b = sqrt(b);
        g = sqrt(g);
    }
    
    r *= 256;
    g *= 256;
    b *= 256;
    
    cout << "rgb(" << (int)r << "," << (int)g << "," << (int)b << ")";
}

void styleBars()
{
    cout << ".zero {\n";
    cout << "    fill: rgb(0,256,0);\n";
    cout << "}\n";
    
    for (int i = 0; i < g_maxExponentInteger; ++i)
    {
        cout << ".multiplesOf" << powi(prime, i) << " {\n";
        cout << "    fill: ";
        
        printBarFill(i);
        
        cout << ";\n";
        cout << "}\n";
    }
}

void drawBars(comp center, double scale)
{
    int max = powi(prime, g_maxExponentFraction);
    
    max = 100;
    
    //Begin transform
    std::cout << "<g id=\"BarsRoot\""
    << " transform=\""
    << "translate(" << center.getre() << "," << center.getim() << ")"
    << " "
    << "scale(" << scale << "," << -1 * scale << ")\"";
    
    //std::cout << " stroke=\"none\" fill=\"black\"";
    
    std::cout << ">\n";
    
    {
        indent inFractions;
        for (int i = -max; i <= max; ++i)
        {
            indent::space();
            
            if (i == 0)
            {
                std::cout << "<rect"
                << " x=\"" << i << "\""
                << " y=\"" << 0 << "\""
                << " width=\"1\" height=\"" << 9001 << "\""
                << " class=\"zero\""
                << "><title>"
                << i << " is divisible by " << prime << "^n for all n"
                << "</title></rect>\n";
            }
            else
            {
                int v = ord(i);
                int length = powi(prime, v);
                
                std::cout << "<rect"
                << " x=\"" << i << "\""
                << " y=\"" << 0 << "\""
                << " width=\"1\" height=\"" << length << "\""
                << " class=\"multiplesOf" << length << "\" "
                << "><title>"
                << i << " is divisible by " << prime << "^" << v << " = " << length
                << "</title></rect>\n";
            }
        }
    }
    
    
    //End transform
    indent::space();
    std::cout << "</g>\n";
}
