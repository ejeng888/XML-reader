#include <iostream>
#include <string>
#include <fstream>
#include <cpplinq.hpp>
#include "../../std_lib_facilities.h"
#include "../../rapidxml.hpp"
#include "../../rapidxml_print.hpp"
#include "../../rapidxml_iterators.hpp"
using namespace rapidxml;
using namespace cpplinq;


struct employee {
	int id;
	string name;
	string city;

	employee(size_t id = 0, string name = "", string city = "")
		:id(move(id)), name(move(name)), city(move(city))
	{
	}
};

void print(vector<employee> test_vector) {

	auto result = from(test_vector)
		>> where([](employee const & e) {return e.city == "Toronto"; })
		>> orderby_ascending([](employee const & e) {return e.name; })
		>> select([](employee const & e) {return e.name; })
		>> to_vector();
	
	for (int i = 0; i != result.size(); ++i) {
		cout << result[i] << "\n";
	}
}

int main()
{
	int i = 0;
	vector<employee> test_vector;
	test_vector.push_back(employee());

	xml_document<> doc;

	ifstream file("C:\\Users\\ejeng\\source\\repos\\xml_test\\xml_test\\Test.xml");
	
	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	buffer.push_back('\0');

	cout << &buffer[0] << "\n"; 

	doc.parse<0>(&buffer[0]);

	xml_node<> *Root = doc.first_node();
	xml_node<> *child = Root->first_node();

	while (child != NULL) {

		xml_node<> *ID = child->first_node();
		xml_node<> *Name = ID->next_sibling();
		xml_node<> *City = Name->next_sibling();

		cout << ID->value() << " ";
		cout << Name->value() << " ";
		cout << City->value() << " \n";

		stringstream buffer(ID->value());
		int n;
		buffer >> n;

		test_vector[i].id = n;
		test_vector[i].name = Name->value();
		test_vector[i].city = City->value();

		test_vector.push_back(employee());
		i++;

		child = child->next_sibling();
	}
	cout << "*******************************" << "\n";
	
	//LINQ part

	print(test_vector);
}


