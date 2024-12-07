#include "json/json.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <windows.h>

using namespace chen::json;
using namespace std;
std::string UTF8ToGB(const char* str)
{
    std::string result;
    WCHAR *strSrc;
    LPSTR szRes;
 
    //获得临时变量的大小
    int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    strSrc = new WCHAR[i + 1];
    MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);
 
    //获得临时变量的大小
    i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
    szRes = new CHAR[i + 1];
    WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);
 
    result = szRes;
    delete[]strSrc;
    delete[]szRes;
 
    return result;
}

int main() {
  // std::cout << "hello json" << std::endl;
  // Json j1;
  // Json v2 = true;
  // Json v3 = 123;
  // Json v4 = 1.5;
  // Json v5 = "hello world";

  // Json arr;
  // // size_t a = 0;
  // arr[0] = true;
  // arr[1] = 1254;
  // arr[8] = "at 9";
  // arr.append(3.1415926);
  // arr.append("hello");

  // Json j = 0;
  // Json j2;
  // j2[std::string("hahah")] = "map";

  // arr.append(j2);
  // std::cout<<arr.str()<<std::endl;

  // for(auto it = arr.begin<std::vector<Json>>(); it !=
  // arr.end<std::vector<Json>>(); ++it){
  //   std::cout<<it->str()<<std::endl;
  // }
  // // arr.clear();

  // // Json obj;
  // std::cout<<j2.find("hahah")->first<<"
  // "<<j2.find("hahah")->second.str()<<std::endl;

  // arr.remove(0);
  // std::cout<<arr.str()<<std::endl;
  // double kkk = 1685929848241;
  try {
    // ifstream fin("../../list.json"); //没有二进制读取
    ifstream fin("../../list.json", std::ios::in | std::ios::binary);
    // ifstream fin("../../main.json", std::ios::in | std::ios::binary);

    if (fin.good()) {
      throw logic_error("can't open file");
    }
    stringstream ss;
    ss << fin.rdbuf();
    const string &data = UTF8ToGB(ss.str().c_str());

    Json json;
    json.parse(data);
    std::cout << json.str() << std::endl;

    // const string &name = json["name"];
    // int type = json["age"];
    // const string &area = json["area"][0];
    json.clear();
  } catch (std::exception &e) {
    std::cout << "catch exception: " << e.what() << std::endl;
  }
  


  return 0;
}