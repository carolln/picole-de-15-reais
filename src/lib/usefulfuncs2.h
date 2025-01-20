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

bool is_index_mode(std::string input);

vector<std::string> tokenize (string line);

std::string strtolower(std::string orig);

bool is_number(string input);

bool is_reg(string input);

std::vector<std::string> split(std::string input, std::string delimiters = " \t");
#endif