//
// clicklabel.h
//
// Created by Adam Plowcha on 6/30/16.
// Extends Qlabel functionality to accept
// mouse events
//

#include "clicklabel.h"

clickLabel::clickLabel(QWidget *parent) : QLabel(parent)
{

}

void clickLabel::mouseMoveEvent(QMouseEvent *ev)
{
    this->x = ev->x();
    this->y = ev->y();
    this->e = ev;
    emit Mouse_Pos();
}

void clickLabel::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_Pressed();
}

void clickLabel::leaveEvent(QEvent *)
{
    emit Mouse_Left();
}
