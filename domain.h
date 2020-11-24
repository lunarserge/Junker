#ifndef DOMAIN_H_
#define DOMAIN_H_

#include <string>
#include <set>

/*
 * Describes a domain and associated records
 */
class Domain {

private:

	/*
	 * Possible domain types
	 */
	enum class DomainType {
		UNINITIALIZED, // domain has been just created and needs initialization
		NORMALIZED,    // domain has a record in a form of '@example.com' or 'example.com'
		NON_NORMALIZED // domain has one or more records in a form of 'somebody@example.com', but no records in a form of 'example.com' or '@example.com'
	};

	/*
	 * Domain type
	 */
	DomainType type;

	/*
	 * Container type for domain users
	 */
	using user_set_t = std::set<std::wstring>;

	/*
	 * Specific users that have records with this domain
	 */
	user_set_t users;

	/*
	 * Determines if the domain needs a cleanup
	 */
	bool needs_cleanup() const;

public:

	/*
	 * Constructs uninitialized domain
	 */
	Domain(): type{DomainType::UNINITIALIZED} {}

	/*
	 * Adds an email address or Internet domain name to the current list
	 */
	static void add_address(const std::wstring& address);

	/*
	 * Process domains and prints steps to be taken with Blocked-Senders-File
	 */
	static void process_all();
};

#endif // DOMAIN_H_