#ifndef _PARSER_H_
#define _PARSER_H_

#include <cstddef>
#include <sstream>
#include <string>


#include "json.h"

namespace chen {
namespace json {

class Parser {
public:
  Parser();
  ~Parser();

  void load(const std::string& str);
  Json parse();


  private:
  void skip_blank();

  char get_next_token();

  Json parse_null();
  Json parse_bool();
  Json parse_number();
  Json parse_string();
  Json parse_array();
  Json parse_object();

private:
  std::string m_str;
  size_t m_idx;
};

} // namespace json

} // namespace chen

#endif // !_PARSER_H_