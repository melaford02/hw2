//pasted from vscode

#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include "util.h"
#include <string>
#include <set>

using namespace std;

class Clothing : public Product {
public:
    Clothing(const string& category, const string& name, double price, int qty, const string& size, const string& brand);

    set<string> keywords() const override;
    string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    string size_;
    string brand_;
};

#endif