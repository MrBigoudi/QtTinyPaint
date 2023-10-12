#include "drawCanvas.h"

#include <QMouseEvent>
#include <iostream>

DrawCanvas::DrawCanvas(QWidget *parent):QWidget(parent){
    // set the size
    setMinimumSize(360, 120);
}

void DrawCanvas::paintEvent(QPaintEvent* e) {
    // standard behavior (draws the background)
    QWidget::paintEvent(e);

    QPainter painter(this);
    QPen pen;

    // Draw the borders
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRect(rect());

    for (qsizetype i = 0; i < _Shapes.size(); i++) {
        _Shapes.at(i)->draw(painter, _MousePos);
    }

}

void DrawCanvas::mousePressEventLeft(QMouseEvent* e){
    _MousePos = e->pos();

    // to unselect a shape must be selecting and not clicking on the current shape bounding box
    if(_IsSelecting && !_CurShape->getBoundingBox().contains(_MousePos)) {
        _IsSelecting = false;
        _IsDeselecting = true;
        _CurShape->setSelected(false);
        update();
        return;
    }


    // check if selecting an element
    ShapePointer selected = isSelecting(_MousePos);
    if(!selected){
        // create the correct shape
        switch(_ShapeType){
        case LINE_SHAPE:
            CreateLine(_MousePos, _MousePos);
            break;
        case RECTANGLE_SHAPE:
            CreateRect(_MousePos, _MousePos);
            break;
        case ELLIPSE_SHAPE:
            CreateEllipse(_MousePos, _MousePos);
            break;
        }
        _CurShape->setDraw(START);
        update();
        return;
    } else {
        // select a shape
        if(!_IsSelecting){
            _IsSelecting = true;
            _CurShape = selected;
            _CurShape->setSelected(true);
            update();
            return;
        }
    }
}

void DrawCanvas::mousePressEventRight(QMouseEvent* e){
    _RightClicked = true;
    if(_IsSelecting){
        _MousePos = e->pos();
        _CurShape->setDraw(MOVE);
        update();
        return;
    } else {
        if(!_CurShape) return;
        _CurShape->setDraw(END);
        update();
    }
}

void DrawCanvas::mousePressEvent(QMouseEvent* e){
    //std::cout << _IsSelecting << std::endl;
    if(e->button() == Qt::LeftButton){
        mousePressEventLeft(e);
    } else if(e->button() == Qt::RightButton){
        mousePressEventRight(e);
    }
}

void DrawCanvas::mouseMoveEvent(QMouseEvent* e){    
    if(!_IsSelecting && !_IsDeselecting && !_RightClicked){
        _MousePos = e->pos();
        _CurShape->setDraw(MOVE);
        update();
        return;
    }
    if(_IsSelecting && !_RightClicked){
        QPoint delta = e->pos() - _MousePos;
        _MousePos = e->pos();
        _CurShape->move(delta.x(), delta.y());
        update();
        return;
    }
    _MousePos = e->pos();
    update();
}

void DrawCanvas::mouseReleaseEvent(QMouseEvent* e){
    if(e->button() == Qt::LeftButton){
        if(_IsDeselecting){
            _IsDeselecting = false;
        }
        else if(!_IsSelecting){
            _CurShape->setDraw(END);
        }
        update();
        return;
    }

    if(e->button() == Qt::RightButton){
        if(!_CurShape) return;
        _CurShape->setDraw(END);
        _RightClicked = false;
        update();
        return;
    }
}
