//
//  main.cpp
//  Hw3_CS300
//
//  Created by Goktug Gokyilmaz on 12.04.2023.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include "Trees.cpp"
#include "Trees.h"
using namespace std;

void toUpper(string& str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
}

int main() {
    chrono::time_point<chrono::high_resolution_clock> bst_start, bst_end,avl_start,avl_end;
    BinarySearchTree<Person> Bst_tree(Person("","","",""));
    AvlTree<Person> Avl_tree(Person("","","",""));
    int actionnum = 0;
    string contact_fname,line;
    ifstream fname;
    cout <<"Please enter the contact file name: ";
    cin >>contact_fname;
    
    //string rootname ="/Users/yucel/Desktop/Xcode/Hw3_CS300/Hw3_CS300/samplesfolder/"; //USED FOR TEST
    //contact_fname=rootname+"PhoneBook-Sample4.txt"; //USED FOR TEST
    
    //bst
    cout << "Loading the phonebook into a BST."<<endl;
    bst_start = chrono::high_resolution_clock::now();
    fname.open(contact_fname);
    while(getline(fname,line)){//opening the contact file again from begining for BST creation
        istringstream iss(line);
        string firstname,lastname,phonenum,city;
        if (iss >> firstname >> lastname >> phonenum >> city){
            toUpper(firstname);
            toUpper(lastname);
            toUpper(city);
            Person *temp = new Person(firstname,lastname,phonenum,city);
            Bst_tree.insert(*temp,true);
        }
    }
    fname.close();
    bst_end = chrono::high_resolution_clock::now();
    auto bst_total_time = bst_end - bst_start;
    cout << "Phonebook creation in BST took "<< chrono::duration_cast<std::chrono::milliseconds>(bst_total_time).count() <<" milliseconds. . ."<<endl;
    Bst_tree.isBalanced();
    
    //avl
    cout << "Loading the phonebook into a AVL."<<endl;
    avl_start = chrono::high_resolution_clock::now();
    fname.open(contact_fname);
    while(getline(fname,line)){//opening the contact file again from begining for AVL creation
        istringstream iss(line);
        string firstname,lastname,phonenum,city;
        if (iss >> firstname >> lastname >> phonenum >> city){

            toUpper(firstname);
            toUpper(lastname);
            toUpper(city);
            
            Person *temp = new Person(firstname,lastname,phonenum,city);
            Avl_tree.insert(*temp,true);
        }
    }
    fname.close();
    avl_end = chrono::high_resolution_clock::now();
    auto avl_total_time = avl_end - avl_start;
    cout << "Phonebook creation in AVL took "<< chrono::duration_cast<std::chrono::milliseconds>(avl_total_time).count() <<" milliseconds. . ."<<endl;
    Avl_tree.isBalanced();
    
    //AFTER ALL OPERATIONS NOW WE CAN ASK FOR FUNCTIONS
    while(actionnum != 6){
        if (actionnum == 0){
            cout << "\nChoose which action to perform from 1 to 6:\n1 - Search a phonebook contac\n2 - Adding a phonebook contact\n3 - Deleting a phonebook contact\n4 - Print the phonebook to a file(inorder)\n    Print the phoenbook to a file(preorder)\n5 - Draw the phonebook as a Tree to a file\n6 - Press 6 to exit"<< endl;
            cin >> actionnum;
        }
        if (actionnum == 1){
            string seachfor="";
            string sfull,sname,slast;
            cout <<endl << "Search for a contact: ";
            while(true){ //here I did this because there is a case user can enter just firstname like GUL
                getline(cin, seachfor);
                if (seachfor.length()>0){
                    break;
                }
            }
            istringstream iss(seachfor);
            int check = 0;
            iss >> sname;

            if (iss >> slast) {// last name is provided.
                sfull=sname+" "+ slast;
            }
            else
            {                // there is no last name provided
                sfull=sname;
            }
            
            toUpper(sfull); //UPPER THE NAME
            
            //we are searching for sfull.
            
            bst_start = chrono::high_resolution_clock::now();
            cout<< "\nSearching an item in the phonebook (BST) . . .\n\nPhonebook: Searching for: ("<<sfull<<")\n====================================\n";
            Bst_tree.search(sfull,check);
            if(check==0){
                cout << "There is no contact with that search...\n";
            }
            bst_end = chrono::high_resolution_clock::now();
            check= 0;
            cout<< "\nSearching an item in the phonebook (AVL) . . .\n\nPhonebook: Searching for: ("<<sfull<<")\n====================================\n";
            
            avl_start = chrono::high_resolution_clock::now();
            Avl_tree.search(sfull,check);
            if(check==0){
                cout << "There is no contact with that search...\n";
            }
            avl_end = chrono::high_resolution_clock::now();
            
            
            
            cout<<"\nThe search in BST took "<<chrono::duration_cast<std::chrono::milliseconds>(bst_end-bst_start).count()<<" milliseconds. . .\nThe search in AVL took "<<chrono::duration_cast<std::chrono::milliseconds>(avl_end-avl_start).count()<<" milliseconds. . ."<<endl;
            actionnum = 0;
            
        }
        if (actionnum == 2){
            string addfirstname,addlastname,addphone,addcity; //Taking infos to be added into bst and avl
            cout <<endl << "Enter the information of the contact to be added:";
            cout <<endl<< "Name: ";
            cin>>addfirstname>>addlastname;
            cout <<endl<< "Tel: ";
            cin>>addphone;
            cout <<endl<< "City: ";
            cin>>addcity;
            toUpper(addfirstname);
            toUpper(addlastname);
            toUpper(addcity);
            Person *temp = new Person(addfirstname,addlastname,addphone,addcity);
            cout <<endl<< "Adding an item to the phonebook BST . . .\n===================================="<<endl; //BST PART
            
            bst_start = chrono::high_resolution_clock::now();
            //BST INSERT
            Bst_tree.insert(*temp,false);
            bst_end = chrono::high_resolution_clock::now();
            
            cout <<endl<< "Adding an item to the phonebook AVL . . .\n===================================="<<endl; //AVL TREE
            avl_start = chrono::high_resolution_clock::now();
            
            //AVL INSERT
            Avl_tree.insert(*temp,false);
            avl_end = chrono::high_resolution_clock::now();
            
            //Computing ends
            
            cout << "Adding a contact to the Binary Tree took "<< chrono::duration_cast<std::chrono::milliseconds>(bst_end-bst_start).count() <<" milliseconds. . ."<<endl;
            cout << "Adding a contact to the AVL Tree took "<< chrono::duration_cast<std::chrono::milliseconds>(avl_end-avl_start).count() <<" milliseconds. . ."<<endl;
            actionnum = 0;
        }
        if (actionnum == 3){//REMOVE FUNCTION
            string dname,dlast;
            cout << "\nDeleting an item from the phonebook . . .\nEnter the fullname of the contact to be deleted: ";
            cin >> dname>>dlast;
            
            toUpper(dname);
            toUpper(dlast);
            auto checkavl = Avl_tree.find(Person(dname,dlast,"",""));
            auto checkbst = Avl_tree.find(Person(dname,dlast,"",""));
            
            if (checkbst != Person("","","","") || checkavl != Person("","","","")){
                
                
                bst_start = chrono::high_resolution_clock::now();
                
                Bst_tree.remove(checkbst);
                
                bst_end = chrono::high_resolution_clock::now();
                
                //AVL
                
                avl_start=chrono::high_resolution_clock::now();

                Avl_tree.remove(checkavl);
                
                avl_end=chrono::high_resolution_clock::now();
                
                cout << "\nDeleted succcessfully. . .\n\nDeletion from the Binary Tree took  "<< chrono::duration_cast<std::chrono::milliseconds>(bst_end-bst_start).count() <<" milliseconds. . ."<<endl;
                cout << "Deletion from the AVL Tree took "<< chrono::duration_cast<std::chrono::milliseconds>(avl_end-avl_start).count() <<" milliseconds. . ."<<endl<<endl;
                
            }
            else{
                cout << "Not Found"<<endl;
            }

            
            actionnum = 0;
        }
        if (actionnum == 4){//pre in order print to file
            
            //Inorder
            bst_start = chrono::high_resolution_clock::now();
            ofstream inbst = ofstream("phonebookInOrderBST.txt");//created new file.
            Bst_tree.printTree(1,inbst); //calls public function then it will call private function number (1(represent which way to print 1 for Inored 0 for PreOrder  , inbst(file to print) )
            bst_end = chrono::high_resolution_clock::now();
            inbst.close();
            //similar for all steps
            avl_start = chrono::high_resolution_clock::now();
            ofstream inavl = ofstream("phonebookInOrderAVL.txt");
            Avl_tree.printTree(1, inavl);
            avl_end = chrono::high_resolution_clock::now();
            inavl.close();
            
            cout<<"\nPrinting in order to file from the Binary Tree took "<<chrono::duration_cast<std::chrono::milliseconds>(bst_end-bst_start).count()<<" milliseconds. . .\nPrinting in order to file from AVL Tree took "<< chrono::duration_cast<std::chrono::milliseconds>(avl_end-avl_start).count()<<" milliseconds. . ."<<endl;
            
            //preorder
            
            bst_start = chrono::high_resolution_clock::now();
            ofstream prebst = ofstream("phonebookPreOrderBST.txt");
            Bst_tree.printTree(0,prebst);
            bst_end = chrono::high_resolution_clock::now();
            prebst.close();
            avl_start = chrono::high_resolution_clock::now();
            ofstream preavl = ofstream("phonebookPreOrderAVL.txt");
            Avl_tree.printTree(0, preavl);
            avl_end = chrono::high_resolution_clock::now();
            preavl.close();
            
            cout<<"Printing in order to file from the Binary Tree took "<<chrono::duration_cast<std::chrono::milliseconds>(bst_end-bst_start).count()<<" milliseconds. . .\nPrinting in order to file from AVL Tree took "<< chrono::duration_cast<std::chrono::milliseconds>(avl_end-avl_start).count()<<" milliseconds. . ."<<endl;
            
            
            actionnum = 0;
        }
        if (actionnum == 5){//Drawtree
            
            
            bst_start = chrono::high_resolution_clock::now();
            ofstream drwbst = ofstream("phonebookTreeBST.txt");
            Bst_tree.printTree(2,drwbst);
            bst_end = chrono::high_resolution_clock::now();
            drwbst.close();
            avl_start = chrono::high_resolution_clock::now();
            ofstream drwavl = ofstream("phonebookTreeAVL.txt");
            Avl_tree.printTree(2, drwavl);
            drwavl.close();
            avl_end = chrono::high_resolution_clock::now();
            
            
            
            
            cout<<"Drawing tree to file from the Binary Tree took "<< chrono::duration_cast<std::chrono::milliseconds>(bst_end-bst_start).count() <<" nanoseconds. . .\nDrawing tree to file from AVL Tree took "<<  chrono::duration_cast<std::chrono::milliseconds>(avl_end-avl_start).count()<<" nanoseconds. . ."<<endl;
            
            
            actionnum = 0;
        }
    }
    
    cout <<endl <<"Exiting...";
    return 0;
}
