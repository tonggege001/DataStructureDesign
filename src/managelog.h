#ifndef MANAGELOG_H
#define MANAGELOG_H
#include"eventlog.h"
#include"tools/linkedlist.h"
#include<vector>

using std::vector;

namespace LOG {
    class manageLog;
}
class manageLog
{   
public:
    static const int INIT_SIZE = 1000; //初始大小
    static const int INCREMENT = 0; //增量
    int logNumber;//事件数
    int size;//空间大小
    int prime;//哈希表的最大素数
    EventLog **logs;//基地址

    manageLog();
    ~manageLog();

    //增加LOG
    bool AddLog(EventLog *e);//增加LOG
    EventLog * getLog(int id);//获得LOG

    //删除Log
    bool DeleteLog(int eventID);
    bool DeleteLog(string logName);
    bool DeleteLogbySourceID(int sourceID);
    bool DeleteLogbyRecordID(int eventRecordID);

    //查找Log
    vector<int> * searchByID(int index);
    vector<int> * searchByTime(time_t time);
    vector<int> * searchByTime(time_t low,time_t high);
    vector<int> * searchByUser(string User);
    vector<int> * searchByRecordID(int id);
    vector<int> * searchByTaskType(int task);

    //修改Log
    bool modifyLog(int eventId,string logName,int sourceID,time_t occurTime,
                              int taskType,int classType,string User,
                                        int eventRecordID,int keyWord,string description);
    //存盘和读取
    bool LoadData();
    bool SaveData();
};

#endif // MANAGELOG_H
