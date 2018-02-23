#include "gnode.h"

GNode::GNode(int ID, QString text,QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    this->text = text;
    this->ID = ID;
}
