#include "Ui.h"

#include <ncurses.h>

#include <clocale>
#include <sstream>
#include <vector>

namespace ui {

namespace {

constexpr int kPairDefault = 1;
constexpr int kPairGood    = 2;
constexpr int kPairMid     = 3;
constexpr int kPairBad     = 4;
constexpr int kPairTitle   = 5;

int barColorPair(int value, int max) {
    int pct = (value * 100) / max;
    if (pct >= 60) return kPairGood;
    if (pct >= 30) return kPairMid;
    return kPairBad;
}

std::vector<std::string> splitLines(const std::string& s) {
    std::vector<std::string> out;
    std::stringstream ss(s);
    std::string line;
    while (std::getline(ss, line)) {
        out.push_back(line);
    }
    return out;
}

void drawBar(WINDOW* win, int y, int x,
             const std::string& label, int value, int max = 100) {
    constexpr int width = 20;
    int filled = (value * width) / max;
    if (filled < 0) filled = 0;
    if (filled > width) filled = width;

    mvwprintw(win, y, x, "%-9s", label.c_str());
    waddch(win, '[');
    int pair = barColorPair(value, max);
    wattron(win, COLOR_PAIR(pair));
    for (int i = 0; i < filled; ++i) waddch(win, '#');
    wattroff(win, COLOR_PAIR(pair));
    for (int i = filled; i < width; ++i) waddch(win, '.');
    waddch(win, ']');
    wprintw(win, " %3d/%d", value, max);
}

void waitAnyKey(WINDOW* win, int y, int x) {
    mvwprintw(win, y, x, "[любая клавиша]");
    wrefresh(win);
    wgetch(win);
}

}

void init() {
    std::setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        use_default_colors();
        init_pair(kPairDefault, COLOR_WHITE, -1);
        init_pair(kPairGood,    COLOR_GREEN, -1);
        init_pair(kPairMid,     COLOR_YELLOW, -1);
        init_pair(kPairBad,     COLOR_RED, -1);
        init_pair(kPairTitle,   COLOR_CYAN, -1);
    }
}

void shutdown() {
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
    mvprintw(12, 4, "            o-''))____");
    mvprintw(13, 4, "             \\_/    /");
    mvprintw(14, 4, "              ) ( )/");

    mvprintw(16, 2, "Нажми 1 или 2: ");
    refresh();

    while (true) {
        int ch = getch();
        if (ch == '1') return 1;
        if (ch == '2') return 2;
    }
}

std::string askName() {
    clear();
    mvprintw(2, 2, "Как назовём питомца? ");
    echo();
    curs_set(1);
    char buf[64] = {0};
    getnstr(buf, sizeof(buf) - 1);
    noecho();
    curs_set(0);
    std::string name(buf);
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

    auto art = splitLines(pet.getAsciiArt());
    int y = 2;
    for (const auto& line : art) {
        mvprintw(y++, 4, "%s", line.c_str());
    }
    mvprintw(y + 1, 4, "\"%s\"", pet.voice().c_str());

    int barY = 2;
    int barX = 30;
    drawBar(stdscr, barY++, barX, "HP",      pet.getHp());
    drawBar(stdscr, barY++, barX, "Голод",   100 - pet.getHunger());
    drawBar(stdscr, barY++, barX, "Жажда",   100 - pet.getThirst());
    drawBar(stdscr, barY++, barX, "Настр.",  pet.getMood());
    drawBar(stdscr, barY++, barX, "Энергия", pet.getEnergy());
}

int askMenuChoice(const Pet& pet) {
    constexpr int kIdleTickMs = 4000;

    int y = 12;
    attron(A_BOLD);
    mvprintw(y++, 4, "Что делаем?");
    attroff(A_BOLD);
    mvprintw(y++, 4, "  1) Покормить");
    mvprintw(y++, 4, "  2) Напоить");
    mvprintw(y++, 4, "  3) Поиграть");
    mvprintw(y++, 4, "  4) Уложить спать");
    mvprintw(y++, 4, "  5) %s", pet.specialActionName().c_str());
    mvprintw(y++, 4, "  6) Выйти");
    mvprintw(y + 1, 4, "Жми цифру (или подожди — время идёт): ");
    refresh();

    timeout(kIdleTickMs);
    int ch = getch();
    timeout(-1);

    if (ch == ERR) return 0;
    if (ch >= '1' && ch <= '6') return ch - '0';
    return 0;
}

void showMessage(const std::string& msg) {
    int y, x;
    (void)x;
    getmaxyx(stdscr, y, x);
    attron(COLOR_PAIR(kPairTitle));
    mvprintw(y - 2, 4, "%-60s", msg.c_str());
    attroff(COLOR_PAIR(kPairTitle));
    refresh();
    napms(700);
}

void animateAction(const Pet& pet, ActionAnim kind) {
    std::vector<std::vector<std::string>> frames;
    switch (kind) {
        case ActionAnim::Feed:
            frames = {
                {"   .       ", "           ", "           "},
                {"  ___      ", "  \\_/      ", "   У       "},
                {"  ___      ", " (~~~)     ", "  \\_/      "},
                {"  ___      ", " (   )     ", "  \\_/  ням ",},
            };
            break;
        case ActionAnim::Drink:
            frames = {
                {"   .       ", "           ", "           "},
                {"   .       ", "   o       ", "           "},
                {"   .       ", "   o       ", "   o       "},
                {"  ~~~      ", " ( H2O )   ", "  \\___/    "},
            };
            break;
        case ActionAnim::Play:
            frames = {
                {"   o       ", "           ", "           "},
                {"           ", "    o      ", "           "},
                {"           ", "           ", "      o    "},
                {"           ", "    o      ", "           "},
                {"   o       ", "           ", "           "},
            };
            break;
        case ActionAnim::Sleep:
            frames = {
                {"           ", "  z        ", "           "},
                {"           ", "  Z z      ", "           "},
                {"   Z       ", "  z Z      ", "           "},
                {"  Z z      ", "   Z       ", "  z        "},
            };
            break;
        case ActionAnim::Special:
            frames = {
                {" ~~~       ", "           ", "           "},
                {" ~~~~~     ", "  ...      ", "           "},
                {" ~~~~~~~   ", "  .....    ", "    ...    "},
                {" ~~~~~~~~~ ", " ........  ", "   ......  "},
            };
            break;
    }

    constexpr int animY = 3;
    constexpr int animX = 18;
    constexpr int frameMs = 160;

    for (const auto& frame : frames) {
        renderGame(pet);
        for (size_t row = 0; row < frame.size(); ++row) {
            mvprintw(animY + static_cast<int>(row), animX, "%s", frame[row].c_str());
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

    waitAnyKey(stdscr, 12, 4);
}

}
