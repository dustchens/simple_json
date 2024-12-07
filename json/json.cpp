#include "json.h"
#include "parser.h"
#include <cstddef>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace chen::json;

Json::Json() : m_type(json_null) {}

Json::Json(bool value) : m_type(json_bool) { m_value.m_bool = value; }

Json::Json(int value) : m_type(json_int) { m_value.m_int = value; }
Json::Json(size_t value) : m_type(json_long) { m_value.m_long = value; }

Json::Json(double value) : m_type(json_double) { m_value.m_double = value; }

Json::Json(const char *value) : m_type(json_string) {
  m_value.m_string = new std::string(value);
}

Json::Json(const std::string &value) : m_type(json_string) {
  m_value.m_string = new std::string(value);
}

Json::Json(Type type) : m_type(type) {
  switch (type) {

  case json_null:
    break;
  case json_bool:
    m_value.m_bool = false;
    break;
  case json_int:
    m_value.m_int = 0;
    break;
  case json_long:
  // 超长整数
    m_value.m_long = 0;
    break;
  case json_double:
    m_value.m_double = 0.0;
    break;
  case json_string:
    m_value.m_string = new std::string("");
    break;
  case json_array:
    m_value.m_array = new std::vector<Json>();
    break;
  case json_object:
    m_value.m_object = new std::map<std::string, Json>();
    break;
  default:
    break;
  }
}

// 非常烂的浅拷贝，必定内存泄漏
Json::Json(const Json &other) {
  m_type = other.m_type;
  switch (m_type) {
  case json_null:
    break;
  case json_bool:
    m_value.m_bool = other.m_value.m_bool;
    break;
  case json_int:
    m_value.m_int = other.m_value.m_int;
    break;
  case json_long:
  // 添加超长long
    m_value.m_long = other.m_value.m_long;
    break;
  case json_double:
    m_value.m_double = other.m_value.m_double;
    break;
  case json_string:
    m_value.m_string = other.m_value.m_string; // 暂定为浅拷贝 深拷贝性能损失大
    // m_value.m_string = new std::string(*other.m_value.m_string); //
    // 暂定为浅拷贝 深拷贝性能损失大
    break;
  case json_array:
    m_value.m_array = other.m_value.m_array;
    break;
  case json_object:
    m_value.m_object = other.m_value.m_object;
    break;
  default:
    break;
  }
}

Json &Json::operator=(const Json &other) {
  if (this == &other)
    return *this;

  clear();
  m_type = other.m_type;
  switch (m_type) {
  case json_null:
    break;
  case json_bool:
    m_value.m_bool = other.m_value.m_bool;
    break;
  case json_int:
    m_value.m_int = other.m_value.m_int;
    break;
  case json_long:
    m_value.m_long = other.m_value.m_long;
    break;
  case json_double:
    m_value.m_double = other.m_value.m_double;
    break;
  case json_string:
    m_value.m_string = other.m_value.m_string; // 暂定为浅拷贝 深拷贝性能损失大
    break;
  case json_array:
    m_value.m_array = other.m_value.m_array;
    break;
  case json_object:
    m_value.m_object = other.m_value.m_object;
    break;
  default:
    break;
  }
  return *this;
}

Json::~Json() {
  // switch (m_type) {
  // case json_null:
  //   break;
  // case json_bool:
  //   m_value.m_bool = false;
  //   break;
  // case json_int:
  //   m_value.m_int = 0;
  //   break;
  // case json_double:
  //   m_value.m_double = 0.0;
  //   break;
  // case json_string:
  //   // 临时变量other 析构导致内存泄漏
  //   // (m_value.m_array)->push_back(other);
  //   if (m_value.m_string != nullptr)
  //     delete m_value.m_string;
  //   break;
  // case json_array:
  //   if (m_value.m_array != nullptr)
  //     delete m_value.m_array;
  //   break;
  // case json_object:
  //   if (m_value.m_array != nullptr)
  //     delete m_value.m_object;
  //   m_value.m_object = nullptr;
  //   break;
  // }
  //   clear();
}

void Json::clear() {
  switch (m_type) {
  case json_null:
    break;
  case json_bool:
    m_value.m_bool = false;
    break;
  case json_int:
    m_value.m_int = 0;
    break;
  case json_long:
    m_value.m_long = 0;
    break;
  case json_double:
    m_value.m_double = 0.0;
    break;
  case json_string:
    if (m_value.m_string != nullptr) {
      delete m_value.m_string;
      // (*m_value.m_string).~basic_string();
      m_value.m_string = nullptr; // 防止悬空
    }

    break;
  case json_array:
    if (m_value.m_array != nullptr) {
      for (auto &obj : *m_value.m_array) {
        obj.clear();
        // obj = nullptr;
      }
      delete m_value.m_array;
      m_value.m_array = nullptr;
    }

    break;
  case json_object:
    if (m_value.m_object != nullptr) {
      for (auto &obj : *m_value.m_object) {
        obj.second.clear();
        // obj.second = nullptr;
      }
      delete m_value.m_object;
      m_value.m_object = nullptr;
    }

    break;
  }
  m_type = json_null;
}

Json::operator bool() {
  if (m_type != json_bool) {
    throw std::logic_error("type error, not bool value");
  }
  return m_value.m_bool;
}

Json::operator int() {
  if (m_type != Json::json_int) {
    throw std::logic_error("type error, not int value");
  }
  return m_value.m_int;
}

Json::operator double() {
  if (m_type != json_double) {
    throw std::logic_error("type error, not double value");
  }
  return m_value.m_double;
}

Json::operator std::string() {
  if (m_type != json_string) {
    throw std::logic_error("type error, not string value");
  }
  return *m_value.m_string;
}

Json &Json::operator[](int index) {
  if (m_type != json_array) {
    m_type = json_array;
    m_value.m_array = new std::vector<Json>();
  }

  if (index < 0) {
    throw std::logic_error("array index < 0 error");
  }
  // if(index >= m_value.m_array->size()) {
  //   if(m_value.m_array->size() == 0)
  //     m_value.m_array->resize(1, Json());
  //   else
  //     m_value.m_array->resize(index * 2, Json());
  // }
  if (index >= m_value.m_array->size()) {
    m_value.m_array->resize(index + 1);
  }
  return m_value.m_array->at(index);
}
void Json::append(const Json &other) {
  if (m_type != json_array) {
    m_type = json_array;
    m_value.m_array = new std::vector<Json>();
  }
  // m_value.m_array->emplace_back(other);
  (m_value.m_array)->push_back(other);
}

std::string Json::str() const {
  std::stringstream str_stream;

  switch (m_type) {

  case json_null:
    str_stream << "null";
    break;
  case json_bool:
    str_stream << (m_value.m_bool ? "true" : "false");
    break;
  case json_int:
    str_stream << m_value.m_int;
    break;
  case json_long:
    str_stream << m_value.m_long;
    break;
  case json_double:
    str_stream << m_value.m_double;
    break;
  case json_string:
    str_stream << '\"' << *m_value.m_string << '\"';
    break;
  case json_array:
    str_stream << '[';
    [&str_stream](const std::vector<Json> arr) {
      for (auto it = arr.begin(); it != arr.end(); it++) {
        str_stream << it->str();
        if (it + 1 != arr.end())
          str_stream << ',';
      }
    }(*m_value.m_array);
    str_stream << ']';
    break;
  case json_object:
    str_stream << '{';
    [&str_stream](const std::map<std::string, Json> json_map) {
      for (auto it = json_map.begin(); it != json_map.end(); it++) {
        if (it != json_map.begin())
          str_stream << ',';
        str_stream << it->first;
        str_stream << ':';
        str_stream << it->second.str();
      }
    }(*m_value.m_object);
    str_stream << '}';
    break;
  default:
    break;
  }

  return str_stream.str();
}

Json &Json::operator[](const std::string &key) {
  if (m_type != json_object) {
    m_type = json_object;
    m_value.m_object = new std::map<std::string, Json>();
  }
  return (*m_value.m_object)[key];
}
Json &Json::operator[](const char *key) {
  if (key != nullptr)
    return (*m_value.m_object)[std::string(key)];
  else
    throw std::logic_error("null error");
}

bool Json::as_bool() const {
  if (m_type != json_bool) {
    throw std::logic_error("can't change to bool");
  }
  return m_value.m_bool;
}

int Json::as_int() const {
  if (m_type != json_int) {
    throw std::logic_error("can't change to int");
  }
  return m_value.m_int;
}
double Json::as_double() const {
  if (m_type != json_double) {
    throw std::logic_error("can't change to double");
  }
  return m_value.m_double;
}
std::string &Json::as_string() const {
  if (m_type != json_string) {
    throw std::logic_error("can't change to string");
  }
  return *m_value.m_string;
}

bool Json::has(const char *key) {
  if (m_type != json_object) {
    throw std::logic_error("type is not a object");
  }
  return m_value.m_object->find(key) != m_value.m_object->end();
}

bool Json::has(const std::string &key) {
  if (m_type != json_object) {
    throw std::logic_error("type is not a object");
  }
  return m_value.m_object->find(key) != m_value.m_object->end();
}

std::map<std::string, Json>::iterator Json::find(const char *key) {
  if (m_type != json_object) {
    throw std::logic_error("type is not a object");
  }
  return m_value.m_object->find(key);
}

std::map<std::string, Json>::iterator Json::find(const std::string &key) {
  if (m_type != json_object) {
    throw std::logic_error("type is not a object");
  }
  return m_value.m_object->find(key);
}

void Json::remove(int index) {
  if (m_type != json_array) {
    throw std::logic_error("type error, not an array");
  }
  if (index < 0 || m_value.m_array->size() < 1 ||
      index >= m_value.m_array->size()) {
    throw std::logic_error("access out of bounds");
  }
  // 务必要释放内存
  m_value.m_array[index].clear();
  m_value.m_array->erase(m_value.m_array->begin() + index);
}

void Json::remove(const char *key) {
  if (m_type != json_object) {
    throw std::logic_error("type error, not a map");
  }
  // 释放内存 必须手动释放
  if (m_value.m_object->find(key) != m_value.m_object->end()) {
    m_value.m_object->find(key)->second.clear();
    m_value.m_object->erase(key);
  }
}

void Json::remove(const std::string &key) {
  if (m_type != json_object) {
    throw std::logic_error("type error, not a map");
  }
  if (m_value.m_object->find(key) != m_value.m_object->end()) {
    m_value.m_object->find(key)->second.clear();
    m_value.m_object->erase(key);
  }
}



void Json::parse(const std::string& str) {
  Parser parser;
  parser.load(str);
  *this = parser.parse();
}