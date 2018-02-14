#ifndef MANAGE_H
#define MANAGE_H
#include"managelog.h"

namespace LOG {
    class manage;
}
class manage
{
public:
    LOG::manageLog * ManageLog;


    manage();
    ~manage();
};


#endif // MANAGE_H
