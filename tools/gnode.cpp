#include "gnode.h"

GNode::GNode(QString ID, QString text, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    this->text = text;
    this->ID = ID;
}
