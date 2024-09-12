#include <stdio.h>
#include <string.h>

#include "user.cpp"


int main(void)
{
    atexit(WriteFile);

    ReadFile();
    Menu();

    return 0;
}
