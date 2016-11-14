/* Copyright 2016 Pete Warden. All Rights Reserved.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 ==============================================================================*/

#ifndef INCLUDE_PICOPROTO_H
#define INCLUDE_PICOPROTO_H

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <iostream>

#define PP_LOG(X) PP_LOG_##X
#define PP_LOG_INFO std::cerr << __FILE__ << ":" << __LINE__ <<  " - INFO: "
#define PP_LOG_WARN std::cerr << __FILE__ << ":" << __LINE__ <<  " - WARN: "
#define PP_LOG_ERROR std::cerr << __FILE__ << ":" << __LINE__ <<  " - ERROR: "
#define PP_CHECK(X) if (!(X)) PP_LOG(ERROR) << "PP_CHECK(" << #X << ") failed. "

namespace picoproto {
  
  enum FieldType {
    FIELD_UNSET,
    FIELD_UINT32,
    FIELD_UINT64,
    FIELD_BYTES,
  };
  
  std::string FieldTypeDebugString(enum FieldType type);
  
  class Message;
  class Field {
  public:
    Field(FieldType type, bool owns_data);
    Field(const Field& other);
    ~Field();
    
    enum FieldType type;
    union {
      std::vector<uint32_t>* v_uint32;
      std::vector<uint64_t>* v_uint64;
      std::vector<std::pair<uint8_t*, size_t> >* v_bytes;
    } value;
    std::vector<Message*>* cached_messages;
    bool owns_data;
  };
  
  class Message {
  public:

    Message();
    Message(bool copy_arrays);
    Message(const Message& other);
    ~Message();
    
    bool ParseFromBytes(uint8_t* binary, size_t binary_size);
    
    std::map<int32_t, size_t> field_map;
    std::vector<Field> fields;
    bool copy_arrays;
    
    Field* AddField(int32_t number, enum FieldType type);
    Field* GetField(int32_t number);
    Field* GetFieldAndCheckType(int32_t number, enum FieldType type);
    
    int32_t GetInt32(int32_t number);
    int64_t GetInt64(int32_t number);
    uint32_t GetUInt32(int32_t number);
    uint64_t GetUInt64(int32_t number);
    int64_t GetInt(int32_t number);
    bool GetBool(int32_t number);
    float GetFloat(int32_t number);
    double GetDouble(int32_t number);
    std::pair<uint8_t*, size_t> GetBytes(int32_t number);
    std::string GetString(int32_t number);
    Message* GetMessage(int32_t number);

    std::vector<int32_t> GetInt32Array(int32_t number);
    std::vector<int64_t> GetInt64Array(int32_t number);
    std::vector<uint32_t> GetUInt32Array(int32_t number);
    std::vector<uint64_t> GetUInt64Array(int32_t number);
    std::vector<bool> GetBoolArray(int32_t number);
    std::vector<float> GetFloatArray(int32_t number);
    std::vector<double> GetDoubleArray(int32_t number);
    std::vector<std::pair<uint8_t*, size_t>> GetByteArray(int32_t number);
    std::vector<std::string> GetStringArray(int32_t number);
    std::vector<Message*> GetMessageArray(int32_t number);

  };
  
}  // namespace picoproto

#endif  // INCLUDE_PICOPROTO_H
