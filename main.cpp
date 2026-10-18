#include <ncurses.h>
using namespace std;

#define heightW 22
#define widthW 22

int Board[widthW][heightW] = {0};

void Gameloop() {
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
    char object = '@';
    int objectX = 1;
    int objectY = 1;

    keypad(win, true);
    nodelay(win, true);

    bool is_running = true;
    int fallCounter = 0;
    int fallSpeed = 20;

    while(is_running) {
        //nodelay(win, true);

        werase(win);      // erases the win after every loop
        box(win, '#', '#');   // draws the box i.e border at every loop

        // For checking the landing elements and drawings them
        for(int r = 0; r <= heightW-2;r++) {
            for(int c = 0; c <= widthW - 2;c++) {
                if(Board[r][c] != 0) {
                   mvwaddch(win, r, c, object);
                }
            }
        }

        int ch = wgetch(win);
        if(ch == 'q' || ch == 'Q') {
            is_running = false;
        }
        fallCounter++;
        if(fallCounter >= fallSpeed) {
            if(objectY < heightW-2) {
                objectY++;
            }
            fallCounter = 0;
        }

        if(Board[objectY +1][objectX] == 0) {
            if(ch == KEY_DOWN) {
                int tempY = heightW - 2;

                while (Board[tempY][objectX] != 0 && tempY >= 0) {
                    tempY--;
                }

                if(objectY < heightW-2) {
                    objectY = tempY;
                }
            }else if(ch == KEY_LEFT) {
                if(objectX > 1 && objectY != heightW -2) {
                    objectX--;
                }
            }else if(ch == KEY_RIGHT && objectY != heightW-2) {
                if(objectX < widthW-2 && objectY != heightW -2) {
                objectX++;
                }
            }
        }
        mvwaddch(win, objectY, objectX, object);
        wrefresh(win);

        if(objectY == heightW - 2 || Board[objectY + 1][objectX] == 1) {
            Board[objectY][objectX] = 1;
            objectX = 1;
            objectY = 1;
        }

        napms(20);
    }

    delwin(win);
    endwin();
}

int main() {
    Gameloop();
    return 0;
}
