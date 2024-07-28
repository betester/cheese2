
#include "chess.h"
#include "raylib.h"

#define CHESS_BOARD_HEIGHT 8
#define CHESS_BOARD_WIDTH 8

void addPiece(Board *board, Piece new_piece) {
  if (board->current_piece_total + 1 >= MAX_CHESS_PIECE) {
    return;
  }

  (*board->pieces)[board->current_piece_total] = new_piece;
  board->current_piece_total++;
}

unsigned char pieceId(ChessPlayer player, PieceType type) {
  return (player << 3) | type;
}

Board initBoard(Piece (*initial_chess_pieces)[MAX_CHESS_PIECE], PieceMovement (*movements)[6]) {

  PieceMovement pawn_movement = {
    .max_diff = 2, 
    .total_movement = 3,
    .movements = {{1, 0}, {1, -1}, {1, 1}}
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
    .current_player = WHITE_P,
    .king_in_check = false,
    .pieces = initial_chess_pieces,
    .current_piece_total = 0,
    .movements = movements,
    .promoted_pawn = NULL
  };

  // add pawns
  for (unsigned char i=0; i < 8; i++) {
    Piece black_piece = {
      .x = 6,
      .y = i,
      .piece_owner = BLACK_P,
      .piece_type = PAWN,
      .taken = false
    }; 
    Piece white_piece = {
      .x = 1,
      .y = i,
      .piece_owner = WHITE_P,
      .piece_type = PAWN,
      .taken = false
    }; 

    addPiece(&board, black_piece);
    addPiece(&board, white_piece);
  }

  // complete the black pieces
  Piece black_king = {
    .x = 7,
    .y = 4,
    .piece_owner = BLACK_P,
    .piece_type = KING,
    .taken = false
  };
  addPiece(&board, black_king);
  Piece black_queen = {
    .x = 7,
    .y = 3, 
    .piece_owner = BLACK_P, 
    .piece_type = QUEEN,
    .taken = false
  };
  addPiece(&board, black_queen);
  Piece black_bishop_left = {
    .x = 7,
    .y = 2,
    .piece_owner = BLACK_P,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, black_bishop_left);
  Piece black_knight_left = {
    .x = 7,
    .y = 1,
    .piece_owner = BLACK_P,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, black_knight_left);
  Piece black_rook_left = {
    .x = 7,
    .y = 0,
    .piece_owner = BLACK_P,
    .piece_type = ROOK,
    .taken = false
  };
  addPiece(&board, black_rook_left);
  Piece black_bishop_right = {
    .x = 7,
    .y = 5,
    .piece_owner = BLACK_P,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, black_bishop_right);
  Piece black_knight_right = {
    .x = 7,
    .y = 6,
    .piece_owner = BLACK_P,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, black_knight_right);
  Piece black_rook_right = {
    .x = 7,
    .y = 7,
    .piece_owner = BLACK_P,
    .piece_type = ROOK,
    .taken = false
  };
  addPiece(&board, black_rook_right);

  // complete the white pieces
  Piece white_king = {
    .x = 0,
    .y = 4,
    .piece_owner = WHITE_P,
    .piece_type = KING,
    .taken = false
  };
  addPiece(&board, white_king);
  Piece white_queen = {
    .x = 0,
    .y = 3,
    .piece_owner = WHITE_P,
    .piece_type = QUEEN,
    .taken = false
  };
  addPiece(&board, white_queen);
  Piece white_bishop_left = {
    .x = 0,
    .y = 2,
    .piece_owner = WHITE_P,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, white_bishop_left);
  Piece white_knight_left = {
    .x = 0,
    .y = 1,
    .piece_owner = WHITE_P,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, white_knight_left);
  Piece white_rook_left = {
    .x = 0,
    .y = 0,
    .piece_owner = WHITE_P,
    .piece_type = ROOK,
    .taken = false
  };
  addPiece(&board, white_rook_left);
  Piece white_bishop_right = {
    .x = 0,
    .y = 5,
    .piece_owner = WHITE_P,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, white_bishop_right);
  Piece white_knight_right = {
    .x = 0,
    .y = 6,
    .piece_owner = WHITE_P,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, white_knight_right);
  Piece white_rook_right = {
    .x = 0,
    .y = 7,
    .piece_owner = WHITE_P,
    .piece_type = ROOK,
    .taken = false
  };
  addPiece(&board, white_rook_right);

  return board;
}

Piece *getPiece(Board *board, int x, int y) {
  for (int i = 0; i < board->current_piece_total; i++) {
    if ((*board->pieces)[i].x == x && (*board->pieces)[i].y == y) {
      return &(*board->pieces)[i];
    }
  }
  return NULL;
}

bool positionOutofBound(int x, int y) {
  return x < 0 || x >= MAX_CHESS_PIECE || y < 0 || y >= MAX_CHESS_PIECE;
}

bool blockedByNonTargetPiece(Board *board, int max_offset, int st_x, int st_y, int dx, int dy, int tx, int ty) {

  //TODO: inline this function only called once anyway
  // check if pawn can go to the direction if there is no other pawn blocking the way
  // except the target not so efficient because we checked every possible direction

  for (int i = 1; i <= max_offset; i++) {
    int x_offset = st_x + dx * i;
    int y_offset = st_y + dy * i;

    if (x_offset == tx && y_offset == ty) {
      continue;
    }

    Piece *piece = getPiece(board, x_offset, y_offset);
    if (piece != NULL){
      return true;
    }
  }

  return false;
}


bool validDirection(PieceMovement *movement, char dx, char dy, char x_dir, char y_dir) {
  bool valid_direction = false;

  // check if direction is valid
  for (int j = 1; j <= movement->max_diff; j++) {
    for (int i = 0; i < movement->total_movement; i++) {
      char valid_dx = x_dir * movement->movements[i][0];
      char valid_dy = y_dir * movement->movements[i][1];

      if (j * valid_dx == dx && j * valid_dy == dy) {
        return true;
      }
    }

  }

  return false;
}

bool movePiece(Board *board, int sp_x, int sp_y, int t_x, int t_y) {

  if (board->promoted_pawn != NULL) {
    printf("Cannot move the pieces as the pawn should be promoted\n");
    return false;
  }

  if (board->king_in_check) {
    printf("Cannot move piece as the king is in check\n");
    return false;
  }

  if (positionOutofBound(sp_x, sp_y) || positionOutofBound(t_x, t_y)) {
    printf("Invalid position due to out of board bound\n");
    return false;
  }


  Piece *sp_piece = getPiece(board, sp_x, sp_y);
  Piece *t_piece = getPiece(board, t_x, t_y);

  // moving non existent piece should return null
  if (sp_piece == NULL) {
    printf("Cannot move empty piece\n");
    return false;
  }

  // cannot move piece if it's not the ownership of the player
  if (sp_piece->piece_owner != board->current_player) {
    printf("Cannot move opponent piece\n");
    return false;
  }

  if (t_piece != NULL && t_piece->piece_owner == sp_piece->piece_owner) {
    printf("Cannot attack your own piece\n");
    return false;
  }

  PieceMovement (*movements)[6] = board->movements;

  int dx = t_x - sp_x;
  int dy = t_y - sp_y;

  PieceMovement pawn_movement = (*movements)[sp_piece->piece_type];
  int direction = (sp_piece->piece_type == PAWN && sp_piece->piece_owner == WHITE_P) ? 1 : -1;

  unsigned char max_diff = pawn_movement.max_diff;

  if (!validDirection(&pawn_movement, dx, dy, direction, 1)) {
    printf("Cannot move piece to direction %d %d with direction %d\n", dx, dy, direction);
    return false;
  }

  bool blocked = blockedByNonTargetPiece(
    board, 
    max_diff, 
    sp_x, 
    sp_y,
    dx, 
    dy,
    t_x,
    t_y
  );

  if (blocked) {
    printf("Cannot move to target due to blocked by other piece\n");
    return false;
  }

  if (sp_piece->piece_type == PAWN) {
    // could either move it 2 steps or 1 step depending whether it has already taken step previously
    // en passant
    // 2 or 1 step ahead on initial start

    // if 2 step but already move then we cant take this step
    if (dx == 2 && !(sp_piece->last_movement[0] == 0 && sp_piece->last_movement[1] == 0)) {
      return false;
    }

    // if diagonal steps are taken

    if (dx == 1 && (dy == 1 || dy == -1)) {

      Piece *sp_beside_piece = getPiece(board, sp_x + dx, sp_y + dy);

      if (t_piece != NULL) {
        printf("Cannot do en passant if the target position is not empty%s\n");
        return false;
      }

      if (sp_beside_piece == NULL) {
        printf("Cannot do en passant no piece on the direction\n");
        return false;
      }

      if (!(sp_beside_piece->last_movement[0] == 2 && sp_beside_piece->last_movement[1] == 0)) {
        printf("Cannot do en passant if two steps are not taken\n");
        return false;
      }
    }

    // eat the piece
    if (t_piece != NULL && !t_piece->taken) {
      t_piece->taken = true;
    } 

    sp_piece->x = t_x;
    sp_piece->y = t_y;
    // update last taken movement
    sp_piece->last_movement[0] = dx;
    sp_piece->last_movement[1] = dy;

    if (t_x == 0 || t_x == 7) {
      board->promoted_pawn = sp_piece;
    }
  }

  // change the current allowed player to move
  board->current_player = (board -> current_player + 1) % 2;

  // TODO: 
  // 1. handle when the king is in check or not for the current player 
  // just loop and find the king, once we find it we check for every enemy piece whether it attacks the king or not.
  // 2. handle whether the king is on checkmate or not
  // this needs to know whether the king is on check or not. but the idea is to see every possible direction the king can go
  // then check whether it's possible to move to certain position if it's not attacked and not occupied. checkmate happens only if 
  // the king is on check with nowhere to go.

  // finding the king position
  Piece *opponent_king;

  for (int i = 0; i < board->current_piece_total; i++) {
    if ((*board->pieces)[i].piece_owner == board->current_player && (*board->pieces)[i].piece_type == KING) {
      opponent_king = &(*board->pieces)[i];
      break;
    }
  }

  unsigned char kx = opponent_king->x;
  unsigned char ky = opponent_king->y;

  PieceMovement king_movements = (*movements)[KING];

  int king_surrounding_loc[king_movements.total_movement][2];

  for (int i = 0; i < king_movements.total_movement; i++) {
    king_surrounding_loc[i][0] = kx + king_movements.movements[i][0];
    king_surrounding_loc[i][1] = ky + king_movements.movements[i][1];
  }

  bool king_in_check = false;

  for (int i = 0; i < board->current_piece_total;i++) {
    Piece piece = (*board->pieces)[i];

    if (piece.piece_owner == board->current_player || piece.taken) {
      continue;
    }
    PieceMovement piece_movement = (*movements)[piece.piece_type];

    int dx_k = kx - piece.x;
    int dy_k = ky - piece.y;

    if (validDirection(&piece_movement, dx_k, dy_k, kx, ky)) {

      king_in_check = king_in_check || blockedByNonTargetPiece(
        board, 
        piece_movement.max_diff, 
        piece.x, 
        piece.y,
        dx_k, 
        dy_k,
        kx,
        ky
      );
    }

    unsigned char total_surrounded = 0;
    unsigned char expected_surrounding_for_checkmate = king_movements.total_movement;

    for (int j = 0; j < king_movements.total_movement; j++) {
      if (positionOutofBound(king_surrounding_loc[j][0], king_surrounding_loc[j][1])) {
        expected_surrounding_for_checkmate--;
        continue;
      }
      int dx_ks = king_surrounding_loc[j][0] - piece.x;
      int dy_ks = king_surrounding_loc[j][1] - piece.y;

      bool piece_can_go_to_surrounding = validDirection(&piece_movement, dx_ks, dy_ks, king_surrounding_loc[j][0], king_surrounding_loc[j][1]);

      bool piece_attacked_the_surrounding = blockedByNonTargetPiece(
        board, 
        max_diff, 
        piece.x, 
        piece.y,
        dx_ks, 
        dy_ks,
        king_surrounding_loc[j][0],
        king_surrounding_loc[j][1]
      );

      if (piece_can_go_to_surrounding && piece_attacked_the_surrounding) {
        total_surrounded++;
      }
    }

    if (king_in_check) {
      board->king_in_check = true;
    }

    if (king_in_check && total_surrounded == expected_surrounding_for_checkmate) {
      board->checkmated = true;
    }
  }

  return true;
}

void mapBoardTo2dBoard(Board *board, unsigned char (*board2d)[8][8]) {
  for (int i=0; i < board->current_piece_total; i++) {
    unsigned char x = (*board->pieces)[i].x;
    unsigned char y = (*board->pieces)[i].y;

    (*board2d)[x][y] = pieceId((*board->pieces)[i].piece_owner, (*board->pieces)[i].piece_type);
  }
}

void promotePawn(Board *board, PieceType promotion_type) {
  Piece *piece = board->promoted_pawn;

  if (piece == NULL || piece->piece_type != PAWN) {
    printf("Can only promote pawn\n");
    return;
  }

  if (promotion_type == PAWN || promotion_type == KING) {
    printf("Cannot promote to pawn or king\n");
    return;
  }

  if (piece->taken) {
    printf("Cannot promote taken piece\n");
    return;
  }

  piece->piece_type = promotion_type;
  board->promoted_pawn = NULL;
}

void UpdateBoard(unsigned char (*board2d)[8][8], unsigned char (*taken_move)[4]) {
  int sp_x, sp_y, t_x, t_y;

  if ((*taken_move)[0] == 0 && (*taken_move)[1] == 0 && (*taken_move)[2] == 0 && (*taken_move)[3] == 0) {
    return;
  }

  sp_x = (*taken_move)[0];
  sp_y = (*taken_move)[1];
  t_x = (*taken_move)[2];
  t_y = (*taken_move)[3];

  unsigned char prev_id = (*board2d)[sp_x][sp_y];
  (*board2d)[sp_x][sp_y] = (*board2d)[t_x][t_y];
  (*board2d)[t_x][t_y] = prev_id;
}

Vector2 getNormalizedPosition(int x_offset, int y_offset, int curr_x, int curr_y, int block_size) {
  int pos_x_diff = curr_x - x_offset; 
  int pos_y_diff = curr_y - y_offset; 

  // inverted because array and coordinate axis is fucked up
  Vector2 result = {.x = pos_y_diff/block_size, .y=pos_x_diff/block_size};
  return result;
}

void PlayChess() {
  printf("Running Game\n");

  Piece pieces[MAX_CHESS_PIECE] = {0};
  PieceMovement movements[6] = {0};
  unsigned char board2d[8][8] = {0};
  char piece_symbols[16][5] = {0};
  unsigned char taken_move[4] = {0};

  Board board = initBoard(&pieces, &movements);
  mapBoardTo2dBoard(&board, &board2d);

  int width = 800;
  int height = 600;

  int rectangle_size = 50;
  int padding_size = 5;
  int block_size = rectangle_size + padding_size;

  int offset_x_mid = width/2 - CHESS_BOARD_WIDTH * (block_size/2);
  int offset_y_mid = height/2 - CHESS_BOARD_HEIGHT * (block_size/2);

  bool initial_color_white = true;
  bool mouse_pressed = false;

  Vector2 mouse_released_pos, normalized_sp;

  Vector2 circles[2] = {
    {.x = 3 * block_size + offset_x_mid + rectangle_size/2, .y = 1 * block_size + offset_y_mid + rectangle_size/2},
    {.x = 3 * block_size + offset_x_mid + rectangle_size/2, .y = 6 * block_size + offset_y_mid + rectangle_size/2}
  };

  int last_circle_p;
  Vector2 last_circle_v;

  InitWindow(width, height, "Chess Game");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // drawing the tiles
    for (int y = 0; y < CHESS_BOARD_HEIGHT; y++) {
      bool current_tile_black = !initial_color_white;
      for (int x = 0; x < CHESS_BOARD_WIDTH; x++) {
        DrawRectangle(x * block_size + offset_x_mid, y * block_size + offset_y_mid, rectangle_size, rectangle_size, current_tile_black ? BLACK : WHITE);
        current_tile_black = !current_tile_black;
      }
      initial_color_white = !initial_color_white;
    }

    for (int i = 0; i < 2; i++) {
      DrawCircle(circles[i].x, circles[i].y, rectangle_size/2, RED);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      Vector2 mouse_pressed_pos = GetMousePosition();

      Vector2 mouse_factor = getNormalizedPosition(offset_x_mid, offset_y_mid, mouse_pressed_pos.x, mouse_pressed_pos.y, block_size);

      float x_normalized = mouse_factor.y * block_size + offset_x_mid + rectangle_size/2;
      float y_normalized = mouse_factor.x * block_size + offset_y_mid + rectangle_size/2;

      for (int i=0; i < 2; i++) {

        if (x_normalized == circles[i].x && y_normalized == circles[i].y) {
          last_circle_p = i;
          last_circle_v.x = x_normalized;
          last_circle_v.y = y_normalized;
          mouse_pressed = true;
          normalized_sp = mouse_factor;
          break;
        }
      }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      mouse_released_pos = GetMousePosition();

      Vector2 normalized_target = getNormalizedPosition(offset_x_mid, offset_y_mid, mouse_released_pos.x, mouse_released_pos.y, block_size);


      bool piece_moved = movePiece(&board, normalized_sp.x, normalized_sp.y, normalized_target.x, normalized_target.y);

      if (piece_moved) {
        circles[last_circle_p].y = normalized_target.x * (block_size) + offset_y_mid + rectangle_size/2;
        circles[last_circle_p].x = normalized_target.y * (block_size) + offset_x_mid + rectangle_size/2;
      } else {
        circles[last_circle_p].x = last_circle_v.x;
        circles[last_circle_p].y = last_circle_v.y;
      }

      mouse_pressed = false;
    }

    if (mouse_pressed) {
      Vector2 mouse_dragged_pos = GetMousePosition();
      circles[last_circle_p].x = mouse_dragged_pos.x;
      circles[last_circle_p].y = mouse_dragged_pos.y;
    }

    EndDrawing();
  }

  CloseWindow();
}
