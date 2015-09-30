//////////////////////////////////////////////////////////////////////////
//  Name:       Jeremy Nims
// Class:       CPS 272, Wed 5:30 PM
// Assignment:  MP3, Part 3 - Prime Factorization
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <iostream>

using namespace std;

class intEntry
{
private:
    int value;
    // integer value

    int count;
    // number of occurrences of value

public:
    // initialize the integer value and its count
    intEntry(int v, int c = 1)
    {
        value = v;
        count = c;
    }

    // return value
    int getValue() const
    {
        return value;
    }

    // return count
    int getCount() const
    {
        return count;
    }

    // increment count
    void increment()
    {
        count++;
    }

    // compare lhs and rhs using value
    friend bool operator< (const intEntry& lhs, const intEntry& rhs) // Never used?
    {
        return lhs.value < rhs.value;
    }

    friend bool operator== (const intEntry& lhs, const intEntry& rhs)
    {
        return lhs.value == rhs.value;
    }

    // output obj in format "value value ... value" (count times)
    friend ostream& operator<< (ostream& ostr, const intEntry& obj);
};

ostream& operator<< (ostream& ostr, const intEntry& obj)
{
    for (int i = 0; i < obj.count; i++)
        ostr << obj.value << " ";
    return ostr;
}

