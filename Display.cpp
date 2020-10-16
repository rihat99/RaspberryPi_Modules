#include "Display.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

using namespace std;


void Display::write_word(int data) const{
    int temp = data;
    if ( BLEN == 1 )
        temp |= 0x08;
    else
        temp &= 0xF7;
    wiringPiI2CWrite(fd, temp);
}

void Display::send_command(int comm) const{
    int buf;
    // Send bit7-4 firstly
    buf = comm & 0xF0;
    buf |= 0x04;			// RS = 0, RW = 0, EN = 1
    write_word(buf);
    delay(2);
    buf &= 0xFB;			// Make EN = 0
    write_word(buf);

    // Send bit3-0 secondly
    buf = (comm & 0x0F) << 4;
    buf |= 0x04;			// RS = 0, RW = 0, EN = 1
    write_word(buf);
    delay(2);
    buf &= 0xFB;			// Make EN = 0
    write_word(buf);
}

void Display::send_data(int data) const {
    int buf;
    // Send bit7-4 firstly
    buf = data & 0xF0;
    buf |= 0x05;			// RS = 1, RW = 0, EN = 1
    write_word(buf);
    delay(2);
    buf &= 0xFB;			// Make EN = 0
    write_word(buf);

    // Send bit3-0 secondly
    buf = (data & 0x0F) << 4;
    buf |= 0x05;			// RS = 1, RW = 0, EN = 1
    write_word(buf);
    delay(2);
    buf &= 0xFB;			// Make EN = 0
    write_word(buf);
}

Display::Display() {
    fd = wiringPiI2CSetup(LCDAddr);
    send_command(0x33);	// Must initialize to 8-line mode at first
    delay(5);
    send_command(0x32);	// Then initialize to 4-line mode
    delay(5);
    send_command(0x28);	// 2 Lines & 5*7 dots
    delay(5);
    send_command(0x0C);	// Enable display without cursor
    delay(5);
    send_command(0x01);	// Clear Screen
    wiringPiI2CWrite(fd, 0x08);
}

void Display::write(int x, int y, const string &str) const {
    int addr, i;
    int tmp;
    if (x < 0)  x = 0;
    if (x > 15) x = 15;
    if (y < 0)  y = 0;
    if (y > 1)  y = 1;

    // Move cursor
    addr = 0x80 + 0x40 * y + x;
    send_command(addr);

    for (auto ch : str) {
        send_data(ch);
    }
}

void Display::clear() const {
    send_command(0x01);	//clear Screen
}

void Display::write(int x, int y, char ch) const {
    int addr, i;
    int tmp;
    if (x < 0)  x = 0;
    if (x > 15) x = 15;
    if (y < 0)  y = 0;
    if (y > 1)  y = 1;

    // Move cursor
    addr = 0x80 + 0x40 * y + x;
    send_command(addr);

    send_data(ch);
}

void Display::write(const string &str) {
    cur_x += str.size();
    cur_x = cur_x%16;
    line += str;
    if (line.size() > 15) {
        line = string(line.begin() + line.size() - 16, line.end());
    }
    clear();
    write(0, 0, line);
}

void Display::loopWord(int y, string str) {
    str += ' ';
    for (int i = 0; i < str.size(); ++i) {
        //clear();
        for (int j = 0; j < 16; ++j) {
            write(j, y, str[(i+j)%str.size()]);
            //delay(20);
        }
        delay(300);
    }
}
