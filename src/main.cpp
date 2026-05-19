#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>

#include "../include/all_headers.hpp"
using namespace std;


SDL_Color lightSquareColor = { 240, 217, 181, 255 }; // Cream
SDL_Color darkSquareColor  = { 181, 136,  99, 255 }; // Brown

const int BOARD_SIZE = 120;
const int WINDOW_SIZE = 960;

void drawWhiteSquare(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer,lightSquareColor.r,lightSquareColor.g,lightSquareColor.b,255); //set color white
    SDL_Rect r;
    r.h = BOARD_SIZE;
    r.w = BOARD_SIZE;
    r.x = x;
    r.y = y;

    SDL_RenderFillRect(renderer,&r);
}
void drawBlackSquare(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer,darkSquareColor.r,darkSquareColor.g,darkSquareColor.b,255); //set color black
    SDL_Rect r;
    r.h = BOARD_SIZE;
    r.w = BOARD_SIZE;
    r.x = x;
    r.y = y;

    SDL_RenderFillRect(renderer,&r);
}
void drawBoard(SDL_Renderer* renderer) {
    for(int i = 0;i < 8; i++) {
        for(int j = 0; j < 8;j++) {
            bool square_color = ((i+j) % 2 == 0) ? true : false;
            int x = i * BOARD_SIZE;
            int y = j * BOARD_SIZE;
            if(square_color) {
                drawWhiteSquare(renderer,x,y);
                
            }
            else {
                drawBlackSquare(renderer,x,y);
                
            } 
        }
        
    }
    
}
/*
void drawPieces(SDL_Renderer* renderer, Board b) {
    Img  piece_png = ("../assests/chess.png");
    for(int i = 0; i < 8;i++) {
        for(int j = 0; j < 8; j++) {
            if (b.get_square(i,j).get_piece() != nullptr) {

                int image_x = piece_png.;
                int image_y = ;
                //draw piece
                SDL_Rect  piece;
                
            }
        }
    }
    
}


*/
void testPrintImg(SDL_Renderer* renderer) {
    // FIX 1: Removed leading slash so it looks inside your project folder
    SDL_Surface* surface = IMG_Load("assets/chess.png");
    if (!surface) {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return; // Exit early so it doesn't crash below
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Texture Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }
    
    // Always free the surface as soon as the texture is made to save memory
    SDL_FreeSurface(surface);

    SDL_Rect destinationRect;
    destinationRect.x = 100;  
    destinationRect.y = 50;   
    destinationRect.w = 200;  
    destinationRect.h = 200;  

    // Copy to the renderer
    SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
    
    // Push the changes to the screen
    SDL_RenderPresent(renderer);

    // Clean up the texture so you don't leak GPU memory
    SDL_DestroyTexture(texture);
}


/*
void testPrintImg(SDL_Renderer* renderer) {
    fstream chess_png;
    chess_png.open("assets/chess.png");
    cout << chess_png.is_open() << endl; //
    streamsize size = chess_png.tellg();
    chess_png.seekg(0,ios::beg);
   
    
    // read file into buffer
     std::vector<char> buffer(size);
    if(!chess_png.read(buffer.data(), size)) {
        cerr << "failed to read file data" << endl;
        
    }

    SDL_RWops* rw = SDL_RWFromConstMem(buffer.data(), size);
    if (!rw) {
        std::cerr << "SDL_RWFromConstMem Error: " << SDL_GetError() << std::endl;
        
    }

    SDL_Surface* surface = IMG_Load("assets/chess.png");
    if (!surface) {
        std::cerr << "IMG_LoadPNG_RW Error: " << IMG_GetError() << std::endl;
        
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_Rect destinationRect;
    destinationRect.x = 100;  // X position on screen
    destinationRect.y = 50;   // Y position on screen
    destinationRect.w = 200;  // Width to stretch or shrink image
    destinationRect.h = 200;  // Height to stretch or shrink image

    // Pass NULL as the source parameter to display the whole texture
    SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
    chess_png.close();
    SDL_RenderPresent(renderer);
}


*/

vector<int> get_move() {
    string move;
    vector<int> coords;
    cout << "Enter the coordinates of the piece you would like to move, eg e2 e4";
    getline(cin, move);
    cout << move << endl;
    //swaped so its old rank, old file, new file, new rank or old col, old row, new  col, new row to match array
    coords.push_back((utils::char_to_int(move[1]))); //e = 
    coords.push_back((7 - utils::char_to_int(move[0])));
    coords.push_back((utils::char_to_int(move[4])));
    coords.push_back((7 - utils::char_to_int(move[3])));
    
    return coords;
}   
int main() {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WINDOW_SIZE,WINDOW_SIZE,0,&window,&renderer);
    SDL_SetWindowTitle(window,"Chess game!");
    bool running = true;

    SDL_MouseButtonEvent mouse_click;
    SDL_Event e;
    SDL_RenderClear(renderer); //make black screen
    testPrintImg(renderer);
    SDL_Delay(1000);
    while(running) {
        SDL_SetRenderDrawColor(renderer,0,0,0,255); //set color black
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) running = false;
            else if(e.type == SDL_MOUSEBUTTONDOWN) {
                int selected_x;
                int selected_y;
                SDL_GetMouseState(&selected_x,&selected_y);
                cout << "mouse click x: " << selected_x << " y: " << selected_y << endl;
              
            }
        }

        
        drawBoard(renderer);
        SDL_RenderPresent(renderer);
        
    }
    
    return 0;
}


