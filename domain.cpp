#include <string>
#include <map>
#include <iostream>
#include "domain.h"

/*
 * Container type for domain descriptors
 */
using domain_set_t = std::map<std::wstring, Domain>;

/*
 * Domain descriptors
 */
domain_set_t domains;

/*
 * Adds an email address or Internet domain name to the current list
 */
void Domain::add_address(const std::wstring& address) {
	const std::wstring::size_type at{address.find('@')};
	Domain& d{domains[(at == std::wstring::npos) ? address : address.substr(at + 1)]};
	
	if (d.type == DomainType::UNINITIALIZED) {
		if (at == std::wstring::npos || at == 0) {
			d.type = DomainType::NORMALIZED;
		} else {
			d.type = DomainType::NON_NORMALIZED;
			d.users.emplace(address.substr(0, at));
		}
	} else {
		d.users.emplace(address.substr(0, at));
	}
}

/*
 * Determines if the domain needs a cleanup
 */
bool Domain::needs_cleanup() const {
	switch (type) {
	case DomainType::NORMALIZED:
		return !users.empty();
	case DomainType::NON_NORMALIZED:
		return users.size() > 1;
	default:
		std::cerr << "INTERNAL ERROR (uninitialized domain): Exiting." << std::endl;
		exit(1);
	}
}

/*
 * Process domains and prints steps to be taken with Blocked-Senders-File
 */
void Domain::process_all() {
	bool file_is_good{true};
	
	for (auto domain: domains) {
		Domain& d{domain.second};
	
		if (d.needs_cleanup()) {
			std::wcout << "Domain " << domain.first << ":" << std::endl;

			for (std::wstring user: d.users) {
				std::wcout << "  remove " << user << "@" << domain.first << std::endl;
			}

			if (d.type == DomainType::NON_NORMALIZED) {
				std::wcout << "  add @" << domain.first << std::endl;
			}
			file_is_good = false;
		}
	}

	if (file_is_good) {
		std::wcout << "Blocked-Senders-File is good" << std::endl;
	}
}