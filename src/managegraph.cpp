#include "managegraph.h"
#include<QGraphicsScene>

manageGraph::manageGraph(manageLog * Manage)
{
    this->size = this->BASE;
    this->Graph = new EventGraph*[this->size];
    for(int i = 0;i<size;i++){
        this->Graph[i] = NULL;
    }
    this->graphCount = 0;
    this->ManageLog = Manage;
}

manageGraph::~manageGraph(){
    for(int i = 0;i<this->graphCount;i++){
        delete this->Graph[i];
    }
    delete Graph;
}

/**
 * @brief manageGraph::addGraph 增加图
 * @param g 图指针
 * @return 正确
 */
bool manageGraph::addGraph(EventGraph *g){
    if(this->graphCount<=this->size){
        EventGraph ** newgra = new EventGraph*[this->size+this->INCRE];
        for(int i = 0;i<graphCount;i++){
            newgra[i] = this->Graph[i];
        }
        delete this->Graph;
        this->Graph = newgra;
    }
    this->Graph[this->graphCount] = g;
    this->graphCount++;
    return true;
}

int manageGraph::GraphCount(){
    return this->graphCount;
}

/**
 * @brief manageGraph::hasGraph 是否存在图
 * @param index 节点的值
 * @param type 图的类型
 * @return
 */
bool manageGraph::hasGraph(int index, int type){
    for(int i = 0;i<this->graphCount;i++){
        if(this->Graph[i]==NULL) continue;
        if(this->Graph[i]->getContent()==type&&
                this->Graph[i]->hasNode(index)) return true;
    }
    return false;
}

void SubCreate(manageLog * ManageLog, EventGraph & Graph,int index);


EventGraph * manageGraph::generateGraph(int index, int Type){
    EventGraph * gra = new EventGraph();
    switch(Type){
    case LOG::GraphType::Subject:
        SubCreate(this->ManageLog,*gra,index);
        gra->setContent(LOG::GraphType::Subject);
        break;
    case LOG::GraphType::Object:
        gra->setContent(LOG::GraphType::Object);
        break;
    case LOG::GraphType::AccomEvent:
        gra->setContent(LOG::GraphType::AccomEvent);
        break;
    case LOG::GraphType::CauseAndEffect:
        gra->setContent(LOG::GraphType::CauseAndEffect);
        break;
    default:
        delete gra;
        return NULL;
    }
    return gra;
}


void SubCreate(manageLog * ManageLog, EventGraph & Graph,int index){
    Graph.addNode(index);
    for(int i = 0;i<ManageLog->size;i++){
        if(ManageLog->logs[i]==NULL) continue;
        if(ManageLog->logs[i]->getID()==index) continue;
        if(ManageLog->logs[i]->getUser().compare(ManageLog->logs[index]->getUser())==0){
            Graph.addNode(ManageLog->logs[i]->getID());
        }
    }
}

void manageGraph::deleteAllGraph(){
    for(int i = 0;i<this->GraphCount();i++){
        delete this->Graph[i];
        this->Graph[i] = NULL;
    }
}

/**
 * @brief manageGraph::findGraph 查找图
 * @param index 图的id
 * @param type 图的类型
 * @return 图的地址
 */
EventGraph * manageGraph::findGraph(int index, int type){
    EventGraph * G = NULL;
    for(int i = 0;i<this->graphCount;i++){
        if(this->Graph[i]==NULL) continue;
        if(this->Graph[i]->getContent()==type&&
                this->Graph[i]->hasNode(index)){
            G = this->Graph[i];
            break;
        }
    }
    return G;
}


void manageGraph::DrawGraph(QGraphicsScene * scene, EventGraph * G){
    int count = 0;int num = 0;
    int ypos = 300;
    for(map<int,int>::iterator i = G->VHmap.begin();i!= G->VHmap.end();i++,count++){
        GNode *gnode = new GNode((int)(i->first),QString::fromStdString(this->ManageLog->getLog(i->first)->getLogName()));
        num = num+(-1)*count*155;
        if(!(num<650&&num>-650)){
            ypos -=150;
            num = count;
        }
        gnode->setPos(num,ypos);

        scene->addItem(gnode);
    }
    /**
    switch(type){
    case LOG::GraphType::Subject:

    }

**/
    scene->update();
}





























