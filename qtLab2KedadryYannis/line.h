#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include <iostream>

class Line : public Shape {

    private:
        QPoint _StartPos = QPoint(0,0);
        QPoint _EndPos = QPoint(0,0);

        QRectF getBoundingBox() const {
            float minX = _StartPos.x() > _EndPos.x() ? _EndPos.x() : _StartPos.x();
            float minY = _StartPos.y() > _EndPos.y() ? _EndPos.y() : _StartPos.y();
            float maxX = _StartPos.x() < _EndPos.x() ? _EndPos.x() : _StartPos.x();
            float maxY = _StartPos.y() < _EndPos.y() ? _EndPos.y() : _StartPos.y();
            return QRectF(QPoint(minX, maxY), QPoint(maxX, minY));
        }

    public:
        Line(Qt::PenStyle style, QColor color, int thickness):Shape(style, color, thickness){
        }

        Line(Qt::PenStyle style, QColor color, int thickness, QPoint startPos, QPoint endPos):Shape(style, color, thickness){
            _StartPos = startPos;
            _EndPos = endPos;
        }

        virtual ~Line(){}

        void setStartPos(QPoint pos){
            if(pos != _StartPos) _StartPos = pos;
        }

        void setEndPos(QPoint pos){
            if(pos != _EndPos) _EndPos = pos;
        }

        void draw(QPainter& painter, QPoint curMousePos) {
            switch(_DrawType){
                case START:
                    // create the startPos
                    setStartPos(curMousePos);
                    _Path->clear();
                    _Path->moveTo(_StartPos);
                    break;

                case MOVE:
                    // draw the preview of the line
                    setEndPos(curMousePos);
                    _Path->clear();
                    _Path->moveTo(_StartPos);
                    _Path->lineTo(_EndPos);
                    Shape::draw(painter, curMousePos);
                    break;

                case END:
                    // block the path
                    _Visible = true;
                    _DrawType = EMPTY;
                    Shape::draw(painter, curMousePos);
                    break;

                case EMPTY:
                    // to keep the line set
                    if(_Visible){
                        Shape::draw(painter, curMousePos);
                    }
                    break;
            }
        }

        bool contains(QPoint mousePos) const {
            qreal tolerance = 5.0;
            QRectF rect(mousePos.x() - tolerance, mousePos.y() - tolerance, 2 * tolerance, 2 * tolerance);
            return _Path->intersects(rect);
        }

        void move(float dx, float dy){
            _StartPos += QPoint(dx,dy);
            _EndPos += QPoint(dx,dy);
            _Path->clear();
            _Path->moveTo(_StartPos);
            _Path->lineTo(_EndPos);
        }
};

#endif // LINE_H
