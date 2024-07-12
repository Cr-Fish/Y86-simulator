#ifndef GUARD_tool_h
#define GUARD_tool_h
#include <string>

int char2Int(char c);
char int2Char(int a);
int getPos(char *s);

long long int getVal(std::string s);
std::string laVteg(long long int reg);
int fetch(int code);

#endif