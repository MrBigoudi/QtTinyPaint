#ifndef SETDRAWATTRIBUTES_H
#define SETDRAWATTRIBUTES_H

#include <QPainter>

enum DrawType{START, MOVE, END, EMPTY};
enum DrawColor{BLUE, WHITE, RED, GREEN, BLACK};
enum DrawStyle{LINE, DOT_LINE, DASH_LINE, DASH_DOT_LINE};

QColor setNewColor(DrawColor newColor);

Qt::PenStyle setNewStyle(DrawStyle newStyle);

int setNewThickness(int newThickness);

#endif // SETDRAWATTRIBUTES_H
