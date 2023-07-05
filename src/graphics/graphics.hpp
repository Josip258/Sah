#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../algorithm/chess_board.hpp"

class Graphics
{
public:
    SDL_Renderer* gRenderer;

    SDL_Texture* board_background;
    SDL_Texture* whitePawn;
    SDL_Texture* blackPawn;
    SDL_Texture* whiteKnight;
    SDL_Texture* blackKnight;
    SDL_Texture* whiteBishop;
    SDL_Texture* blackBishop;
    SDL_Texture* whiteRook;
    SDL_Texture* blackRook;
    SDL_Texture* whiteQueen;
    SDL_Texture* blackQueen;
    SDL_Texture* whiteKing;
    SDL_Texture* blackKing;

    int board_x; 
    int board_y; 
    int board_widht; 
    int board_height;

    std::pair<int, int> highlighted_square;
    std::vector<int> highlight_color;

    Graphics();
    Graphics( SDL_Renderer* gRenderer, int board_x, int board_y, int board_widht, int board_height );
    ~Graphics();

    void draw_board( ChessBoard cb );

    void highlight_square( std::pair<int, int> tile );
    void remove_highlight();
};