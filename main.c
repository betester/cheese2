
#include "chess.h"

int main() {

  printf("Running Game\n");

  Piece pieces[MAX_CHESS_PIECE];
  PieceMovement movements[6];
  unsigned char board2d[8][8];
  char piece_symbols[16][5];

  Board board = InitBoard(&pieces,  &movements);
  MapBoardTo2dBoard(&board, &board2d);
  InitPieceSymbols(&piece_symbols);
  
  while (true) {
    DisplayBoard(&board2d, &piece_symbols);
    UserInput(&board);
  }
}
