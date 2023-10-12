#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPainterPath>

#include "setDrawAttributes.h"

class Shape{
    protected:
        DrawType _DrawType = EMPTY;
        bool _Visible = false;

        QPainterPath* _Path = new QPainterPath();
        QColor _Color;
        int _Thickness;
        Qt::PenStyle _Style;

        bool _IsSelected = false;

    protected:
        Shape(Qt::PenStyle style, QColor color, int thickness){
            _Style = style;
            _Color = color;
            _Thickness = thickness;
        };

    public:
        virtual QRectF getBoundingBox() const = 0;
        virtual void move(float dx, float dy) = 0;


    private:
        void drawBoundingBox(QPainter& painter) const {
            QPen pen;
            pen.setColor(Qt::black);
            pen.setWidth(2);
            pen.setStyle(Qt::DotLine);
            painter.setPen(pen);

            float delta = 10;
            QRectF boundingBox = getBoundingBox();
            QRectF scaledBoundingBox =
                QRectF(
                    boundingBox.topLeft() + QPoint(-delta, delta),
                    boundingBox.bottomRight() + QPoint(delta, -delta)
                );
            painter.drawRect(scaledBoundingBox);
        }

    public:
        ~Shape(){
            delete _Path;
        }

        void setSelected(bool isSelected){
            _IsSelected = isSelected;
        }

        void setDraw(DrawType newType){
            if(_DrawType != newType) _DrawType = newType;
        }

        void setColor(DrawColor newColor){
            _Color = setNewColor(newColor);
        };

        void setStyle(DrawStyle newStyle){
            _Style = setNewStyle(newStyle);
        }

        void setThickness(int newThickness){
            _Thickness = setNewThickness(newThickness);
        }

        virtual void draw(QPainter& painter, QPoint){
            QPen pen;
            pen.setColor(_Color);
            pen.setWidth(_Thickness);
            pen.setStyle(_Style);
            painter.setPen(pen);
            painter.drawPath(*_Path);

            if(_IsSelected) drawBoundingBox(painter);
        };

        virtual bool contains(QPoint mousePos) const {
            return _Path->contains(mousePos);
        }

};

#endif // SHAPE_H
