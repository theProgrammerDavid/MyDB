#pragma once

#ifndef TABLE_H
#define TABLE_H


#include "Protocol.h"
#include <string>
#include <vector>
#include <iostream>
#include "ext/json.hpp"
#include "ext/picosha2.h"

#define MAX_ROW_SIZE 100

using json = nlohmann::json;

int primaryHashFunction(std::string s);
int secondaryHashFunction(std::string s);

enum bg{A,B,AB,O};
enum sex { M, F };;

class Element {
public:

	std::string name;
	std::string pswd;
	int blood_group;
	std::string phoneNo;
	std::string donorName;
	std::string donorFather;
	std::string transferDate;
	int age;
	int sex;
	
	Element();
	Element(std::string n,std::string pass, std::string phone,
		std::string dname, std::string dfather, std::string tdate,
		int _bg, int _age, int _sex);

};

class Field {

public:
	std::vector< Element> vec;
	int noOfChains;

	Field();
	Element getElement(int );
};


class Table
{
public:

	Field row[MAX_ROW_SIZE];

	json ReadProtocol(json j);

	Table();
	~Table();

	void registerSchema(json j);
	
	json addEntry(json j);
	json addEntryCheckup(json j);
	json findAll(json j);
	json findOne(json j);
	json deleteEntry(json j);
	json findOneAndUpdate(json j);
	json findAllAndUpdate(json j);

private:
	bool copyExists(std::vector<Element>vec, Element e);
	void fillObj(json j, Element *e);
	void filljson(json &j, Element e);
};




#endif // !TABLE_H


