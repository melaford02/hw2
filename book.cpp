//pasted from vscode

#include "book.h"
#include <sstream>
#include <iomanip>

using namespace std;

Book::Book(const string& category, const string& name, double price, int qty, const string& isbn, const string& author)
    : Product(category, name, price, qty)
{ 
    author_ = author;
    isbn_ = isbn;
}

void Book::dump(ostream& os) const {
    string c = category_;
    string n = name_;

    double p = price_;
    int q = qty_;

    string i = isbn_;
    string a = author_;

    os << c << endl;
    os << n << endl;
    os << p << endl;
    os << q << endl;
    os << i << endl;
    os << a << endl;

}

set<string> Book::keywords() const {
    vector<string> tempWords;       

    set<string> nameWords = parseStringToWords(convToLower(name_));
    for(set<string>::iterator ptr = nameWords.begin(); ptr != nameWords.end(); ++ptr) {
        tempWords.push_back(*ptr);
    }

    set<string> authorWords = parseStringToWords(convToLower(author_));
    for(set<string>::iterator ptr = authorWords.begin(); ptr != authorWords.end(); ++ptr) {
        tempWords.push_back(*ptr);
    }

    tempWords.push_back(isbn_);

    string cat = convToLower(category_);
    tempWords.push_back(cat);

    set<string> finalKeys;
    for(int i = 0; i < (int)tempWords.size(); i++) {
        finalKeys.insert(tempWords[i]);
    }

    return finalKeys;
}



string Book::displayString() const {
    string out;  

    out = name_;
    out = out + "\n";

    string auth = "Author: ";
    auth = auth + author_;
    string num = " ISBN: ";
    num = num + isbn_;
    out = out + auth + num + "\n";

    ostringstream tmpPrice;
    tmpPrice << fixed << setprecision(2) << price_;  
    string pricePart = tmpPrice.str();

    string qtyPart = to_string(qty_);

    string leftovers = " left.";
    out = out + pricePart;
    out = out + " ";
    out = out + qtyPart;
    out = out + leftovers;

    return out;
}