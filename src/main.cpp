#include "stdafx.h"
#include "Game.h"
#include "DefaultScreen.h"

using namespace stellabellum;

class StellaBellum: public Game {
public:
    StellaBellum(Options & options): Game(options) {
        addState(new DefaultScreen());
    }
};

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR, int) {
    int result = -1;
    try {
        Game::Options options;
        StellaBellum game(options);
        game.run();
        result = 0;
    } catch (std::exception & e) {
        MessageBoxA(GetTopWindow(0), e.what(), "ERROR", MB_OK | MB_TOPMOST);
    } catch (...) {
        MessageBoxA(GetTopWindow(0), "Unknown exception", "ERROR", MB_OK | MB_TOPMOST);
    }
    return result;
}