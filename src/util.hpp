#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <unistd.h>
#include <cmath>
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
// Cursor Functions:
#define CURSOR_HOME ESC"[H"
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
  return ESC"[" + std::to_string(line) + ";" + std::to_string(column) + "H";
}

template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

// Debug:
template<typename... Args>
void _fn_println(Args&&... args) {
    (std::cout << ... << args) << std::endl;
}
#ifdef DEBUG
// Optionally run a block of code if DEBUG is defined
// Uses "do {} while()" syntax, so it should work in "single-line" if statements
#define dbg(...) do {__VA_ARGS__} while(0)
#define println(...) _fn_println(__VA_ARGS__)
#else
#define println(...)
#define dbg(...)
#endif
// END Debug

#ifdef NO_FILE_UTILS
// NO_FILE_UTILS
#else
// File Utils
#include <fstream>
#include <sstream>
void readfile(const std::string path, std::string& src) {
    std::ifstream file;
    std::stringstream ss;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path);
        file.seekg(0, std::ios::end);
        src.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&src[0], src.size());
    } catch (const std::ifstream::failure& e) {
        std::cout << "Exception thrown: " << e.what() << std::endl;
    }
}
// note: doesn't include trailing slash
std::string getDirectory(const std::string& path) {
    size_t pos = path.find_last_of("/\\");   // handle both slashes
    if (pos == std::string::npos) return ""; // no directory
    return path.substr(0, pos);          // include trailing slash
}
#endif// NO_FILE_UTILS

#include <glm/glm.hpp>
namespace util {
    inline std::pair<int, int> getCursorPos() {
        // Request cursor position: ESC[6n
        std::cout << "\x1b[6n" << std::flush;
        // Enter raw mode
        termios oldt, raw;
        tcgetattr(STDIN_FILENO, &oldt);
        raw = oldt;
        raw.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
        // Read until 'R'
        std::string resp;
        char ch;
        while (read(STDIN_FILENO, &ch, 1) == 1) {
            resp += ch;
            if (ch == 'R') break;
        }
        // Restore terminal mode
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        // Expected format: ESC [ row ; col R
        int row = -1, col = -1;
        sscanf(resp.c_str(), "\x1b[%d;%dR", &row, &col);
        return {row, col};
    }
};

namespace util::coord {
    // TODO:
    // - make this work
    // - use polar angle instead of hard-coded axis
    struct Spherical {
        // Polar axis aligned with Z by default
        glm::vec3 polar=glm::vec3(0.0f, 0.0f, 1.0f);
        // Radius/Magnitude
        double r=0;
        // Azimuthal angle (Angle from polar axis)
        double theta=0;
        // Polar angle (Angle around polar axis)
        double phi=0;
        Spherical();
        Spherical(double r, double theta, double phi):
            r(r), theta(theta), phi(phi) {}
        // Cartesian to spherical coords
        // see: https://www.math3d.org/x6dcWlCwL5
        inline Spherical(glm::vec3 cartesian) {
            float& x=cartesian.x;
            float& y=cartesian.y;
            float& z=cartesian.z;
            r=sqrt(pow(x,2) + pow(y,2) + pow(z,2));
            theta=-atan2( z, sqrt(pow(x,2) + pow(y,2)) )*sgn(x);
            phi=atan2(y,x);
        }
        static inline glm::vec3 toCartesian(Spherical& s) {
            double& r = s.r;
            double& phi = s.phi;
            double& theta = s.theta;
            return glm::vec3(
                r*(sin(phi)*cos(theta)),
                r*(sin(phi)*sin(theta)),
                r*cos(phi)
            );
        }
        inline glm::vec3 toCartesian() {
            return toCartesian(*this);
        }
    };
}
