
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/bimap.hpp>
#include <string>

void TokenDemo() {

	boost::char_separator<char> sep("<> =\"");
	std::string str = "The Boost C++ Libraries";

	boost::tokenizer<boost::char_separator<char>> token(str, sep);

	for (std::string part : token)
		std::cout << part << "\n";

	std::cout << "--------------------------------------------------------\n";

	int offset[] = { 3, 4, 5 };
	boost::offset_separator sep2{ offset, offset + 3 };
	boost::tokenizer<boost::offset_separator> token2(str, sep2);

	for (const auto& pt : token2)
		std::cout << pt << "\n";
}

void LexicalCastDemo() {
	std::string strNum = "1729";
	int num = boost::lexical_cast<int>(strNum);
	std::cout << "Number : " << num << "\n";

	try {
		double dnum = boost::lexical_cast<double>("abcd");
	}
	catch (const boost::bad_lexical_cast& blc) {
		std::cout << "Error : " << blc.what();
	}
}

void AlgDemo() {
	std::string str = "Hello   World\r\n";
	boost::trim_all(str);
	boost::to_upper(str);
	std::cout << "Trimmed String - " << str << "\n";
}

enum class Colors { RED, BLUE, GREEN};
typedef boost::bimap<Colors, std::string> ColorMapType;
ColorMapType colortype;

void BimapDemo() {
	colortype.insert(ColorMapType::value_type(Colors::RED, "Red"));
	colortype.insert(ColorMapType::value_type(Colors::BLUE, "Blue"));
	colortype.insert(ColorMapType::value_type(Colors::GREEN, "Green"));

	Colors clr = colortype.right.at("Red");
	std::string clrValue = colortype.left.at(Colors::GREEN);

	std::cout << "Color Value - " << clrValue << "\n";
}

//int main() {
//
//	//TokenDemo();
//	//LexicalCastDemo();
//	//AlgDemo();
//	BimapDemo();
//}