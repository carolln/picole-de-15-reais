#ifndef USEFULFUNCS_H
#define USEFULFUNCS_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
using std::vector;
using std::map;
using std::string;

string decode(string str, map<string, string> &dicionario);

void fill_dictionary(map<string, string> &mapa);

vector<std::string> tokenize (string line);

std::vector<std::string> split(std::string input, std::string delimiters = " \t");
#endif