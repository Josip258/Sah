#include <iostream>
//#include <windows.h>

#include "game.hpp"
#include "fen_load.hpp"
#include "algorithm/algorithm.hpp"


Game::Game(SDL_Renderer* gRenderer, SDL_Window* gWindow){
    this->pocetni_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    ChessBoard cb = FEN_to_board(pocetni_FEN);
    this->played_moves.push_back(cb);
    this->gRenderer = gRenderer;
    this->graphics = Graphics(gRenderer, 0, 0, 1000, 1000);
    this->selected_square = {-1, -1};
    this->gWindow = gWindow;
    this->dubina = 4;
}

Game::Game(std::string FEN, SDL_Renderer* gRenderer, SDL_Window* gWindow){
    this->pocetni_FEN = FEN;
    ChessBoard cb = FEN_to_board(pocetni_FEN);
    this->played_moves.push_back(cb);
    this->gRenderer = gRenderer;
    this->graphics = Graphics(gRenderer, 0, 0, 1000, 1000);
    this->selected_square = {-1, -1};
    this->gWindow = gWindow;
    this->dubina = 4;
}

Game::~Game(){}

ChessBoard Game::getCurrentBoard(){
    return this->played_moves.back();
}

bool Game::playMove(ChessBoard cb){
    std::vector<ChessBoard> pm = possibleMoves(this->played_moves.back());
    
    bool legal = false;
    for (long long unsigned int i = 0; i < pm.size(); i++)
    {
        if (chessBoardCompare(pm[i], cb))
        {
            this->played_moves.push_back(cb);
            legal = true;
            break;
        }
    }
    
    return legal;
}

bool Game::returnLastMove(){
    if (this->played_moves.size() > 2)
    {
        this->played_moves.pop_back();
        this->played_moves.pop_back();
        return true;
    } else {
        return false;
    }
}

void Game::draw(){
        this->graphics.draw_board(this->played_moves.back());
        updateTitle();
}



void Game::click(int pos_x, int pos_y){
    int x = -1, y = -1;
    x = this->graphics.board_x / 8;
    for (int i = 0; i < 8; i++)
    {
        if (pos_x > i * (this->graphics.board_widht / 8) && pos_x < (i + 1) * (this->graphics.board_widht / 8))
        {
            x = i;
        }

        if (pos_y > i * (this->graphics.board_height / 8) && pos_y < (i + 1) * (this->graphics.board_height / 8))
        {
            y = i;
        }
    }
    
    if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
    {
        if (this->selected_square.first == -1 && this->selected_square.second == -1)
        {
            this->selected_square = {x, y};
            this->graphics.highlight_square(this->selected_square);

        } else if (this->selected_square.first == x && this->selected_square.second == y)
        {
            this->selected_square = {-1 ,-1};
            this->graphics.remove_highlight();
        } else {
            ChessBoard potez;
            if (!odigrajPotez(selected_square, {x, y}, this->getCurrentBoard(), &potez))
            {
                std::cout << "Ilegalan potez!" << std::endl;

            } else {
                this->played_moves.push_back(potez);

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                this->draw();
                SDL_RenderPresent( gRenderer );
                
                this->played_moves.push_back(izracunajPotez());
            }

            this->selected_square = {-1, -1};
            this->graphics.remove_highlight();            
        }
    }
}

ChessBoard Game::izracunajPotez(){

    ChessBoard cb = this->getCurrentBoard(); 
    std::vector<ChessBoard> moguci_potezi = possibleMoves(cb);
    std::vector<float> evaluacije;
    std::vector<int> najbolji_potezi;
    int trenutni_najbolji = 0;

    if (moguci_potezi.size() == 0)
    {
        std::cout << "Nema mogucih poteza" << std::endl;
        return cb;
    }
    
    for (long long unsigned int i = 0; i < moguci_potezi.size(); i++)
    {
        evaluacije.push_back(minimax(moguci_potezi[i], dubina, -2000, 2000));
        
        if (cb.whiteOnMove)
        {
            if (evaluacije[trenutni_najbolji] < evaluacije[i])
            {
                trenutni_najbolji = i;
                najbolji_potezi.clear();
                najbolji_potezi.push_back(i);
            } else if (evaluacije[trenutni_najbolji] == evaluacije[i])
            {
                najbolji_potezi.push_back(i);
            }

        } else {
            if (evaluacije[trenutni_najbolji] > evaluacije[i])
            {
                trenutni_najbolji = i;
                najbolji_potezi.clear();
                najbolji_potezi.push_back(i);
            } else if (evaluacije[trenutni_najbolji] == evaluacije[i])
            {
                najbolji_potezi.push_back(i);
            }
        }
    }

    
    srand(time(0));
    int t = rand() % najbolji_potezi.size();
    return moguci_potezi[najbolji_potezi[t]];
}

void Game::reset(){
    this->played_moves.clear();
    this->played_moves.push_back(FEN_to_board(pocetni_FEN));
}

void Game::swapSides(){
    this->reset();
    this->played_moves.push_back(izracunajPotez());
}

void Game::updateTitle(){
    std::string s = "Sah aplikacija | dubina = " + std::to_string(this->dubina + 1);
    SDL_SetWindowTitle(this->gWindow, &s[0]);
}

void Game::povecajDubinu(){
    if (dubina < 7)
    {
        this->dubina++;
    }
}

void Game::smanjiDubinu(){
    if (dubina > 1)
    {
        this->dubina--;
    }
}