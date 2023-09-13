#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <map>
#include <mysql.h>


using namespace std;
class Chat
{
public:
	Chat();
	//parser user
	bool parser(const char* mes);
	//check user
	bool check(string name, string famil, string login, string pass);
	bool check_nick(string name);
	bool check_login(string login);
	bool check_pass(string login, string pass);
	//reg
	void reg(string name, string famil, string login, string pass);
	//print data
	string print();
	//get id - name
	string id(string name);
	//get name - id
	string get_name(string id);
	//get name
	string get(const char* mes);
	//send
	string send(string sender, string recivered, string text);
	//receive
	string receive(string name);
	//parser message (receiver, mes)
	void parser_mes(const char* mes);
};
