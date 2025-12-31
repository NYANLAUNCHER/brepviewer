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
    // - use field polar to adjust calculations
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
            theta=atan2(z, sqrt( pow(x,2) + pow(y,2) ));
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
