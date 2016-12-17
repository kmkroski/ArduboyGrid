// Grid
// K. M. Kroski
// 16 Dec 2016

#define GRID_W 13
#define GRID_H 13
#define GRIDCELL_W 5
#define GRIDCELL_H 5

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#include <Arduboy.h>

Arduboy arduboy;

int ubuf = 0;
int dbuf = 0;
int lbuf = 0;
int rbuf = 0;
int abuf = 0;

byte grid[GRID_W][GRID_H] = {};

int px = 0;
int py = 0;
int po = DOWN;

void setupGrid() {
  for (int x = 0; x < GRID_W; x++) {
    for (int y = 0; y < GRID_H; y++) {
      grid[x][y] = 0;
    }
  }
}

void generateMaze() {
  // Generate random origin coords
  int sx = 0;
  do {
    sx = random(0, GRID_W);
  } while (sx % 2 == 0);

  int sy = 0;
  do {
    sy = random(0, GRID_H);
  } while (sy % 2 == 0);

  // Pick origin
  grid[sx][sy] = 1;
  checkCell(sx, sy);

  // Add start
  byte str = 0;
  do {
    str = random(0, GRID_W);
  } while (grid[str][1] == 0);
  grid[str][0] = 2;
  px = str;
  py = 0;
  po = DOWN;

  // Add exit
  byte ext = 0;
  do {
    ext = random(0, GRID_H);
  } while (grid[ext][GRID_H - 2] == 0);
  grid[ext][GRID_H - 1] = 2;
}

void checkCell(int x, int y) {
  // Shuffle directions
  int directions[4] = {0, 1, 2, 3};
  for (int i = 3; i > 0; i--) {
    int r = random(i + 1);
    if (r != i) {
      int temp = directions[i];
      directions[i] = directions[r];
      directions[r] = temp;
    }
  }

  // Follow directions
  for (int i = 0; i < 4; i++) {
    switch (directions[i]) {
      case 0: // Up
        if (y - 2 < 0) { continue; }
        
        if (grid[x][y - 2] == 0) {
          grid[x][y - 2] = 1;
          grid[x][y - 1] = 1;
          checkCell(x, y - 2);
        }
        break;
        
      case 1: // Down
        if (y + 2 >= GRID_H) { continue; }
        
        if (grid[x][y + 2] == 0) {
          grid[x][y + 2] = 1;
          grid[x][y + 1] = 1;
          checkCell(x, y + 2);
        }
        break;

      case 2: // Left
        if (x - 2 < 0) { continue; }
        
        if (grid[x - 2][y] == 0) {
          grid[x - 2][y] = 1;
          grid[x - 1][y] = 1;
          checkCell(x - 2, y);
        }
        break;

      case 3: // Right
        if (x + 2 >= GRID_W) { continue; }
        
        if (grid[x + 2][y] == 0) {
          grid[x + 2][y] = 1;
          grid[x + 1][y] = 1;
          checkCell(x + 2, y);
        }
        break;
    }
  }
}

void drawGrid() {
  for (int x = 0; x < GRID_W; x++) {
    for (int y = 0; y < GRID_H; y++) {
      if (grid[x][y] > 0) {
        arduboy.fillRect(x * GRIDCELL_W, y * GRIDCELL_H, GRIDCELL_W, GRIDCELL_H, WHITE);
      } else if (grid[x][y] == 0) {
        arduboy.fillRect(x * GRIDCELL_W, y * GRIDCELL_H, GRIDCELL_W, GRIDCELL_H, BLACK);
      }
    }
  }

  byte nx = px * GRIDCELL_W + 2;
  byte ny = py * GRIDCELL_H + 2;
  switch (po) {
    case DOWN:
      arduboy.fillTriangle(nx - 1, ny, nx + 1, ny, nx, ny + 1, BLACK);
      break;
    case UP:
      arduboy.fillTriangle(nx - 1, ny, nx + 1, ny, nx, ny - 1, BLACK);
      break;
    case LEFT:
      arduboy.fillTriangle(nx, ny - 1, nx, ny + 1, nx - 1, ny, BLACK);
      break;
    case RIGHT:
      arduboy.fillTriangle(nx, ny - 1, nx, ny + 1, nx + 1, ny, BLACK);
      break;
  }
}

void drawView() {
  byte x_offset = 64;

  byte x0 = 0;
  byte y0 = 0;
  byte x0l = 0;
  byte y0l = 0;
  byte x0r = 0;
  byte y0r = 0;
  
  byte x1 = 0;
  byte y1 = 0;
  byte x1l = 0;
  byte y1l = 0;
  byte x1r = 0;
  byte y1r = 0;
  
  byte x2 = 0;
  byte y2 = 0;
  byte x2l = 0;
  byte y2l = 0;
  byte x2r = 0;
  byte y2r = 0;

  byte x3 = 0;
  byte y3 = 0;

  switch (po) {
    case DOWN:
      x0 = px;
      y0 = py;
      x0l = px + 1;
      y0l = py;
      x0r = px - 1;
      y0r = py;
      
      x1 = px;
      y1 = py + 1;
      x1l = px + 1;
      y1l = py + 1;
      x1r = px - 1;
      y1r = py + 1;
      
      x2 = px;
      y2 = py + 2;
      x2l = px + 1;
      y2l = py + 2;
      x2r = px - 1;
      y2r = py + 2;

      x3 = px;
      y3 = py + 3;
      break;

    case UP:
      x0 = px;
      y0 = py;
      x0l = px - 1;
      y0l = py;
      x0r = px + 1;
      y0r = py;
      
      x1 = px;
      y1 = py - 1;
      x1l = px - 1;
      y1l = py - 1;
      x1r = px + 1;
      y1r = py - 1;
      
      x2 = px;
      y2 = py - 2;
      x2l = px - 1;
      y2l = py - 2;
      x2r = px + 1;
      y2r = py - 2;

      x3 = px;
      y3 = py - 3;
      break;

    case LEFT:
      x0 = px;
      y0 = py;
      x0l = px;
      y0l = py + 1;
      x0r = px;
      y0r = py - 1;
      
      x1 = px - 1;
      y1 = py;
      x1l = px - 1;
      y1l = py + 1;
      x1r = px - 1;
      y1r = py - 1;
      
      x2 = px - 2;
      y2 = py;
      x2l = px - 2;
      y2l = py + 1;
      x2r = px - 2;
      y2r = py - 1;

      x3 = px - 3;
      y3 = py;
      break;

    case RIGHT:
      x0 = px;
      y0 = py;
      x0l = px;
      y0l = py - 1;
      x0r = px;
      y0r = py + 1;
      
      x1 = px + 1;
      y1 = py;
      x1l = px + 1;
      y1l = py - 1;
      x1r = px + 1;
      y1r = py + 1;
      
      x2 = px + 2;
      y2 = py;
      x2l = px + 2;
      y2l = py - 1;
      x2r = px + 2;
      y2r = py + 1;

      x3 = px + 3;
      y3 = py;
      break;
  }


  arduboy.drawLine(x_offset, 63, x_offset + 31, 32, WHITE); 
  arduboy.drawLine(x_offset + 63, 63, x_offset + 32, 32, WHITE); 

  // First draw 0
  arduboy.fillRect(x_offset, 8, 7, 48, WHITE);
  arduboy.fillRect(x_offset + 57, 8, 7, 48, WHITE);
  arduboy.drawFastHLine(x_offset + 8, 55, 48, WHITE);
  
  if (grid[x0l][y0l] == 0) {
    arduboy.fillTriangle(x_offset, 0, x_offset, 8, x_offset + 6, 8, WHITE);
    arduboy.fillTriangle(x_offset, 56, x_offset, 63, x_offset + 6, 56, WHITE);
  }

  if (grid[x0r][y0r] == 0) {
    arduboy.fillTriangle(x_offset + 63, 0, x_offset + 63, 8, x_offset + 57, 8, WHITE);
    arduboy.fillTriangle(x_offset + 63, 63, x_offset + 63, 56, x_offset + 57, 56, WHITE);
  }
  

  // Next draw 1
  if (grid[x1][y1] > 0) {
    arduboy.fillRect(x_offset + 8, 20, 11, 24, WHITE);
    arduboy.fillRect(x_offset + 45, 20, 11, 24, WHITE);
    arduboy.drawFastHLine(x_offset + 20, 43, 24, WHITE);
    
    if (grid[x1l][y1l] == 0) {
      arduboy.fillTriangle(x_offset + 8, 8, x_offset + 8, 20, x_offset + 18, 20, WHITE);
      arduboy.fillTriangle(x_offset + 8, 55, x_offset + 8, 43, x_offset + 18, 43, WHITE);
    }

    if (grid[x1r][y1r] == 0) {
      arduboy.fillTriangle(x_offset + 45, 20, x_offset + 55, 20, x_offset + 55, 9, WHITE);
      arduboy.fillTriangle(x_offset + 45, 43, x_offset + 55, 43, x_offset + 55, 55, WHITE);
    }
  } else {
    arduboy.fillRect(x_offset + 8, 8, 48, 48, WHITE);
  }

  // Next draw 2
  if (grid[x2][y2] > 0) {
    arduboy.fillRect(x_offset + 20, 28, 7, 8, WHITE);
    arduboy.fillRect(x_offset + 37, 28, 7, 8, WHITE);
    arduboy.drawFastHLine(x_offset + 28, 35, 8, WHITE);
    
    if (grid[x2l][y2l] == 0) {
      arduboy.fillTriangle(x_offset + 20, 20, x_offset + 20, 28, x_offset + 26, 28, WHITE);
      arduboy.fillTriangle(x_offset + 20, 43, x_offset + 20, 35, x_offset + 26, 35, WHITE);
    }

    if (grid[x2r][y2r] == 0) {
      arduboy.fillTriangle(x_offset + 43, 20, x_offset + 43, 28, x_offset + 37, 28, WHITE);
      arduboy.fillTriangle(x_offset + 43, 44, x_offset + 43, 35, x_offset + 37, 35, WHITE);
    }
  } else {
    arduboy.fillRect(x_offset + 20, 20, 24, 24, WHITE);
  }

  // Next draw 2
  if (grid[x3][y3] == 0) {
    arduboy.fillRect(x_offset + 28, 28, 8, 8, WHITE);
  }
}

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();

  setupGrid();
  generateMaze();
}

void loop() {
  if (!arduboy.nextFrame()) { return; }

  arduboy.clear();

  if (abuf > 0) { abuf--; }
  if (ubuf > 0) { ubuf--; }
  if (dbuf > 0) { dbuf--; }
  if (lbuf > 0) { lbuf--; }
  if (rbuf > 0) { rbuf--; }

  if (arduboy.pressed(UP_BUTTON) && ubuf == 0) {
    ubuf = 10;

    switch (po) {
      case DOWN:
        if (grid[px][py + 1] > 0) {
          py++;
        }
        break;
      case UP:
        if (grid[px][py - 1] > 0) {
          py--;
        }
        break;
      case LEFT:
        if (grid[px - 1][py] > 0) {
          px--;
        }
        break;
      case RIGHT:
        if (grid[px + 1][py] > 0) {
          px++;
        }
        break;
    }
  }

  if (arduboy.pressed(DOWN_BUTTON) && dbuf == 0) {
    dbuf = 10;

    switch (po) {
      case DOWN:
        if (grid[px][py - 1] > 0) {
          py--;
        }
        break;
      case UP:
        if (grid[px][py + 1] > 0) {
          py++;
        }
        break;
      case LEFT:
        if (grid[px + 1][py] > 0) {
          px++;
        }
        break;
      case RIGHT:
        if (grid[px - 1][py] > 0) {
          px--;
        }
        break;
    }
  }

  if (arduboy.pressed(LEFT_BUTTON) && lbuf == 0) {
    lbuf = 10;

    switch (po) {
      case DOWN:
        po = RIGHT;
        break;
      case UP:
        po = LEFT;
        break;
      case LEFT:
        po = DOWN;
        break;
      case RIGHT:
        po = UP;
        break;
    }
  }

  if (arduboy.pressed(RIGHT_BUTTON) && rbuf == 0) {
    rbuf = 10;

    switch (po) {
      case DOWN:
        po = LEFT;
        break;
      case UP:
        po = RIGHT;
        break;
      case LEFT:
        po = UP;
        break;
      case RIGHT:
        po = DOWN;
        break;
    }
  }

  
  
  if (arduboy.pressed(A_BUTTON) && abuf == 0) {
    abuf = 10;
    
    setupGrid();
    generateMaze();
  }
  
  drawGrid();
  drawView();
  arduboy.display();
}
