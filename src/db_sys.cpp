#include "db_sys.h"

void DB::start()
{
    while(true)
    {
        cout << "my_db>> ";
        string cmd;
        cin >> cmd;
        Cmdtype type = Single<CmdParser>::getInstance().select_cmd_type(cmd);
        switch(type)
        {
        case Cmdtype::exit_sys:
            {
                cout << "Bye!"<<endl;
                return ;
            }
        case Cmdtype::sql_error:
            {
                cout << EnumParser::type_parser(Cmdtype::sql_error) << endl;
                break;
            }
        case Cmdtype::create_database:
            {
                if(create_database())
                    cout << "create database success!"<<endl;
                else cout << "create database fail!"<<endl;
                break;
            }
        case Cmdtype::create_table:
            {
                if(create_table())
                    cout << "create table success!" << endl;
                else cout << "create table fail!" << endl;
                break;
            }
        case Cmdtype::open_database:
            {
                if(open_database())
                    cout << "open database success!" << endl;
                else cout << "open database fail!" << endl;
                break;
            }
        case Cmdtype::open_table:
            {
                if(open_table())
                    cout << "open table success!" << endl;
                else cout << "open table fail!" << endl;
                break;
            }
        case Cmdtype::insert_data:
            {
                if(insert_tb())
                    cout << "insert into table values success!" << endl;
                else cout << "insert table fail!" << endl;
                break;
            }
        case Cmdtype::select_data:
            {
                if(!select_tb())
                    cout << "select table fail!" << endl;
                break;
            }
        case Cmdtype::update_data:
            {
                if(update_tb())
                    cout << "update table data success!" << endl;
                else cout << "update table data fail!" << endl;
                break;
            }
        case Cmdtype::sql_help:
            {
                help();
                break;
            }
        }
    }
}

bool DB::help()
{
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+ 1 create database db_name                 +" << endl;
    cout << "+ 2 create table tb_name(f1 t1,f2 t2,...)   +" << endl;
    cout << "+ 3 open database db_name                   +" << endl;
    cout << "+ 4 open table tb_name                      +" << endl;
    cout << "+ 5 insert into tb_name values(v1,v2,v3,...)+" << endl;
    cout << "+ 6 select * from tb_name                   +" << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    return true;
}

//create database db_name
//比如 create database my_db
bool DB::create_database()
{
    string db_name;
    cin >> db_name;
    db_name = DB_DIR + db_name;
    if(access(db_name.c_str(),0777) == -1)
    {
        mkdir(db_name.c_str(),0777);
        curr_db = db_name;
        return true;
    }
    return false;
}

//create table tb_name(f1 type1,f2 type2,...)
//比如 create table students(name string,age int,sex string)
bool DB::create_table()
{
    string tb_input;
    cin >> tb_input;
	//将tb_name(f1 type1,f2 type2,...)全部接收完毕，再进行处理
    while(true)
    {
        string temp;
        cin >> temp;
        tb_input += " " + temp;
        if(temp.back() == ')')
            break;
    }
    //tb_name(f1 type1,f2 type2,...)
    vector<string> fs,ts;

	//分割出表名
    int pos = tb_input.find('(');
    if(pos == string::npos) return false;
    string tb_name = tb_input.substr(0,pos);

    if(tb_input[pos] != '(' || tb_input.back() != ')') return false;
    //分割出 f1 type1,f2 type2,...
    string values = tb_input.substr(pos+1,tb_input.size()-pos-2);
    //write
    {
        while(true)
        {
            int _pos = values.find(',');
            //f1 type1
            string val_type = values.substr(0,_pos);
            values = values.substr(_pos+1);
            //value type
            int space_pos = val_type.find(' ');
            if(space_pos == string::npos) return false;
            string val = val_type.substr(0,space_pos);
            string tye = val_type.substr(space_pos+1);
            fs.push_back(val);
            ts.push_back(tye);
            if(_pos == string::npos)
                break;
            else _pos = values.find(',');
        }
    }

    //append to tables
    Table tb(tb_name,curr_db + "/" + tb_name + ".db");
    tb.set_fields(fs);
    tb.set_types(ts);
    if(curr_db.empty()) return false;
    tables.push_back(tb);

    curr_tb = curr_db + "/" + tb_name + ".db";

    if(access(curr_tb.c_str(),F_OK) != -1) return false;
    if(creat(tb.get_tb_path().c_str(),0777) < 0)
        return false;
    FILE* fd = fopen(curr_tb.c_str(),"w");
    //write fields to table
    {
        //fields numbers
        fprintf(fd,"%ld",fs.size());
        fprintf(fd,"%c",'\n');
        for(int i=0;i<fs.size();i++)
        {
            fprintf(fd,"%s %s",fs[i].c_str(),ts[i].c_str());
            fprintf(fd,"%c",'\n');
        }
    }
    fclose(fd);
    return true;
}

//open database db_name
bool DB::open_database()
{
    string db_name;
    cin >> db_name;
    db_name = DB_DIR + db_name;
    if(access(db_name.c_str(),F_OK) == -1)
        return false;
    curr_db = db_name;
    return true;
}

//open table tb_name
bool DB::open_table()
{
    string tb_name;
    cin >> tb_name;
    if(curr_db.empty()) return false;
    tb_name = curr_db + "/" + tb_name + ".db";
    if(access(tb_name.c_str(),F_OK) == -1)
        return false;
    curr_tb = tb_name;
    return true;
}

//find table pos
int DB::tablePos(const string& tb_name)
{
    if(tb_name.empty()) return false;

    for(int i=0;i<tables.size();i++)
        if(tables[i].get_tb_name() == tb_name)
            return i;

    string path = curr_db + "/" + tb_name + ".db";
    if(access(path.c_str(),F_OK) == -1)
        return -1;
    Table tb(tb_name,path);
    
    vector<string> fields , types;
    
    {
        FILE* fd = fopen(path.c_str(),"r");
        int field_num;
        fscanf(fd,"%d",&field_num);
        while(field_num--)
        {
            char field[20] = {0}, type[10] = {0};
            fscanf(fd,"%s %s",field,type);
            fields.push_back(string(field));
            types.push_back(string(type));
        }
        fclose(fd);
    }

    tb.set_fields(fields);
    tb.set_types(types);
    tables.push_back(tb);
    return tables.size()-1;
}

//insert into table_name values(v1,v2...)
bool DB::insert_tb()
{
    //table values(v1,v2,v3...)
    string table_name , table_values;
    cin >> table_name >> table_values;

    //values(v1,v2,v3...) ---> v1,v2,v3...
    int vpos = table_values.find('(');  
    if((table_values.substr(0,6)) != "values") return false;
    table_values = table_values.substr(vpos+1,table_values.size()-vpos-2); 
    //check table exist
    int tpos = tablePos(table_name);
    if(tpos == -1) return false;

    vector<string> val_arr;
    while(true)
    {
        int pos = table_values.find(',');
        if(pos == string::npos) break;
        string v = table_values.substr(0,pos);
        table_values = table_values.substr(pos+1);
        val_arr.push_back(v);
    }
    val_arr.push_back(table_values);
    return tables[tpos].insert(val_arr);
}
//select * from tb_name;
bool DB::select_tb()
{
    string tb_name;
    cin >> tb_name;
    int tb_pos = tablePos(tb_name);
    if(tb_pos == -1) return false;
    vector<string> results;
    return tables[tb_pos].select(results);
}
//update field=value from tb_name where f1=v1
bool DB::update_tb()
{
    string tb_name , where , field_value;
    cin >> tb_name >> where >> field_value;
    int tb_pos = tablePos(tb_name);
    if(tb_pos == -1) return false;
    
    if(field_value == "all")
    { 
        //return tables[tb_pos].update_tb(field_value);
    }

    int pos = field_value.find('=');
    if(pos == string::npos) return false;
    string field = field_value.substr(0,pos); 
    string value = field_value.substr(pos,field_value.size()-pos);
    
    //return tables[tb_pos].update_tb(field,value);
}
