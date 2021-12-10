#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

// Allocate the static constant space.
const int Xwindow::MAX_NUM_COLOURS = 5; 

Xwindow::Xwindow(int width, int height) {
    XColor c;

    Colormap map;
    map=DefaultColormap(d,DefaultScreen(d));

    const int ALL_COLOURS = 8;
    char allColours[8][8] = {
        "White", "Black", "Red", 
        "Green", "Blue", "Orange", 
        "Brown", "Cyan"
    };

    d = XOpenDisplay(nullptr);

    if (d == NULL) {
		cerr << "Could not open display" << endl;
		return;
	}
    
    for(int i = 0; i < ALL_COLOURS; i++) {
        XParseColor(d,map,allColours[i],&xcolour);
        XAllocColor(d,map,&xcolour);
        colours[i]=xcolour.pixel;
    }

	XSetForeground(d,gc,colours[Black]);
}

Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, 
    Xwindow::Colour colour) 
{
    XSetForeground(d, gc, colours[static_cast<int>(colour)]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[static_cast<int>(Colour::Black)]);
}

void Xwindow::drawString(int x, int y, std::string msg) {
    XDrawString(d, w, DefaultGC(d, s), x, y, 
        msg.c_str(), msg.length());
}