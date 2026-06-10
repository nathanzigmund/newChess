#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <algorithm>

#include "../include/all_headers.hpp"
using namespace std;


SDL_Color lightSquareColor = { 240, 217, 181, 255 }; // Cream
SDL_Color darkSquareColor  = { 181, 136,  99, 255 }; // Brown

const int TILE_SIZE = 120;
const int WINDOW_SIZE = 960;

//Engine Logic
bool player_turn = true; 
bool select_mode = true;
int selected_x, selected_y;
int move_x, move_y;
std::vector<Move> moves;

void drawWhiteSquare(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer,lightSquareColor.r,lightSquareColor.g,lightSquareColor.b,255); //set color white
    SDL_Rect r;
    r.h = TILE_SIZE;
    r.w = TILE_SIZE;
    r.x = x;
    r.y = y;

    SDL_RenderFillRect(renderer,&r);
}
void drawBlackSquare(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer,darkSquareColor.r,darkSquareColor.g,darkSquareColor.b,255); //set color black
    SDL_Rect r;
    r.h = TILE_SIZE;
    r.w = TILE_SIZE;
    r.x = x;
    r.y = y;

    SDL_RenderFillRect(renderer,&r);
}
void drawBoard(SDL_Renderer* renderer, Board b) {
    for(int i = 0;i < 8; i++) {
        for(int j = 0; j < 8;j++) {
            bool square_color = b.get_square(i,j).get_color();
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;
            if(square_color) {
                drawWhiteSquare(renderer,x,y);
                
            }
            else {
                drawBlackSquare(renderer,x,y);
                
            } 
        }
        
    }
    
}


void highlight_moves_square(SDL_Renderer* renderer, int row, int col) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Color lightPurple = { 230, 230, 250, 128 };
    SDL_SetRenderDrawColor(renderer, lightPurple.r, lightPurple.g, lightPurple.b, lightPurple.a);

    SDL_Rect highlightRect;
    highlightRect.x = col * TILE_SIZE; // Columns map to X-axis
    highlightRect.y = row * TILE_SIZE; // Rows map to Y-axis
    highlightRect.w = TILE_SIZE;
    highlightRect.h = TILE_SIZE;
    
    SDL_RenderFillRect(renderer, &highlightRect);
    
    // Reset blend mode back to default so other textures aren't corrupted
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    
}

void highlight_select_square(SDL_Renderer* renderer, int row, int col) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Color lightBlue = { 173, 216, 230, 128 };
    SDL_SetRenderDrawColor(renderer, lightBlue.r, lightBlue.g, lightBlue.b, lightBlue.a);

    SDL_Rect highlightRect;
    highlightRect.x = col * TILE_SIZE; // Columns map to X-axis
    highlightRect.y = row * TILE_SIZE; // Rows map to Y-axis
    highlightRect.w = TILE_SIZE;
    highlightRect.h = TILE_SIZE;
    
    SDL_RenderFillRect(renderer, &highlightRect);
    
    // Reset blend mode back to default so other textures aren't corrupted
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    
}
void draw_highlight(SDL_Renderer* renderer, int row , int col, vector<Move> moves) {
    if(select_mode == false) {
        highlight_select_square(renderer,row,col);
        for(auto& m : moves) {
            highlight_moves_square(renderer,m.to_row,m.to_col);
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
                sourceRect.y = 0;
            } else {
                sourceRect.y = (int)(img_y / 2);
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
            destinationRect.x = TILE_SIZE * j;  
            destinationRect.y = TILE_SIZE * i;   
            destinationRect.w = TILE_SIZE;  
            destinationRect.h = TILE_SIZE;  

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
    
    Board board = Board(true);
    
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
                
                if(select_mode) {
                    
                    SDL_GetMouseState(&selected_x,&selected_y);
                    selected_x = selected_x/ TILE_SIZE;
                    selected_y = selected_y / TILE_SIZE;
                    board.get_square(selected_y,selected_x).print();
                    Piece* p = board.get_square(selected_y,selected_x).get_piece();
                    if(p) {
                        if(player_turn == p->get_team() ) {
                            moves = board.get_moves_for_piece(selected_y,selected_x);
                            if (!moves.empty()) {
                                for(int i = 0; i < (int)moves.size(); i++) {
                                    cout << "move " << i <<": " << moves.at(i).to_row << " " << moves.at(i).to_col << endl;
                                }
                            }
                            select_mode = false;
                        }
                        
                    }
                    
                    
                    
                    
                    
                    
                    
                } 
                //else move mode
                else {
                    SDL_GetMouseState(&move_x,&move_y);
                    move_x = move_x/ TILE_SIZE;
                    move_y = move_y / TILE_SIZE;
                    if(!(selected_x == move_x && selected_y == move_y)) { //  cancel the same square as selected
                        //cout << "same square selected, cancel move" << endl;
                    
                        Move player_move = Move(move_y,move_x);

                        if(find(moves.begin(),moves.end(), player_move) != moves.end()) {
                            cout << "valid move" << endl;
                            board.move_piece(selected_y,selected_x,move_y,move_x);
                            player_turn = !player_turn;
                        }
                        else {
                            cout << "invalid move" << endl;
                        }
                        
                    }
                    
                    select_mode = true;
                }
                
                

              
            }
        }

        
        drawBoard(renderer, board);
        printPieces(renderer,board,texture,img_x,img_y);
        draw_highlight(renderer,selected_y,selected_x,moves);
        SDL_RenderPresent(renderer);
        
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    return 0;
}


