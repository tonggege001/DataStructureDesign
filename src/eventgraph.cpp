#include "eventgraph.h"
#include<ostream>
#include<istream>

EventGraph::EventGraph()
{
    this->nodeCount = 0;
    this->adj = new int*[this->BASENUM];//行
    for(int i = 0;i<BASENUM;i++){
        this->adj[i] = new int[BASENUM];//列
    }
    //邻接矩阵初始化为0
    for(int i = 0;i<BASENUM;i++){
        for(int j = 0;j<BASENUM;j++){
            this->adj[i][j] = 0;
        }
    }
    this->size = BASENUM;
}

EventGraph::~EventGraph(){
    //释放空间
    for(int i = 0;i<this->size;i++){
        delete this->adj[i];
    }
    delete this->adj;
}

/**
 * @brief EventGraph::addNode 增加图节点
 * @param value 值
 * @return
 */
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

/**
 * @brief EventGraph::addAdj 增加图的边
 * @param tailValue 弧尾节点的值
 * @param headValue 弧头结点的值
 * @return
 */
bool EventGraph::addAdj(int tailValue,int headValue){
    //判断传值是否合法
    if(!this->VHmap.count(tailValue)) return false;
    if(!this->VHmap.count(headValue)) return false;
    int tail = VHmap.at(tailValue);
    int head = VHmap.at(headValue);
    //修改邻接矩阵的值
    this->adj[tail][head] = 1;
    return true;
}

/**
 * @brief EventGraph::hasNode 图是否有某节点
 * @param value 节点的值
 * @return
 */
bool EventGraph::hasNode(int value){
    return VHmap.count(value)==1;
}

/**
 * @brief EventGraph::getKeyByValue 通过值获得顶点序号
 * @param value 顶点的值
 * @return
 */
int EventGraph::getKeyByValue(int value){
    for(map<int,int>::iterator iter = this->VHmap.begin();iter!=this->VHmap.end();iter++){
        if(iter->second == value) return iter->first;
    }
    return -1;
}

/**
 * @brief EventGraph::getContent 获得图的类型
 * @return
 */
int EventGraph::getContent(){
    return this->GraphContent;
}
/**
 * @brief EventGraph::setContent 设置图的类型
 * @param type 类型
 * @return
 */
bool EventGraph::setContent(int type){
    this->GraphContent = type;
    return true;
}

std::ostream &operator<<(std::ostream & out , EventGraph & G){
    out<<G.size<<' '<<G.nodeCount<<' '<<G.GraphContent<<' ';
    for(map<int,int>::iterator iter = G.VHmap.begin();iter!=G.VHmap.end();iter++){
        out<<iter->first<<' '<<iter->second<<' ';
    }
    for(int i = 0;i<G.nodeCount;i++){
        for(int j = 0;j<G.nodeCount;j++){
            out<<G.adj[i][j]<<' ';
        }
    }
    return out;
}

std::istream &operator>>(std::istream & input , EventGraph & G){
    input >>G.size>>G.nodeCount>>G.GraphContent;
    G.adj = new int*[G.size];
    for(int i = 0;i<G.size;i++){
        G.adj[i] = new int[G.size];
        for(int j = 0;j<G.size;j++){
            G.adj[i][j] = 0;
        }
    }
    for(int i = 0;i<G.nodeCount;i++){
        int key;int value;
        input >> key>>value;
        G.VHmap[key] = value;
    }
    for(int i = 0;i<G.nodeCount;i++){
            for(int j = 0;j<G.nodeCount;j++){
                input >> G.adj[i][j];
        }
    }
    return input;
}
