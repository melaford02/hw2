//pasted from vscode to run tests
#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>

using namespace std;

/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
set<T> setIntersection(const set<T>& s1, const set<T>& s2)
{
    set<T> answer;

    typename set<T>::iterator first = s1.begin();
    typename set<T>::iterator second = s2.begin();

    while(first != s1.end() && second != s2.end())
    {
        T val1 = *first;
        T val2 = *second;

        if(val1 == val2) {
            answer.insert(val1);
            ++first;
            ++second;
        }
        else if(val1 < val2) {
            ++first;
        }
        else {
            ++second;
        }
    }

    return answer;
}

template <typename T>
set<T> setUnion(const set<T>& s1, const set<T>& s2)
{
    set<T> answer;

    typename set<T>::iterator first = s1.begin();
    typename set<T>::iterator second = s2.begin();

    while(first != s1.end() && second != s2.end())
    {
        T val1 = *first;
        T val2 = *second;

        if(val1 == val2) {
            answer.insert(val1);
            ++first;
            ++second;
        }
        else if(val1 < val2) {
            answer.insert(val1);
            ++first;
        }
        else {
            answer.insert(val2);
            ++second;
        }
    }

    while(first != s1.end()) {
        answer.insert(*first);
        ++first;
    }

    while(second != s2.end()) {
        answer.insert(*second);
        ++second;
    }

    return answer;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/
std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

std::string &ltrim(std::string &s) ;
std::string &rtrim(std::string &s) ;
std::string &trim(std::string &s) ;

#endif

