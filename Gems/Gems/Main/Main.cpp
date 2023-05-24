#define HEIGTH 800
#define WIDTH 800

#include "Window.h"

int main()
{
    Window *window = new Window(HEIGTH, WIDTH);
    window->live();
    return 0;
}