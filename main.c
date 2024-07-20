
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

typedef struct PieceMovement {
  unsigned char max_diff;
  unsigned char total_movement;
  unsigned char movements[8][2];
} PieceMovement;

typedef struct Piece {
  unsigned char x;
  unsigned char y;
  Player piece_owner;
  PieceType piece_type;
  bool has_moved; // change this into an actual movement taken
  bool taken;
} Piece;

typedef struct Board {
  Player current_player; 
  bool king_in_check;
  bool checkmated;
  unsigned char current_piece_total;
  PieceMovement (*movements)[6];
  Piece (*pieces)[MAX_CHESS_PIECE];
} Board;

void AddPiece(Board *board, Piece new_piece) {
  if (board->current_piece_total + 1 >= MAX_CHESS_PIECE) {
    return;
  }

  (*board->pieces)[board->current_piece_total] = new_piece;
  board->current_piece_total++;
}

Board InitBoard(Piece (*initial_chess_pieces)[MAX_CHESS_PIECE], unsigned char initial_size, PieceMovement (*movements)[6]) {

  PieceMovement pawn_movement = {
    .max_diff = 2, 
    .total_movement = 1,
    .movements = {{1, 0}}
  };
  PieceMovement king_movement = {
    .max_diff = 1,
    .total_movement = 8,
    .movements = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, 1}, {1, 1}, {-1, -1}, {1, -1}}
  };
  PieceMovement queen_movement = {
    .max_diff = 8, 
    .total_movement = 8,
    .movements = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, 1}, {1, 1}, {-1, -1}, {1, -1}}
  };
  PieceMovement bishop_movement = {
    .max_diff = 8, 
    .total_movement = 4,
    .movements = {{-1, 1}, {1, 1}, {-1, -1}, {1, -1}}
  };
  PieceMovement rook_movement = {
    .max_diff = 8, 
    .total_movement = 4,
    .movements = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}}
  };
  PieceMovement knight_movement = {
    .max_diff = 1, 
    .total_movement = 8,
    .movements = {{-2,-1}, {-2, 1}, {2, -1}, {2,1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}}
  };

  (*movements)[PAWN] = pawn_movement;
  (*movements)[KING] = king_movement;
  (*movements)[QUEEN] = queen_movement;
  (*movements)[BISHOP] = bishop_movement;
  (*movements)[ROOK] = bishop_movement;
  (*movements)[KNIGHT] = knight_movement;

  Board board = {
    .current_player = WHITE,
    .king_in_check = false,
    .pieces = initial_chess_pieces,
    .current_piece_total = initial_size,
    .movements = movements
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

Piece *GetPiece(Board *board, int x, int y) {
  for (int i=0; i < board->current_piece_total; i++) {
    if ((*board->pieces[i]).x == x && (*board->pieces[i]).y == y && !(*board->pieces[i]).taken) {
      return &(*board->pieces[i]);
    }
  }
  return NULL;
}

bool PositionOutOfBound(int x, int y) {
  return x < 0 || x >= MAX_CHESS_PIECE || y < 0 || y >= MAX_CHESS_PIECE;
}

unsigned char* GetDirection(int x1, int y1, int x2, int y2) {
  // TODO: somehow get the normalized direction from 2 points
  // probably just the diff?
  static unsigned char base_direction[2];

  base_direction[0] = x2 - x1;
  base_direction[1] = y2 - y1;

  return base_direction;
}

bool BlockedByNonTargetPiece(Board *board, int max_offset, int st_x, int st_y, int dx, int dy, int tx, int ty) {

  // check if pawn can go to the direction if there is no other pawn blocking the way
  // except the target not so efficient because we checked every possible direction
  // TODO: calculate the direction and see whether that direction is possible to be accessed

  for (int i = 1; i <= max_offset; i++) {
    int x_offset = st_x + dx * st_x;
    int y_offset = st_y + dy * st_y;

    if (x_offset == tx && y_offset == ty) {
      continue;
    }

    Piece *piece = GetPiece(board, x_offset, y_offset);
    if (piece != NULL){
      return true;
    }
  }

  return false;
}

void MovePiece(Board *board, int sp_x, int sp_y, int t_x, int t_y) {

  if (board->king_in_check) {
    return;
  }

  if (PositionOutOfBound(sp_x, sp_y) || PositionOutOfBound(t_x, t_y)) {
    return;
  }

  Piece *sp_piece = GetPiece(board, sp_x, sp_y);
  Piece *t_piece = GetPiece(board, t_x, t_y);

  // moving non existent piece should return null
  if (sp_piece == NULL) {
    return;
  }

  // cannot move piece if it's not the ownership of the player
  if (sp_piece->piece_owner != board->current_player) {
    return;
  }

  if (t_piece != NULL && t_piece->piece_owner == sp_piece->piece_owner) {
    return;
  }

  PieceMovement (*movements)[6] = board->movements;

  if (sp_piece->piece_type == PAWN) {
    // could either move it 2 steps or 1 step depending whether it has already taken step previously
    // en passant
    // 2 or 1 step ahead on initial start
    int x_diff = t_x - sp_x;
    int y_dif = t_y - sp_y;

    PieceMovement pawn_movement = (*movements)[PAWN];
    int direction = sp_piece->piece_owner == WHITE ? -1 : 1;

    unsigned char *base_direction = GetDirection(sp_x, sp_y, t_x, t_y);
    unsigned char max_diff;

    bool valid_direction = false;

    // check if direction is valid
    for (int i = 0; i < pawn_movement.total_movement; i++) {
      int dx = direction * pawn_movement.movements[i][0];
      int dy = pawn_movement.movements[i][1];

      if (base_direction[0] == dx && base_direction[1] == dy) {
        valid_direction = true;
        max_diff = pawn_movement.max_diff;
        break;
      }
    }

    if (!valid_direction) {
      return;
    }

    bool blocked = BlockedByNonTargetPiece(
      board, 
      max_diff, 
      sp_x, 
      sp_y,
      base_direction[0], 
      base_direction[1],
      t_x,
      t_y
    );

    if (blocked) {
      return;
    }

    // if 2 step but already move then we cant take this step
    if (base_direction[0] == 2 && sp_piece->has_moved) {
      return;
    }

    // eat the piece
    if (t_piece != NULL && !t_piece->taken) {
      t_piece->taken = true;
      sp_piece->x = t_x;
      sp_piece->y = t_y;
      sp_piece->has_moved = true;
    } 

  }
  return;
} 

int main() {

  Piece pieces[MAX_CHESS_PIECE];
  PieceMovement movements[6];

  unsigned char init_size = 0;
  Board board = InitBoard(&pieces, init_size, &movements);

  while (true) {

  }
}
