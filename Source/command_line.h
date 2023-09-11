#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

//output info for lzw encode
void OutputInfo1(char** argv, int in_size, int out_size, map<string, int> dict);

//output info for lzw decode
void OutputInfo2(char** argv, int in_size, int out_size, map<int, string> dict);

//command process for encoding
void EncodeLZW(char** argv);

//command process for decoding
void DecodeLZW(char** argv);

//command process
void Command(int argc, char** argv);
