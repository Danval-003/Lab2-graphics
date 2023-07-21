#pragma once

#include <cstdint>
#include <iostream>

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    float alpha;

    Color() : red(0), green(0), blue(0), alpha(0) {}

    Color(int r, int g, int b) : red(clamp(r)), green(clamp(g)), blue(clamp(b)), alpha(porcent(0)){}

    Color(int r, int g, int b, float a) : red(clamp(r)), green(clamp(g)), blue(clamp(b)), alpha(porcent(a)){}

    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        if(color.alpha>0){
            os << "Color (R: " << static_cast<int>(color.red) << ", G: " << static_cast<int>(color.green) << ", B: " << static_cast<int>(color.blue)<< ", A: " << static_cast<float>(color.alpha) << ")";
        } else{
            os << "Color (R: " << static_cast<int>(color.red) << ", G: " << static_cast<int>(color.green) << ", B: " << static_cast<int>(color.blue) << ")";
        }
        return os;
    }

    bool operator==(const Color& other) const {
        return (red == other.red) && (green == other.green) && (blue == other.blue) && (alpha == other.alpha);
    }

    bool operator!=(const Color& other) const {
        return !(*this == other);
    }

    Color operator+(const Color& other) const {
        int newRed = red + other.red;
        int newGreen = green + other.green;
        int newBlue = blue + other.blue;

        // Verificar y ajustar si se excede el valor de 255
        if (newRed > 255) {
            newRed = 255;
        }
        if (newGreen > 255) {
            newGreen = 255;
        }
        if (newBlue > 255) {
            newBlue = 255;
        }

        return {newRed, newGreen, newBlue};
    }

    Color operator*(float factor) const {
        int newRed = static_cast<int>(red * factor);
        int newGreen = static_cast<int>(green * factor);
        int newBlue = static_cast<int>(blue * factor);

        // Verificar y ajustar si se excede el valor de 255
        if (newRed > 255) {
            newRed = 255;
        }
        if (newGreen > 255) {
            newGreen = 255;
        }
        if (newBlue > 255) {
            newBlue = 255;
        }

        return {newRed, newGreen, newBlue};
    }

private:
    static uint8_t clamp(int value) {
        if (value < 0) {
            return 0;
        } else if (value > 255) {
            return 255;
        } else {
            return static_cast<uint8_t>(value);
        }
    }

    static float porcent(float value) {
        if (value < 0) {
            return 0;
        } else if (value > 1) {
            return 1;
        } else {
            return static_cast<float>(value);
        }
    }
};

extern Color WHITE;
extern Color NAVY_BLUE;
extern Color BLACK;
extern Color GRAY;
extern Color YELLOW;
