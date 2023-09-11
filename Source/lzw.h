#pragma once
#include <iostream>
#include <string.h>
#include <map>
#include <vector>
using namespace std;

//map for lzw encode
map<string, int> CreateDictionary1();

//map for lzw decode
map<int, string> CreateDictionary2();

//lzw encode algorithm
vector<int> Encode(string str, map<string, int> &dict);

//lzw decode algorithm
string Decode(vector<int> code, map<int, string> &dict);
