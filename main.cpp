#include <ncurses.h>
using namespace std;

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

void handleInput(int ch) {
    if(ch == 'q' || ch == 'Q') {
        is_running = false;
    }

    if(ch == KEY_DOWN) {
        if(Board[objectY + 1][objectX] == 0) {
            int tempY = heightW - 2;

            while (Board[tempY][objectX] != 0 && tempY >= 0) {
                tempY--;
            }

            if(objectY < heightW-2) {
                objectY = tempY;
            }
        }
    }else if(ch == KEY_LEFT && objectX > 1 && objectY != heightW -2 && Board[objectY][objectX-1] != 1) {
            objectX--;
    }else if(ch == KEY_RIGHT && objectY != heightW-2 && objectX < widthW-2 && Board[objectY][objectX+1] != 1) {
        objectX++;
    }
}

void update() {
    fallCounter++;
    if(fallCounter >= fallSpeed) {
        if(objectY < heightW-2 && Board[objectY+1][objectX] != 1) {
            objectY++;
        }
        fallCounter = 0;
    }

    if(objectY == heightW - 2 || Board[objectY + 1][objectX] == 1) {
        Board[objectY][objectX] = 1;
        objectX = 1;
        objectY = 1;
    }
}

void render(WINDOW* win) {
    werase(win);
    box(win, '#', '#');

    for(int r = 0; r <= heightW-2;r++) {
        for(int c = 0; c <= widthW - 2;c++) {
            if(Board[r][c] != 0) {
                mvwaddch(win, r, c, object);
            }
        }
    }

    mvwaddch(win, objectY, objectX, object);
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
    return 0;
}
