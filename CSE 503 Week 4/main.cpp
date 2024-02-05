//
//  main.cpp
//  CSE 503 Week 4
//
//  Created by Alex Myers on 2/5/24.
//

#include<iostream>

const int TABLE_SIZE = 7;

class HashEntry {
private:
    int key;
    int value;
    
public:
    HashEntry(int key, int value) : key(key), value(value) {}
    
    int getKey() const {
        return key;
    }
    
    int& getValue() {
        return value;
    }
};

class HashMap {
private:
    HashEntry **table;
    int currentSize = 0;
    int tableSize;
public:
    HashMap() : tableSize(TABLE_SIZE) {
        table = new HashEntry*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = NULL;
    }
    
    int get(int key) {
        int hash = (key % tableSize);
        
        while (table[hash] != NULL && table[hash]->getKey() != key)
            hash = (hash + 1) % tableSize;
        if (table[hash] == NULL)
            return hash;
        else
            return -1;
    }
    
    void insert(int value) {
        int hash = get(value);
        
        if(hash != -1){
            table[hash] = new HashEntry(hash, value);
            currentSize++;
        }
        else if(hash == -1){
            table[hash]->getValue() = value;
        }
        if (currentSize > tableSize / 2) {
            std::cout << "BEFORE Rehash: " << std::endl;
            print();
            rehash();
            std::cout << "Rehashed table: " << tableSize << std::endl;
            print();
        }
        
    }
    
    void print() {
        for (int i = 0; i < tableSize; ++i) {
            if (table[i] != NULL) {
                std::cout << "Key: " << table[i]->getKey() << ", Value: " << table[i]->getValue() << std::endl;
            }
        }
        std::cout<< "Hash Table Current Size: " << currentSize << std::endl;
    }
    int myhash(const int & x) const
    {
        int hashVal = 5 * x + 2;
        
        hashVal %= tableSize;
        if (hashVal < 0)
            hashVal += tableSize;
        
        return hashVal;
    }
    
    void rehash() {
        int oldSize = tableSize;
        HashEntry **oldTable = table;
        
        tableSize = nextPrime(2 * oldSize);
        table = new HashEntry*[tableSize];
        currentSize = 0;
        
        for (int i = 0; i < tableSize; i++)
            table[i] = NULL;
        
        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != NULL) {
                insert(oldTable[i]->getValue());
                delete oldTable[i];
            }
        }
        
        delete[] oldTable;
    }
    
    
    
    bool isPrime(int n)
    {
        if (n == 2 || n == 3)
            return true;
        
        if (n == 1 || n % 2 == 0)
            return false;
        
        for (int i = 3; i * i <= n; i += 2)
            if (n % i == 0)
                return false;
        
        return true;
    }
    
    int nextPrime(int n)
    {
        if (n <= 0)
            n = 3;
        
        if (n % 2 == 0)
            n++;
        
        for (; !isPrime(n); n += 2)
            ;
        
        return n;
    }
    
    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (table[i] != NULL)
                delete table[i];
        delete[] table;
    }
};

int main(int argc, const char * argv[])
{
    HashMap Kirsten;
    Kirsten.insert(138);
    Kirsten.insert(99);
    Kirsten.insert(16);
    Kirsten.insert(134);
    Kirsten.insert(42);
    Kirsten.insert(0);
    Kirsten.insert(6);
    Kirsten.insert(9);
    Kirsten.insert(4);
    Kirsten.insert(53);
    Kirsten.insert(47);
    Kirsten.insert(66);
    std::cout << "Printed Hash Table: " << std::endl;
    Kirsten.print();
}

