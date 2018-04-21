//
// clicklabel.h
//
// Created by Adam Plowcha on 6/30/16.
// Extends Qlabel functionality to accept
// mouse events
//

#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>

class clickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit clickLabel(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);

    int x, y;

    QMouseEvent *e;

signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();

public slots:


};

#endif // CLICKLABEL_H
