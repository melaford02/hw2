//pasted from vscode

#include "mydatastore.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <set>

using namespace std;

MyDataStore::MyDataStore() { 

}

MyDataStore::~MyDataStore() {
  for (int i = 0; i < (int)products_.size(); i++) {
        Product* p = products_[i];
        if (p != nullptr) {
            delete p;
            p = nullptr; 
        }
    }

    for (int j = 0; j < (int)users_.size(); j++) {
        User* u = users_[j];
        if (u != nullptr) {
            delete u;
            u = nullptr; 
        }
    }
}

void MyDataStore::addProduct(Product* newProduct) 
{
    products_.push_back(newProduct);

    set<string> wordList = newProduct->keywords();

    
    for(set<string>::iterator it = wordList.begin(); it != wordList.end(); ++it) 
    {
        string currentWord = *it;

        // add the product under this keyword
        keywordMap_[currentWord].insert(newProduct);
    }
}


void MyDataStore::addUser(User* newUser) 
{
    users_.push_back(newUser);

    string userName = newUser->getName();

    string lowerUserName = convToLower(userName);

    userMap_.insert(make_pair(lowerUserName, newUser));

    vector<Product*> cart;
    carts_.insert(make_pair(lowerUserName, cart));
}


vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    vector<Product*> foundProducts;
    
    if(terms.size() == 0) {
        return foundProducts;
    }
    
    vector<std::string> searchTerms;

// ***go back and conv to lowercase****
    for(size_t i = 0; i < terms.size(); i++) {
        string currentTerm = terms[i];
        string lowerTerm = convToLower(currentTerm);
        searchTerms.push_back(lowerTerm);
    }
    
    set<Product*> matchingProducts;
    
    if(type == 0) {
        bool firstTermFound = false;
        
        if(keywordMap_.count(searchTerms[0]) > 0) {
            matchingProducts = keywordMap_[searchTerms[0]];
            firstTermFound = true;
        }
        
        if(firstTermFound) {
            for(size_t i = 1; i < searchTerms.size(); i++) {
                string currentSearchTerm = searchTerms[i];
                
                // Check if this term exists
                if(keywordMap_.count(currentSearchTerm) > 0) {
                    set<Product*> currentTermProducts = keywordMap_[currentSearchTerm];
                    set<Product*> combinedProducts;
                    
                    // Find products that are in both sets
                    for(Product* product : matchingProducts) {
                        if(currentTermProducts.find(product) != currentTermProducts.end()) {
                            combinedProducts.insert(product);
                        }
                    }
                    
                    matchingProducts = combinedProducts;
                    
                    if(matchingProducts.empty()) {
                        break;
                    }
                } else {
                    matchingProducts.clear();
                    break;
                }
            }
        }
    }
    else {
        for(size_t i = 0; i < searchTerms.size(); i++) {
            string currentSearchTerm = searchTerms[i];
            
            if(keywordMap_.count(currentSearchTerm) > 0) {
                std::set<Product*> termProducts = keywordMap_[currentSearchTerm];
                
                for(Product* product : termProducts) {
                    matchingProducts.insert(product);
                }
            }
        }
    }
    
    for(Product* product : matchingProducts) {
        foundProducts.push_back(product);
    }
    
    return foundProducts;
}

void MyDataStore::dump(ostream& ofile) {
    ofile << "<products>" << std::endl;

    for(int i = 0; i < (int)products_.size(); i++) 
    {
        Product* p = products_[i];
        p->dump(ofile);
    }

    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;

    for(int j = 0; j < (int)users_.size(); j++) 
    {
        User* u = users_[j];
        u->dump(ofile);
    }

    ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(const string& username, Product* product) 
{
    string loweredName = convToLower(username);

    if(userMap_.count(loweredName) == 0) 
    {
        cout << "Invalid username" << endl;
        return;
    }

    vector<Product*> cartNow = carts_[loweredName];
    cartNow.push_back(product);

    carts_[loweredName] = cartNow;
}


void MyDataStore::viewCart(const string& username) const 
{
    string loweredName = convToLower(username);

    map<string, vector<Product*>>::const_iterator it = carts_.find(loweredName);

    if(it == carts_.end()) 
    {
        cout << "Invalid username" << endl;
        return;
    }

    vector<Product*> userCart = it->second;

    for(int i = 0; i < (int)userCart.size(); i++) 
    {
        int itemNumber = i + 1;
        cout << "Item " << itemNumber << endl;

        Product* current = userCart[i];
        cout << current->displayString() << endl;
    }
}


void MyDataStore::buyCart(const string& username) 
{
    string lowerUser = convToLower(username);

    map<string, vector<Product*>>::iterator it = carts_.find(lowerUser);

    if(it == carts_.end()) 
    {
        cout << "Invalid username" << endl;
        return;
    }

    vector<Product*> currentCart = it->second;
    vector<Product*> leftoverCart;

    User* buyer = userMap_[lowerUser];

    for(int i = 0; i < (int)currentCart.size(); i++) 
    {
        Product* prod = currentCart[i];

        int qtyAvailable = prod->getQty();
        double userBalance = buyer->getBalance();
        double price = prod->getPrice();

        bool canBuy = false;
        if(qtyAvailable > 0) 
        {
            if(userBalance >= price) 
            {
                canBuy = true;
            }
        }

        if(canBuy) 
        {
            prod->subtractQty(1);
            buyer->deductAmount(price);
        }
        else 
        {
            leftoverCart.push_back(prod);
        }
    }
    carts_[lowerUser] = leftoverCart;
}

bool MyDataStore::userExists(const std::string& username) const{
  string loweredName = convToLower(username);
  bool exists = (userMap_.find(loweredName) != userMap_.end());

  return exists;
}