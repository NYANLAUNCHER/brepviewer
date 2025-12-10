#pragma once
#include <iostream>
#include <string>
#include <unistd.h>
#include <termios.h>
// Esc Sequences:
#define ESC "\033"
// Text Colors & Attributes:
#define ANSI_RESET  ESC"[0m"
#define ANSI_RED    ESC"[31m"
#define ANSI_GREEN  ESC"[32m"
#define ANSI_YELLOW ESC"[33m"
#define ANSI_BLUE   ESC"[34m"
inline std::string RED(std::string s) { return ANSI_RED + s + ANSI_RESET; }
inline std::string GREEN(std::string s) { return ANSI_GREEN + s + ANSI_RESET; }
inline std::string YELLOW(std::string s) { return ANSI_YELLOW + s + ANSI_RESET; }
inline std::string BLUE(std::string s) { return ANSI_BLUE + s + ANSI_RESET; }
// Erase Functions:
#define CLR_AFTER ESC"[J"
// Cursor
#define CURSOR_HOME ESC"]H"
// move cursor up by `lines`
inline std::string CURSOR_UP(unsigned int lines) {
  return ESC"[" + std::to_string(lines) + "A";
}
// move cursor down by `lines`
inline std::string CURSOR_DOWN(unsigned int lines) {
  return ESC"[" + std::to_string(lines) + "B";
}
// move cursor right by `columns`
inline std::string CURSOR_RIGHT(unsigned int columns) {
  return ESC"[" + std::to_string(columns) + "C";
}
// move cursor left by `columns`
inline std::string CURSOR_LEFT(unsigned int columns) {
  return ESC"[" + std::to_string(columns) + "D";
}
// move cusor to absolute position
inline std::string CURSOR_POS(int line, int column) {
  std::string s = ESC"[" + std::to_string(line) + ";" + std::to_string(column) + "";
  return s;
}

namespace util {
  inline std::pair<int, int> getCursorPos() {
        // Send the request ESC[6n
    std::cout << "\x1b[6n" << std::flush;

    // Put terminal in raw mode
    termios oldt, raw;
    tcgetattr(STDIN_FILENO, &oldt);
    raw = oldt;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    // Read characters until 'R'
    std::string resp;
    char ch;
    while (read(STDIN_FILENO, &ch, 1) == 1) {
        resp += ch;
        if (ch == 'R') break;
    }

    // Restore terminal mode
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // Expected format: ESC[<row>;<col>R
    int row, col;
    if (sscanf(resp.c_str(), "\x1b[%d;%dR", &row, &col) == 2) {
        return {row, col};
    }
    return {-1, -1};  // failed
  }
};
