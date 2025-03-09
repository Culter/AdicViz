//
//  Svg.h
//  NewIll
//
//  Created by Christopher Culter on 2/9/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef NewIll_Svg_h
#define NewIll_Svg_h

void preamble(int x, int y);
void postamble(void);

void beginScript();
void insertScript();
void endScript();

void beginDefs();
void endDefs();

void beginStyle();
void endStyle();

class indent
{
public:
    indent();
    ~indent();
    
    static void space();
    
    static int level;
};

#endif
