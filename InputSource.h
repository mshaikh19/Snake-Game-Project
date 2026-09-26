#ifndef INPUT_SOURCE_H
#define INPUT_SOURCE_H

#ifdef _WIN32
    #include <conio.h>
    #define kbhit _kbhit
    #define getch _getch
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    int kbhit();
    int getch();
#endif

#include <cctype>

class InputSource {
public:
    virtual ~InputSource() = default;
    virtual bool hasInput() = 0;
    virtual char getInput() = 0;
};

class ConsoleInputSource : public InputSource {
public:
    bool hasInput() override {
        return kbhit();
    }
    char getInput() override {
        return getch();
    }
};

// Seam function for processing user input
inline bool processGameInput(InputSource& inputSource, char& direction) {
    if (inputSource.hasInput()) {
        char input = inputSource.getInput();
        if (input == 'x' || input == 'X') {
            return false;
        }
        if (input == 'w' || input == 'W' || input == 'a' || input == 'A' ||
            input == 's' || input == 'S' || input == 'd' || input == 'D') {
            direction = static_cast<char>(toupper(static_cast<unsigned char>(input)));
        }
    }
    return true;
}

#endif
