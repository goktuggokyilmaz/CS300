#ifndef Trees_H
#define Trees_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Person{
    string name;
    string lastname;
    string phonenumber;
    string city;
    Person(){
    }
    Person(string nm,string lm,string pn,string cn){
        name = nm;
        lastname = lm;
        phonenumber = pn;
        city = cn;
    }
    bool operator<(const Person& other) const {
        return name + lastname < other.name + other.lastname;
    }
    bool operator>(const Person& other) const {
        return name + lastname > other.name + other.lastname;
    }
    bool operator==(const Person& other) const {
        return name + lastname == other.name + other.lastname;
    }
    bool operator!=(const Person& other) const
    {
        return ! (name + lastname == other.name + other.lastname);
    }
    
};

ostream& operator<<(ostream& os, const Person& prs) {
    os << prs.name << " " <<prs.lastname<< " "<< prs.phonenumber<<" "<< prs.city;
    return os;
}


//BST
template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
    Comparable element; //person
    BinaryNode  *left;
    BinaryNode  *right;

    int height(BinaryNode<Comparable> * root);

    BinaryNode( const Comparable & theElement,
              BinaryNode *lt, BinaryNode *rt )
               : element( theElement ), left( lt ), right( rt ) { }
            
    friend class BinarySearchTree<Comparable>;

};

//The find, findMin , findMax , makeEmpty, operator=, printTree are like bst work on it.

template <class Comparable>
class BinarySearchTree
{
    public:
        explicit BinarySearchTree( const Comparable & notFound );
        BinarySearchTree( const BinarySearchTree & rhs );
        ~BinarySearchTree( );

        const Comparable & findMin( ) const;
        const Comparable & findMax( ) const;
        const Comparable & find( const Comparable & x ) const;
        bool isEmpty( ) const;
        void isBalanced();
        void makeEmpty( );
        void insert( Comparable & x ,bool silent);
        void remove( const Comparable & x );
        void search(const string& searchstr,int& check);
        const BinarySearchTree & operator=( const BinarySearchTree & rhs );
    private: //private
        BinaryNode<Comparable> *root;
        const Comparable ITEM_NOT_FOUND;
        void searchNode(BinaryNode<Comparable>* node, const string& searchstr,int& check);

        const Comparable & elementAt( BinaryNode<Comparable> *t ) const;

        void insert( Comparable & x, BinaryNode<Comparable> * & t ,bool silent) const;
        void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
        BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
        BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
        BinaryNode<Comparable> * find( const Comparable & x,BinaryNode<Comparable> *t ) const;
        void makeEmpty( BinaryNode<Comparable> * & t ) const;
};
//Hashtable

template <class HashedObj>
class HashTable{
    public:
        explicit HashTable( const HashedObj & notFound, int size = 53 );
        HashTable( const HashTable & rhs )
        : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
        array( rhs.array ), currentSize( rhs.currentSize ) { }
        
        const HashedObj & find( const HashedObj & x ) const;
        
        void makeEmpty();
        void insert( HashedObj & x );
        void remove( const HashedObj & x );
        int getsize();
        
        const HashTable & operator=( const HashTable & rhs );
        
        enum EntryType { ACTIVE, EMPTY, DELETED };
        
    private:
        struct HashEntry
        {
            HashedObj element;
            EntryType info;
            
            HashEntry( const HashedObj & e = HashedObj( ),EntryType i = EMPTY ): element( e ), info( i ) { }
        };
        
        vector<HashEntry> array;
        int currentSize;
        const HashedObj ITEM_NOT_FOUND;
        
        bool isActive( int currentPos ) const;
        int findPos( const HashedObj & x ) const;
        void rehash( );
};

#endif
