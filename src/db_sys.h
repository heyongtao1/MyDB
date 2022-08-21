#ifndef _DB_SYS_H
#define _DB_SYS_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "cmdtype.h"
#include "single.h"
#include "cmdparser.h"
#include "table.h"
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

//数据库存储路径
#define DB_DIR "./"

class DB{
public:
    DB():curr_db("") {}
private:
    bool create_database();
    bool open_database();
    bool close_database(const string& db_name);
    bool drop_database();

    bool create_table();
    bool open_table();
    bool close_table(const string& tb_name);
    bool drop_table();

    bool select_tb();
    bool insert_tb();
    bool update_tb();
    bool delete_tb();

	//查找表的存储在tables的下标位置
    int tablePos(const string& tb_name);

    bool show_all_database();
    bool show_all_table();

    //help
    bool help();
public:
    void start();
private:
    vector<Table> tables;
private:
	//当前操作的数据库
    string curr_db;
	//当前操作的表
    string curr_tb;
};

#endif
