#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>


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
    public:
        
        void add_length(coords);
        coords get_body_coords(int);
        char get_body();
        int get_size();
        void move_snake();
        
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
    
    while(running){

        //Refresh the map at a specified fps
        //for now 1 fps
        cout << "SCORE: " << snek.get_size() << endl;
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                cout << map[i][j] << "  ";
            }
            cout << endl;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::system("clear");
        
        
    }
    
}