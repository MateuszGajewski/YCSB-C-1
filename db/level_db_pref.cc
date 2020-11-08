#include "db/level_db_pref.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

namespace ycsbc
{

string LevelPref::encode_key_table_(const string& table, const string& key, const std::string& fields){
string encode;
encode = table + key + fields;
return encode;
}

LevelPref::LevelPref(const std::string &path)
{
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, path, &db);
    if (!status.ok())
        std::cerr << status.ToString() << std::endl;

}
LevelPref::~LevelPref()
{
    delete db;
}


int LevelPref::Read(const std::string &table, const std::string &key, const std::vector<std::string> *fields, std::vector<KVPair> &result)
{
	string result_record;
	if (fields){
	for(const auto i : (*fields)){

	string key_table = encode_key_table_(table, key, i);
	db->Get(leveldb::ReadOptions(), key_table, &result_record);
	result.push_back(make_pair(i, result_record));
	}}
	else {
	for(const auto i : fields_set){

	string key_table = encode_key_table_(table, key, i);
	db->Get(leveldb::ReadOptions(), key_table, &result_record);
	result.push_back(make_pair(i, result_record));
	}
	}
	
	
	

    
    return kOK;
}

int LevelPref::Scan(const std::string &table, const std::string &key, int record_count, const std::vector<std::string> *fields,std::vector<std::vector<KVPair>> &result)
{

    return kOK;
}

int LevelPref::Update(const std::string &table, const std::string &key, std::vector<KVPair> &values)
{
for(int i = 0; i < values.size(); i++){
    unsigned int total_count = 0;
    string key_table = encode_key_table_(table, key, (values[i]).first);
    db->Put(leveldb::WriteOptions(), key_table, (values[i]).second);
    //fields_set.insert((values[i]).first);
    }

    return kOK;
}

int LevelPref::Insert(const std::string &table, const std::string &key, std::vector<KVPair> &values)
{

return Update(table, key, values);

}

int LevelPref::Delete(const std::string &table, const std::string &key)
{
   string test;
   for(auto i : fields_set){
   string key_table = encode_key_table_(table, key, i);

   	db->Delete(leveldb::WriteOptions(), key_table);}
    return kOK;
}







}
