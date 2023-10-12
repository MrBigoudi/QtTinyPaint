#ifndef DRAWCANVAS_H
#define DRAWCANVAS_H

#include <QWidget>
#include <QFrame>
#include <QPainterPath>
#include <QPainter>
#include <QSharedPointer>

#include "setDrawAttributes.h"

#include "shape.h"
#include "line.h"
#include "rectangle.h"
#include "ellipse.h"

enum DrawShape{LINE_SHAPE, RECTANGLE_SHAPE, ELLIPSE_SHAPE};

using ShapePointer = QSharedPointer<Shape>;

class DrawCanvas : public QWidget {
    Q_OBJECT

    private:
        QList<ShapePointer> _Shapes;
        ShapePointer _CurShape = nullptr;

        DrawShape _ShapeType = LINE_SHAPE;
        QColor _Color = Qt::black;
        int _Thickness = 2;
        Qt::PenStyle _Style = Qt::SolidLine;

        QPoint _MousePos = QPoint();
        bool _IsSelecting = false;
        bool _IsDeselecting = false;
        bool _RightClicked = false;

    private:
        void CreateLine(QPoint start, QPoint end){
            ShapePointer line(new Line(_Style, _Color, _Thickness, start, end));
            _CurShape = line;
            _Shapes.push_back(_CurShape);
        }

        void CreateRect(QPoint topLeft, QPoint bottomRight){
            ShapePointer rect(new Rectangle(_Style, _Color, _Thickness, topLeft, bottomRight));
            _CurShape = rect;
            _Shapes.push_back(_CurShape);
        }

        void CreateEllipse(QPoint topLeft, QPoint bottomRight){
            ShapePointer ellipse(new Ellipse(_Style, _Color, _Thickness, topLeft, bottomRight));
            _CurShape = ellipse;
            _Shapes.push_back(_CurShape);
        }

    public:
        DrawCanvas(QWidget *parent = nullptr);
        ~DrawCanvas(){};

        void setColor(DrawColor newColor){
            _Color = setNewColor(newColor);
            if(_IsSelecting){
                _CurShape->setColor(newColor);
                update();
            }
        };

        void setStyle(DrawStyle newStyle){
            _Style = setNewStyle(newStyle);
            if(_IsSelecting){
                _CurShape->setStyle(newStyle);
                update();
            }
        }

        void setThickness(int newThickness){
            _Thickness = setNewThickness(newThickness);
            if(_IsSelecting){
                _CurShape->setThickness(newThickness);
                update();
            }
        }

        void setShape(DrawShape newShape){
            _ShapeType = newShape;
        }

        // return the first selected element or nullptr if none is selected
        ShapePointer isSelecting(QPoint mousePosition) const {
            // reverse iteration
            for (qsizetype i = _Shapes.size()-1; i>=0; i--) {
                if(_Shapes.at(i)->contains(mousePosition))
                    return _Shapes.at(i);
            }
            return nullptr;
        }

    private:
        void mousePressEventLeft(QMouseEvent* e);
        void mousePressEventRight(QMouseEvent* e);

    protected:
        virtual void paintEvent(QPaintEvent*);
        void mousePressEvent(QMouseEvent*);
        void mouseReleaseEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);
};

#endif // DRAWCANVAS_H
