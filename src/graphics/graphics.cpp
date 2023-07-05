#include "graphics.hpp"
#include "load.hpp"

Graphics::Graphics(){}

Graphics::~Graphics(){}

Graphics::Graphics( SDL_Renderer* gRenderer, int board_x, int board_y, int board_widht, int board_height ){
    this->board_x = board_x;
    this->board_y = board_y;
    this->board_widht = board_widht;
    this->board_height = board_height;

    this->gRenderer = gRenderer;

    this->board_background = loadTexture("res/Other/Board1.bmp" , gRenderer);

    this->blackPawn = loadTexture("res/Pieces/Black/p.bmp" , gRenderer);
    this->blackKnight = loadTexture("res/Pieces/Black/n.bmp" , gRenderer);
    this->blackBishop = loadTexture("res/Pieces/Black/b.bmp" , gRenderer);
    this->blackRook = loadTexture("res/Pieces/Black/r.bmp" , gRenderer);
    this->blackQueen = loadTexture("res/Pieces/Black/q.bmp" , gRenderer);
    this->blackKing = loadTexture("res/Pieces/Black/k.bmp" , gRenderer);

    this->whitePawn = loadTexture("res/Pieces/White/p.bmp" , gRenderer);
    this->whiteKnight = loadTexture("res/Pieces/White/n.bmp" , gRenderer);
    this->whiteBishop = loadTexture("res/Pieces/White/b.bmp" , gRenderer);
    this->whiteRook = loadTexture("res/Pieces/White/r.bmp" , gRenderer);
    this->whiteQueen = loadTexture("res/Pieces/White/q.bmp" , gRenderer);
    this->whiteKing = loadTexture("res/Pieces/White/k.bmp" , gRenderer);

    this->highlighted_square = {-1, -1};
    this->highlight_color = {150, 80, 20};
}

void Graphics::draw_board( ChessBoard cb ){

    SDL_Rect rect = {this->board_x, this->board_y, this->board_widht, this->board_height};
    SDL_RenderCopy( this->gRenderer, this->board_background, NULL, &rect );

    if (this->highlighted_square.first != -1 && this->highlighted_square.second != -1)
    {
        SDL_SetRenderDrawColor( gRenderer, this->highlight_color[0], this->highlight_color[1], this->highlight_color[2], 0xFF );
        SDL_Rect rect = {this->highlighted_square.first * (this->board_widht / 8), this->highlighted_square.second * (this->board_height / 8), this->board_widht / 8, this->board_height / 8};
        SDL_RenderFillRect(this->gRenderer, &rect);
    }

    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            SDL_Rect rect = {this->board_x + (this->board_widht / 8) * i + ((this->board_widht / 8) - ( this->board_widht / 10)) / 2, this->board_y + (this->board_height / 8) * j + ((this->board_height / 8) - ( this->board_height / 10)) / 2, this->board_widht / 10, this->board_height / 10};
            
            if (cb.board[i][j].color == WHITE)
            {
                switch (cb.board[i][j].type)
                {
                    case PAWN: SDL_RenderCopy( this->gRenderer, this->whitePawn, NULL, &rect ); break;
                    case KNIGHT: SDL_RenderCopy( this->gRenderer, this->whiteKnight, NULL, &rect ); break;
                    case BISHOP: SDL_RenderCopy( this->gRenderer, this->whiteBishop, NULL, &rect ); break;
                    case ROOK: SDL_RenderCopy( this->gRenderer, this->whiteRook, NULL, &rect ); break;
                    case QUEEN: SDL_RenderCopy( this->gRenderer, this->whiteQueen, NULL, &rect ); break;
                    case KING: SDL_RenderCopy( this->gRenderer, this->whiteKing, NULL, &rect ); break;
                    default: break;
                }
            } else if (cb.board[i][j].color == BLACK)
            {
                switch (cb.board[i][j].type)
                {
                    case PAWN: SDL_RenderCopy( this->gRenderer, this->blackPawn, NULL, &rect ); break;
                    case KNIGHT: SDL_RenderCopy( this->gRenderer, this->blackKnight, NULL, &rect ); break;
                    case BISHOP: SDL_RenderCopy( this->gRenderer, this->blackBishop, NULL, &rect ); break;
                    case ROOK: SDL_RenderCopy( this->gRenderer, this->blackRook, NULL, &rect ); break;
                    case QUEEN: SDL_RenderCopy( this->gRenderer, this->blackQueen, NULL, &rect ); break;
                    case KING: SDL_RenderCopy( this->gRenderer, this->blackKing, NULL, &rect ); break;
                    default: break;
                }
            }
        }
    }
}

void Graphics::highlight_square( std::pair<int, int> tile ){
    this->highlighted_square = tile;
}


void Graphics::remove_highlight(){
    this->highlighted_square = {-1, -1};
}
