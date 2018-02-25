#include "managegraph.h"
#include<QGraphicsScene>
#include<fstream>
manageGraph::manageGraph(manageLog * Manage)
{
    this->size = this->BASE;
    this->Graph = new EventGraph*[this->size];
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

void SubCreate(manageLog * ManageLog, EventGraph & Graph,int index);//使用者相同
void ObjCreate(manageLog * ManageLog, EventGraph & Graph,int index);//来源相同相同
void AccumCreate(manageLog * ManageLog, EventGraph & Graph,int index);//任务类型相同
void CauseAndEffectCreate(manageLog * ManageLog, EventGraph & Graph,int index);//同一进程下的事件
EventGraph * manageGraph::generateGraph(int index, int Type){
    EventGraph * gra = new EventGraph();
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
 * @param ManageLog
 * @param Graph
 * @param index
 */
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

void ObjCreate(manageLog * ManageLog, EventGraph & Graph,int index){
    Graph.addNode(index);
    for(int i = 0;i<ManageLog->size;i++){
        if(ManageLog->logs[i]==NULL) continue;
        if(ManageLog->logs[i]->getID()==index) continue;
        int time1 = ManageLog->logs[i]->getTime();int time2 = ManageLog->logs[index]->getTime();
        if(ManageLog->logs[i]->getSourceID()==ManageLog->logs[index]->getSourceID()
                &&(time1-time2)*(time1-time2)<100){
            Graph.addNode(ManageLog->logs[i]->getID());
        }
    }
}
void AccumCreate(manageLog * ManageLog, EventGraph & Graph,int index){
    Graph.addNode(index);
    for(int i = 0;i<ManageLog->size;i++){
        if(ManageLog->logs[i]==NULL) continue;
        if(ManageLog->logs[i]->getID()==index) continue;
        int time1 = ManageLog->logs[i]->getTime();int time2 = ManageLog->logs[index]->getTime();
        if(ManageLog->logs[i]->getEventRecordID()==ManageLog->logs[index]->getEventRecordID()
              &&(time1-time2)*(time1-time2)<100 ){
            Graph.addNode(ManageLog->logs[i]->getID());
        }
    }
}
void CauseAndEffectCreate(manageLog * ManageLog, EventGraph & Graph,int index){
    Graph.addNode(index);
    vector<int> nodes;
    nodes.push_back(index);
    for(int i = 0;i<ManageLog->size;i++){
        if(ManageLog->logs[i]==NULL) continue;
        if(ManageLog->logs[i]->getID()==index) continue;
        //事件进程相同
        int time1 = ManageLog->logs[i]->getTime();int time2 = ManageLog->logs[index]->getTime();
        if(ManageLog->logs[i]->getEventRecordID()==ManageLog->logs[index]->getEventRecordID()&&
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
    //加边
    for(vector<int>::iterator iter_out = nodes.begin();iter_out!=nodes.end();iter_out++){
        for(vector<int>::iterator iter_in = nodes.begin();iter_in!=nodes.end();iter_in++){
            if(*iter_out==(*iter_in)) continue;
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
        if(this->Graph[i]->getContent()==type&&
                this->Graph[i]->hasNode(index)){
            G = this->Graph[i];
            break;
        }
    }
    return G;
}

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

bool manageGraph::LoadGraph(){
    std::ifstream infile("EventGraph");
    if(!infile.is_open()) return false;
    int total;
    infile >>total;
    EventGraph * G;

    for(int i = 0;i<total;i++){
        G = new EventGraph();
        infile >> *G;
        this->addGraph(G);
    }
    infile.close();
    return true;
}
bool manageGraph::SaveGraph(){
    std::ofstream outfile("EventGraph");
    outfile <<this->graphCount<<' ';
    for(int i = 0;i<this->graphCount;i++){
        if(this->Graph[i]!=NULL){
            outfile<< *Graph[i];
        }
    }
    return true;
}





















