#ifndef YCSB_C_LEVELDB_PREF_H
#define YCSB_C_LEVELDB_PREF_H

#include "core/db.h"
#include <leveldb/db.h>
#include <vector>
#include <string>
#include <set>
using namespace std;
namespace ycsbc
{

class LevelPref : public DB
{
    leveldb::DB *db;
    int field_count;
    std::set < std::string > fields_set;
    int serializator = 0;


public:
	
    LevelPref(const std::string&);
    ~LevelPref();

    int Read(const std::string&, const std::string&, const std::vector<std::string>*, std::vector<KVPair>&);

    int Scan(const std::string&, const std::string&, int, const std::vector<std::string>*,std::vector<std::vector<KVPair>>&);

    int Update(const std::string&, const std::string&, std::vector<KVPair>&);

    int Insert(const std::string&, const std::string&, std::vector<KVPair>&);

    int Delete(const std::string&, const std::string&);

private:
std::string serialize(std::vector<DB::KVPair> &pairs, unsigned int *count);
void deserialize(vector<DB::KVPair> &result,  const char* s, int total_count);
std::string encode_key_table_(const std::string&, const std::string&, const std::string&);
void parse_response(vector<DB::KVPair> &result, const std::vector<std::string> *fields, vector<DB::KVPair> &result_record);
};


}

#endif

