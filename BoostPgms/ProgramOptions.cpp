
#include <iostream>
#include <boost/program_options.hpp>
#include <string>
#include <vector>

namespace po = boost::program_options;

void OnAge(int a) {
	std::cout << "OnAge : " << a << "\n";
}

void Customization(int argc, char* argv[]) {

	int value;
	po::options_description desc("File Processor");

	desc.add_options()
		("value, v", po::value<int>(&value)->default_value(42), "Input Value")
		("files", po::value<std::vector<std::string>>()->multitoken(), "Input Files");

	po::positional_options_description pos;
	pos.add("files", -1);

	po::variables_map vm;
	po::command_line_parser parser (argc, argv);
	auto parsed_options = parser.options(desc).positional(pos).run();
	po::store(parsed_options, vm);
	po::notify(vm);

	std::cout << desc << "\n";
	std::cout << "Value - " << value << "\n";

	if (vm.count("files")) {
		int i = 0;
		auto files = vm["files"].as<std::vector<std::string>>();
		for (auto& f : files)
			std::cout << "File " << ++i << " : " << f << "\n";
	}
}

void Fundamentals(int argc, char* argv[]) {

	po::options_description desc("Program Options");
	desc.add_options()
		("help,h", "print info")
		("filename", po::value<std::string>()->default_value("default.txt"), "file to process")
		("age", po::value<int>()->notifier(OnAge), "For Age");


	po::variables_map vm;
	auto parsed = po::parse_command_line(argc, argv, desc);
	po::store(parsed, vm);

	if (vm.count("help"))
		std::cout << desc << "\n";
	
	if (vm.count("filename")) {
		std::string fname = vm["filename"].as<std::string>();
		std::cout << "Processing file : " << fname << "\n";
	}
	
	if (vm.count("age")) {
		//std::cout << "Main -- " << vm["age"].as<int>() << "\n";
		po::notify(vm);
	}
}
//
//int main(int argc, char* argv[]) {
//	//Fundamentals(argc, argv);
//	Customization(argc, argv);
//}
//
