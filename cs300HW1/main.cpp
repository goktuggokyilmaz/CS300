//
//  main.cpp
//  cs300HW1
//
//  Created by GoktugGokyilmaz on 16.03.2023.
//
#include "MazeStack.h"
#include "MazeStack.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

void whichwaytogo(const MazeCell old, MazeCell &newone, vector<vector<MazeCell>> &base){
    unsigned short new_x = old.x_cord;
    unsigned short new_y = old.y_cord;
    bool find = false;
    if (old.rgt == false && base[new_x+1][new_y].visited == false){ // if right of current Mazecell acesseble and notvisited visit make newone MazeCell to that and change newone MazeCell since its referance it effect my implementation in main function
        newone = base[new_x+1][new_y];
        find = true;
    }
    if (old.upr == false && base[new_x][new_y+1].visited == false){
        newone = base[new_x][new_y+1];
        find = true;
    }
    if (old.dwn == false && base[new_x][new_y-1].visited == false){
        newone = base[new_x][new_y-1];
        find = true;
    }
    if (old.lft == false && base[new_x-1][new_y].visited == false){
        newone = base[new_x-1][new_y];
        find = true;
    }
    if (find == false){
        newone = old;
    }
}

vector<MazeCell> possibleoptions(const MazeCell & current,vector<vector<MazeCell>> &maze, const unsigned short & col,const unsigned short & row ){
    vector<MazeCell> newpossibles;
    if ((current.x_cord+1 >= 0 && current.x_cord+1 < col) && !maze[current.x_cord+1][current.y_cord].visited){//right
        newpossibles.push_back(maze[current.x_cord+1][current.y_cord]);
    }
    
    if ((current.x_cord-1 >= 0 && current.x_cord-1 < col) && !maze[current.x_cord-1][current.y_cord].visited){//left
        newpossibles.push_back(maze[current.x_cord-1][current.y_cord]);
    }

    if ((current.y_cord+1 >= 0 && current.y_cord+1 < row) && !maze[current.x_cord][current.y_cord+1].visited){//up
        newpossibles.push_back(maze[current.x_cord][current.y_cord+1]);
    }

    if ((current.y_cord-1 >= 0 && current.y_cord-1 < row) && !maze[current.x_cord][current.y_cord-1].visited){//down
        newpossibles.push_back(maze[current.x_cord][current.y_cord-1]);
    }
    return newpossibles;
}

void breakwall(MazeCell& f_cell, MazeCell& s_cell){//this will break two walls between 2 mazecell paramaters must correct pre checked.
    if (f_cell.x_cord - s_cell.x_cord == -1){
        f_cell.rgt = false;
        s_cell.lft = false;
    }
    else if (f_cell.x_cord - s_cell.x_cord == 1){
        f_cell.lft = false;
        s_cell.rgt = false;
    }
    else if(f_cell.y_cord - s_cell.y_cord == -1){
        f_cell.upr = false;
        s_cell.dwn = false;
    }
    else if(f_cell.y_cord - s_cell.y_cord == 1){
        f_cell.dwn = false;
        s_cell.upr = false;
    }
    else{
        cout << "Error occured" << endl;
    }
    s_cell.visited=true;
    
}

void createMaze(int i,int row,int col){//In this function it takes 3 paramaters number of row col and id id represent how many different maze.txt will created differently for each I will create random maze.
    srand((unsigned) time(NULL) + i ); // I  learned that sead value must be different at each time
    unsigned short rannum = 0;
        
    ofstream file_maze;
    
    string fname = "maze_" + to_string(i) +".txt";
    // file get its name accordig to "i"
    
    //In the beleow loops all Matrix members defined and their walls set to true however they marked as unvisited (visited=false)
    vector<vector<MazeCell>> My_Matrix(col, vector<MazeCell>(row));
    for (int c= 0;c < col; c++ ) // col num c
    {
        for (int r= 0;r < row; r++) // row num r
        {
            My_Matrix[c][r].x_cord = c;
            My_Matrix[c][r].y_cord = r;
            My_Matrix[c][r].rgt = true;
            My_Matrix[c][r].lft = true;
            My_Matrix[c][r].upr = true;
            My_Matrix[c][r].dwn = true;
            My_Matrix[c][r].visited = false;
        }
    }
    // Randomization phase
    Stack<MazeCell> stack_path;
    My_Matrix[0][0].visited = true;
    stack_path.push(My_Matrix[0][0]);
    int totalunvisited = (col*row)-1;
    while(totalunvisited!=0){
        unsigned short c_x = stack_path.top().x_cord;
        unsigned short c_y = stack_path.top().y_cord;
        vector<MazeCell> possibilities = possibleoptions(My_Matrix[c_x][c_y],My_Matrix,col,row);
        /*for (int b = 0; b < possibilities.size(); b++){ It was my way to check if posibilities were correct.
            cout << (possibilities[b].x_cord);cout << "," << possibilities[b].y_cord  << endl;
        }*/
        if (possibilities.size()> 0){//there are some posibille cells to add that mazecell
            rannum = rand() %(possibilities.size()); //here i produce random number between 0 to size
            My_Matrix[possibilities[rannum].x_cord][possibilities[rannum].y_cord];
            breakwall(My_Matrix[stack_path.top().x_cord][stack_path.top().y_cord], My_Matrix[possibilities[rannum].x_cord][possibilities[rannum].y_cord]);
            stack_path.push(My_Matrix[possibilities[rannum].x_cord][possibilities[rannum].y_cord]);
            totalunvisited--;
        }
        else{ // there is no cell left to add that one we should go back in stack
            stack_path.pop();
        }
        
        // writing info into the i'th txt file with its values according to required format
    }
    //cout << i << "th maze generated" <<endl; Succesfuly generated ith file.
    file_maze.open(fname);
    if(file_maze.is_open()){
        file_maze<< row <<" "<< col<<endl;
        for (int r= 0;r < row; r++){
            for (int c= 0;c < col; c++ ){
                file_maze<< "x="<< My_Matrix[c][r].x_cord << " y=" << My_Matrix[c][r].y_cord << " l=" << My_Matrix[c][r].lft <<" r=" << My_Matrix[c][r].rgt << " u=" << My_Matrix[c][r].upr <<" d=" << My_Matrix[c][r].dwn << endl;
            }
        }
    }
    file_maze.close();
}
    
void findPath(int id, int en_x, int en_y,int ex_x,int ex_y,unsigned short row,unsigned short col){ //This function finds to correct path to given ex_x(Exit x cord),ex_y(Exit y cord) from given enter cords (en_x,en_y) the id represented which maze txt it should read to findpath, row and col unsigned short numbers required to create suitible vector of vector to store
    ofstream path_file;
    string rname= "maze_" + to_string(id) +".txt";//"mazeExample.txt";
    ifstream read_from;
    vector<vector<MazeCell>> My_Matrix(col, vector<MazeCell>(row));
    read_from.open(rname);
    
    Stack<MazeCell> stack_path;
    string line;
    
    //In here I would like to start reading data from given ID's file
    int line_num= 0;
    while(getline(read_from,line)){//here I read line by line all specific informations and add them into My_Matrix vector of vector type MazeCell they have x,y(unsigned short since max size they can take 0-1000), cord wall informations(bools) and also visited informations(bools) in MazeCell struct
        if (line_num > 0){
            istringstream iss(line);
            unsigned short x, y; //store the x or y cord since it cannot be larger then
            bool l,r,u,d; // walls are bool type since they can only be 0 or 1 (0=false/NoWall) (1=true/Wall)
            char ch;
            if (iss >> ch >> ch >> x >> ch >> ch >> y>> ch >> ch >> l>> ch >> ch >> r>>ch >> ch >> u>> ch >> ch >> d) {
                //cout << "x=  " << x << " y=  " << y << endl;
                MazeCell cell;
                cell.x_cord = x;
                cell.y_cord = y;
                cell.dwn = d;
                cell.upr = u;
                cell.rgt = r;
                cell.lft = l;
                My_Matrix[x][y] = cell;
            }
        }
        line_num++;
    }
    stack_path.push(My_Matrix[en_x][en_y]);
    My_Matrix[en_x][en_y].visited = true;
    MazeCell new_one;
    new_one.x_cord = 0;
    new_one.y_cord = 0;
    while(stack_path.top().x_cord != ex_x || stack_path.top().y_cord != ex_y){//Find way to go out here I use Stack as wanted in the homework documment.
        whichwaytogo(stack_path.top(), new_one, My_Matrix);
        if ((new_one.x_cord == stack_path.top().x_cord) && ( new_one.y_cord == stack_path.top().y_cord )){ //if whichwaytogo returned same x y values I send so there is no way to go that is why we need to pop items.
            stack_path.pop();
        }
        else{ //the function"whichwaytogo" found other MazeCell to go as a option so a add it to my stack_path stack.
            stack_path.push(new_one);
            My_Matrix[new_one.x_cord][new_one.y_cord].visited = true; //and make it visited bool to true so after if I couldn't find way from this direction I can find any other Mazecell unvisited
        }
    }
    //after found the result I would like to write their x y informatins into path_file
    //(Write founded path stack to the file)
    //
    read_from.close();
    string fname = "maze_"+to_string(id)+"_path_"+to_string(en_x)+"_"+to_string(en_y)+"_"+to_string(ex_x)+"_"+to_string(ex_y)+".txt";
    
    path_file.open(fname); // the file which contains the final path on maze id to (en_x,en_y) to (ex_x,ex_y)
    if(path_file.is_open()){
        
        //print stack_path
        Stack<MazeCell> stack_reverse;
        //Below code reverse stack into stack_reverse
        while (!stack_path.isEmpty()){
            //path_file << stack_path.top().x_cord << " " << stack_path.top().y_cord <<endl;
            //cout <<stack_path.top().x_cord << " " << stack_path.top().y_cord << endl;
            stack_reverse.push(stack_path.top());
            stack_path.pop();
        }
        //below code prints stack_reverse code into the file.
        while (!stack_reverse.isEmpty()){
            path_file << stack_reverse.top().x_cord << " " << stack_reverse.top().y_cord <<endl;
            //cout <<stack_reverse.top().x_cord << " " << stack_reverse.top().y_cord << endl; //prints it into consol to check
            stack_reverse.pop();
        }
        path_file.close();
    }
}


int main() {
    int maze_num ,row_num ,col_num ;
    int maze_id ,entr_X,entr_Y,ext_X,ext_Y;
    cout <<"Enter the number of mazes: ";
    cin >>maze_num;
    cout <<"Enter the number of rows and columns (M and N): ";
    cin >>row_num>>col_num;
    for (int i = 1;i<maze_num+1;i++){
        createMaze(i, row_num, col_num);
    }
    
    cout <<"All mazes are generated."<<endl<<endl;
    
    cout << "Enter a maze ID between 1 to "<<maze_num<<" inclusive to find a path: ";
    cin >>maze_id;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin >>entr_X>>entr_Y;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin >>ext_X>>ext_Y;
    findPath(maze_id, entr_X, entr_Y, ext_X, ext_Y, row_num, col_num);

    
    return 0;
}
