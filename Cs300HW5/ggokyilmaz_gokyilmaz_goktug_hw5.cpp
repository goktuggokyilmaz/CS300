//
//  main.cpp
//  Cs300HW5
//
//  Created by Goktug Gokyilmaz on 23.05.2023.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>
#include <vector>



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
    bool operator<=(const Person& other) const
    {
        return (name + lastname <= other.name + other.lastname);
    }
    string getFull() const{
        return name+lastname;
    }
    
};

ostream& operator<<(ostream& os, const Person& prs) { //without inline I get duplicate error so I figure out I should use inline keyword
    os << prs.name << " " <<prs.lastname<< " "<< prs.phonenumber<<" "<< prs.city;
    return os;
}
//binarysearch
template <class Comparable>
unsigned long binaryminSearch(const vector<Comparable>& elements, const string& prefix, unsigned long left, unsigned long right) {
    unsigned long result = 0;  // Initialize the result variable

    while (left <= right) {
        unsigned long mid = (left + right) / 2;
        if ((elements[mid].name+elements[mid].lastname).substr(0, prefix.size()) == prefix) {
            result = mid;  // Update the result variable
            right = mid - 1;  // Continue searching for a smaller occurrence
        }
        else if ((elements[mid].name+elements[mid].lastname) > prefix) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return result;
}

template <class Comparable>
unsigned long binarymaxSearch(const vector<Comparable>& elements, const string& prefix, unsigned long left, unsigned long right) {
    unsigned long result = 0;  // Initialize the result variable

    while (left <= right) {
        unsigned long mid = (left + right) / 2;
        if ((elements[mid].name+elements[mid].lastname).substr(0, prefix.size()) == prefix) {
            result = mid;  // Update the result variable
            left = mid + 1;  // Continue searching for a larger occurrence
        }
        else if ((elements[mid].name+elements[mid].lastname) > prefix) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return result;
}

template <class Comparable>
std::vector<Comparable> binarySearch(const std::vector<Comparable>& elements, const std::string& prefix) {
    std::vector<Comparable> result;
    unsigned long left = 0;
    unsigned long right = elements.size()-1;
    while(left <= right){
        unsigned long mid = (left + right) / 2;
        if ((elements[mid].name+elements[mid].lastname).substr(0,prefix.size()) == prefix){ // it finds the match however I tried to find  smallest occurence then add them into result vector
            unsigned long minnum = binaryminSearch(elements, prefix,left,mid);
            unsigned long maxnum = binarymaxSearch(elements, prefix,mid,right);
            for (unsigned long x= minnum;x <=maxnum; x++){
                result.push_back(elements[x]);
            }
            return result;
        }
        else if ((elements[mid].name+elements[mid].lastname) > prefix){
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    
    
    return result;
}


//sequentialSearch
std::vector<Person> sequentialSearch(const std::vector<Person>& persons, const std::string& targetSubstring) {
    std::vector<Person> result;

    for (unsigned long i = 0; i < persons.size(); ++i) {
        string personfname = persons[i].name+persons[i].lastname;
        if (personfname.substr(0,targetSubstring.size()) == targetSubstring) {
            // Add the index to the result if the target substring is found in the name
            result.push_back(persons[i]);
        }
    }

    return result;
}
/**
* Standard swap GK
*/
template <class Comparable>
inline void Myswap( Comparable & obj1,Comparable & obj2 )
{
     Comparable tmp = obj1;
     obj1 = obj2;
     obj2 = tmp;
}

/**
* Internal insertion sort routine for subarrays
* that is used by quicksort.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
   for ( int p = left + 1; p <= right; p++ )
   {
        Comparable tmp = a[ p ];
        int j;

        for ( j = p; j > left && tmp < a[ j - 1 ]; j-- )
             a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
  }
}

/**
* Internal quicksort method that makes recursive calls.
* Uses median-of-three partitioning and a cutoff of 10.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <class Comparable>
void quicksort( vector<Comparable> & a,
               int left, int right )
{
    if ( left + 10 <= right )
    {
        Comparable pivot = median3( a, left, right );

        int i = left, j = right - 1;
        for ( ; ; )
        {
            while ( a[ ++i ] < pivot ) { }

            while ( pivot < a[ --j ] ) { }

            if ( i < j )
                  Myswap( a[ i ], a[ j ] );
            else
                  break;
        }
        Myswap( a[ i ], a[ right - 1 ] );   // Restore pivot

        quicksort( a, left, i - 1 );       // Sort small elements
        quicksort( a, i + 1, right );    // Sort large elements
   }
   else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}




/**
 * Quicksort algorithm (driver).
*/
template <class Comparable>
void quicksort( vector<Comparable> & a )
{
      quicksort( a, 0, a.size( ) - 1 );
}


/** Return median of left, center, and right.
    *   Order these and hide the pivot.
  */
 template <class Comparable>
 const Comparable & median3( vector<Comparable> & a,
                                    int left, int right )
 {
       int center = ( left + right ) / 2;
       if ( a[ center ] < a[ left ] )
         Myswap( a[ left ], a[ center ] );
       if ( a[ right ] < a[ left ] )
         Myswap( a[ left ], a[ right ] );
       if ( a[ right ] < a[ center ] )
         Myswap( a[ center ], a[ right ] );

       // Place pivot at position right - 1
       Myswap( a[ center ], a[ right - 1 ] );
       return a[ right - 1 ];
 }

//Insertsorth

template <class Comparable>
void insertionSort (vector <Comparable> & a)
{
    int j;
               // loop over the passes
    for (int p = 1;  p < a.size(); p++)
    {
        Comparable tmp = a[p];
                            // loop over the elements
        for (j = p; j > 0 &&  tmp < a[j - 1]; j --){
            a[j] = a[j -1];
        }
        a[j] = tmp;
    }
}

//Heapsort

inline int leftChild( int i )
{
    return 2*i+1;
}


template <class Comparable>
void heapsort(vector<Comparable> & a)
{
    // buildHeap
    for (int i = a.size()/2; i >=0; i--)
        percDown(a, i, a.size());

    // sort
    for (int j = a.size() -1; j >0; j--)
    {
        Myswap(a[0], a[j]);    // swap max to the last pos.
        percDown(a, 0, j); // re-form the heap
    }
}

template <class Comparable>  // for deleteMax
// a is the array, i is the position to percolate down from
// n is the logical size of the array
void percDown( vector<Comparable> & a, int i, int n )
{
    int child;
      Comparable tmp;

      for (tmp=a[i] ; leftChild(i) < n; i = child )
      {
            child = leftChild(i);
            if ( child != n-1 && a[ child  ] < a[ child+1 ] )
                 child++;
                 if ( a[child ] > tmp )
                      a[i] = a[ child ];
                 else
                      break;
       }
       a[ i ] = tmp;
}

//mergesort
/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
template <class Comparable>
void merge(  vector<Comparable> & a,
             vector<Comparable> & tmpArray,
                  int leftPos, int rightPos, int rightEnd )
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;
    // Main loop
    while ( leftPos <= leftEnd && rightPos <= rightEnd )
         if ( a[ leftPos ] <= a[ rightPos ] )
             tmpArray[ tmpPos++ ] = a[ leftPos++ ];
         else
             tmpArray[ tmpPos++ ] = a[ rightPos++ ];

    while ( leftPos <= leftEnd )    // Copy rest of first half
        tmpArray[ tmpPos++ ] = a[ leftPos++ ];

    while ( rightPos <= rightEnd )  // Copy rest of right half
        tmpArray[ tmpPos++ ] = a[ rightPos++ ];

    // Copy tmpArray back
    for ( int i = 0; i < numElements; i++, rightEnd-- )
        a[ rightEnd ] = tmpArray[ rightEnd ];
}



template <class Comparable>
void merge( vector<Comparable> & a, int left, int mid, int right ) {
    int leftEnd = mid - 1;
    int numElements = right - left + 1;
    vector<Comparable> tmp(numElements);
    
    int i = left; // Pointer for the left subarray
    int j = mid; // Pointer for the right subarray
    int k = 0; // Pointer for the temporary array
    
    // Merge the subarrays in-place into the temporary array
    while (i <= leftEnd && j <= right) {
        if (a[i] <= a[j]) {
            tmp[k++] = move(a[i++]);
        } else {
            tmp[k++] = move(a[j++]);
        }
    }
    
    // Copy the remaining elements from the left subarray, if any
    while (i <= leftEnd) {
        tmp[k++] = move(a[i++]);
    }
    
    // Copy the remaining elements from the right subarray, if any
    while (j <= right) {
        tmp[k++] = move(a[j++]);
    }
    
    // Copy the merged elements back to the original array in-place
    for (int x = 0; x < numElements; x++, right--) {
        a[right] = move(tmp[right - left]);
    }
}

template <class Comparable>
void mergeSort( vector<Comparable> & a, int left, int right ) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid + 1, right);
    }
}

template <class Comparable>
void mergeSort( vector<Comparable> & a ) {
    mergeSort(a, 0, a.size() - 1);
}




void toUpper(string& str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
}


//MAIN CODE

int main() {
    int checktime = 10; // number of times sorting functions work and then take the average of sum/worktime
    vector<Person> mainvec,vec_insert,vec_quick,vec_heap,vec_merge;
    string contact_fname;
    cout << "Enter the file name: ";
    cin >> contact_fname;
    string line;
    ifstream fname;
    fname.open(contact_fname);
    while(getline(fname,line)){//opening the contact file again from begining for BST creation
        istringstream iss(line);
        string firstname,lastname,phonenum,city;
        if (iss >> firstname >> lastname >> phonenum >> city){
            toUpper(firstname);
            toUpper(lastname);
            Person *temp = new Person(firstname,lastname,phonenum,city);
            mainvec.push_back(*temp);
        }
    }
    cout << endl;
    //AFTER ALL OPERATIONS NOW WE CAN ASK FOR FUNCTIONS
    string seachfor="";
    string sfull,sname,slast;
    cout <<endl << "Please enter the word to be queried: ";
    while(true){ //here I did this because there is a case user can enter just firstname like GUL
        getline(cin, seachfor);
        if (seachfor.length()>0){
            break;
        }
    }
    istringstream iss(seachfor);
    iss >> sname;
    
    if (iss >> slast) {// last name is provided.
        sfull=sname+slast;
    }
    else
    {                // there is no last name provided
        sfull=sname;
    }
    
    
    toUpper(sfull); //UPPER THE NAME
    
    chrono::time_point<chrono::high_resolution_clock> tempt_start,tempt_end;
    chrono::nanoseconds durationquick,durationinsert,durationmerge,durationheap,durationsequential,durationbinary;
    
    tempt_start = chrono::high_resolution_clock::now();//quick sorth
    for (int x =0;x<checktime;x++){
        vec_quick = mainvec;
        quicksort(vec_quick);
    }
    tempt_end = chrono::high_resolution_clock::now();
    durationquick = chrono::duration_cast<chrono::nanoseconds>(tempt_end-tempt_start)/checktime;
    
    tempt_start = chrono::high_resolution_clock::now();//insertion sort
    for (int x =0;x<checktime;x++){
        vec_insert = mainvec;
        insertionSort(vec_insert);
    }
    tempt_end = chrono::high_resolution_clock::now();
    durationinsert = chrono::duration_cast<chrono::nanoseconds>(tempt_end-tempt_start)/checktime;
    
    tempt_start = chrono::high_resolution_clock::now();//merge sort
    for (int x =0;x<checktime;x++){
        vec_merge = mainvec;
        mergeSort(vec_merge);

    }
    tempt_end = chrono::high_resolution_clock::now();
    durationmerge = chrono::duration_cast<chrono::nanoseconds>(tempt_end-tempt_start)/checktime;
    
    
    tempt_start = chrono::high_resolution_clock::now();//heap sort
    for (int x =0;x<checktime;x++){
        vec_heap = mainvec;
        heapsort(vec_heap);
    }
    tempt_end = chrono::high_resolution_clock::now();
    durationheap = chrono::duration_cast<chrono::nanoseconds>(tempt_end-tempt_start)/checktime;
    
    
    cout<<"\nSorting the vector copies\n======================================";
    cout<<"\nQuick Sort Time: "<< durationquick.count() <<" Nanoseconds\nInsertion Sort Time: "<< durationinsert.count() <<" Nanoseconds\nMerge Sort Time: "<< durationmerge.count() <<" Nanoseconds\nHeap Sort Time: "<<  durationheap.count() <<" Nanoseconds";
    
    cout << "\n\nSearching for "<<sfull<<" \n======================================\n"; //search for binary
    quicksort(mainvec);
    vector<Person>result;
    
    
    tempt_start = chrono::high_resolution_clock::now();
    result = binarySearch(mainvec,sfull);
    if (result.size() == 0){
        cout << sfull << " does NOT exist in the dataset"<<endl;
    }else{
        for (unsigned long intx = 0;intx < result.size();intx++ ){
            cout << (result[intx])<<endl;
        }
    }
    tempt_end = chrono::high_resolution_clock::now();
    durationbinary = chrono::duration_cast<chrono::nanoseconds>(tempt_end-tempt_start);
    cout << "\nBinary Search Time: "<<durationbinary.count()<<" Nanoseconds";
    
    
    cout << "\n\nSearch results for Sequential Search: \n"; //search for sequential
    tempt_start = chrono::high_resolution_clock::now();
    result = sequentialSearch(mainvec,sfull);
    if (result.size() == 0){
        cout << sfull << " does NOT exist in the dataset"<<endl;
    }else{
        for (unsigned long intx = 0;intx < result.size();intx++ ){
            cout << (result[intx])<<endl;
        }
    }
    tempt_end = chrono::high_resolution_clock::now();
    durationsequential = chrono::duration_cast<chrono::nanoseconds>(tempt_end-tempt_start);
    
    cout <<"\nSequential Search Time: "<<durationsequential.count()<<" Nanoseconds\n";
    cout <<"\nSpeedUp between Search Algorithms\n======================================\n";
    cout <<"(Sequential Search/ Binary Search) SpeedUp = "<<static_cast<double>(durationsequential.count()) / static_cast<double>(durationbinary.count()) ;
    
    //I needed to add static_cast<double>, for solve the problem of results become intager
    cout <<"\n\nSpeedUps between Sorting Algorithms\n======================================\n";
    cout <<"(Insertion Sort/ Quick Sort) SpeedUp = "<<static_cast<double>(durationinsert.count()) / static_cast<double>(durationquick.count()) ;
    cout <<"\n(Merge Sort / Quick Sort) SpeedUp = "<<static_cast<double>(durationmerge.count()) / static_cast<double>(durationquick.count()) ;
    cout <<"\n(Heap Sort / Quick Sort) SpeedUp = "<<static_cast<double>(durationheap.count()) / static_cast<double>(durationquick.count()) ;
    cout <<endl;
    return 0;
}

