#include <stdint.h>
#include <SeeedTouchScreen.h>
#include <TFTv2.h>
#include <SPI.h>

// initialize blank board
byte board[3][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};
int turn_num = 1;
int color;
int win = 0;
TouchScreen ts = TouchScreen(XP, YP, XM, YM);
char turn = 'x';
int x, y, board_x, board_y;
// vertical zones
int top = 39;
int mid = 119;
int bottom = 199; 
int bottom_edge = 279;

// horizontal zones
int left = 0;
int center = 79;
int right = 159;

void setup(){
  TFT_BL_ON;
  Tft.TFTinit();
  
  Tft.drawHorizontalLine(0, 119, 240, WHITE);
  Tft.drawHorizontalLine(0, 199, 240, WHITE);
  Tft.drawVerticalLine(79, 39, 240, WHITE);
  Tft.drawVerticalLine(159, 39, 240, WHITE);
}
void(*resetFunc)(void) = 0;
void loop(){
  Point tap = ts.getPoint();
  tap.x = map(tap.x, TS_MINX, TS_MAXX, 0, 240);
  tap.y = map(tap.y, TS_MINY, TS_MAXY, 0, 320);
  
  //Find screen zone
  if (tap.y > top){
    if (tap.y < mid){
      y = 79;
      board_y = 0;
    }
    else if (tap.y < bottom){
      y = 159;
      board_y = 1;
    }
    else if (tap.y < bottom_edge){
      y = 239;
      board_y = 2;
    }
  }
  if (tap.x < center){
    x = 39;
    board_x = 0;
  }
  else if (tap.x < right){
    x = 119;
    board_x = 1;
  }
  else{
    x = 199;
    board_x = 2;
  }
  if (!win){
    if (tap.z > __PRESURE){
      if (board[board_x][board_y] == 0){
        board[board_x][board_y] = turn;
        if (turn == 'x'){
            drawX(x, y);
            check_win(turn, board_x, board_y);
            if (!win){
              turn = 'o';
            }
            delay(500);
        }
        else{
          drawO(x, y);
          check_win(turn, board_x, board_y);
          if (!win){
            turn = 'x';
          }
          delay(500);
        }
      }
      turn_num++;
    }
  }
  if (win && turn == 'x'){
    Tft.drawString("X Wins!", 0, 120, 4, BLUE);
    delay(3000);
    resetFunc();
  }
  if (win && turn == 'o'){
    Tft.drawString("O Wins!", 0, 120, 4, RED);
    delay(3000);
    resetFunc();
  }
  if (turn_num > 9 && win == 0){
    Tft.drawString("STALEMATE", 0, 120, 4, GREEN);
    delay(3000);
    resetFunc();
  }
}
void drawX(int x, int y){
  Tft.drawLine(x, y, x + 18, y + 18, BLUE);
  Tft.drawLine(x, y, x + 18, y - 18, BLUE);
  Tft.drawLine(x, y, x - 18, y + 18, BLUE);
  Tft.drawLine(x, y, x - 18, y - 18, BLUE);
}
void drawO(int x, int y){
  Tft.drawCircle(x, y, 36, RED);
}
void check_win(char turn, int x, int y){
  if (turn == 'x'){
    color = BLUE;
  }
  else{
    color = RED;
    }
  // Three configurations to check:
  // Edge square (can only get win in 2 directions)
  // Corner square (can get win in 3 directions)
  // Center square (can get win in 4 directions)
  
  // Check if edge square
  if (x % 2 == 0 && y % 2 == 1 || x % 2 == 1 && y % 2 == 0){
    if (x % 2 == 0){
      if (board[0][1] == turn && board[1][1] == turn && board[2][1] == turn){
        win = 1;
        Tft.drawHorizontalLine(0, 159, 240, color);
      }
      else if (board[x][0] == turn && board[x][1] == turn && board[x][2] == turn){
        win = 1;
        if (x == 0){
          Tft.drawVerticalLine(39, 39, 240, color);
        }
        else{
          Tft.drawVerticalLine(199, 39, 240, color);
        }
      }
    }
    else {
      if (board[1][0] == turn && board[1][1] == turn && board[1][2] == turn){
        win = 1;
        Tft.drawVerticalLine(119, 39, 240, color);
      }
      else if (board[0][y] == turn && board[1][y] == turn && board[2][y] == turn){
        win = 1;
        if (y == 0){
          Tft.drawHorizontalLine(0, 79, 240, color);
        }
        else{
          Tft.drawHorizontalLine(0, 239, 240, color);
      }
    }
  }
  }
  // Check if corner square
  else if (x % 2 == 0 && y % 2 == 0){
    if (x == y){
      // top left and bottom right corners (0,0 and 2,2)
      if (board[0][0] == turn && board[1][1] == turn && board[2][2] == turn){
        win = 1;
        Tft.drawLine(0, 39, 239, 279, color);
      }
      else if (board[x][0] == turn && board[x][1] == turn && board[x][2] == turn){
        win = 1;
        if (x == 0){
          Tft.drawVerticalLine(39, 39, 240, color);
        }
        else{
          Tft.drawVerticalLine(199, 39, 240, color);
        }
      }
      else if (board[0][y] == turn && board[1][y] == turn && board[2][y] == turn){
        win = 1;
        if (y == 0){
          Tft.drawHorizontalLine(0, 79, 240, color);
        }
        else{
          Tft.drawHorizontalLine(0, 239, 240, color);
        }
      }
    }
    else {
      // top right and bottom left (0,2 and 2, 0)
      if (board[2][0] == turn && board[1][1] == turn && board[0][2] == turn){
        win = 1;
        Tft.drawLine(239, 39, 0, 279, color);
      }
      else if (board[x][0] == turn && board[x][1] == turn && board[x][2] == turn){
        win = 1;
        if (x == 0){
          Tft.drawVerticalLine(39, 39, 240, color);
        }
        else{
          Tft.drawVerticalLine(199, 39, 240, color);
        }
      }
      else if (board[0][y] == turn && board[1][y] == turn && board[2][y] == turn){
        win = 1;
        if (y == 0){
          Tft.drawHorizontalLine(0, 79, 240, color);
        }
        else{
          Tft.drawHorizontalLine(0, 239, 240, color);
        }
      }
    }
  }
  // Check if center square
  else if (x == 1 && y == 1){
    if (board[0][1] == turn && board [2][1] == turn){
      win = 1;
      Tft.drawHorizontalLine(0, 159, 240, color);
    }
    else if (board[1][0] == turn && board[1][2] == turn){
      win = 1;
      Tft.drawVerticalLine(119, 39, 240, color);
    }
    else if (board[0][0] == turn && board[2][2] == turn){
      win = 1;
      Tft.drawLine(0, 39, 239, 279, color);
    }
    else if (board[0][2] == turn && board[2][0] == turn){
      win = 1;
      Tft.drawLine(239, 39, 0, 279, color);
    }
  }
}

