#ifndef Trees_C
#define Trees_C

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



template <class Comparable>
int BinaryNode<Comparable>::height(BinaryNode<Comparable> * root){
    if (root == nullptr) {
        return 0;
    }
    else {
        int left_height = height(root->left);
        int right_height = height(root->right);
        return max(left_height, right_height) + 1;
    }
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const{
    if (this->root==nullptr){
        return true;
    }
    else{
        return false;
    }
}


template <class Comparable>
void BinarySearchTree<Comparable>::isBalanced()
{
    if (this->root!=nullptr){
        BinaryNode<Comparable> *rightptr = this->root->right;
        BinaryNode<Comparable> *leftptr = this->root->left;
        int right_max= 0;
        int left_max = 0;
        right_max = rightptr->height(rightptr);
        left_max = leftptr->height(leftptr);
        if (right_max == left_max){
            cout << "The tree is balanced" <<endl;
        }
        else{
            cout << "The tree is not balanced\nThe heights of BST are for left: "<<left_max<<" and right: "<<right_max<<endl;
        }
    }
}
/**
* Construct the tree.
*/
 template <class Comparable>
 BinarySearchTree<Comparable>::
 BinarySearchTree(const Comparable & notFound ) :
               ITEM_NOT_FOUND( notFound ), root( NULL )
 {
 }

/**
* Internal method to get element field in node t.
* Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::
elementAt( BinaryNode<Comparable> *t ) const
{
   return t == NULL ? ITEM_NOT_FOUND : t->element;
}
/**
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::find( const Comparable & x ) const
{
   return elementAt( find( x, root ) );
}


/**
* Internal method to find an item in a subtree.
* x is item to search for.
* t is the node that roots the tree.
* Return node containing the matched item.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::find( const Comparable & x, BinaryNode<Comparable> *t ) const
{
    while( t != nullptr )
        if( x < t->element )
            t = t->left;
        else if( t->element < x )
            t = t->right;
        else
            return t;    // Match

    return nullptr;   // No match
}

//search For bst

template <class Comparable>
void BinarySearchTree<Comparable>::search(const string& searchstr,int & check) {
    searchNode(root, searchstr,check);
}


template <class Comparable>
void BinarySearchTree<Comparable>::searchNode(BinaryNode<Comparable>* node, const string& searchstr,int & check) {
    if (node != nullptr) {
        string fullname = node->element.name + " " + node->element.lastname;
        searchNode(node->left,searchstr,check);
        if (fullname.substr(0,searchstr.length()) == searchstr){
            cout << node->element.name+node->element.lastname << endl;
            check++;
        }
        searchNode(node->right,searchstr,check);
    }
}







/**
  * Find the smallest item in the tree.
  * Return smallest item or ITEM_NOT_FOUND if empty.
  */
 template <class Comparable>
 const Comparable & BinarySearchTree<Comparable>::findMin( ) const
 {
     return elementAt( findMin( root ) );
 }

/**
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template <class Comparable>
BinaryNode<Comparable> *
BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) const
{
    if( t == nullptr )
        return nullptr;
    if( t->left == nullptr )
        return t;
    return findMin( t->left );
}
/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const
{
 return elementAt( findMax( root ) );
}



/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <class Comparable>
BinaryNode<Comparable> *
BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t ) const
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}

/**
** Internal method to insert into a subtree.
* x is the item to insert.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::insert( Comparable & x, BinaryNode<Comparable> * & t ,bool silent) const
{
    if( t == NULL ){
        //  create a new node at the right place
        t = new BinaryNode<Comparable>( x, NULL, NULL );
        if(!silent){
            cout << "Contact has been added successfully to the BST"<<endl;
        }
    }
    else if( x < t->element ){
        insert( x, t->left,silent );  // insert at the left or
    }
    else if( t->element < x ){
        insert( x, t->right,silent );  // right subtree
    }
    else{
        cout << "The given contact full name already exists in the database"<<endl;  // Duplicate; warn the user
    }
}
/**
* Insert x into the tree; duplicates are ignored.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::insert( Comparable & x ,bool silent)
{
    insert( x, root ,silent);
}




/**
* Remove x from the tree. Nothing is done if x is not found.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove
              ( const Comparable & x )
{
   remove( x, root );
}
/**
* Internal method to remove from a subtree.
* x is the item to remove.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x, BinaryNode<Comparable> * & t ) const
{
   if( t == NULL )
       return;   // Item not found; do nothing
   if( x < t->element )
       remove( x, t->left );
   else if( t->element < x )
       remove( x, t->right );
   else if( t->left != NULL && t->right != NULL ) // Two children
     {
         t->element = findMin( t->right )->element;
         remove( t->element, t->right );
     }
     else // one or no children
     {
         BinaryNode<Comparable> *oldNode = t;
         t = ( t->left != NULL ) ? t->left : t->right;
         delete oldNode;
     }
 }
/**
* Make the tree logically empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )
{
     makeEmpty( root );
}


/**
* Internal method to make subtree empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::
makeEmpty( BinaryNode<Comparable> * & t ) const
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}





/**
* Destructor for the tree.
*/
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
 makeEmpty( );
}
/**
* Copy constructor.
*/
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :
     root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
   *this = rhs;
}

//======================================================================
//AVL ==================================================================
//======================================================================
//The find, findMin , findMax , makeEmpty, operator=, printTree are like bst work on it.
template <class Comparable>
int hash(const Comparable & key, int tableSize)
{
    string Fullname= key->name + key->lastname; //takes fullnamestring
    int hashVal = 0;
  
    for (int i = 0; i < Fullname.length();i++)
      hashVal = 37 * hashVal + Fullname[ i ];

    hashVal = hashVal % tableSize;

    if (hashVal < 0)
        hashVal = hashVal + tableSize;
    return(hashVal);
}


/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
inline bool isPrime( int n )
{
    if ( n == 2 || n == 3 )
        return true;

    if ( n == 1 || n % 2 == 0 )
        return false;

    for ( int i = 3; i * i <= n; i += 2 )
         if ( n % i == 0 )
             return false;

    return true;
}

/**
* Internal method to return a prime number
* at least as large as n.  Assumes n > 0.
*/
inline int nextPrime( int n )
{
     if ( n % 2 == 0 )
         n++;

     for ( ; ! isPrime( n ); n += 2 )
          ;

     return n;
}
template <class HashedObj>
int HashTable<HashedObj>::getsize()
{
    return currentSize;
}
/**
* Make the hash table logically empty.
*/
template <class HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    for (int i = 0; i < array.size(); i++)
    {
        if (array[i].info == ACTIVE)
        {
            delete array[i].element;
        }
        array[i].info = EMPTY;
    }
    currentSize = 0;
    // destroy the lists but not the vector!
}


/**
 * Construct the hash table.
 */
template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound,
                                      int size )
          : ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
{
       makeEmpty( );
}



/**
* Return true if currentPos exists and is active.
*/
template <class HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos ) const
{
     return array[ currentPos ].info == ACTIVE;
}

/**
 * Remove item x from the hash table.
 *  x has to be in the table
 */
template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
{
    int currentPos = findPos( x );
    cout << currentPos<<endl;
    cout << isActive( currentPos )<<endl;
    if ( isActive( currentPos ) ){
        array[ currentPos ].info = DELETED;
        currentSize--;
    }
}

/**
 * Find item x in the hash table.
 * Return the matching item, or ITEM_NOT_FOUND, if not found.
 */
template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find( const HashedObj & x )const
{
     int currentPos = findPos( x );
     if (isActive( currentPos ))
          return array[ currentPos ].element;
     return   ITEM_NOT_FOUND;
}
/**
 * Method that performs quadratic probing resolution.
 * Return the position where the search for x terminates.
 */
template <class HashedObj>
int HashTable<HashedObj>::findPos( const HashedObj & x ) const
{
       int collisionNum = 0;
       int currentPos = ::hash( x, array.size( ) );

       while (array[currentPos].info != EMPTY && (array[currentPos].element->name != x->name || array[currentPos].element->lastname != x->lastname))
       {
            currentPos += pow(++collisionNum, 2) ;  //add the difference
            if (currentPos >= array.size( ))              // perform the mod
                currentPos -= array.size( );                // if necessary
       }
       return currentPos;
}

/**
  * Insert item x into the hash table. If the item is
  * already present, then do nothing.
  */
template <class HashedObj>
void HashTable<HashedObj>::insert( HashedObj & x )
{
    // Insert x as active
    int currentPos = findPos( x );
    if ( isActive( currentPos ) ){
        return;
    }
    array[ currentPos ] = HashEntry( x, ACTIVE );
    cout << x->name << currentPos;
    // enlarge the hash table if necessary
    if ( ++currentSize >= array.size( ) / 2 ){
        rehash( );
    }
}

/**
 * Expand the hash table.
 */
template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{
    vector<HashEntry> oldArray = array;
    cout << "rehashed..."<<endl;
    // Create new double-sized, empty table
    array.resize( nextPrime( 2 * oldArray.size( ) ) );
    for ( int j = 0; j < array.size( ); j++ )
         array[ j ].info = EMPTY;

    // Copy table over
    currentSize = 0;
    for ( int i = 0; i < oldArray.size( ); i++ )
        if ( oldArray[ i ].info == ACTIVE ){
            insert( oldArray[ i ].element );
        }
}


#endif
