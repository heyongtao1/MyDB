#ifndef _CMDTYPE_H
#define _CMDTYPE_H

#include <iostream>
#include <string>
using namespace std;

//数据库操作指令
enum class Cmdtype{
    CREATE,
    OPEN,
    CLOSE,
    DROP,
  
    create_database,
    open_database,
    close_database,
    drop_database,
  
    create_table,
    open_table,
    close_table,
    drop_table,

    select_data,
    delete_data,
    update_data,
    insert_data,

    sql_help,
    sql_error,
    exit_sys
};

//枚举类解析器
class EnumParser{
public:
	static string type_parser(const Cmdtype& type)
	{
		switch(type)
		{
			case Cmdtype::CREATE: return "create";
			case Cmdtype::OPEN: return "open";
			case Cmdtype::CLOSE: return "close";
			case Cmdtype::DROP: return "drop";
			
			case Cmdtype::create_database: return "create database";
			case Cmdtype::open_database: return "open database";
			case Cmdtype::close_database: return "close database";
			case Cmdtype::drop_database: return "drop database";
			
			case Cmdtype::create_table: return "create table";
			case Cmdtype::open_table: return "open table";
			case Cmdtype::close_table: return "close table";
			case Cmdtype::drop_table: return "drop table";
			
			case Cmdtype::select_data: return "select";
			case Cmdtype::delete_data: return "delete";
			case Cmdtype::update_data: return "update";
			case Cmdtype::insert_data: return "insert";
			
            case Cmdtype::sql_help: return "help";
			case Cmdtype::sql_error: return "sql_error";
			case Cmdtype::exit_sys: return "exit";
		}
	}
};

#endif

