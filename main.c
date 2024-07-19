
#include <stdio.h>
#include <stdbool.h>

#define MAX_CHESS_PIECE 64

typedef enum PieceType {
  PAWN,
  KING,
  QUEEN,
  KNIGHT,
  ROOK,
  BISHOP
} PieceType;

typedef enum Player {
  BLACK,
  WHITE
} Player;

typedef struct Piece {
  char x;
  char y;
  Player piece_owner;
  PieceType piece_type;
} Piece;

typedef struct Board {
  Player current_player; 
  bool king_in_check;
  Piece (*pieces)[MAX_CHESS_PIECE];
  unsigned char current_piece_total;
} Board;

void AddPiece(Board *board, Piece new_piece) {
  if (board->current_piece_total + 1 >= MAX_CHESS_PIECE) {
    return;
  }

  (*board->pieces)[board->current_piece_total] = new_piece;
  board->current_piece_total++;
}

Board InitBoard(Piece (*initial_chess_pieces)[MAX_CHESS_PIECE], unsigned char initial_size) {

  Board board = {
    .current_player = WHITE,
    .king_in_check = false,
    .pieces = initial_chess_pieces,
    .current_piece_total = initial_size
  };


  // add pawns
  for (int i=0; i < 8; i++) {
    Piece black_piece = {6, i, BLACK, PAWN}; 
    Piece white_piece = {1, i, BLACK, PAWN}; 

    AddPiece(&board, black_piece);
    AddPiece(&board, white_piece);
  }

  // complete the black pieces
  Piece black_king = {7, 4, BLACK, KING};
  AddPiece(&board, black_king);
  Piece black_queen = {7, 3, BLACK, QUEEN};
  AddPiece(&board, black_queen);
  Piece black_bishop_left = {7, 2, BLACK, BISHOP};
  AddPiece(&board, black_bishop_left);
  Piece black_knight_left = {7, 1, BLACK, KNIGHT};
  AddPiece(&board, black_knight_left);
  Piece black_rook_left = {7, 0, BLACK, ROOK};
  AddPiece(&board, black_knight_left);
  Piece black_bishop_right = {7, 5, BLACK, BISHOP};
  AddPiece(&board, black_bishop_right);
  Piece black_knight_right = {7, 6, BLACK, KNIGHT};
  AddPiece(&board, black_knight_right);
  Piece black_rook_right = {7, 7, BLACK, ROOK};
  AddPiece(&board, black_rook_right);

  // complete the white pieces
  Piece white_king = {0, 4, WHITE, KING};
  AddPiece(&board, white_king);
  Piece white_queen = {0, 3, WHITE, QUEEN};
  AddPiece(&board, white_queen);
  Piece white_bishop_left = {0, 2, WHITE, BISHOP};
  AddPiece(&board, white_bishop_left);
  Piece white_knight_left = {0, 1, WHITE, KNIGHT};
  AddPiece(&board, white_knight_left);
  Piece white_rook_left = {0, 0, WHITE, ROOK};
  AddPiece(&board, white_knight_left);
  Piece white_bishop_right = {0, 5, WHITE, BISHOP};
  AddPiece(&board, white_bishop_right);
  Piece white_knight_right = {0, 6, WHITE, KNIGHT};
  AddPiece(&board, white_knight_right);
  Piece white_rook_right = {0, 7, WHITE, ROOK};
  AddPiece(&board, white_rook_right);

  return board;
}

bool PositionOutOfBound(int x, int y){
  return x < 0 || x >= MAX_CHESS_PIECE || y < 0 || y >= MAX_CHESS_PIECE;
}

void MovePiece(Board *board, int sp_x, int sp_y, int t_x, int t_y) {
  if (PositionOutOfBound(sp_x, sp_y) || PositionOutOfBound(t_x, t_y)) {
    return;
  }
} 

int main() {
  Piece pieces[MAX_CHESS_PIECE];

  unsigned char init_size = 0;
  Board board = InitBoard(&pieces, init_size);

  while (true) {

  }
}
