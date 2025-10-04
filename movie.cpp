//pasted from vscode

#include "movie.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

Movie::Movie(const string& category, const string& name, double price, int qty, const string& genre, const string& rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating)
{ 
    genre_ = genre;
    rating_ = rating;
}

set<string> Movie::keywords() const {
   vector<string> tempWords;

   set<string> nameWords = parseStringToWords(convToLower(name_));

    for(set<string>::iterator it = nameWords.begin(); it != nameWords.end(); ++it) {
       tempWords.push_back(*it);
    }

    string g = convToLower(genre_);
    tempWords.push_back(g);

    set<string> keys(tempWords.begin(), tempWords.end());

    return keys;
}

string Movie::displayString() const {
    string output = "";

    //needs to output line 1 (movie name)
    output = name_;
    output = output + "\n";

    //TO DO: ouput line 2 and maybe check if rating should be uppercase
    
    string line2 = "Genre: " + genre_ + " Rating: " + rating_;
    output = output + line2 + "\n";

    string priceStr = to_string(price_);
    int dotLoc = priceStr.find(".");
    if(dotLoc != -1 && dotLoc + 3 < (int)priceStr.size()) {
        priceStr = priceStr.substr(0, dotLoc + 3);
    }
    

    string qtyStr = to_string(qty_);
    string qtyCopy = qtyStr; 
    qtyStr = qtyCopy;

    output = output + priceStr;
    output = output + " ";
    output = output + qtyStr;
    output = output + " left.";

    return output;

}



void Movie::dump(std::ostream& os) const {
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << genre_ << "\n"
       << rating_ << endl;
}