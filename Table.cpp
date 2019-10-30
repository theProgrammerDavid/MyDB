#include "pch.h"
#include "Table.h"


Table::Table()
{
}


Table::~Table()
{
}

Element::Element() {

}

Element::Element(std::string n, std::string pass, std::string phone,
	std::string dname, std::string dfather, std::string tdate,
	int _bg, int _age, int _sex) {
	name = n;
	pswd = pass;
	phoneNo = phone;
	donorName = dname;
	donorFather = dfather;
	transferDate = tdate;
	blood_group = _bg;
	age = _age;
	sex = _sex;
}

Field::Field(){
	noOfChains = 0;
}

Element Field::getElement(int pos = 0) {
	return vec[pos];
}

int primaryHashFunction(std::string s) {
	
	int hashVal = 0, asc;
	for (int i = 0; i < s.size(); i++)
	{
		asc = s[i] > 96 ? s[i] - 96 : s[i] - 64;
		hashVal = (hashVal * 32 + asc) % MAX_ROW_SIZE;
	}
	return hashVal;

}

int  secondaryHashFunction(std::string s) {
	return 0;
}


void Table::ReadProtocol(json j) {

	std::string p = j["protocol"].dump();
	
	std::cout << "\nregistered with: " << j["protocol"]<< std::endl;
	if (strcmp(p.c_str(), "99") == 0) {
		registerSchema(j);
	}
	else if (strcmp(p.c_str(), "102") == 0) {
		addEntryCheckup(j);
	}
	else if (strcmp(p.c_str(),"100")==0) {
		addEntry(j);
	}
	else if (strcmp(p.c_str(), "200") == 0) {
		findAll(j);
	}
	else if (strcmp(p.c_str(), "201") == 0) {
		findOne(j);
	}
	else if (strcmp(p.c_str(), "402") == 0) {
		deleteEntry(j);
	}
	else if (strcmp(p.c_str(), "301") == 0) {
		findOneAndUpdate(j);
	}
	else if (strcmp(p.c_str(), "300") == 0) {
		findAllAndUpdate(j);
	}

}

void Table::registerSchema(json j) {

}

void Table::addEntry(json j) {
	std::cout << "adding entry" <<std::endl;
	Element e;
	
}

void Table::addEntryCheckup(json j) {

}

json Table::findAll(json j) {
	return NULL;
}
json Table::findOne(json j) {
	return NULL;
}


void Table::deleteEntry(json j) {

}

void Table::findOneAndUpdate(json j) {

}

void Table::findAllAndUpdate(json j) {
	
}