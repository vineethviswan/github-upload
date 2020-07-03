
#include <boost/optional.hpp>
#include <iostream>
#include <typeinfo>
#include <string>

class Address {
public:
	Address(std::string sname):streetname(sname){}
	std::string streetname;
};

class Person {
public:
	Person(std::string fname, std::string lname, Address adr): firstname (fname), lastname (lname), address(adr){}
	Person(std::string fname, std::string mname, std::string lname) : firstname(fname), middlename(mname), lastname(lname) {}

	boost::optional<std::string> GetMiddleName() {
		return middlename;
	}

	boost::optional<Address> GetAddress() {
		return address;
	}
private:
	std::string firstname, lastname;
	boost::optional<std::string> middlename;
	boost::optional<Address> address;
};

//int main() {
//	
//	Address a1("221 Baker St.");
//	Person p1("John", "Jr.", "Watson");
//
//	auto mname = p1.GetMiddleName();
//
//	//std::cout << typeid(mname).name() << "\n";
//	/*if (mname)
//		std::cout << "Middle Name --- "<< mname.value() << "\n";
//	else
//		std::cout << "No Middle Name\n";*/
//
//	try {
//		std::cout << "Middle Name --- " << mname.value() << "\n";
//	}
//	catch (const boost::bad_optional_access& boa) {
//		std::cout << "Error : " << boa.what() << "\n";
//	}
//
//	Person p2("Sherlock", "Homes", a1);
//
//	auto ad = p2.GetAddress();
//	if (ad)
//		std::cout << "Address --- " << ad.value().streetname << "\n";
//
//	try {
//		std::cout << p1.GetAddress().value().streetname << "\n";
//	}
//	catch (boost::bad_optional_access& boa) {
//		std::cout << "Error : " << boa.what() << "\n";
//	}
//}