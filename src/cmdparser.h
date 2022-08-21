#ifndef _CMDPARSER_H
#define _CMDPARSER_H

#include <iostream>
#include "cmdtype.h"
#include "single.h"
using namespace std;

//Sql命令解析器
class CmdParser{
public:
    Cmdtype select_cmd_type(const string& input);
};

#endif
