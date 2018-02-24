#include <cmath>
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

vector<EventLog *> PriorNode(manageGraph * ManageGraph,EventLog log){
    EventGraph * G = ManageGraph->findGraph(log.getID(),LOG::GraphType::CauseAndEffect);

}

















