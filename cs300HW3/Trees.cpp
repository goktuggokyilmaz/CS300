#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
using namespace std;

#include "Trees.h"

inline ostream& operator<<(ostream& os, const Person prs) { //without inline I get duplicate error so I figure out I should use inline keyword
    os << prs.name << " " <<prs.lastname<< " "<< prs.phonenumber<<" "<< prs.city;
    return os;
}

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
            cout << node->element << endl;
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
 * Print the tree contents in sorted order.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::printTree(const unsigned short num,ofstream &ostr ) const
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    else{
        if (num == 0){ //preorder
            printPreTree( root , ostr);
        }
        else if (num == 1){ //postorder
            printInTree( root , ostr);
        }
        else if (num == 2){ //drawtree
            drawTree( root , ostr,"",true);
        }
        else{
            cout << "number inside function is wrong" << endl;
        }
    }
}



/**
* Internal method to print a subtree rooted at t in sorted order.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::printPreTree( BinaryNode<Comparable> * t,ofstream &ostr) const
{
    if ( t != NULL )
    {
        ostr << t->element << endl;
        printPreTree( t->left ,ostr);
        printPreTree( t->right ,ostr);
    }
}

template <class Comparable>
void BinarySearchTree<Comparable>::printInTree( BinaryNode<Comparable> * t ,ofstream &ostr) const
{
    if ( t != NULL )
    {
        printInTree( t->left ,ostr);
        ostr << t->element << endl;
        printInTree( t->right ,ostr);
    }
}

template <class Comparable>
void BinarySearchTree<Comparable>::drawTree(BinaryNode<Comparable> *t, ofstream &ostr, string prefix ,bool isTail) const
{
    if (t != nullptr) {
        ostr << prefix;

        if (isTail) {
            ostr << "|__";
            prefix += "   ";
        } else {
            ostr << "|--";
            prefix += "|  ";
        }

        ostr << t->element.name << " " << t->element.lastname << endl;

        drawTree(t->left, ostr, prefix , t->right == nullptr);
        drawTree(t->right, ostr, prefix , true);
    }
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

// Constructor
template <class Comparable>
AvlTree<Comparable>::AvlTree(const Comparable &notFound)
    : root(nullptr), ITEM_NOT_FOUND(notFound)
{
}

// Copy constructor
template <class Comparable>
AvlTree<Comparable>::AvlTree(const AvlTree &rhs)
    : root(nullptr), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{
    root = clone(rhs.root);
}

// Destructor
template <class Comparable>
AvlTree<Comparable>::~AvlTree()
{
    makeEmpty(root);
}

// Public member functions

// Find the smallest element in the tree
template <class Comparable>
const Comparable &AvlTree<Comparable>::findMin() const
{
    if (isEmpty())
        return ITEM_NOT_FOUND;

    AvlNode<Comparable> *minNode = findMin(root);
    return minNode->element;
}

// Find the largest element in the tree
template <class Comparable>
const Comparable &AvlTree<Comparable>::findMax() const
{
    if (isEmpty())
        return ITEM_NOT_FOUND;

    AvlNode<Comparable> *maxNode = findMax(root);
    return maxNode->element;
}

// Find an element in the tree
template <class Comparable>
const Comparable &AvlTree<Comparable>::find(const Comparable &x) const
{
    AvlNode<Comparable> *foundNode = find(x, root);

    if (foundNode == nullptr)
        return ITEM_NOT_FOUND;

    return foundNode->element;
}

// Check if the tree is empty
template <class Comparable>
bool AvlTree<Comparable>::isEmpty() const
{
    return root == nullptr;
}

// Make the tree empty
template <class Comparable>
void AvlTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}

// Insert an element into the tree
template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable &x,bool silent)
{
    insert(x, root,silent);
}

// Remove an element from the tree
template <class Comparable>
void AvlTree<Comparable>::remove(const Comparable &x)
{
    remove(x, root);
}

// Assignment operator
template <class Comparable>
const AvlTree<Comparable> &AvlTree<Comparable>::operator=(const AvlTree &rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        ITEM_NOT_FOUND = rhs.ITEM_NOT_FOUND;
        root = clone(rhs.root);
    }
    return *this;
}

// Check if the tree is balanced
template <class Comparable>
void AvlTree<Comparable>::isBalanced()
{
    if (getroot()!=nullptr && getroot()->left!=nullptr&& getroot()->right!=nullptr){
        if (getroot()->left->height - getroot()->right->height > -2 && getroot()->left->height - getroot()->right->height <2){
            cout << "The tree is balanced"<<endl;
        }
        else{
            cout << "The tree is not balanced"<<endl;
        }
        cout <<"The heights of AVL are for left: " <<getroot()->left->height+1<< " and right: " <<getroot()->right->height+1 << endl;
    }
}

// Get the root node of the tree
template <class Comparable>
AvlNode<Comparable> *AvlTree<Comparable>::getroot()
{
    return root;
}

// Private member functions

// Return the element contained in the given node
template <class Comparable>
const Comparable &AvlTree<Comparable>::elementAt(AvlNode<Comparable> *t) const
{
    if (t == nullptr)
        return ITEM_NOT_FOUND;

    return t->element;
}

// Insert an element into the tree
template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable &x, AvlNode<Comparable> *&t,bool silent) const
{
    if (t == nullptr){
        t = new AvlNode<Comparable>(x, nullptr, nullptr);
        if(!silent){
            cout << "Contact has been added successfully to the AVL Tree"<<endl;
        }
    }
    else if (x < t->element)
    {
        insert(x, t->left,silent);
        balance(t);
    }
    else if (t->element < x)
    {
        insert(x, t->right,silent);
        balance(t);
    }
    else
    cout << "The given contact full name already exists in the database"<<endl;// Duplicate; give error
}

// Remove an element from the tree
template <class Comparable>
void AvlTree<Comparable>::remove(const Comparable &x, AvlNode<Comparable> *&t) const
{
    if (t == nullptr)
        return;  // Item not found; do nothing

    if (x < t->element)
    {
        remove(x, t->left);
        balance(t);
    }
    else if (t->element < x)
    {
        remove(x, t->right);
        balance(t);
    }
    else if (t->left != nullptr && t->right != nullptr)  // Two children
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
        balance(t);
    }
    else
    {
        AvlNode<Comparable> *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}

// Find the minimum element in the subtree rooted at t
template <class Comparable>
AvlNode<Comparable> *AvlTree<Comparable>::findMin(AvlNode<Comparable> *t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}

// Find the maximum element in the subtree rooted at t
template <class Comparable>
AvlNode<Comparable> *AvlTree<Comparable>::findMax(AvlNode<Comparable> *t) const
{
    if (t != nullptr)
    {
        while (t->right != nullptr)
            t = t->right;
    }
    return t;
}

// Find an element x in the subtree rooted at t
template <class Comparable>
AvlNode<Comparable> *AvlTree<Comparable>::find(const Comparable &x, AvlNode<Comparable> *t) const
{
    if (t == nullptr)
        return nullptr;
    else if (x < t->element)
        return find(x, t->left);
    else if (t->element < x)
        return find(x, t->right);
    else
        return t;  // Match
}

// Make the subtree rooted at t empty
template <class Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode<Comparable> *&t) const
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

// Clone the subtree rooted at t
template <class Comparable>
AvlNode<Comparable> *AvlTree<Comparable>::clone(AvlNode<Comparable> *t) const
{
    if (t == nullptr)
        return nullptr;
    else
        return new AvlNode<Comparable>(t->element, clone(t->left), clone(t->right), t->height);
}

// Return the height of the node t
template <class Comparable>
int AvlTree<Comparable>::height(AvlNode<Comparable> *t) const
{
    if (t == nullptr)
        return -1;
    else
        return t->height;
}

// Update the height of the node t
template <class Comparable>
void AvlTree<Comparable>::updateHeight(AvlNode<Comparable> *t) const
{
    t->height = max(height(t->left), height(t->right)) + 1;
}

// Perform a single rotation with left child (LL rotation)
template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(AvlNode<Comparable> *&k2) const
{
    AvlNode<Comparable> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    updateHeight(k2);
    updateHeight(k1);
    k2 = k1;
}

// Perform a single rotation with right child (RR rotation)
template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild(AvlNode<Comparable> *&k1) const
{
    AvlNode<Comparable> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    updateHeight(k1);
    updateHeight(k2);
    k1 = k2;
}

// Perform a double rotation with left child (LR rotation)
template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild(AvlNode<Comparable> *&k3) const
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

// Perform a double rotation with right child (RL rotation)
template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild(AvlNode<Comparable> *&k1) const
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

// Balance the subtree rooted at t
template <class Comparable>
void AvlTree<Comparable>::balance(AvlNode<Comparable> *&t) const
{
    if (t == nullptr)
        return;

    if (height(t->left) - height(t->right) > 1)
    {
        if (height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    }
    else if (height(t->right) - height(t->left) > 1)
    {
        if (height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);
        else
            doubleWithRightChild(t);
    }

    updateHeight(t);
}
/**
 * Print the tree contents in sorted order.
 */
template <class Comparable>
void AvlTree<Comparable>::printTree(const unsigned short num,ofstream &ostr ) const
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    else{
        if (num == 0){ //preorder
            printPreTree( root , ostr);
        }
        else if (num == 1){ //postorder
            printInTree( root , ostr);
        }
        else if (num == 2){ //drawtree
            drawTree( root , ostr,"",true);
        }
        else{
            cout << "number inside function is wrong" << endl;
        }
    }
}

/**
* Internal method to print a subtree rooted at t in sorted order.
*/
template <class Comparable>
void AvlTree<Comparable>::printPreTree( AvlNode<Comparable> * t,ofstream &ostr) const
{
    if ( t != NULL )
    {
        ostr << t->element << endl;
        printPreTree( t->left ,ostr);
        printPreTree( t->right ,ostr);
    }
}

template <class Comparable>
void AvlTree<Comparable>::printInTree( AvlNode<Comparable> * t ,ofstream &ostr) const
{
    if ( t != NULL )
    {
        printInTree( t->left ,ostr);
        ostr << t->element << endl;
        printInTree( t->right ,ostr);
    }
}

template <class Comparable>
void AvlTree<Comparable>::drawTree(AvlNode<Comparable> *t, ofstream &ostr, string prefix ,bool isTail) const
{
    if (t != nullptr) {
        ostr << prefix;

        if (isTail) {
            ostr << "|__";
            prefix += "   ";
        } else {
            ostr << "|--";
            prefix += "|  ";
        }

        ostr << t->element.name << " " << t->element.lastname << endl;

        drawTree(t->left, ostr, prefix , t->right == nullptr);
        drawTree(t->right, ostr, prefix , true);
    }
}

// Return the maximum of two integers
template <class Comparable>
int AvlTree<Comparable>::max(int lhs, int rhs) const
{
    return (lhs > rhs) ? lhs : rhs;
}

template <class Comparable>
void AvlTree<Comparable>::search(const string& searchstr,int & check) {
    searchNode(root, searchstr,check);
}


template <class Comparable>
void AvlTree<Comparable>::searchNode(AvlNode<Comparable>* node, const string& searchstr,int & check) {
    if (node != nullptr) {
        string fullname = node->element.name + " " + node->element.lastname;
        searchNode(node->left,searchstr,check);
        if (fullname.substr(0,searchstr.length()) == searchstr){
            cout << node->element << endl;
            check++;
        }
        searchNode(node->right,searchstr,check);
    }
}
