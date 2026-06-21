#include "Ui.h"

#include <ncurses.h>

#include <clocale>
#include <sstream>
#include <vector>

using namespace std;

static const int kPairDefault = 1;
static const int kPairGood    = 2;
static const int kPairMid     = 3;
static const int kPairBad     = 4;
static const int kPairTitle   = 5;

static int barColorPair(int value) {
    int pct = value;
    if (pct >= 60) return kPairGood;
    if (pct >= 30) return kPairMid;
    return kPairBad;
}

static vector<string> splitLines(const string& s) {
    vector<string> out;
    stringstream ss(s);
    string line;
    while (getline(ss, line)) {
        out.push_back(line);
    }
    return out;
}

static void drawBar(int y, int x, const string& label, int value) {
    int width = 20;
    int filled = (value * width) / 100;
    if (filled < 0) filled = 0;
    if (filled > width) filled = width;

    mvprintw(y, x, "%-9s", label.c_str());
    addch('[');
    int pair = barColorPair(value);
    attron(COLOR_PAIR(pair));
    for (int i = 0; i < filled; i++) addch('#');
    attroff(COLOR_PAIR(pair));
    for (int i = filled; i < width; i++) addch('.');
    addch(']');
    printw(" %3d/100", value);
}

static void waitAnyKey(int y, int x) {
    mvprintw(y, x, "[любая клавиша]");
    refresh();
    getch();
}

void uiInit() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        use_default_colors();
        init_pair(kPairDefault, COLOR_WHITE,  -1);
        init_pair(kPairGood,    COLOR_GREEN,  -1);
        init_pair(kPairMid,     COLOR_YELLOW, -1);
        init_pair(kPairBad,     COLOR_RED,    -1);
        init_pair(kPairTitle,   COLOR_CYAN,   -1);
    }
}

void uiShutdown() {
    curs_set(1);
    endwin();
}

int showWelcome() {
    clear();
    attron(COLOR_PAIR(kPairTitle) | A_BOLD);
    mvprintw(1, 2, "============================");
    mvprintw(2, 2, "      ТАМАГОЧИ на C++");
    mvprintw(3, 2, "============================");
    attroff(COLOR_PAIR(kPairTitle) | A_BOLD);

    mvprintw(5, 2, "Выбери питомца:");

    mvprintw(7,  4, "1) Кот        /\\_/\\");
    mvprintw(8,  4, "             ( ^.^ )");
    mvprintw(9,  4, "              > ^ <");

    mvprintw(11, 4, "2) Собака      __");
    mvprintw(12, 4, "             /  \\__");
    mvprintw(13, 4, "            ( ^.^ )_/");
    mvprintw(14, 4, "             U   U");

    mvprintw(16, 2, "Нажми 1 или 2: ");
    refresh();

    while (true) {
        int ch = getch();
        if (ch == '1') return 1;
        if (ch == '2') return 2;
    }
}

string askName() {
    clear();
    mvprintw(2, 2, "Как назовём питомца? ");
    echo();
    curs_set(1);

    char buf[64];
    for (int i = 0; i < 64; i++) buf[i] = 0;
    getnstr(buf, 63);

    noecho();
    curs_set(0);

    string name(buf);
    if (name.empty()) name = "Безымянный";
    return name;
}

void renderGame(const Pet& pet) {
    clear();

    attron(COLOR_PAIR(kPairTitle) | A_BOLD);
    mvprintw(0, 2, "==== ТАМАГОЧИ: %s (%s) — ход %d ====",
             pet.getName().c_str(), pet.species().c_str(), pet.getAge());
    attroff(COLOR_PAIR(kPairTitle) | A_BOLD);

    box(stdscr, 0, 0);

    vector<string> art = splitLines(pet.getAsciiArt());
    int y = 2;
    for (int i = 0; i < (int)art.size(); i++) {
        mvprintw(y, 4, "%s", art[i].c_str());
        y++;
    }
    mvprintw(y + 1, 4, "\"%s\"", pet.voice().c_str());

    int barY = 2;
    int barX = 30;
    drawBar(barY, barX, "HP",      pet.getHp());            barY++;
    drawBar(barY, barX, "Голод",   100 - pet.getHunger());  barY++;
    drawBar(barY, barX, "Жажда",   100 - pet.getThirst());  barY++;
    drawBar(barY, barX, "Настр.",  pet.getMood());          barY++;
    drawBar(barY, barX, "Энергия", pet.getEnergy());        barY++;
}

int askMenuChoice(const Pet& pet) {
    int idleMs = 4000;

    int y = 12;
    attron(A_BOLD);
    mvprintw(y, 4, "Что делаем?"); y++;
    attroff(A_BOLD);
    mvprintw(y, 4, "  1) Покормить");       y++;
    mvprintw(y, 4, "  2) Напоить");         y++;
    mvprintw(y, 4, "  3) Поиграть");        y++;
    mvprintw(y, 4, "  4) Уложить спать");   y++;
    mvprintw(y, 4, "  5) %s", pet.specialActionName().c_str()); y++;
    mvprintw(y, 4, "  6) Выйти");           y++;
    mvprintw(y + 1, 4, "Жми цифру (или подожди — время идёт): ");
    refresh();

    timeout(idleMs);
    int ch = getch();
    timeout(-1);

    if (ch == ERR) return 0;
    if (ch >= '1' && ch <= '6') return ch - '0';
    return 0;
}

void showMessage(const string& msg) {
    int y, x;
    getmaxyx(stdscr, y, x);
    (void)x;
    attron(COLOR_PAIR(kPairTitle));
    mvprintw(y - 2, 4, "%-60s", msg.c_str());
    attroff(COLOR_PAIR(kPairTitle));
    refresh();
    napms(700);
}

void animateAction(const Pet& pet, ActionAnim kind) {
    vector< vector<string> > frames;

    if (kind == AnimFeed) {
        frames.push_back({"   .       ", "           ", "           "});
        frames.push_back({"  ___      ", "  \\_/      ", "   У       "});
        frames.push_back({"  ___      ", " (~~~)     ", "  \\_/      "});
        frames.push_back({"  ___      ", " (   )     ", "  \\_/  ням "});
    } else if (kind == AnimDrink) {
        frames.push_back({"   .       ", "           ", "           "});
        frames.push_back({"   .       ", "   o       ", "           "});
        frames.push_back({"   .       ", "   o       ", "   o       "});
        frames.push_back({"  ~~~      ", " ( H2O )   ", "  \\___/    "});
    } else if (kind == AnimPlay) {
        frames.push_back({"   o       ", "           ", "           "});
        frames.push_back({"           ", "    o      ", "           "});
        frames.push_back({"           ", "           ", "      o    "});
        frames.push_back({"           ", "    o      ", "           "});
        frames.push_back({"   o       ", "           ", "           "});
    } else if (kind == AnimSleep) {
        frames.push_back({"           ", "  z        ", "           "});
        frames.push_back({"           ", "  Z z      ", "           "});
        frames.push_back({"   Z       ", "  z Z      ", "           "});
        frames.push_back({"  Z z      ", "   Z       ", "  z        "});
    } else {
        frames.push_back({" ~~~       ", "           ", "           "});
        frames.push_back({" ~~~~~     ", "  ...      ", "           "});
        frames.push_back({" ~~~~~~~   ", "  .....    ", "    ...    "});
        frames.push_back({" ~~~~~~~~~ ", " ........  ", "   ......  "});
    }

    int animY = 3;
    int animX = 18;
    int frameMs = 160;

    for (int f = 0; f < (int)frames.size(); f++) {
        renderGame(pet);
        for (int row = 0; row < (int)frames[f].size(); row++) {
            mvprintw(animY + row, animX, "%s", frames[f][row].c_str());
        }
        refresh();
        napms(frameMs);
    }
}

void showDeathScreen(const Pet& pet) {
    clear();
    attron(COLOR_PAIR(kPairBad) | A_BOLD);
    mvprintw(2, 4, "   _______");
    mvprintw(3, 4, "  |       |");
    mvprintw(4, 4, "  |  RIP  |");
    mvprintw(5, 4, "  |       |");
    mvprintw(6, 4, "  | %s", pet.getName().c_str());
    mvprintw(7, 4, "  |_______|");
    attroff(COLOR_PAIR(kPairBad) | A_BOLD);

    mvprintw(10, 4, "Твой %s по имени %s прожил %d ходов.",
             pet.species().c_str(), pet.getName().c_str(), pet.getAge());

    waitAnyKey(12, 4);
}
