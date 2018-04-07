#ifndef EVENTGRAPH_H
#define EVENTGRAPH_H
#include<map>

using std::map;
namespace LOG {
class EventGraph;
}


class EventGraph
{
private:
    int GraphContent;
    int size;//邻接表大小


public:
    static const int BASENUM = 10;
    static const int INCREMENT = 5;
    map<int,int> VHmap;//映射表，《index,value》
    int **adj;//邻接矩阵
    int nodeCount;//顶点数

    EventGraph();
    ~EventGraph();
    bool addNode(int value); //增加节点
    bool addAdj(int tailValue,int headValue);//增加边

    int getContent();//获取关联图的类型
    bool setContent(int type);//设置关联图类型
    bool hasNode(int value);//是否存在点
    int getKeyByValue(int value);//通过key获得Value
    //int getValue(int HashCode);
    //int getHash(int Value);

    friend std::ostream &operator<<(std::ostream & , EventGraph &);
    friend std::istream &operator>>(std::istream & , EventGraph &);

};

#endif // EVENTGRAPH_H
