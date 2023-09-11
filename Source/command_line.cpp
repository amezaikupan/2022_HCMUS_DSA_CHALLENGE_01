#include "command_line.h"
#include "lzw.h"

using namespace std;

void OutputInfo1(char** argv, int in_size, int out_size, map<string, int> dict)
{
    //given command a value to define output
    map<string, int> info = { {"-i", 1}, {"-d", 2}, {"-ind", 3} };
    
    //information
    if (info[string(argv[4])] == 1 || info[string(argv[4])] == 3)
    {
        cout << "Input size: " << in_size << " bits" << endl;
        cout << "Output size: " << out_size << " bits" << endl;
        cout << "Space saved: " << (1 - (float)out_size / in_size) * 100 << "%" << endl;
    }

    //dictionary
    if (info[string(argv[4])] == 2 || info[string(argv[4])] == 3)
    {
        cout << "LZW dictionary: " << endl;
        for (map<string, int>::iterator i = dict.begin(); i != dict.end(); i++)
        {
            if (i->second > 255)
                cout << i->first << ": " << i->second << endl;
        }
    }
    if (info[string(argv[4])] == 0)
        cout << "ERROR Output Info!" << endl;
}

void OutputInfo2(char** argv, int in_size, int out_size, map<int, string> dict)
{
    //given command a value to define output
    map<string, int> info = { {"-i", 1}, {"-d", 2}, {"-ind", 3} };

    //information
    if (info[string(argv[4])] == 1 || info[string(argv[4])] == 3)
    {
        cout << "Input size: " << in_size << " bits" << endl;
        cout << "Output size: " << out_size << " bits" << endl;
        cout << "Space saved: " << (1 - (float)out_size / in_size) * 100 << "%" << endl;
    }

    //dictionary
    if (info[string(argv[4])] == 2 || info[string(argv[4])] == 3)
    {
        cout << "LZW dictionary: " << endl;
        for (map<int, string>::iterator i = dict.begin(); i != dict.end(); i++)
        {
            if (i->first > 255)
                cout << i->first << ": " << i->second << endl;
        }
    }
    if (info[string(argv[4])] == 0)
        cout << "ERROR Output Info!" << endl;
}

void EncodeLZW(char** argv)
{
    string str;
    map<string, int> dict;
    vector<int> B;

    if (string(argv[2]).find(".txt") == -1)
    {
        cout << "ERROR: Input file must be .txt" << endl;
        return;
    }

    //get data from a file
    ifstream fin;
    fin.open(string(argv[2]));
    if (fin.is_open())
    {
        getline(fin, str);
        fin.close();
    }
    else 
    {
        cout << "ERROR File Open!" << endl;
        return;
    }
    dict = CreateDictionary1();
    //Encode a given string, return a map and a vector binary
    B = Encode(str, dict);

    OutputInfo1(argv, 8 * str.size(), 10 * B.size(), dict);

    //write output to a file
    ofstream fout;
    fout.open(string(argv[3]));
    for (int i = 0; i < B.size(); i++)
    {
        fout << B[i];
        if (i != B.size() - 1) 
            fout << " ";
    }
    fout.close();
}

void DecodeLZW(char** argv)
{
    string str;
    int temp;
    map<int, string> dict;
    vector<int> B;

    if (string(argv[2]).find(".lzw") == -1)
    {
        cout << "ERROR: Input file must be .lzw" << endl;
        return;
    }

    //get data from a file
    ifstream fin;
    fin.open(string(argv[2]), ios::binary);
    if (fin.is_open())
    {
        while(!fin.eof())
        {
            fin >> temp;
            B.push_back(temp);
        }
    }
    else 
    {
        cout << "ERROR File Open!" << endl;
        return;
    }
    dict = CreateDictionary2();
    //Decode a given vector binary, return a map and a string
    str = Decode(B, dict);

    OutputInfo2(argv, 10 * B.size(), 8 * str.size(), dict);

    //write output to a file
    ofstream fout;
    fout.open(string(argv[3]));
    fout << str;
    fout.close();
}

void Command(int argc, char** argv)
{
    if (strcmp(argv[1], "-e") == 0)
    {
        EncodeLZW(argv);
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        DecodeLZW(argv);
    }
    else
    {
        cout << "ERROR Action!" << endl;
    }
}
