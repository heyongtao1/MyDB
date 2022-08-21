#include <iostream>
#include "single.h"
#include "db_sys.h"

using namespace std;

int main()
{
	//启动数据库
    Single<DB>::getInstance().start();
    return 0;
}
