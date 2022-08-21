#ifndef _TABLE_H
#define _TABLE_H

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

class Table{
public:
    Table(){}
    Table(string _name,string _path):tb_name(_name),tb_path(_path){}
public:
    bool insert(vector<string>& values);
    bool select(vector<string>& results);
    bool select(string where_sql,vector<string>& results);
    bool update(string field,string value);
    bool update(string all);
public:
    const vector<string>& get_fields();
    const vector<string>& get_types();
    const string& get_tb_name();
    const string& get_tb_path();

    void set_fields(vector<string>& _fields);
    void set_types(vector<string>& _types);
    void set_tb_name(string& _name);
    void set_tb_path(string& _path);
private:
    vector<string> fields;
    vector<string> types;
    vector<int> sizes;
private:
    string tb_name;
    string tb_path;
};

#endif
