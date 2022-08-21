#include "table.h"

bool Table::insert(vector<string>& values)
{
    if(values.size() != fields.size()) return false;
    if(values.empty()) return false;
    cout << tb_path << endl;
    FILE* fd = fopen(tb_path.c_str(),"a+");
    for(int i=0;i<types.size();i++)
    {
        if(types[i] == "int")
        {
            fprintf(fd,"%d",atoi(values[i].c_str()));
        }
        else if(types[i] == "float")
        {
            fprintf(fd,"%f",atof(values[i].c_str()));
        }
        else if(types[i] == "double")
        {
            fprintf(fd,"%f",atof(values[i].c_str()));
        }
        else if(types[i] == "string")
        {
            fprintf(fd,"%s",values[i].c_str());
        }
        if(i != types[i].size()-1) fprintf(fd,"%s"," ");
    }
    fprintf(fd,"%c",'\n');
    fclose(fd);
    return true;
}

bool Table::select(vector<string>& results)
{
    FILE* fd = fopen(tb_path.c_str(),"r");
    int field_num;
    fscanf(fd,"%d",&field_num);
    for(int i=0;i<field_num+1;i++)
    {
        char temp[1024] = {0};
        fgets(temp,sizeof(temp),fd);
    }
    //read all data
    while(!feof(fd))
    {
        char data[1024] = {0};
        fgets(data,sizeof(data),fd);
        string values = data;
        cout << values;
    }
    fclose(fd);
    return true;
}
/*
bool Table::update_tb(string all)
{
    //update table all data
    FILE* fd = fopen(tb_path,"r");
    //name age sex
    
}

bool Table::update_tb(string field,string value)
{

}
*/
void Table::set_fields(vector<string>& _fields)
{
    fields = _fields;
}

void Table::set_types(vector<string>& _types)
{
    types = _types;
}

const string& Table::get_tb_name()
{
    return tb_name;
}

const string& Table::get_tb_path()
{
    return tb_path;
}
