//////////////////////////////////////////////////////////////////////////
//  Name:       Jeremy Nims
// Class:       CPS 272, Wed 5:30 PM
// Assignment:  MP3, Part 3 - Prime Factorization
//////////////////////////////////////////////////////////////////////////

#include <list>
#include <cmath>
#include "intEntry.h"

using namespace std;

// Calculates and returns the number represented by the primes list
int gcd(const list<intEntry>& primes);

// Clears, then fills primes list with prime numbers
void generatePrimeNumbers(list<int>& primes);

// Clears, then fills the primes list with the prime factors of n
void loadPrimes(list<intEntry>& primes, int n);

// Prints the prime factors stored in primeList
void printFactors(const list<intEntry>& primeList);

// Returns true if number is a prime number
bool isPrime(int number);

// Retrieves a number to factor into primes
int getInput();

// Returns a new list that contains the common prime factors of primes_1 and primes_2
list<intEntry> getCommonPrimes(const list<intEntry>& primes_1, const list<intEntry>& primes_2);

void main()
{
    int inputNumber_1, inputNumber_2, greatestFactor;
    list<intEntry> primeList_1, primeList_2, commonPrimesList;

    inputNumber_1 = getInput();
    inputNumber_2 = getInput();
    
    loadPrimes(primeList_1, inputNumber_1);
    loadPrimes(primeList_2, inputNumber_2);
    commonPrimesList = getCommonPrimes(primeList_1, primeList_2);
    greatestFactor = gcd(commonPrimesList);
    
    cout << endl << "Number " << inputNumber_1 << ": " << endl;
    printFactors(primeList_1);
    cout << endl << "Number " << inputNumber_2 << ": " << endl;
    printFactors(primeList_2);
    cout << endl
        << "The greatest common factor of "
        << inputNumber_1 << " and " << inputNumber_2
        << " is " << greatestFactor << endl;
    cout << "Number " << greatestFactor << ": " << endl;
    printFactors(commonPrimesList);
}

int gcd(const list<intEntry>& primes)
{
    int gcd = 1;
    for each (intEntry elem in primes)
        gcd *= pow(elem.getValue(), elem.getCount());
    return gcd;
}

void generatePrimeNumbers(list<int>& primes)
{
    // Make sure the list is empty
    primes.clear();

    // Add two manually so we can ignore even numbers in the loop for efficiency
    primes.push_back(2);

    // Every possible prime factor of MAX_NUMBER will be covered if we stop at ~sqrt
    // since any number received from input will be <= MAX_NUMBER
    for (int i = 3; i < sqrt(INT_MAX) + 1; i += 2)
        if (isPrime(i))
            primes.push_back(i);
}

void loadPrimes(list<intEntry>& primes, int n)
{
    // Keep a list of primes that we can use to test against 'n'
    // This method is not feasible if we use < 32-bit integers
    static list<int> primeNumbers;
    static bool isPrimeNumbersInitialized = false;
    if (!isPrimeNumbersInitialized)
    {
        // Fill the list with all the primes that could be factors of type int
        generatePrimeNumbers(primeNumbers);
        isPrimeNumbersInitialized = true;
    }
    primes.clear();
    for each (int elem in primeNumbers)
    {
        // If elem is a factor, push it to the list.
        if (n % elem == 0)
        {
            primes.push_back(elem);
            n /= elem;
        }
        else
            continue;
        // If elem is still a factor, increment the list element
        while (n % elem == 0)
        {
            primes.back().increment();
            n /= elem;
        }
        // Found all the factors; stop looking
        if (n == 1)
            break;
    }
    // If a number other than 1 remains in n, it must be prime since 
    // all other possible factors were tested -> push it to the list
    if (n != 1)
        primes.push_back(n);
}

void printFactors(const list<intEntry>& primeList)
{
    cout << "Prime Factors: ";
    for each (intEntry elem in primeList)
        cout << elem.getValue() << "^" << elem.getCount() << "    ";
    cout << "( ";
    for each (intEntry elem in primeList)
        cout << elem;
    cout << ')' << endl;
}

bool isPrime(int number)
{
    // Handle 2 manually so we can ignore even numbers in the loop for efficiency
    if (number == 2)
        return true;
    if (number % 2 == 0)
        return false;

    // - Every possible prime factor of 'number' will be covered if we stop at ~sqrt
    // - Skip even numbers for efficiency
    for (int i = 3; i < sqrt(number) + 1; i += 2)
        if (number % i == 0)
            return false;
    return true;
}

int getInput()
{
    long long inputNumber = 0;

    cout << "Please enter a positive integer less than " << INT_MAX << ": ";
    cin >> inputNumber;
    while (inputNumber > INT_MAX || inputNumber < 0 || cin.fail())
    {
        if (cin.fail())
            cin.clear();
        cout << "That is not a valid input." << endl <<
            "Please enter positive integer less than " << INT_MAX << ": ";
        cin.ignore(INT_MAX, '\n');
        cin >> inputNumber;
    }
    return (int)inputNumber;
}

list<intEntry> getCommonPrimes(const list<intEntry>& primes_1, const list<intEntry>& primes_2)
{
    list<intEntry> newList;
    for each (intEntry num_1 in primes_1)
    {
        for each (intEntry num_2 in primes_2)
        {
            if (num_1 == num_2)
            {
                intEntry temp(
                    num_1.getValue(),
                    num_1.getCount() < num_2.getCount() ?
                    num_1.getCount() :
                    num_2.getCount());
                newList.push_back(temp);
                // Found a match, go to the next number.
                break;
            }
        }
    }
    return newList;
}