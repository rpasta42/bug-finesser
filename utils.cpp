#include "main.h"

#include <termios.h>

char getch(bool echo) {
   char buf = 0;
   struct termios old = {0};
   if (tcgetattr(0, &old) < 0)
      perror("tcsetattr()");
   old.c_lflag &= ~ICANON;
   if (echo)
      old.c_lflag &= ~ECHO;
   old.c_cc[VMIN] = 1;
   old.c_cc[VTIME] = 0;
   if (tcsetattr(0, TCSANOW, &old) < 0)
      perror("tcsetattr ICANON");
   if (read(0, &buf, 1) < 0)
      perror ("read()");
   old.c_lflag |= ICANON;
   old.c_lflag |= ECHO;
   if (tcsetattr(0, TCSADRAIN, &old) < 0)
      perror ("tcsetattr ~ICANON");
   return (buf);
}

void print_bin(uint64_t n) {
   for (uint64_t i = 0; i < 63; i++) {
      cout << (bool)(n & ((uint64_t)1 << i));
   }
   cout << endl;
}

vecStr &split(const string &s, char delim, vecStr &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vecStr split(const string &s, char delim) {
    vecStr elems;
    split(s, delim, elems);
    return elems;
}
