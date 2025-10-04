//pasted from vscode

#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <map>
#include <set>
#include <vector>
#include <string>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;

    void addToCart(const std::string& username, Product* p);
    void viewCart(const std::string& username) const;
    void buyCart(const std::string& username);

    bool userExists(const std::string& username) const;

private:
    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::map<std::string, User*> userMap_;
    std::map<std::string, std::vector<Product*>> carts_;
    std::map<std::string, std::set<Product*>> keywordMap_;
};

#endif