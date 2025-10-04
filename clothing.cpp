//pasted from vscode

#include "clothing.h"
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

Clothing::Clothing(const string& category, const string& name, double price, int qty, const string& size, const string& brand)
    : Product(category, name, price, qty), size_(size), brand_(brand)
{ }

set<string> Clothing::keywords() const {
   vector<string> tempWords;

   //break name into words
   set<string> nameWords = parseStringToWords(convToLower(name_));
   set<string> brandWords = parseStringToWords(convToLower(brand_));

    for (string word : nameWords) {
        tempWords.push_back(word);
    }

    for (string word : brandWords) {
        tempWords.push_back(word);
    }

    set<string> finalWords;
    for (int i = 0; i < (int)tempWords.size(); i++) {
        finalWords.insert(tempWords[i]);
    }

    return finalWords;
}

string Clothing::displayString() const {
 string output = "";

 // cout << "building display string for clothing" << endl;

output = name_;
output = output + "\n";

string line2 = "Size: " + size_ + " Brand: " + brand_;
output = output + line2 + "\n";

string priceStr = to_string(price_);
int dot = priceStr.find(".");
if(dot != -1) {
        if(dot + 3 < (int)priceStr.size()) {
            priceStr = priceStr.substr(0, dot + 3);
        }
    }

// cout << "price string = " << priceStr << endl;

string qtyStr = to_string(qty_);

string qtyCopy = qtyStr;  
qtyStr = qtyCopy;  

    output = output + priceStr;
    output = output + " ";
    output = output + qtyStr;
    output = output + " left.";

    return output;
}

void Clothing::dump(ostream& os) const {
    string c = category_;
    string n = name_;
    double p = price_;
    int q = qty_;
    string s = size_;
    string b = brand_;

    os << c << endl;
    os << n << endl;
    os << p << endl;
    os << q << endl;
    os << s << endl;
    os << b << endl;
}