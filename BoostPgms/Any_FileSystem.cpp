
//#include <boost/any.hpp>
#include <iostream>
#include <string>
//#include <typeinfo>
//#include <vector>

//Boost::Any

//int main() {
//
//	boost::any val = 125.55;
//	std::cout << typeid(val).name() << "\n";
//
//	if (!val.empty())
//		std::cout << val.type().name() << "\n";
//
//	std::vector<boost::any> vec { 1729, "AnyValues" };
//
//
//	int i = boost::any_cast<int>(vec[0]);
//	std::cout << "Integer Value - " << i << "\n";
//
//	try {
//		std::string str = boost::any_cast<std::string>(vec[0]);
//	}
//	catch (const boost::bad_any_cast& bac) {
//		std::cout << "Error : " << bac.what() << "\n";
//	}
//
//	for (boost::any a : vec) {
//		int* iPtr = boost::any_cast<int>(&a);
//		if (iPtr)
//			std::cout << *iPtr << "\n";
//		
//		const char** cPtr = boost::any_cast<const char*>(&a);
//		if (cPtr)
//			std::cout << *cPtr << "\n";
//	}
//}

#include <boost\filesystem.hpp>

namespace bfs = boost::filesystem;

void CheckFile(bfs::path& p) {
	auto st = bfs::status(p);
	auto tp = st.type();
	auto ps = st.permissions();

	std::cout << "Type - " << tp << "\n Permission - " << ps << "\n";

	if ((ps & bfs::owner_write) != bfs::owner_write)
		std::cout << "No Permission to Write \n";
}

void CheckPath(const char* p) {
	bfs::path testpath(p);

	if (!bfs::exists(testpath))
		std::cout << "Path " << testpath << " Does not exist..\n";
	else {
		if (bfs::is_regular_file(p)) {
			std::cout << "Path " << testpath.filename().replace_extension() << " is a regular file of size "
				<< bfs::file_size(testpath) << "\n";
		}
		else if (bfs::is_directory(testpath)) {
			std::cout << "Path " << testpath.filename() << " is a directory..\n";
		}
	}
}

void Fundamentals(const char* p) {

	CheckPath(p);
	CheckPath("Foo");

	auto dir = bfs::path(p).parent_path();
	CheckPath(dir.string().c_str());

	for (auto& p : dir) {
		std::cout << p << "\n";
	}

	bfs::path pth("Junk");
	try {
		bfs::file_size(pth);
	}
	catch (const bfs::filesystem_error& fse) {
		std::cout << "Error : " << fse.what() << "\n";
	}
}

void DirectoryNavigation(bfs::path& dir) {
	bfs::directory_iterator end;
	for (bfs::directory_iterator itr(dir); itr != end; ++itr) {
		bfs::path p = itr->path();
		CheckPath(p.string().c_str());
		if(bfs::is_directory(p))
			DirectoryNavigation(p);
	}
}


//int main(int argc, char* argv[]) {
//	
//	bfs::path testpath(argv[0]);
//	CheckFile(testpath);
//
//	Fundamentals(argv[0]);
//
//	bfs::path dir = bfs::path(argv[0]).parent_path().parent_path();
//
//	DirectoryNavigation(dir);
//}