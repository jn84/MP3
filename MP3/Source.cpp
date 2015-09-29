#include <list>
#include <cmath>
#include "intEntry.h"

using namespace std;

const int MAX_NUMBER = INT_MAX;

void loadPrimes(list<intEntry>& primes, int n);
void generatePrimeNumbers(list<int>& primes);
bool isPrime(int number);

void main()
{
    list<intEntry> primeList_1, primeList_2;

    loadPrimes(primeList_1, 23852892);
    loadPrimes(primeList_2, 2328592);
    for each (intEntry elem in primeList_1)
        cout << elem;
    cout << endl;
    for each (intEntry elem in primeList_2)
        cout << elem;
    cout << endl;
}

void loadPrimes(list<intEntry>& primes, int n)
{
    static list<int> primeNumbers;
    static bool isPrimeNumbersInitialized = false;
    if (!isPrimeNumbersInitialized)
    {
        // Fill the list with all the primes that could be factors of type int
        generatePrimeNumbers(primeNumbers);
        isPrimeNumbersInitialized = true;
    }
    for each  (int elem in primeNumbers)
    {
        if (n % elem == 0)
        {
            primes.push_back({ elem });
            n /= elem;
        }
        else
            continue;
        while (n % elem == 0)
        {
            primes.back().increment();
            n /= elem;
        }
        if (n == 1)
            break;
    }
}

// Build a list of prime numbers so we don't have to run through and find them every time.
void generatePrimeNumbers(list<int>& primes)
{
    // Make sure the list is empty
    primes.clear();

    // Add two manually so we can ignore even numbers in the loop for efficiency
    primes.push_back(2);

    // Every possible prime factor of MAX_NUMBER will be covered if we stop at ~sqrt
    // since any number received from input will be <= MAX_NUMBER
    for (int i = 3; i < sqrt(MAX_NUMBER) + 1; i += 2)
        if (isPrime(i))
            primes.push_back(i);
}

bool isPrime(int number)
{
    // Handle two manually so we can ignore even numbers in the loop for efficiency
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