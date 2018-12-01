// Copyright (c) 2018 The Aegeus developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KEYREGISTRY_H
#define KEYREGISTRY_H

#include <iostream>
#include <sstream>
#include "leveldbwrapper.h"

class KeyRegistry;
extern KeyRegistry *keyregistry;

class KeyRegistry
{

private:
    //! database options used
    leveldb::Options options;

    //! options used when reading from the database
    leveldb::ReadOptions readoptions;

    //! options used when iterating over values of the database
    leveldb::ReadOptions iteroptions;

    //! options used when writing to the database
    leveldb::WriteOptions writeoptions;

    //! the database itself
    leveldb::DB* keyreg;


public:
    std::string dbFetch(std::string dbKey);
    bool dbPut(std::string dbKey, std::string dbValue);

    //! attempt to initialize the DB
    leveldb::Status openDB();

};

#endif
