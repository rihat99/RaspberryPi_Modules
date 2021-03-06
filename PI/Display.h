#pragma once

#include <string>
#include <iostream>
#include <sstream>

namespace PI {

    class Display {
    public:
        Display();

        void write(int x, int y, const std::string &str) const;

        void write(int x, int y, char ch) const;

        void write(const std::string &str);

        void loopWord(int y, std::string str);

        void clear() const;

        template<typename T>
        Display& operator << (const T& data) {
            std::ostringstream ss;
            ss << data;
            write(ss.str());
            return *this;
        }

    private:
        int cur_x = 0;
        int cur_y = 0;
        std::string line;
        int fd;
        int LCDAddr = 0x27;
        int BLEN = 1;

        void write_word(int data) const;

        void send_command(int comm) const;

        void send_data(int data) const;

    };

}//PI