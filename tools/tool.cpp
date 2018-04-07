#include <cmath>
#include"tools/tool.h"

bool isPrime(int M){
    for(int i = 2;i<sqrt(M);i++){
        if(M%i==0) return false;
    }
    return true;
}
int MinPrime(int N){
    for(int i = N;i>1;i--){
        if(isPrime(i)) return i;
    }
    return 1;
}
/**
 * @brief Value2Hash 将整数映射到哈希表
 * @param prime 素数
 * @param max 最大值
 * @param value 数值
 * @param array 数组基地址
 * @return 哈希表
 */
int Value2Hash(int prime,int max,int value,int * array){
    while(value<0) value+=prime;//让值为正数
    value = value%prime;//映射到0-prime-1
    //寻找空位
    while(array[value]!=-1){
        value++;
        value%=prime;
    }
    return value;
}
/**
 * @brief similarLog 获得相似的事件，并返回成vector
 * @param ManageLog
 * @param log
 * @return
 */
vector<EventLog *> similarLog(manageLog * ManageLog,EventLog log){
    vector<EventLog *> simlog;
    for(int i = 0;i<ManageLog->size;i++){
        EventLog * founded = ManageLog->logs[i];
        if(founded==NULL) continue;
        int count = 0;//相似因子,当相似因子的数大于5时，视为该LOG相似
        if(founded->getLogName().compare(log.getLogName())==0) count++;
        if(founded->getTaskType()==log.getTaskType()) count++;
        if(founded->getClassType()==log.getClassType()) count++;
        if(founded->getKeyWord()==log.getKeyWord()) count++;
        if(founded->getSourceID()==log.getSourceID()) count++;
        if(founded->getUser().compare(log.getUser())==0) count++;
        if(count >= 5) simlog.push_back(founded);
    }
    return simlog;
}
/**
 * @brief PriorNode 获得一个节点的所有前驱节点
 * @param ManageGraph 图管理器
 * @param log 节点事件
 * @return
 */
vector<EventLog *> PriorNode(manageGraph * ManageGraph, manageLog * ManageLog, EventLog log){
    EventGraph * G = ManageGraph->findGraph(log.getID(),LOG::GraphType::CauseAndEffect);
    vector<EventLog *> vec;
    for(int i = 0;i<G->nodeCount;i++){
        if(G->adj[i][G->VHmap[log.getID()]]==1){//邻接矩阵的值为1时，保存相应的节点
            int id = G->getKeyByValue(i);//反向获得ID
            vec.push_back(ManageLog->getLog(id));
        }
    }
    return vec;
}
/**
 * @brief NextNode 获得一个节点的所有后继节点
 * @param ManageGraph
 * @param ManageLog
 * @param log
 * @return
 */
vector<EventLog *> NextNode(manageGraph * ManageGraph, manageLog * ManageLog, EventLog log){
    EventGraph * G = ManageGraph->findGraph(log.getID(),LOG::GraphType::CauseAndEffect);
    vector<EventLog *> vec;
    for(int i = 0;i<G->nodeCount;i++){
        if(G->adj[G->VHmap[log.getID()]][i]==1){//邻接矩阵的值为1时，保存相应的节点
            int id = G->getKeyByValue(i);//反向获得ID
            vec.push_back(ManageLog->getLog(id));
        }
    }
    return vec;
}

/**
 * @brief ResultStr 根据查询结果获得最终评判字符串
 * @param ManageGraph
 * @param ManageLog
 * @param log
 * @return
 */
QString ResultStr(manageGraph * ManageGraph, manageLog * ManageLog, EventLog * log){

    //查询相似事件的结果
    vector <EventLog*> simlog = similarLog(ManageLog,*log);
    if(simlog.empty()){
        return "";
    }
    QString labelText;
    int num = (int)simlog.size();
    QString * strSet = new QString[num];
    labelText = "过往的事件总共有"+QString::number(num)+"种情况，我们做了如下预测：\n";
    for(int i = 0;i<num;i++){
        strSet[i] = "第"+QString::number(i+1)+"种情况：";
        EventLog * eventlog = simlog.back();
        strSet[i] = strSet[i]+"本次事件与ID为"+QString::number(eventlog->getID())+"的事件相似，所以我们推测";
        simlog.pop_back();
        //获得前驱和后记事件；然后给出结果
        vector<EventLog *> prior = PriorNode(ManageGraph, ManageLog, *eventlog);
        vector<EventLog *> nextN = NextNode(ManageGraph, ManageLog, *eventlog);
        QString pr,nx;
        for(int j = 0;j<(int)(prior.size());j++){
            EventLog * log2 = prior.back();prior.pop_back();
            pr = pr+" “"+ QString::fromStdString(log2->getDescription()) +"”";
        }
        for(int j = 0;j<(int)(nextN.size());j++){
            EventLog * log3 = nextN.back();nextN.pop_back();
            nx = nx+" “"+ QString::fromStdString(log3->getDescription()) +"”";
        }
        if(pr.length()==0){
            strSet[i] = strSet[i]+"本次事件可能是源头事件,";
        }
        else{
            strSet[i] = strSet[i] + "本次事件可能是"+pr+"导致的，";
        }
        if(nx.length()==0){
            strSet[i] = strSet[i] +"本次事件是汇点事件。\n";
        }
        else{
            strSet[i] = strSet[i] + "随后可能会发生"+nx+"等事件。\n";
        }
    }
    for(int i = 0;i<num;i++){
        labelText = labelText+strSet[i];
    }
    delete []strSet;
    return labelText;

}












