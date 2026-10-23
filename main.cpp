#include <ncurses.h>

#define heightW 22
#define widthW 22

char object = '@';
int objectX = 1;
int objectY = 1;

int Board[widthW][heightW] = {0};

bool is_running = true;
int fallCounter = 0;
int fallSpeed = 20;

WINDOW* win = nullptr;

int rotationIndex = 0;
int PieceNo = 0;

int Pieces[7][4][4][4] = {
    // I = 0
    {{{0,1,0,0},
      {0,1,0,0},
      {0,1,0,0},
      {0,1,0,0}},

     {{0,0,0,0},
      {1,1,1,1},
      {0,0,0,0},
      {0,0,0,0}},

     {{0,1,0,0},
      {0,1,0,0},
      {0,1,0,0},
      {0,1,0,0}},

     {{0,0,0,0},
      {1,1,1,1},
      {0,0,0,0},
      {0,0,0,0}}},

// O = 1
    {{{0,1,1,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}},

     {{0,1,1,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}},

     {{0,1,1,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}},

     {{0,1,1,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}}},

    // T = 2
    {{{0,1,0,0},
      {1,1,1,0},
      {0,0,0,0},
      {0,0,0,0}},

     {{0,1,0,0},
      {0,1,1,0},
      {0,1,0,0},
      {0,0,0,0}},

     {{0,0,0,0},
      {1,1,1,0},
      {0,1,0,0},
      {0,0,0,0}},

     {{0,1,0,0},
      {1,1,0,0},
      {0,1,0,0},
      {0,0,0,0}}},

    // L = 3
    {{{1,0,0,0},
      {1,1,1,0},
      {0,0,0,0},
      {0,0,0,0}},

     {{0,1,1,0},
      {0,1,0,0},
      {0,1,0,0},
      {0,0,0,0}},

     {{0,0,0,0},
      {1,1,1,0},
      {0,0,1,0},
      {0,0,0,0}},

     {{0,1,0,0},
      {0,1,0,0},
      {1,1,0,0},
      {0,0,0,0}}},

    // S = 4
    {{{0,1,1,0},
      {1,1,0,0},
      {0,0,0,0},
      {0,0,0,0}},

     {{0,1,0,0},
      {0,1,1,0},
      {0,0,1,0},
      {0,0,0,0}},

     {{0,1,1,0},
      {1,1,0,0},
      {0,0,0,0},
      {0,0,0,0}},

     {{1,0,0,0},
      {1,1,0,0},
      {0,1,0,0},
      {0,0,0,0}}},

    // L reverse = 5
    {{{0,0,1,0},
      {1,1,1,0},
      {0,0,0,0},
      {0,0,0,0}},

     {{0,1,0,0},
      {0,1,0,0},
      {0,1,1,0},
      {0,0,0,0}},

     {{0,0,0,0},
      {1,1,1,0},
      {1,0,0,0},
      {0,0,0,0}},

     {{1,1,0,0},
      {0,1,0,0},
      {0,1,0,0},
      {0,0,0,0}}},

    // Z = 6
    {{{1,1,0,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}},

     {{0,1,0,0},
      {1,1,0,0},
      {1,0,0,0},
      {0,0,0,0}},

     {{1,1,0,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}},

     {{0,1,0,0},
      {1,1,0,0},
      {1,0,0,0},
      {0,0,0,0}}}};

bool canPieceFit(int objectX, int objectY) {

    int checkX = 0;
    int checkY = 0;

    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c++) {
            if(Pieces[PieceNo][rotationIndex][r][c] == 1)
            {
                checkX = objectX + c;
                checkY = objectY + r;
                if(checkX < 1 || checkX > widthW -2 || checkY > heightW - 2 || Board[checkY][checkX] == 1)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void handleInput(int ch) {
    if(ch == 'q' || ch == 'Q') {
        is_running = false;
    }

    if(ch == KEY_DOWN && canPieceFit(objectX, objectY)) {
            objectY++;
    }else if(ch == KEY_LEFT && canPieceFit(objectX-1, objectY)) {
            objectX--;
    }else if(ch == KEY_RIGHT && canPieceFit(objectX+1, objectY)) {
        objectX++;
    }else if(ch == KEY_UP){
        rotationIndex = (rotationIndex + 1) % 4;
    }
}

void update() {
    //gravity
    fallCounter++;
    if(fallCounter >= fallSpeed) {
        if(objectY < heightW-2 && Board[objectY+1][objectX] != 1) {
            objectY++;
        }
        fallCounter = 0;
    }

    // checking collision and coping into board
    for(int r = 0; r < 4; r++) {
        for (int c = 0;c < 4;c++) {
            if(!(canPieceFit(objectX, objectY + 1)))
            {
                for(int r = 0; r < 4; r++) {
                    for(int c = 0; c < 4; c++) {
                        if(Pieces[PieceNo][rotationIndex][r][c] == 1) {
                            Board[objectY + r][objectX + c] = 1;
                        }
                    }
                }
                objectX = 1;
                objectY = 1;
                PieceNo = (PieceNo + 1) % 6;
            }
        }
    }
}

// draw helper function for render
void draw(WINDOW* win) {
    for(int r = 0;r < 4;r++) {
        for(int c = 0;c < 4;c++) {
             if(Pieces[PieceNo][rotationIndex][r][c] == 1) {
                 mvwaddch(win, objectY + r, objectX + c, object);
            }
        }
    }
}

void render(WINDOW* win) {
    werase(win);
    box(win, '#', '#');

    // redrawing the old pieces before new ones
    for(int r = 0; r <= heightW-2;r++) {
        for(int c = 0; c <= widthW - 2;c++) {
            if(Board[r][c] != 0) {
                mvwaddch(win, r,c,object);
            }
        }
    }

    draw(win);      // drawing current pieces
    wrefresh(win);
}

void Gameloop(WINDOW* win) {
    while(is_running) {
        int ch = wgetch(win);

        handleInput(ch);
        update();
        render(win);
        napms(20);
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    int startY = 0;
    int startX = 0;

    WINDOW* win = newwin(heightW, widthW, startY, startX);
    refresh();
    box(win, '#', '#');
    wrefresh(win);

    keypad(win, true);
    nodelay(win, true);

    Gameloop(win);

    delwin(win);
    endwin();
}
