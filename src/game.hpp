#pragma once

#include <vector>
#include <string>

#include "graphics/graphics.hpp"
#include "algorithm/chess_board.hpp"

class Game
{
private:
    std::vector<ChessBoard> played_moves;
    SDL_Renderer* gRenderer;
    SDL_Window* gWindow;
    Graphics graphics;
    std::pair<int, int> selected_square;

    Uint32 startTime = 0;
    const int DISPLAY_FPS = 60;
    const int DISPLAY_FRAME_TIME = 1000 / DISPLAY_FPS;

    std::string pocetni_FEN;
    int dubina;

public:
    //Normalna pozicija
    Game(SDL_Renderer* gRenderer, SDL_Window* gWindow);

    //Ucitaj poziciju iz FEN-a
    Game(std::string FEN, SDL_Renderer* gRenderer, SDL_Window* gWindow);

    ~Game();
    
    ChessBoard getCurrentBoard();

    //false ako je potez ilegalan
    bool playMove(ChessBoard cb);

    //false ako je zadnji potez prvi potez, vraca potez
    bool returnLastMove();

    void draw();
        
    void click(int pos_x, int pos_y);

    ChessBoard izracunajPotez();

    //Resetiraj igru
    void reset();

    //Zamijeni strane s botom i resetiraj igru
    void swapSides();

    void updateTitle();

    void povecajDubinu();

    void smanjiDubinu();
};
