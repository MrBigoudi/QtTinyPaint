#include "setDrawAttributes.h"

QColor setNewColor(DrawColor newColor){
    switch(newColor){
    case WHITE:
        return Qt::white;
    case BLACK:
        return Qt::black;
    case RED:
        return Qt::red;
    case GREEN:
        return Qt::green;
    case BLUE:
        return Qt::blue;
    }
}

Qt::PenStyle setNewStyle(DrawStyle newStyle){
    switch(newStyle){
    case LINE:
        return Qt::SolidLine;
    case DOT_LINE:
        return Qt::DotLine;
    case DASH_LINE:
        return Qt::DashLine;
    case DASH_DOT_LINE:
        return Qt::DashDotLine;
    }
}

int setNewThickness(int newThickness){
    return newThickness < 0 ? 0 : newThickness;
}
