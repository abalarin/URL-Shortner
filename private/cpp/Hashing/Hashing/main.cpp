//
//  main.cpp
//  Hashing
//
//  Created by Austin Balarin on 11/14/16.
//  Copyright © 2016 Austin Balarin. All rights reserved.
//

#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

template <typename KEY, typename VALUE>
class Entry
{
    template<typename K, typename V> friend class HashTable;
    
private:
    KEY key;
    VALUE value;
    Entry * next_entry;
    
public:
    /*** Constructors ***/
    Entry(void) : key(KEY()), value(VALUE()), next_entry(NULL) {}
    Entry(KEY key, VALUE value) : key(key), value(value), next_entry(NULL) {}
    Entry(KEY key, VALUE value, Entry * next) : key(key), value(value), next_entry(next) {}
    
    //accessors
    KEY get_key() { return key; }
    VALUE get_value() { return value; }
    Entry * get_next_entry() { return next_entry; }
    
    //mutators
    //void set_key(KEY key) { this.key = key; }
    //void set_value(VALUE value) { this.value = value; }
    //void set_next_entry(Entry * entry) { this.next_entry = entry; }
    
};

template<typename K, typename V>
class HashTable
{
private:
    int N;
    Entry<K, V> **hash_table; //Make sure you understand this line
    
public:
    HashTable()
    {
        this->N = 10000;
        hash_table = new Entry<K, V> *[this->N];
        
        for (int i = 0; i < this->N; i++)
            hash_table[i] = NULL;
    }
    
    HashTable(int N)
    {
        this->N = N;
        hash_table = new Entry<K, V> *[this->N];
        
        for (int i = 0; i < this->N; i++)
            hash_table[i] = NULL;
    }
    
    /* hashcose string to int */
    int hashcode(string s)
    {
        //This hash function is just a mimick from what
        //you taught in class
        int hv = 0;
        for (int i = 0; i < s.length(); i++)
            hv = (127 * hv + s[i]) % 16908799;
        
        cout << "string: " << hv << endl;
        cout << "string: " << compression(hv) << endl;
        return hv = compression(hv);
    }
    
    /* hashcode int to int */
    int hashcode(int i)
    {
        /*Using Knuth's multiplication theroy*/
        cout << "num: "<<  i * pow(2,32);
        return i = i * pow(2,32);
    }
    
    /* hascode char to int */
    int hashcode(char c)
    {
        //Simple hash function takes ascii value
        //and compresses it
        int ascii = (int)c;
        cout << "char: "<< compression(ascii);
        return ascii = compression(ascii);
    }
    
    /* hascode long to int */
    int hashcode(unsigned long ul)
    {
        /*Roberts Jenkins 32 bit integer hash function*/
        ul = (ul + 0x7ed55d16) + (ul << 12);
        ul = (ul ^ 0xc761c23c) ^ (ul >> 19);
        ul = (ul + 0x165667b1) + (ul << 5);
        ul = (ul + 0xd3a2646c) ^ (ul << 9);
        ul = (ul + 0xfd7046c5) + (ul << 3);
        ul = (ul ^ 0xb55a4f09) ^ (ul >> 16);
        return ul = compression(ul);
    }
    
    /* basic compression function */
    int compression(int hc)
    {
        //Just takes the hashcode and
        //return mod of total size of array
        return hc % N;
    }
    
    /* insert e into hash table */
    void insert(Entry<K, V> * e)
    {
        /*is the index supposed to be the hashcode of the key or value?*/
        int index = hashcode(e->value);
        cout << "i: " << index << endl;
        //Case 0: Bucket is empty
        if (hash_table[index] == NULL)
            hash_table[index] = e;
        
        //Case 1: Bucket has atleast 1 item
        else
        {
            Entry<K, V> * p = hash_table[index];
            while (p->next_entry != NULL)
                p = p->next_entry;
            p->next_entry = e;
        }
    }
    
    /* replace e1 with e2 */
    void replace(Entry<K, V> * e1, Entry<K, V> * e2)
    {
        //Check to see if pointer is NULL
        if (e1 == NULL)
        {
            cout << "error: Pointer is NULL" << endl;
            return;
        }
        
        int index = hashcode(e1->value);
        Entry<K, V> * p = hash_table[index];
        Entry<K, V> * p2 = hash_table[index];
        
        //Case 0: Entry does not exsist
        if (hash_table[index] == NULL)
        {
            cout << "error: Entry to be replaced does not exsist.";
            return;
        }
        
        //Case 1: Item found and is only item in bucket
        else if (p == e1 && p->next_entry == NULL)
        {
            hash_table[index] = e2;
            delete e1;
        }
        
        //Case 2: Multiple items in bucket and item found is first in bucket
        else if (p == e1)
        {
            p = p->next_entry;
            hash_table[index] = hash_table[index]->next_entry = e2;
            e2->next_entry = p;
            delete e1;
        }
        
        //Case 3: Multiple items in bucket and item found
        //but is not first item in bucket
        else
        {
            p2 = p;
            p = p->next_entry;
            while (p != NULL && p->key != e1->key)
            {
                p2 = p;
                p = p->next_entry;
            }
            //Case 3.1: no match
            if (p == NULL)
                cout << "error: Item to be removed not found." << endl;
            //Case 3.2: match found
            else
            {
                cout << "p2: "<<p2->key<<endl;
                p2->next_entry = e2;
                e2->next_entry = p->next_entry;
                delete e1;
            }
        }
    }
    
    /* find e and return */
    Entry<K, V> * find(Entry<K, V> * e)
    {
        int index = hashcode(e->value);
        Entry<K, V> * p = hash_table[index];
        
        //Case 0: Entry not found
        if (hash_table[index] == NULL)
        {
            cout << "error: No index found matching entry hash.";
            return NULL;
        }
        
        //Case 1: Entry hash matches with exsiting index of a
        //buckets with entries
        else
        {
            while (p != NULL && p->key != e->key)
                p = p->next_entry;
            
            //Case 1.1: No items matching requested item in bucket
            if (p == NULL)
            {
                cout << "error: No items matching requested item in bucket.";
                return NULL;
            }
            //Case 1.2: Item found
            else
                return p;
        }
    }
    
    /* remove e from the table */
    void remove(Entry<K, V> * e)
    {
        //Check to see if pointer is NULL
        if (e == NULL)
        {
            cout << "error: Pointer is NULL" << endl;
            return;
        }
        
        int index = hashcode(e->value);
        Entry<K, V> * p1 = hash_table[index];
        Entry<K, V> * p2;
        
        
        //Case 0: Entry does not exsist
        if (hash_table[index] == NULL)
            cout << "error: Item to be removed not found.";
        
        //Case 1: Item found and is only item in bucket
        else if (p1 == e && p1->next_entry == NULL)
            hash_table[index] = NULL;
        
        //Case 2: Multiple items in list and item found is first in list
        else if (p1 == e)
        {
            p1 = p1->next_entry;
            hash_table[index] = hash_table[index]->next_entry = p1;
            delete e;
        }
        
        //Case 3: Multiple items in list and item found
        //but is not first item in list
        else
        {
            p2 = p1;
            p1 = p1->next_entry;
            while (p1 != NULL && p1->key != e->key)
            {
                p2 = p1;
                p1 = p1->next_entry;
            }
            //Case 3.1: no match
            if (p1 == NULL)
                cout << "error: Item to be removed not found." << endl;
            //Case 3.2: match found
            else
            {
                e = p1;
                p1 = p1->next_entry;
                p2->next_entry = p1;
                
                delete e;
            }
        }
    }
    
    /* if grow = 1 increase the table
     * otherwise decrease the table
     */
    void resize(bool grow)
    {
        cout << endl << endl;
        Entry<K, V> * e;
        
        //Case 0: Double the size of hash_table
        if (grow)
        {
            HashTable<K, V> new_table(N * 2);
            
            for (int i = 0; i < N; i++)
            {
                e = hash_table[i];
                while (e != NULL)
                {
                    new_table.insert(e);
                    e = e->next_entry;
                }
            }
        }
        //Case 1: Shrink size of hash_table by half
        else
        {
            HashTable<K, V> new_table(N / 2);
            
            for (int i = 0; i < N; i++)
            {
                e = hash_table[i];
                while (e != NULL)
                {
                    new_table.insert(e);
                    e = e->next_entry;
                }
            }
        }
    }
    
    double compute_load_factor()
    {
        double number_of_entries = 0;
        
        //Finds total number of items inputed into hash_table
        for (int i = 0; i < N; i++)
            number_of_entries += items_in_bucket(i);
        
        double size_of_array = N;
        double loadFactor = number_of_entries / size_of_array;
        
        return loadFactor;
    }
    
    /*find number of entries in bucket*/
    int items_in_bucket(int index)
    {
        int count = 0;
        Entry<K,V> * e = hash_table[index];
        
        //Case 0: No entries in bucket
        if (e==NULL)
            return count;
        
        //Case 1: One or more entries in bucket
        else
        {
            count++;
            while (e->next_entry != NULL)
            {
                count++;
                e = e->next_entry;
            }
        }
        return count;
    }
    
    /* find the longest chain */
    int longest_chain_length()
    {
        int longestChain = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (items_in_bucket(i) > items_in_bucket(j))
                    longestChain = items_in_bucket(i);
            }
        }
        return longestChain;
    }
    
    /* a not so neat print func (used to test code)*/
    void print()
    {
        for (int i = 0; i < N; i++)
        {
            Entry<K, V> * e = hash_table[i];
            cout << "---------------" << endl;
            if (e != NULL)
            {
                cout << "Key: " << e->key << "\nValue: " << e->value << "\nItems in bucket: " << items_in_bucket(i) << endl;
                while (e->next_entry != NULL)
                {
                    cout << "\tKey: " << e->key << "\n\tValue: " << e->value << endl;
                    e = e->next_entry;
                }
                cout << "\tKey: " << e->key << "\n\tValue: " << e->value << endl;
            }
            else
                cout << "Key: empty" << "\nValue: empty" << "\nItems in bucket: " << items_in_bucket(i) << endl;
            cout << "---------------" << endl;
        }
    }
};// End class Hash Table

/* I recomend you make a temp main for testing all of your boundry
 * cases.  I reserve the right to change the main function.  I promise
 * it will only call the function prototypes provided; which means, you
 * cannot change the prototypes.
 */
int main()
{
    /*
    HashTable<int, string> table_01(6);
     Entry<int, string> * e;
     Entry<int, string> * e1;
     
     e1 = new Entry<int, string>(34, "austin");
     table_01.insert(e1);
     e = new Entry<int, string>(22, "mark");
     table_01.insert(e);
     e = new Entry<int, string>(3244, "tyler");
     table_01.insert(e);
     e = new Entry<int, string>(234, "izzy");
     table_01.insert(e);
     e = new Entry<int, string>(785, "lake");
     table_01.insert(e);
     table_01.remove(e1);
     cout << "Longest Chain: " << table_01.longest_chain_length() << endl;
     
     //cout << "Found: " << func.find(func);
    */
    
    //seed the random number generator	
    srand(42);
    
    HashTable<unsigned long, string>  table_01(20);
    unsigned long key;
    string value;
    Entry<unsigned long, string> * e;
    //e = new Entry<unsigned long, string>()
    // Fill the table with random entries
    for (int i = 0; i < 10; i++)
    {
        //create a random entry 
        key = (sizeof(int) < sizeof(long)) ? (static_cast<int>(((unsigned long)rand()) << (sizeof(int)* 8)) | rand()) : rand();
        value = "";
        for (int j = 0; j < (rand() % 45 + 1); j++)
            value += 'a' + rand() % 26;
        cout<< "key: " << key << endl;
        e = new Entry<unsigned long, string>(key, value);
        
        table_01.insert(e);
    }
    table_01.print();
    cout << "Longest Chain: " << table_01.longest_chain_length() << endl;
    cout << "Load Factor: " << table_01.compute_load_factor() << endl;
    
    return 0;
}
