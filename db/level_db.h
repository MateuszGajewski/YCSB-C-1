#ifndef YCSB_C_LEVELDB_H
#define YCSB_C_LEVELDB_H

#include "core/db.h"
#include <leveldb/db.h>
#include <vector>
#include <string>
using namespace std;
namespace ycsbc
{

class Level : public DB
{
    leveldb::DB *db;
    int serializator = 0;


public:
	
    Level(const std::string&);
    ~Level();

    int Read(const std::string&, const std::string&, const std::vector<std::string>*, std::vector<KVPair>&);

    int Scan(const std::string&, const std::string&, int, const std::vector<std::string>*,std::vector<std::vector<KVPair>>&);

    int Update(const std::string&, const std::string&, std::vector<KVPair>&);

    int Insert(const std::string&, const std::string&, std::vector<KVPair>&);

    int Delete(const std::string&, const std::string&);

private:
std::string serialize(std::vector<DB::KVPair> &pairs, unsigned int *count);
void deserialize(vector<DB::KVPair> &result,  const char* s, int total_count);
std::string encode_key_table_(const std::string&, const std::string&);
void parse_response(vector<DB::KVPair> &result, const std::vector<std::string> *fields, vector<DB::KVPair> &result_record);
};


}

#endif

