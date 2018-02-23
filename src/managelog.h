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
    static const int INIT_SIZE = 100;
    static const int INCREMENT = 50;
    int logNumber;
    int size;
    int prime;
    EventLog **logs;

    manageLog();
    ~manageLog();

    bool AddLog(EventLog *e);
    EventLog * getLog(int id);

    bool DeleteLog(int eventID);
    bool DeleteLog(string logName);
    bool DeleteLogbySourceID(int sourceID);
    bool DeleteLogbyRecordID(int eventRecordID);

    vector<int> * searchByID(int index);
    vector<int> * searchByTime(time_t time);
    vector<int> * searchByTime(time_t low,time_t high);
    vector<int> * searchByUser(string User);
    vector<int> * searchByRecordID(int id);
    vector<int> * searchByTaskType(int task);

    bool modifyLog(int eventId,string logName,int sourceID,time_t occurTime,
                              int taskType,int classType,string User,
                                        int eventRecordID,int keyWord,string description);

    bool LoadData();
    bool SaveData();
};

#endif // MANAGELOG_H
