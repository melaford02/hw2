//pasted from vscode

#ifndef BOOK_H
#define BOOK_H

#include <set>
#include "product.h"
#include "util.h"
#include <string>
#include <vector>

using namespace std;

class Book : public Product {
public:
    Book(const string& category, 
         const string& name, 
         double price, 
         int qty, 
         const string& isbn, 
         const string& author);

    
    set<string> keywords() const override;
    string displayString() const override;
    void dump(ostream& os) const override;

private:
    string isbn_;
    string author_;
};

#endif