//
//  main.cpp
//  Hw3_CS300
//
//  Created by Goktug Gokyilmaz on 12.04.2023.
//
#include "Trees.h"
#include "Trees.cpp"

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

void toUpper(string& str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
}

int main() {
    chrono::time_point<chrono::high_resolution_clock> bst_start, bst_end,avl_start,avl_end;
    BinarySearchTree<Person> Bst_tree(Person("","","",""));
    HashTable<Person*> HS_tree(nullptr, 53);
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
    cout << "Loading the phonebook into a HashBook."<<endl;
    avl_start = chrono::high_resolution_clock::now();
    fname.open(contact_fname);
    while(getline(fname,line)){//opening the contact file again from begining for AVL creation
        istringstream iss(line);
        string firstname,lastname,phonenum,city;
        if (iss >> firstname >> lastname >> phonenum >> city){

            toUpper(firstname);
            toUpper(lastname);
            toUpper(city);
            
            Person* temp = new Person(firstname,lastname,phonenum,city);
            HS_tree.insert(temp);
        }
    }
    fname.close();
    avl_end = chrono::high_resolution_clock::now();
    auto avl_total_time = avl_end - avl_start;
    cout << "Phonebook creation in Hash took "<< chrono::duration_cast<std::chrono::milliseconds>(avl_total_time).count() <<" milliseconds. . ."<<endl;
    
    //AFTER ALL OPERATIONS NOW WE CAN ASK FOR FUNCTIONS
    while(actionnum != 4){
        if (actionnum == 0){
            cout << "\nChoose which action to perform from 1 to 6:\n1 - Search a phonebook contac\n2 - Adding a phonebook contact\n3 - Deleting a phonebook contact\n4 - Press 4 to exit"<< endl;  //it says 1 to 6 in the sampleruns so I leave it like that
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
            toUpper(sname);
            toUpper(slast);
            toUpper(sfull); //UPPER THE NAME
            Person* searchperson = new Person(sname,slast,"","");
            
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
            cout << HS_tree.find(searchperson) <<endl;
            delete searchperson;
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
            
            cout <<endl<< "Adding an item to the phonebook (Hashtable) . . .\n===================================="<<endl; //AVL TREE
            avl_start = chrono::high_resolution_clock::now();
            
            //AVL INSERT
            HS_tree.insert(temp);
            avl_end = chrono::high_resolution_clock::now();
            
            //Computing ends
            
            cout << "Adding a contact to the Binary Tree took "<< chrono::duration_cast<std::chrono::milliseconds>(bst_end-bst_start).count() <<" milliseconds. . ."<<endl;
            cout << "Adding a contact to the Hashtable took "<< chrono::duration_cast<std::chrono::milliseconds>(avl_end-avl_start).count() <<" milliseconds. . ."<<endl;
            actionnum = 0;
        }
        if (actionnum == 3){//REMOVE FUNCTION
            string dname,dlast;
            cout << "\nDeleting an item from the phonebook . . .\nEnter the fullname of the contact to be deleted: ";
            cin >> dname>>dlast;
            
            toUpper(dname);
            toUpper(dlast);
            Person *temp = new Person(dname,dlast,"","");
            auto checkavl = HS_tree.find(temp);
            auto checkbst = Bst_tree.find(Person(dname,dlast,"",""));
            
            if (checkbst != Person("","","","") || checkavl != nullptr ){// || checkavl != Person("","","","")
                
                
                bst_start = chrono::high_resolution_clock::now();
                
                Bst_tree.remove(checkbst);
                
                bst_end = chrono::high_resolution_clock::now();
                
                //AVL
                
                avl_start=chrono::high_resolution_clock::now();

                HS_tree.remove(temp);
                
                avl_end=chrono::high_resolution_clock::now();
                
                cout << "\nDeleted succcessfully. . .\n\nDeletion from the Binary Tree took  "<< chrono::duration_cast<std::chrono::milliseconds>(bst_end-bst_start).count() <<" milliseconds. . ."<<endl;
                cout << "Deletion from the Hashtable took "<< chrono::duration_cast<std::chrono::milliseconds>(avl_end-avl_start).count() <<" milliseconds. . ."<<endl<<endl;
                
            }
            else{
                cout << "Not Found"<<endl;
            }
            actionnum = 0;
        }
    }
    
    cout <<endl <<"Exiting...";
    return 0;
}
