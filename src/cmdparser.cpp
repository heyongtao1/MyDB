#include "cmdparser.h"

Cmdtype CmdParser::select_cmd_type(const string& input)
{
    string& cmd = const_cast<string&>(input);
    if(cmd == EnumParser::type_parser(Cmdtype::CREATE))
    {
		//type 可能是database 、table
        string type;
        cin >> type;
		//合并后，可能是create_database 、create_table
        type = cmd + " " + type;
        if(type == EnumParser::type_parser(Cmdtype::create_database))
        {
            return Cmdtype::create_database;
        }
        else if(type == EnumParser::type_parser(Cmdtype::create_table))
        {
            return Cmdtype::create_table;
        }
        else return Cmdtype::sql_error;
    }
    else if(cmd == EnumParser::type_parser(Cmdtype::OPEN))
    {
        string type;
        cin >> type;
		//open_database 、open_table
        type = cmd + " " + type;
        if(type == EnumParser::type_parser(Cmdtype::open_database))
        {
            return Cmdtype::open_database;
        }
        else if(type == EnumParser::type_parser(Cmdtype::open_table))
        {
            return Cmdtype::open_table;
        }
        else return Cmdtype::sql_error;
    }
    else if(cmd == EnumParser::type_parser(Cmdtype::insert_data))
    {
        //insert into from tb_name values(v1,v2...)
        string into;
        cin  >> into;
        if(into != "into") return Cmdtype::sql_error;
        return Cmdtype::insert_data;
    }
    else if(cmd == EnumParser::type_parser(Cmdtype::select_data))
    {
        //只支持 select * from tb_name
        string xin , from;
        cin >> xin >> from;
        if(xin != "*" || from != "from") return Cmdtype::sql_error;
        return Cmdtype::select_data;
    }
    else if(cmd == EnumParser::type_parser(Cmdtype::update_data))
    {
        //update field=v1 from tb_name where field=w
        string field_value , from;
        cin >> field_value >> from;
        if(field_value.find('=') == string::npos || from != "from") return Cmdtype::sql_error;
        return Cmdtype::update_data;
    }
    else if(cmd == EnumParser::type_parser(Cmdtype::sql_help))
    {
		//输入help指令，输出支持的sql语句格式
        return Cmdtype::sql_help;
    }
    else if(cmd == EnumParser::type_parser(Cmdtype::exit_sys))
        return Cmdtype::exit_sys;
    return Cmdtype::sql_error;
}
