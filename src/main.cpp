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


void printPieces(SDL_Renderer* renderer, Board b, SDL_Texture* texture, int img_x, int img_y) {
    
    for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8;j++) {
            Piece* p = b.get_square(i,j).get_piece();
            if(!p) {
                continue;
            }
            
            SDL_Rect sourceRect;
            if(p->get_team()) {
                sourceRect.y = (int)(img_y / 2);
            } else {
                sourceRect.y = 0;
            }


            if(p->get_type() == PieceType::King) {
                sourceRect.x = 0;
                
            } 
            else if (p->get_type() == PieceType::Queen) {
                sourceRect.x = (int)((img_x / 6) * 1 );
            }
             else if (p->get_type() == PieceType::Bishop) {
                sourceRect.x = (int)((img_x / 6) * 2 );
            }
             else if (p->get_type() == PieceType::Knight) {
                sourceRect.x = (int)((img_x / 6) * 3 );
            }
             else if (p->get_type() == PieceType::Rook) {
                sourceRect.x = (int)((img_x / 6) * 4 );
            }
            else {
                sourceRect.x = (int)((img_x / 6) * 5 );
            }

            
            
            
            sourceRect.h = (int)(img_y / 2);
            sourceRect.w = (int)(img_x / 6);
            SDL_Rect destinationRect;
            destinationRect.x = BOARD_SIZE * j;  
            destinationRect.y = BOARD_SIZE * i;   
            destinationRect.w = BOARD_SIZE;  
            destinationRect.h = BOARD_SIZE;  

            // Copy to the renderer
            SDL_RenderCopy(renderer, texture, &sourceRect, &destinationRect);
            
        }
    }
    // Always free the surface as soon as the texture is made to save memory
    
   
    

   
}


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
    
    Board board = Board();
    board.display_board();
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WINDOW_SIZE,WINDOW_SIZE,0,&window,&renderer);
    SDL_SetWindowTitle(window,"Chess game!");
    bool running = true;

    SDL_Surface* surface = IMG_Load("assets/chess.png");
    
    int img_x = surface->w;
    int img_y = surface->h;
    if (!surface) {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return 0; // Exit early so it doesn't crash below
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Texture Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return 0;
    }

    SDL_MouseButtonEvent mouse_click;
    SDL_Event e;
    SDL_RenderClear(renderer); //make black screen
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
        printPieces(renderer,board,texture,img_x,img_y);
        SDL_RenderPresent(renderer);
        
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    return 0;
}


