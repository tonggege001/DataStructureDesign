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
    static const int INCREMENT = 10;
    map<int,int> VHmap;//映射表，《index,value》
    int **adj;//邻接矩阵
    int nodeCount;//顶点数

    EventGraph();
    ~EventGraph();
    bool addNode(int value);
    bool addAdj(int tailValue,int headValue);

    int getContent();//获取关联图的类型
    bool setContent(int type);//设置关联图类型
    bool hasNode(int value);
    int getKeyByValue(int value);
    //int getValue(int HashCode);
    //int getHash(int Value);

    friend std::ostream &operator<<(std::ostream & , EventGraph &);
    friend std::istream &operator>>(std::istream & , EventGraph &);

};

#endif // EVENTGRAPH_H
