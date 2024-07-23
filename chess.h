
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHESS_PIECE 64
#define TOTAL_PIECES 6

typedef enum PieceType {
  NEUTRAL,
  PAWN,
  KING,
  QUEEN,
  KNIGHT,
  ROOK,
  BISHOP
} PieceType;

typedef enum ChessPlayer { BLACK_P, WHITE_P } ChessPlayer;

typedef struct PieceMovement {
  unsigned char max_diff;
  unsigned char total_movement;
  unsigned char movements[8][2];
} PieceMovement;

typedef struct Piece {
  unsigned char x;
  unsigned char y;
  ChessPlayer piece_owner;
  PieceType piece_type;
  bool taken;
  char last_movement[2];
} Piece;

typedef struct Board {
  ChessPlayer current_player;
  bool king_in_check;
  bool checkmated;
  Piece *promoted_pawn;
  unsigned char current_piece_total;
  PieceMovement (*movements)[TOTAL_PIECES];
  Piece (*pieces)[MAX_CHESS_PIECE];
} Board;

Board InitBoard(Piece (*initial_chess_pieces)[MAX_CHESS_PIECE],
                PieceMovement (*movements)[TOTAL_PIECES]);

void DisplayBoard(unsigned char (*board2d)[8][8], char (*piece_symbols)[16][5]);

void InitPieceSymbols(char (*piece_symbols)[16][5]);

void MapBoardTo2dBoard(Board *board, unsigned char (*board2d)[8][8]);

void UserInput(Board *board, unsigned char (*taken_move)[4]);

void UpdateBoard(unsigned char (*board2d)[8][8],
                 unsigned char (*taken_move)[4]);
