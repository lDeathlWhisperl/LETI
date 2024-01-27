#include <iostream>

struct Book
{
	std::string ISBN;
	std::string name;
	std::string author;
	int sheets;
	
	bool operator>(Book&);
	
	bool operator<(Book&);
	
	bool operator==(Book&);
};

std::ostream& operator<<(std::ostream&, Book&);

std::istream& operator>>(std::istream&, Book&);
