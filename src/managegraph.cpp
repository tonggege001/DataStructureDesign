#include "managegraph.h"
#include<QGraphicsScene>
#include<fstream>
#include<QMessageBox>

/**
 * @brief manageGraph::manageGraph 管理图类的构造器
 * @param Manage 管理LOG的地址
 */
manageGraph::manageGraph(manageLog * Manage)
{
    this->size = this->BASE;
    this->Graph = new EventGraph*[this->size];//分配空间
    for(int i = 0;i<size;i++){
        this->Graph[i] = NULL;
    }
    this->graphCount = 0;
    this->ManageLog = Manage;
    this->LoadGraph();
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
    if((this->graphCount+2)==this->size){//空间是否满，重新分配空间
        EventGraph ** newgra = new EventGraph*[this->size+this->INCRE];
        for(int i = 0;i<graphCount;i++){
            newgra[i] = this->Graph[i];
        }
        delete this->Graph; //释放原有空间
        this->Graph = newgra;
        this->size = this->size+this->INCRE;
    }
    //插入图
    this->Graph[this->graphCount] = g;
    this->graphCount++;//图的数量增加
    return true;
}
/**
 * @brief manageGraph::GraphCount
 *      获得图的数量
 * @return
 */
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
    //遍历图，寻找符合要求的图
    for(int i = 0;i<this->graphCount;i++){
        if(this->Graph[i]==NULL) continue;
        if(this->Graph[i]->getContent()==type&&
                this->Graph[i]->hasNode(index)) return true;
    }
    return false;
}

void SubCreate(manageLog * ManageLog, EventGraph & Graph,int index);//使用者相同
void ObjCreate(manageLog * ManageLog, EventGraph & Graph,int index);//来源相同相同
void AccumCreate(manageLog * ManageLog, EventGraph & Graph,int index);//任务类型相同
void CauseAndEffectCreate(manageLog * ManageLog, EventGraph & Graph,int index);//同一进程下的事件

/**
 * @brief manageGraph::generateGraph 根据序号和类型生成相应的图
 * @param index 序号
 * @param Type 类型
 * @return
 */
EventGraph * manageGraph::generateGraph(int index, int Type){
    EventGraph * gra = new EventGraph();//生成一个空图

    //根据要求生成相应的图
    switch(Type){
    case LOG::GraphType::Subject:
        SubCreate(this->ManageLog,*gra,index);
        gra->setContent(LOG::GraphType::Subject);
        break;
    case LOG::GraphType::Object:
        ObjCreate(this->ManageLog,*gra,index);
        gra->setContent(LOG::GraphType::Object);
        break;
    case LOG::GraphType::AccomEvent:
        AccumCreate(this->ManageLog,*gra,index);
        gra->setContent(LOG::GraphType::AccomEvent);
        break;
    case LOG::GraphType::CauseAndEffect:
        CauseAndEffectCreate(this->ManageLog, *gra,index);
        gra->setContent(LOG::GraphType::CauseAndEffect);
        break;
    default:
        delete gra;
        return NULL;
    }
    return gra;
}

/**
 * @brief SubCreate 生成主体相关图
 * @param ManageLog LOG管理器
 * @param Graph 图引用
 * @param index 序号值
 */
void SubCreate(manageLog * ManageLog, EventGraph & Graph,int index){
    Graph.addNode(index);//增加顶点
    for(int i = 0;i<ManageLog->size;i++){
        if(ManageLog->logs[i]==NULL) continue;
        if(ManageLog->logs[i]->getID()==index) continue;
        //若两个事件的使用者相同，并且名称不同，则该接待加入到图中
        if(ManageLog->logs[i]->getUser().compare(ManageLog->getLog(index)->getUser())==0
                &&ManageLog->logs[i]->getLogName().compare(ManageLog->getLog(index)->getLogName())!=0){
            Graph.addNode(ManageLog->logs[i]->getID());
        }
    }
}
/**
 * @brief ObjCreate 生成客体相关图
 * @param ManageLog LOG管理器
 * @param Graph 图引用
 * @param index 序号值
 */
void ObjCreate(manageLog * ManageLog, EventGraph & Graph,int index){
    Graph.addNode(index);
    for(int i = 0;i<ManageLog->size;i++){
        if(ManageLog->logs[i]==NULL) continue;
        if(ManageLog->logs[i]->getID()==index) continue;
        int time1 = ManageLog->logs[i]->getTime();int time2 = ManageLog->getLog(index)->getTime();
        if(ManageLog->logs[i]->getSourceID()==ManageLog->getLog(index)->getSourceID()
                &&(time1-time2)*(time1-time2)<100&&ManageLog->logs[i]->getLogName().compare(ManageLog->getLog(index)->getLogName())!=0){
            Graph.addNode(ManageLog->logs[i]->getID());
        }
    }
}
/**
 * @brief AccumCreate 生成伴随事件图
 * @param ManageLog LOG管理器
 * @param Graph 图引用
 * @param index 序号值
 */
void AccumCreate(manageLog * ManageLog, EventGraph & Graph,int index){
    Graph.addNode(index);
    for(int i = 0;i<ManageLog->size;i++){
        if(ManageLog->logs[i]==NULL) continue;
        if(ManageLog->logs[i]->getID()==index||ManageLog->getLog(i)->getLogName().compare(ManageLog->getLog(index)->getLogName())==0) continue;
        int time1 = ManageLog->logs[i]->getTime();int time2 = ManageLog->getLog(index)->getTime();
        //进程ID相同，且时间相差在10s以内，则增加该顶点
        if(ManageLog->logs[i]->getEventRecordID()==ManageLog->getLog(index)->getEventRecordID()
              &&(time1-time2)*(time1-time2)<100 ){
            Graph.addNode(ManageLog->logs[i]->getID());
        }
    }
}
/**
 * @brief CauseAndEffectCreate 生成因果相关图
 * @param ManageLog LOG管理器
 * @param Graph 图引用
 * @param index 序号值
 */
void CauseAndEffectCreate(manageLog * ManageLog, EventGraph & Graph,int index){
    Graph.addNode(index);
    vector<int> nodes;
    nodes.push_back(index);
    for(int i = 0;i<ManageLog->size;i++){
        if(ManageLog->logs[i]==NULL) continue;
        if(ManageLog->logs[i]->getID()==index) continue;
        //事件进程相同，且时间相差10s则增加定点
        int time1 = ManageLog->logs[i]->getTime();int time2 = ManageLog->getLog(index)->getTime();
        if(ManageLog->logs[i]->getEventRecordID()==ManageLog->getLog(index)->getEventRecordID()&&
                (time1-time2)*(time1-time2)<500){
            Graph.addNode(ManageLog->logs[i]->getID());
            nodes.push_back(ManageLog->logs[i]->getID());
            /*
            if(time1>time2){
                Graph.addAdj(ManageLog->logs[index]->getTime(),ManageLog->logs[i]->getID());
            }
            else{
                Graph.addAdj(ManageLog->logs[i]->getID(),ManageLog->logs[index]->getTime());
            }
            */
        }
    }
    //加边，根据时间点，分成本事件之前和本事件之后
    for(vector<int>::iterator iter_out = nodes.begin();iter_out!=nodes.end();iter_out++){
        for(vector<int>::iterator iter_in = nodes.begin();iter_in!=nodes.end();iter_in++){
            if(*iter_out==(*iter_in)) continue;
            //根据时间分类
            if(ManageLog->getLog(*iter_out)->getTime()>ManageLog->getLog(*iter_in)->getTime()){
                Graph.addAdj(*iter_in,*iter_out);
            }
            else{
                Graph.addAdj(*iter_out,*iter_in);
            }
        }
    }
}




/**
 * @brief manageGraph::deleteAllGraph
 * 删除所有的图
 */
void manageGraph::deleteAllGraph(){
    for(int i = 0;i<this->GraphCount();i++){
        delete this->Graph[i];
        this->Graph[i] = NULL;
    }
    this->graphCount = 0;
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
        //当满足类型相同，并且顶点相同，图找到
        if(this->Graph[i]->getContent()==type&&
                this->Graph[i]->hasNode(index)){
            G = this->Graph[i];
            break;
        }
    }
    return G;
}

/**
 * @brief manageGraph::DrawGraph 将图以二维图片表示出来（非核心逻辑代码，注释省略）
 * @param scene 场景
 * @param G 图
 * @param type
 */
void manageGraph::DrawGraph(QGraphicsScene * scene, EventGraph * G,int type){
    int count = 0;int num = -100;
    int ypos = 250;
    map<int,int>::iterator iter = G->VHmap.begin();
    QString titleTxt;
    GNode * title;
    switch (type){
    case LOG::GraphType::Subject:
        titleTxt = QString::fromStdString(this->ManageLog->getLog(iter->first)->getUser());
        title = new GNode("主体相关:",titleTxt);
        title->setPos(-155,-200);
        scene->addItem(title);
        break;

    case LOG::GraphType::Object:
        titleTxt = QString::number(this->ManageLog->getLog(iter->first)->getSourceID());
        title = new GNode("客体相关:",titleTxt);
        title->setPos(-155,-200);
        scene->addItem(title);
        break;
    case LOG::GraphType::AccomEvent:
        titleTxt = QString::number(this->ManageLog->getLog(iter->first)->getTaskType());
        title = new GNode("伴随事件:",titleTxt);
        title->setPos(-155,-200);
        scene->addItem(title);
        break;
    }
    if(type!=LOG::GraphType::CauseAndEffect){
        for(map<int,int>::iterator i = G->VHmap.begin();i!= G->VHmap.end();i++,count++){
            GNode *gnode = new GNode(QString::number(i->first),
                                     QString::fromStdString(this->ManageLog->getLog(i->first)->getLogName()));
            num = num+(-1)*count*155;
            if(!(num<650&&num>-650)){
                ypos -=150;
                num = count;
            }
            gnode->setPos(num,ypos);

            scene->addItem(gnode);
            scene->addLine(-155,-175,num,ypos-25);
        }
        scene->update();
    }
    else
        DrawGraphCE(scene,G,iter->first);

}
void propDraw(manageLog * ManageLog, QGraphicsScene * scene, EventGraph *G,vector<int> *review, int centralID,int X,int Y);
void backDraw(manageLog * ManageLog, QGraphicsScene * scene, EventGraph *G,vector<int> *review, int centralID,int X,int Y);
/**
 * @brief manageGraph::DrawGraphCE 将因果关系图画成二维图片，非核心逻辑代码，注释省略
 * @param scene
 * @param G
 * @param centralID
 */
void manageGraph::DrawGraphCE(QGraphicsScene * scene, EventGraph *G,int centralID){

    QGraphicsTextItem * txttile = new QGraphicsTextItem("本次事件的位置如下：");
    txttile->setPos(-75,-60);
    scene->addItem(txttile);


    GNode * gnode = new GNode(QString::number(centralID),QString::fromStdString(this->ManageLog->getLog(centralID)->getLogName()));
    gnode->setPos(0,0);
    scene->addItem(gnode);
    vector<int> *review  = new vector<int>();
    review->push_back(G->VHmap[centralID]);
    //向后传播
    int count = 0;
    for(int i = 0;i<G->nodeCount;i++){
        if(G->VHmap[centralID]==i) continue;
        if(G->adj[G->VHmap[centralID]][i]!=0){
            vector<int>::iterator it;

            it=find(review->begin(),review->end(),i); //查找是否存在
            if (it==review->end())
            {
                count++;
                review->push_back(G->VHmap[centralID]);
                //画边
                scene->addLine(75,0,0+count*160-75,0+pow((-1),count)*50*count);
                backDraw(this->ManageLog,scene,G,review,G->getKeyByValue(i), 0+count*160, 0+pow((-1),count)*50*count);
            }
        }
    }
    //向前传播
    count = 0;
    for(int i = 0;i<G->nodeCount;i++){
        if(G->VHmap[centralID]==i) continue;
        if(G->adj[i][G->VHmap[centralID]]!=0){
            vector<int>::iterator it;

            it=find(review->begin(),review->end(),i); //查找是否存在
            if (it==review->end())
            {
                count++;
                review->push_back(G->VHmap[centralID]);
                //画边
                scene->addLine(-75,0,0-count*160+75,0+pow((-1),count)*50*count);
                propDraw(this->ManageLog,scene,G,review,G->getKeyByValue(i), 0-count*160, 0+pow((-1),count)*50*count);
            }
        }
    }
    scene->update();
}

void backDraw(manageLog * ManageLog,QGraphicsScene * scene, EventGraph *G,vector<int> *review, int centralID,int X,int Y){
    GNode * gnode = new GNode(QString::number(centralID),QString::fromStdString(ManageLog->getLog(centralID)->getLogName()));
    gnode->setPos(X,Y);
  //  review->push_back(G->VHmap[centralID]);
    scene->addItem(gnode);
    int count = 0;
    for(int i = 0;i<G->nodeCount;i++){
        if(G->VHmap[centralID]==i) continue;
        if(G->adj[G->VHmap[centralID]][i]!=0){
            scene->addLine(X,Y,X+count*160, Y+pow((-1),count)*50*count);
            vector<int>::iterator it;
            it=find(review->begin(),review->end(),i); //查找是否存在
            if (it!=review->end())
            {
                count++;
                review->push_back(G->VHmap[centralID]);
                backDraw(ManageLog,scene,G,review,G->getKeyByValue(i), X+count*80, Y+pow((-1),count)*50*count);
            }
        }
    }
}

void propDraw(manageLog * ManageLog, QGraphicsScene * scene, EventGraph *G,vector<int> *review, int centralID,int X,int Y){
    GNode * gnode = new GNode(QString::number(centralID),QString::fromStdString(ManageLog->getLog(centralID)->getLogName()));
    gnode->setPos(X,Y);
  //  review->push_back(G->VHmap[centralID]);
    scene->addItem(gnode);
    int count = 0;
    for(int i = 0;i<G->nodeCount;i++){
        if(G->VHmap[centralID]==i) continue;
        if(G->adj[i][G->VHmap[centralID]]!=0){
          //  scene->addLine(X,Y,X-count*160, Y-pow((-1),count)*50*count);
            vector<int>::iterator it;
            it=find(review->begin(),review->end(),i); //查找是否存在
            if (it!=review->end())
            {
                count++;
                review->push_back(G->VHmap[centralID]);
                backDraw(ManageLog,scene,G,review,G->getKeyByValue(i), X-count*80, Y-pow((-1),count)*50*count);
            }
        }
    }
}

/**
 * @brief manageGraph::LoadGraph 加载图
 * @return
 */
bool manageGraph::LoadGraph(){
    //打开文件
    std::ifstream infile("EventGraph");
    if(!infile.is_open()) return false;
    int total;
    infile >>total;
    EventGraph * G;
    //读取图数量，循环读取图的邻接矩阵信息
    for(int i = 0;i<total;i++){
        G = new EventGraph();
        infile >> *G; //（>>运算符已重载）
        this->addGraph(G);
    }
    infile.close();
    return true;
}

/**
 * @brief manageGraph::SaveGraph 保存图
 * @return
 */
bool manageGraph::SaveGraph(){
    std::ofstream outfile("EventGraph");//打开文件
    outfile <<this->graphCount<<' ';//输出图的数量
    //循环输出图的玲姐矩阵
    for(int i = 0;i<this->graphCount;i++){
        if(this->Graph[i]!=NULL){
            outfile<< *Graph[i];//（<<运算符已重载）
        }
    }
    return true;
}





















