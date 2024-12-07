#ifndef _JSON_H_
#define _JSON_H_

#include <cstddef>
#include <map>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>


namespace chen {
namespace json {
class Json {
public:
  enum Type {
    json_null = 0,
    json_bool,
    json_int, /// 区分整数和浮点数
    json_long,
    json_double,
    json_string,
    json_array,
    json_object
  };

  Json();
  Json(bool value);
  Json(int value);
  Json(size_t value);
  Json(double value);
  Json(const char *value);
  Json(const std::string &value);

  Json(Type type); // 根据类型构造

  Json(const Json &other); // 拷贝构造
  Json &operator=(const Json &other);

  ~Json();
  // 释放内存
  void clear();

  // 基本类型转换
  operator bool();
  operator int();
  operator double();
  operator std::string();

  // 数组 [] append 添加   同时可以赋值给其他基本类型
  Json &operator[](int index); // 转换造成的bug
  // Json& operator[](size_t index);
  // size_t a = 0;
  // arr[a] = true;

  void append(const Json &other);

  // 数组转字符串
  std::string str() const;

  // explicit operator char(){}
  // 重载 operator[]，专门处理 nullptr_t 类型的空指针
  // void operator[](std::nullptr_t) = delete;  // 禁用 nullptr_t 作为键
  //  int& operator[](size_t) = delete;
  // map object 相关
  // 重载 operator[]，专门处理 int 类型的键
  // Json& operator[](int index) = delete;  // 禁用 int 作为键

  // 重载 operator[]，专门处理 nullptr_t 类型的空指针
  // Json& operator[](std::nullptr_t) = delete;
  Json &operator[](const std::string &key);
  Json &operator[](const char *key); // 二义性 char* 和 0二义

  // 使用 enable_if 特化特定模板 当然用c++17的技术更好
  // iterator
  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::vector<Json>>::value,
  //                         typename std::vector<Json>::iterator>::type
  // begin();
  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::vector<Json>>::value,
  //                         typename std::vector<Json>::iterator>::type
  // end();
  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::vector<Json>>::value,
  //                         typename std::vector<Json>::const_iterator>::type
  // cbegin() const;

  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::vector<Json>>::value,
  //                         typename std::vector<Json>::const_iterator>::type
  // cend() const;

  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::map<std::string,
  // Json>>::value,
  //                         typename std::map<std::string,
  //                         Json>::iterator>::type
  // begin();
  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::map<std::string,
  // Json>>::value,
  //                         typename std::map<std::string,
  //                         Json>::iterator>::type
  // end();
  // template <typename T>
  // typename std::enable_if<
  //     std::is_same<T, std::map<std::string, Json>>::value,
  //     typename std::map<std::string, Json>::const_iterator>::type
  // cbegin() const;

  // template <typename T>
  // typename std::enable_if<
  //     std::is_same<T, std::map<std::string, Json>>::value,
  //     typename std::map<std::string, Json>::const_iterator>::type
  // cend() const;
  // 模板在h内定义
  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::vector<Json>>::value,
  //                         typename std::vector<Json>::iterator>::type
  // begin() {
  //   if (m_type != json_array) {
  //     throw std::logic_error("not an array");
  //   }
  //   return m_value.m_array->begin();
  // }
  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::vector<Json>>::value,
  //                         typename std::vector<Json>::iterator>::type
  // end() {
  //   if (m_type != json_array) {
  //     throw std::logic_error("not an array");
  //   }
  //   return m_value.m_array->end();
  // }
  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::vector<Json>>::value,
  //                         typename std::vector<Json>::const_iterator>::type
  // cbegin() const {
  //   if (m_type != json_array) {
  //     throw std::logic_error("not an array");
  //   }
  //   return m_value.m_array->cbegin();
  // }
  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::vector<Json>>::value,
  //                         typename std::vector<Json>::const_iterator>::type
  // cend() const {
  //   if (m_type != json_array) {
  //     throw std::logic_error("not an array");
  //   }
  //   return m_value.m_array->cend();
  // }

  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::map<std::string, Json>>::value,
  //                         typename std::map<std::string, Json>::iterator>::type
  // begin() {
  //   if (m_type != json_object) {
  //     throw std::logic_error("not an object map");
  //   }
  //   return m_value.m_object->begin();
  // }
  // template <typename T>
  // typename std::enable_if<std::is_same<T, std::map<std::string, Json>>::value,
  //                         typename std::map<std::string, Json>::iterator>::type
  // end() {
  //   if (m_type != json_object) {
  //     throw std::logic_error("not an object map");
  //   }
  //   return m_value.m_object->end();
  // }
  // template <typename T>
  // typename std::enable_if<
  //     std::is_same<T, std::map<std::string, Json>>::value,
  //     typename std::map<std::string, Json>::const_iterator>::type
  // cbegin() const {
  //   if (m_type != json_object) {
  //     throw std::logic_error("not an object map");
  //   }
  //   return m_value.m_object->cbegin();
  // }
  // template <typename T>
  // typename std::enable_if<
  //     std::is_same<T, std::map<std::string, Json>>::value,
  //     typename std::map<std::string, Json>::const_iterator>::type
  // cend() const {
  //   if (m_type != json_object) {
  //     throw std::logic_error("not an object map");
  //   }
  //   return m_value.m_object->cend();
  // }
template <typename T>
typename  T::iterator begin() {
  if constexpr(std::is_same_v<T, std::vector<Json>>) {
    if(m_type != json_array) {
      throw std::logic_error("not an array");
    }
    return m_value.m_array->begin();
  } else if constexpr(std::is_same_v<T, std::map<std::string, Json>>) {
    if(m_type != json_array) {
      throw std::logic_error("not an object map");
    }
    return m_value.m_object->begin();
  }
}

template <typename T>
typename  T::iterator end() {
  if constexpr(std::is_same_v<T, std::vector<Json>>) {
    if(m_type != json_array) {
      throw std::logic_error("not an array");
    }
    return m_value.m_array->end();
  } else if constexpr(std::is_same_v<T, std::map<std::string, Json>>) {
    if(m_type != json_array) {
      throw std::logic_error("not an object map");
    }
    return m_value.m_object->end();
  }
}

template <typename T>
typename  T::const_iterator cbegin() const {
  if constexpr(std::is_same_v<T, std::vector<Json>>) {
    if(m_type != json_array) {
      throw std::logic_error("not an array");
    }
    return m_value.m_array->cbegin();
  } else if constexpr(std::is_same_v<T, std::map<std::string, Json>>) {
    if(m_type != json_array) {
      throw std::logic_error("not an object map");
    }
    return m_value.m_object->cbegin();
  }
}

template <typename T>
typename  T::const_iterator cend() const {
  if constexpr(std::is_same_v<T, std::vector<Json>>) {
    if(m_type != json_array) {
      throw std::logic_error("not an array");
    }
    return m_value.m_array->cend();
  } else if constexpr(std::is_same_v<T, std::map<std::string, Json>>) {
    if(m_type != json_array) {
      throw std::logic_error("not an object map");
    }
    return m_value.m_object->cend();
  }
}


Type get_type() {
  return m_type;
}

bool operator==(const Json& other);
bool operator!=(const Json& other);

bool is_null() const { return m_type == json_null;}
bool is_bool() const { return m_type == json_bool;}
bool is_int() const { return m_type == json_int;}
bool is_double() const { return m_type == json_double;}
bool is_string() const { return m_type == json_string;}
bool is_array() const { return m_type == json_array;}
bool is_object() const { return m_type == json_object;}

bool as_bool() const;
int as_int() const;
double as_double() const;
std::string& as_string() const;

// array移除
void remove(int index);

// map键值对
bool has(const char* key);
bool has(const std::string& key);
std::map<std::string, Json>::iterator find(const char* key);
std::map<std::string, Json>::iterator find(const std::string& key);

// map remove
void remove(const char* key);
void remove(const std::string& key);



    void parse(const std::string & str);

private:
  // 内存公用 最大的 大约 8 字节 double
  union Value {
    bool m_bool;
    int m_int;
    size_t m_long;    // "timestamp":1685929848241
    double m_double;
    std::string *m_string;
    std::vector<Json> *m_array;
    std::map<std::string, Json> *m_object;

    // ~Value(){}
  };

private:
  Type m_type;
  Value m_value;
};

} // namespace json
} // namespace chen

#endif // !_JSON_H_