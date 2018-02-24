#ifndef MANAGEGRAPH_H
#define MANAGEGRAPH_H
#include"src/managelog.h"
#include"src/eventgraph.h"
#include"tools/gnode.h"

namespace LOG {
    class manageGraph;
enum GraphType{Subject,Object,AccomEvent,CauseAndEffect};
}
class manageGraph
{
private:
    manageLog * ManageLog;//事件集操作
    int graphCount;
    int size;

public:
    static const int BASE = 10;
    static const int INCRE = 10;
    EventGraph ** Graph;//主体相关图
   // vector<GNode *> v;//用作关联图的删除

    manageGraph(manageLog * Manage);
    ~manageGraph();
    bool addGraph(EventGraph *g);//增加图
    EventGraph * generateGraph(int index,int Type);//从事件记录中生成图
    int GraphCount();
    bool hasGraph(int index, int type);//判断某张图是否存在
    void deleteAllGraph();//删除所有图
    EventGraph * findGraph(int index, int type);//查找图
    void DrawGraph(QGraphicsScene * scene, EventGraph *G, int type);
    void DrawGraphCE(QGraphicsScene * scene, EventGraph *G,int centralID);//画因果关系图
    bool LoadGraph();
    bool SaveGraph();

};

#endif // MANAGEGRAPH_H
