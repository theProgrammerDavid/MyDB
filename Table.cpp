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


json Table::ReadProtocol(json j) {

	std::string p = j["protocol"].dump();
	json ret;

	std::cout << "\nregistered with: " << j["val"]<< std::endl;
	if (strcmp(p.c_str(), "99") == 0) {
		registerSchema(j["val"]);
	}
	else if (strcmp(p.c_str(), "102") == 0) {
		std::cout << "add entry checkup" << std::endl;
		ret = addEntryCheckup(j["val"]);
	}
	else if (strcmp(p.c_str(),"100")==0) {
		std::cout << "add entry" << std::endl;
		ret = addEntry(j["val"]);
	}
	else if (strcmp(p.c_str(), "200") == 0) {
		std::cout << "find all" << std::endl;
		ret = findAll(j["val"]);
	}
	else if (strcmp(p.c_str(), "201") == 0) {
		std::cout << "find one" << std::endl;
		ret = findOne(j["val"]);
	}
	else if (strcmp(p.c_str(), "402") == 0) {
		std::cout << "delete entry" << std::endl;
		ret = deleteEntry(j["val"]);
	}
	else if (strcmp(p.c_str(), "301") == 0) {
		std::cout << "find one and update" << std::endl;
		ret = findOneAndUpdate(j["val"]);
	}
	else if (strcmp(p.c_str(), "300") == 0) {
		std::cout << "find all and update" << std::endl;
		ret = findAllAndUpdate(j["val"]);
	}

	return ret;
}

void Table::registerSchema(json j) {

}

json Table::addEntry(json j) {
	std::cout << "adding entry" <<std::endl;
	Element e;
	json resp;
	fillObj(j, &e);
	int pos = primaryHashFunction(e.phoneNo);

	row[pos].vec.push_back(e);
	row[pos].noOfChains++;

	resp["status"] = "OK";
	return resp;
}

json Table::addEntryCheckup(json j) {
	std::cout << "\nadding entry with check\n" << std::endl;
	Element e;
	fillObj(j, &e);
	json resp;
	std::string phno = j["phoneNo"].dump();
	//first check if the stuff exists

	int pos = primaryHashFunction(e.phoneNo);
	bool found = false;
	auto scanVec = row[pos].vec;

	for (int i = 0; i < scanVec.size(); i++) {
		if (scanVec[i].phoneNo == phno) {
			found = true;
		}
	}

	if (found) {
		std::cout << "duplicate found in check" << std::endl;
		resp["status"] = "DUPLICATE_FOUND";
	}
	else {
		std::cout << "duplicate not found in check\nadding entry" << std::endl;
		row[pos].vec.push_back(e);
		row[pos].noOfChains++;
		resp["status"] = "OK";
	}

	return resp;
}
void Table::fillObj(json j, Element *e) {
	
	e->name = j["name"].dump();
	e->pswd = j["pswd"].dump();
	e->phoneNo = j["phoneNo"].dump();
	e->donorFather = j["donorFather"].dump();
	e->transferDate = j["transferDate"].dump();
	e->donorName = j["donorName"].dump();
	e->blood_group = atoi(j["bloodGroup"].dump().c_str());
	e->age = atoi(j["age"].dump().c_str());
	e->sex = atoi(j["sex"].dump().c_str());
}

bool Table::copyExists(std::vector<Element> vec, Element e) {
	bool exists = false;

	for (std::vector<Element>::iterator i = vec.begin(); i != vec.end(); i++) {
		
		if (i->phoneNo == e.phoneNo) {
			exists = true;
		}
	}

	return exists;
}

json Table::findAll(json j) {
	
	std::string phno = j["phoneNo"].dump();
	Element e;
	json resp;
	json fill;

	int pos = primaryHashFunction(phno);
	auto scanVec = row[pos].vec;

	if (row[pos].noOfChains == 0) {
		resp["status"] = "NULL";
	}
	else {

	for (int i = 0; i < scanVec.size(); i++) {
		filljson(fill , scanVec[i]);
		resp[i] = fill;
	}


	}
	return resp;
}

void Table::filljson(json &j, Element e) {



	j["name"] = e.name;
	j["pswd"] = e.pswd;
	j["blood_group"] = e.blood_group;
	j["phoneNo"] = e.phoneNo;
	j["donorFather"] = e.donorFather;
	j["donorName"] = e.donorName;
	j["transferDate"] = e.transferDate;
	j["age"] = e.age;
	j["sex"] = e.sex;
}

json Table::findOne(json j) {
	
	std::string phno = j["phoneNo"].dump();
	Element e;
	json resp;

	int pos = primaryHashFunction(phno);
	std::cout << "filling json" << std::endl;
	
	if (row[pos].noOfChains == 0) {
		resp["status"] = "NULL";
	}
	else {

	filljson(resp, row[pos].vec[0]);
	}
	
	return resp;
}


json Table::deleteEntry(json j) {
	std::string phno = j["phoneNo"].dump();
	Element e;
	json resp;

	int pos = primaryHashFunction(phno);
	auto scanVec = row[pos].vec;

	for (int i = 0; i < scanVec.size(); i++) {
		if (scanVec[i].phoneNo == phno) {
			
		}
	}
	return resp;
}

json Table::findOneAndUpdate(json j) {
	std::string phno = j["phoneNo"].dump();
	Element e;
	json resp;

	fillObj(j, &e);

	int pos = primaryHashFunction(phno);
	 row[pos].vec[0]=e;
	
	 resp["status"] = "OK";
	 return resp;
}

json Table::findAllAndUpdate(json j) {
	std::string phno = j["phoneNo"].dump();
	Element e;
	json resp;

	fillObj(j, &e);

	int pos = primaryHashFunction(phno);
	auto scanVec = row[pos].vec;

	for (int i = 0; i < scanVec.size(); i++) {

		if (scanVec[i].phoneNo == phno) {
			scanVec[i] = e;
		}
	}
	resp["status"] = "OK";
	return resp;
}