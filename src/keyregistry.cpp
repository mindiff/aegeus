// Copyright (c) 2018 The Aegeus developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "keyregistry.h"
#include "main.h"
#include "leveldb/include/leveldb/db.h"
#include <sstream>
#include <iostream>
#include <string>

KeyRegistry* keyregistry = new KeyRegistry();

// Open/create the key registry DB
leveldb::Status KeyRegistry::openDB() {
  std::stringstream keyRegistryPath;
  keyRegistryPath << GetDataDir().string() << "/keyregistry";
  options.create_if_missing = true;
  options.compression = leveldb::kSnappyCompression;
  options.max_open_files = 64;

  if (leveldb::kMajorVersion > 1 || (leveldb::kMajorVersion == 1 && leveldb::kMinorVersion >= 16)) {
    options.paranoid_checks = true;
  }

  leveldb::Status open_status = leveldb::DB::Open(options, keyRegistryPath.str(), &keyreg);
  return open_status;
}

// Fetch data from the key registry DB
std::string KeyRegistry::dbFetch(std::string dbKey) {
  std::string dbValue;
  leveldb::Status get_status = keyreg->Get(readoptions,dbKey, &dbValue);

  if (false == get_status.ok()) {
    LogPrintf("Unable to fetch %s error: %s\n", dbKey, get_status.ToString());
    return "FETCHERROR";
  }

  return dbValue;
}

// Store data in the key registry DB
bool KeyRegistry::dbPut(std::string dbKey, std::string dbValue) {
  leveldb::Status put_status = keyreg->Put(writeoptions, dbKey, dbValue);

  if (false == put_status.ok()) {
    LogPrintf("Unable to put: %s for value: %s error: %s\n", dbValue, dbKey, put_status.ToString());
    return false;
  }

  return true;
}

