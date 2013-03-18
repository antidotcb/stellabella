#include "stdafx.h"
#include "stellabellum.h"
#include "DefaultScreen.h"

using namespace stellabellum;

class StellaBellum: public game::CGame {
public:
    StellaBellum(const SOptions& options)
        : game::CGame(options)
    {
        addState(new CMainGameScreen());
    }
};

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR, int) {
    int result = -1;
    try {
        game::CGame::SOptions options;
        StellaBellum game(options);
        game.run();
        result = 0;
    } catch (std::exception& e) {
        MessageBoxA(GetTopWindow(0), e.what(), "ERROR", MB_OK | MB_TOPMOST);
    } catch (...) {
        MessageBoxA(GetTopWindow(0), "Unknown exception", "ERROR", MB_OK | MB_TOPMOST);
    }
    return result;
}