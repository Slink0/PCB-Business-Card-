#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


using std::vector, std::cout, std::endl;

//(x,y) coordinates 
struct coords{
    int x;
    int y;
};

class snake{
    private:
        vector<coords> body_coords;
        char body;
        int size;
        char direction;//this is temporary until I either implement button control or if I need to ise multithreading to handle inputs
    public:
        
        void add_length(coords);
        coords get_body_coords(int);
        char get_body();
        int get_size();
        void move_snake();
        void change_direction(char);
        coords get_head();
        
        snake(){
            srand(static_cast<unsigned int>(time(NULL)));
            body = '@';
            body_coords.resize(64);
            body_coords[0].x = rand() % 8 ;
            body_coords[0].y = rand() % 8 ;
            size = 1; 
        }
        
};

coords snake::get_body_coords(int index){
    coords ind_coord;
    ind_coord.x = body_coords[index].x;
    ind_coord.y = body_coords[index].y;
    return ind_coord;
}

char snake::get_body(){
    return body;
}

int snake::get_size(){
    return size;
}

coords snake::get_head(){
    return body_coords.front();
}

//The input method is tempory
//Need to determine how to handle this with multitasking
//goal is to use multitasking avoid unregistered inputs
void snake::change_direction(char current_direction){
    direction = current_direction;
    switch(direction){
        case 'w':
            direction = 'w';
            break;
        case 'a':
            direction = 'a';
            break;
        case 's':
            direction = 's';
            break;
        case 'd':
            direction = 'd';
            break;
        default:
          break;  
    }
}

void snake::move_snake(){
    coords head = body_coords[0];
    cout << head.x << ", " << head.y << endl;
    switch(direction){
        case 'w':
            cout << "moving up" << endl;
            head.y = head.y - 1;
            break;
        case 'a':
            cout << "moving left" << endl;
            head.x= head.x - 1;
            break;
        case 's':
            cout << "moving down" << endl;
            head.y = head.y + 1;
            break;
        case 'd':
            cout << "moving right" << endl;
            head.x = head.x + 1;
            break;
        default:
            cout << "invalid input" << endl;
    }
    body_coords.insert(body_coords.begin(),head);
    body_coords.erase(body_coords.begin() + size);
    cout << body_coords.front().x << ", " << body_coords.front().y << endl;
    
    
    
}

//Display 8x8 frame
void show_frame(vector<vector<char>> current_frame){
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                cout << current_frame[i][j] << "  ";
            }
            cout << endl;
        }
}

int main(){
    //8x8 map representing LED matrix
    vector<vector<char>> map = {
        {'-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-'}
    };
    bool running = true;
    snake snek;
    char body = snek.get_body();
    
    //set starting point on map
    coords start = snek.get_body_coords(0);
    map[start.x][start.y] = body;
    
    char input;

    while(running){

        //Refresh the map at a specified fps
        //for now 1 fps
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::system("clear");
        std::cin >> input;
        snek.change_direction(input);
        snek.move_snake();
        map[snek.get_head().y][snek.get_head().x] = body;
        show_frame(map);
        
        
        
    }
    
}