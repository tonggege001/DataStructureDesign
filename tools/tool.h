#ifndef TOOL_H
#define TOOL_H

#endif // TOOL_H

#include<vector>
#include"src/eventlog.h"
#include"src/eventgraph.h"
#include"src/managelog.h"
#include"src/managegraph.h"

//是否是素数
bool isPrime(int M);

//N以内的最小素数
int MinPrime(int N);

//值转换成Hash
int Value2Hash(int prime,int max,int ID);
//相似的Log
vector<EventLog *> similarLog(manageLog * ManageLog,EventLog log);
//图的前面的节点
vector<EventLog *> PriorNode(manageGraph * ManageGraph, manageLog * ManageLog, EventLog log);
//图的后面的节点
vector<EventLog *> NextNode(manageGraph * ManageGraph, manageLog * ManageLog, EventLog log);
//结果字符串
QString ResultStr(manageGraph * ManageGraph, manageLog * ManageLog, EventLog * log);
