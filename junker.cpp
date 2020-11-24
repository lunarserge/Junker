#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <codecvt>
#include "domain.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << std::filesystem::path(argv[0]).filename() << " Blocked-Senders-File" << std::endl;
		return 1;
	}
	char* fn{argv[1]};

	std::wifstream in{fn};
	if (in.fail()) {
		std::cerr << "Input file " << fn << " can not be read. Exiting." << std::endl;
		return 1;
	}

	// I know std::codecvt_utf16 is deprecated in C++17, but looks like the alternative is not yet available until C++20
	in.imbue(std::locale(in.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

	std::wstring s;
	while (in >> s) {
		Domain::add_address(s);
	}
	in.close();

	Domain::process_all();
	return 0;
}