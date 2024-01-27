#include <string>

#include "Book.h"

bool Book::operator>(Book& book)
{	
	return author > book.author;
}

bool Book::operator<(Book& book)
{
	return author < book.author;
}

bool Book::operator==(Book& book)
{
    if(ISBN   == book.ISBN   &&
       name   == book.name   &&
       author == book.author &&
       sheets == book.sheets) return true;
       
    return false;    
}

std::ostream& operator<<(std::ostream& out, Book& book)
{
	out << "ISBN:......... "   << book.ISBN   << '\n' 
		<< "Book name:.... \"" << book.name   << "\"\n" 
		<< "Book author:.. "   << book.author << '\n'
		<< "Sheets count:. "   << book.sheets << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, Book& book)
{
    std::getline(in >> std::ws, book.ISBN);
    std::getline(in >> std::ws, book.name);
    std::getline(in >> std::ws, book.author);
    return in >> book.sheets;
}
