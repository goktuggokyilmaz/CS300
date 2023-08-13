#include <string>
#include <iostream>
using namespace std;
#ifndef Trees_H
#define Trees_H

struct Person{
    string name;
    string lastname;
    string phonenumber;
    string city;
    Person(string nm,string lm,string pn,string cn){
        name = nm;
        lastname = lm;
        phonenumber = pn;
        city = cn;
    }
    bool operator<(const Person& other) const {
        return name+lastname < other.name+other.lastname;
    }
    bool operator>(const Person& other) const {
        return name+lastname > other.name+other.lastname;
    }
    bool operator==(const Person& other) const {
        return name+lastname == other.name+other.lastname;
    }
};



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
        void printTree(const unsigned short num,ofstream &ostr) const; //num = 0 for preOrder //  1 for Inorder

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
        void printPreTree( BinaryNode<Comparable> *t ,ofstream &ostr) const;
        void printInTree( BinaryNode<Comparable> *t ,ofstream &ostr) const;
        void drawTree(BinaryNode<Comparable> *t, ofstream &ostr, string prefix ,bool isTail) const;
};
//AVL
template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode
{
    Comparable     element;
    AvlNode           *left;
    AvlNode           *right;
    int                height;
    AvlNode( const Comparable & theElement,
    AvlNode *lt, AvlNode *rt, int h = 0 )
    : element( theElement ), left( lt ), right( rt ), height( h ) { }

    friend class AvlTree<Comparable>;
};


template <class Comparable>
class AvlTree
{
    public:
        explicit AvlTree( const Comparable & notFound );
        AvlTree( const AvlTree & rhs );
       ~AvlTree( );

        const Comparable & findMin( ) const;
        const Comparable & findMax( ) const;
        const Comparable & find( const Comparable & x ) const;
        bool isEmpty( ) const;
        void printTree(const unsigned short num,ofstream &ostr) const; //num = 0 for preOrder //  1 for Inorder
        void makeEmpty( );
        void insert( const Comparable & x ,bool silent);
        void remove( const Comparable & x );
        void search(const string& searchstr,int& check);
        const AvlTree & operator=( const AvlTree & rhs );
    
        void isBalanced();
        AvlNode<Comparable>* getroot();
    private:
        AvlNode<Comparable> *root;
        const Comparable ITEM_NOT_FOUND;

        const Comparable & elementAt( AvlNode<Comparable> *t ) const;

        void insert( const Comparable & x, AvlNode<Comparable> * & t, bool silent) const;
        void remove(const Comparable & x, AvlNode<Comparable> * & t ) const;
        void updateHeight(AvlNode<Comparable> *t) const;
        void searchNode(AvlNode<Comparable>* node, const string& searchstr,int& check);
        AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) const;
        AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) const;
        AvlNode<Comparable> * find( const Comparable & x, AvlNode<Comparable> *t )const;
        void makeEmpty( AvlNode<Comparable> * & t ) const;
        AvlNode<Comparable> * clone( AvlNode<Comparable> *t ) const;
        // Avl manipulations
        int height( AvlNode<Comparable> *t ) const;
        void balance(AvlNode<Comparable> * & t) const;
        int max( int lhs, int rhs ) const;
        void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const;
        void rotateWithRightChild( AvlNode<Comparable> * & k1 ) const;
        void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const;
        void doubleWithRightChild( AvlNode<Comparable> * & k1 ) const;
    
        void printPreTree( AvlNode<Comparable> *t ,ofstream &ostr) const;
        void printInTree( AvlNode<Comparable> *t ,ofstream &ostr) const;
        void drawTree(AvlNode<Comparable> *t, ofstream &ostr, string prefix,bool isTail) const;
};


#endif
