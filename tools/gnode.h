#ifndef GNODE_H
#define GNODE_H
#include<QGraphicsItem>
#include<QPainter>
#include<string>


class GNode : public QGraphicsItem
{
public:
    int ID;
    QString text;
    GNode(int ID, QString text, QGraphicsItem *parent = Q_NULLPTR);
    QRectF boundingRect() const{
        return QRectF(-75, -25, 150, 50);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
    {
        QColor Q(0,0,0,255);
        painter->setPen(Q);
        painter->drawRoundedRect(-75, -25, 150, 50, 5, 5);
        painter->drawText(-75, -25, 150, 20, Qt::AlignCenter, QString::number(this->ID));
        painter->drawText(-75,-10,150,30,Qt::AlignCenter,text);
    }

};
#endif
