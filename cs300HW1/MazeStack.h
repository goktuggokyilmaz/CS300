#include <string>
#include <iostream>
using namespace std;
#ifndef MazeStack_H
#define MazeStack_H

struct MazeCell{
    unsigned short x_cord; //cordinat
    unsigned short y_cord;
    bool visited = false;
    bool lft; //walls
    bool rgt;
    bool upr;
    bool dwn;
};

template <class Object>
class Stack
{
public:
    Stack( );
    Stack( const Stack & rhs );
    ~Stack( );
    bool isEmpty( ) const;
    bool isFull( ) const;
    void makeEmpty( );
    void pop( );
    void push( const Object & x );
    Object topAndPop( );
    const Object & top( ) const;
    const Stack & operator=( const Stack & rhs );
    private:
        struct ListNode {
         Object element;
         ListNode *next;
         ListNode( const Object & theElement, ListNode * n = nullptr )
             : element( theElement ), next( n ) {}
        };
        ListNode *topOfStack;  // list itself is the stack
};

#endif //MazeStack_H
