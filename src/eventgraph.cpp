#include "eventgraph.h"


EventGraph::EventGraph()
{
    this->nodeCount = 0;
    this->adj = new int*[this->BASENUM];//行
    for(int i = 0;i<BASENUM;i++){
        this->adj[i] = new int[BASENUM];
    }
    for(int i = 0;i<BASENUM;i++){
        for(int j = 0;j<BASENUM;j++){
            this->adj[i][j] = 0;
        }
    }
    this->size = BASENUM;
}

EventGraph::~EventGraph(){
    for(int i = 0;i<this->size;i++){
        delete this->adj[i];
    }
    delete this->adj;
}

bool EventGraph::addNode(int value){
    if(this->VHmap.count(value)) return false;//节点已经存在
    if(this->nodeCount>=this->size){
        //产生新内存
        int ** newadj = new int*[this->size+this->INCREMENT];
        for(int i = 0;i<this->size+this->INCREMENT;i++){
            newadj[i] = new int[this->size+this->INCREMENT];
        }
        //新内存初始化
        for(int i = 0;i<this->size+this->INCREMENT;i++){
            for(int j = 0;j<this->size+this->INCREMENT;j++){
                newadj[i][j] = 0;
            }
        }
        //将原来的数据移到新内存中
        for(int i = 0;i<this->size;i++){
            for(int j = 0;j<this->size;j++){
                newadj[i][j] = this->adj[i][j];
            }
        }
        //释放原来的内存
        for(int i = 0;i<this->size;i++){
            delete this->adj[i];
        }
        delete this->adj;

        //修改属性
        this->adj = newadj;
        this->size = this->size+this->INCREMENT;
    }
    this->VHmap[value] = this->nodeCount++;
    return true;
}
bool EventGraph::addAdj(int tailValue,int headValue){
    if(!this->VHmap.count(tailValue)) return false;
    if(!this->VHmap.count(headValue)) return false;
    int tail = VHmap.at(tailValue);
    int head = VHmap.at(headValue);
    this->adj[tail][head] = 1;
    return true;
}

bool EventGraph::hasNode(int value){
    return VHmap.count(value)==1;
}





















int EventGraph::getContent(){
    return this->GraphContent;
}
bool EventGraph::setContent(int type){
    this->GraphContent = type;
    return true;
}
