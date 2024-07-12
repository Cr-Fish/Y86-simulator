#include <iostream>
#include <vector>
#include "tool.h"
using std::cout;    using std::endl;
using std::cin;     using std::vector;
using std::string;

int char2Int(char c)
{
    if (c >= 97)
    {
        return c - 'a' + 10;
    }
    else
        return c - '0';
}
// ascii转int
char int2Char(int a)
{
    if (a <= 9)
        return '0' + a;
    else
        return 'a'-10 + a;
}
//int转ascii
int getPos(char *s)
{
    int ret;
    ret = char2Int(s[2]);
    ret *= 16;
    ret += char2Int(s[3]);
    ret *= 16;
    ret += char2Int(s[4]);
    return ret;
}
//指令地址
long long int getVal(string s)
{
    vector<int> t;
    int byte;
    for (int i = 0; i < s.size(); i += 2)
    {
        byte = char2Int(s[i]);
        byte *= 16;
        byte += char2Int(s[i + 1]);
        t.push_back(byte);
    }

    long long ret = 0;
    for (int i = t.size() - 1; i >= 0; --i)
    {
        ret *= 256;
        ret += t[i];
    }

    if (s[s.size() - 2] - '0' < 8)
        return ret;
    else
    {
        long long go = 1;
        go << (s.size() * 4 - 1);
        return ret - go + 1;
    }
}
string laVteg(long long int reg)
{
    string ret;
    for (int i = 0; i < 8; ++i)
    {
        string piece;
        piece.push_back(int2Char(reg & 0xF));
        reg = (reg >> 4);
        string small;
        small.push_back(int2Char(reg & 0xF));
        piece.insert(0, small);
        reg = (reg >> 4);
        ret += piece;
    }
    return ret;
}
int fetch(int code)
{
    int ret;
    switch (code)
    {
    case 0x0:
        ret = 1;
        break;
    case 0x1:
        ret = 1;
        break;
    case 0x2:
        ret = 2;
        break;
    case 0x3:
        ret = 10;
        break;
    case 0x4:
        ret = 10;
        break;
    case 0x5:
        ret = 10;
        break;
    case 0x6:
        ret = 2;
        break;
    case 0x7:
        ret = 9;
        break;
    case 0x8:
        ret = 9;
        break;
    case 0x9:
        ret = 1;
        break;
    case 0xA:
        ret = 2;
        break;
    case 0xB:
        ret = 2;
        break;
    case 0xC:
        ret = 10;
        break;
    }
    return ret;
}
//指令字节数