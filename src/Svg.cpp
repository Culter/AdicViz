//
//  Svg.cpp
//  NewIll
//
//  Created by Christopher Culter on 2/9/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "Svg.h"
#include "Comp.h"
#include "Settings.h"

using namespace std;

void preamble(int x, int y) {
	cout << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
	cout << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
	cout << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\""
    << " width=\"" << x << "\" height=\"" << y << "\">\n";
}
void postamble(void) {
	cout << "</svg>\n";
}

void beginScript()
{
    indent::space();
    cout << "<script type=\"application/ecmascript\">\n<![CDATA[\n";
}

void insertScript()
{
    ifstream jsFile("../../NewIll/SvgScript.js");
    if (jsFile.good())
    {
        cout << "var g_prime = " << prime << ";\n";
        cout << jsFile.rdbuf();
    }
}

void endScript()
{
    cout << "]]>\n";
    indent::space();
    cout << "</script>\n\n";
}

void beginDefs()
{
    indent::space();
    cout << "<defs>\n";
}
void endDefs()
{
    indent::space();
    cout << "</defs>\n\n";
}

void beginStyle()
{
    indent::space();
    cout << "<style type=\"text/css\">\n<![CDATA[\n";
}
void endStyle()
{
    cout << "]]>\n";
    indent::space();
    cout << "</style>\n\n";
}

int indent::level = 0;

indent::indent()
{
    ++level;
}

indent::~indent()
{
    --level;
}

void indent::space()
{
    for (int i = 0; i < level; ++i)
    {
        cout << "  ";
    }
}