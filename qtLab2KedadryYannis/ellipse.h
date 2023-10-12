#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape{

    private:
        QPoint _TopLeft = QPoint(0,0);
        QPoint _BottomRight = QPoint(0,0);

    private:
        void setTopLeftCorner(QPoint pos){
            _TopLeft = pos;
        }
        void setBottomRightCorner(QPoint pos){
            _BottomRight = pos;
        }
        QRectF getBoundingBox() const {
            float minX = _TopLeft.x() > _BottomRight.x() ? _BottomRight.x() : _TopLeft.x();
            float minY = _TopLeft.y() > _BottomRight.y() ? _BottomRight.y() : _TopLeft.y();
            float maxX = _TopLeft.x() < _BottomRight.x() ? _BottomRight.x() : _TopLeft.x();
            float maxY = _TopLeft.y() < _BottomRight.y() ? _BottomRight.y() : _TopLeft.y();
            return QRectF(QPoint(minX, maxY), QPoint(maxX, minY));
        }

    public:
        Ellipse(Qt::PenStyle style, QColor color, int thickness):Shape(style, color, thickness){
        }

        Ellipse(Qt::PenStyle style, QColor color, int thickness, QPoint topLeft, QPoint bottomRight):Shape(style, color, thickness){
            _TopLeft = topLeft;
            _BottomRight = bottomRight;
        }

        virtual ~Ellipse(){}

        void draw(QPainter& painter, QPoint curMousePos) {
            switch(_DrawType){
                case START:
                    // create the startPos
                    setTopLeftCorner(curMousePos);
                    _Path->clear();
                    _Path->addEllipse(QRectF(_TopLeft, _BottomRight));
                    break;

                case MOVE:
                    // draw the preview of the line
                    setBottomRightCorner(curMousePos);
                    _Path->clear();
                    _Path->addEllipse(QRectF(_TopLeft, _BottomRight));
                    Shape::draw(painter, curMousePos);
                    break;

                case END:
                    // block the path
                    _Visible = true;
                    _DrawType = EMPTY;
                    Shape::draw(painter, curMousePos);
                    break;

                case EMPTY:
                    // to keep the ellipse set
                    if(_Visible){
                        Shape::draw(painter, curMousePos);
                    }
                    break;
            }
        }

        void move(float dx, float dy){
            _TopLeft += QPoint(dx,dy);
            _BottomRight += QPoint(dx,dy);
            _Path->clear();
            _Path->addEllipse(QRectF(_TopLeft, _BottomRight));
        }
};

#endif // ELLIPSE_H
