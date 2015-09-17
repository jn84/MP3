#pragma once

#include <iostream>
using namespace std;

class intEntry
{
public:
    // initialize the integer value and its count
    intEntry(int v, int c = 1);

    // return value
    int getValue() const;

    // return count
    int getCount() const;

    // increment count
    void increment();

    // compare lhs and rhs using value
    friend bool operator< (const intEntry& lhs, const intEntry& rhs);
    friend bool operator== (const intEntry& lhs, const intEntry& rhs);

    // output obj in format "value value ... value" (count times)
    friend ostream& operator<< (ostream& ostr, const intEntry& obj);

private:
    int value;
    // integer value
    int count;
    // number of occurrences of value
};

