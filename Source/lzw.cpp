#include "lzw.h"

map<string, int> CreateDictionary1()
{
    map<string, int> dict;
    string temp = "";
    for (int i = 0; i <= 255; i++)
    {
        temp = char(i);
        dict[temp] = i;
    }
    return dict;
}

map<int, string> CreateDictionary2()
{
    map <int, string> dict;
    for (int i = 0; i <= 255; i++)
    {
        string s = "";
        s += char(i);
        dict[i] = s;
    }
    return dict;
}

vector<int> Encode(string str, map<string, int> &dict)
{
    int dSize = 256;
    int i = 0;
    int len = str.length();

    vector<int> table;
    string symbol = "";

    while(i <= len){
        if(dict.find(symbol + str[i]) != dict.end()){
            symbol += str[i];    
        }else{
            table.push_back(dict[symbol]);
            dict[symbol + str[i]] = dSize++;
            symbol = str[i];
        }
        i++;
    }

    //Return encoded table
    return table;
}

string Decode(vector<int> code, map<int, string> &dict)
{
    int c = code[0], p;
    string P, C, str;
    int count = 256;
    string s = str = dict[c];

    for (int i = 0; i < code.size() - 1; i++)
    {
        P = "";
        C = "";
        p = c;
        c = code[i + 1];

        if (dict.find(c) == dict.end())
        {
            P = dict[p];
            C += dict[p][0];
            str += P + C;
        }
        else
        {
            str += dict[c];
            P = dict[p];
            C += dict[c][0];
        }
        dict[count] = P + C;
        count++;
    }

    //return decoded string
    return str;
}
