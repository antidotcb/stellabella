#include "stellabellum.h"
#include "Screen.h"
#include "Game.h"

namespace stellabellum {
    namespace game {

        void CScreen::setBgColor(const video::SColor& color) {
            BackgroundColor = color;
        }

        CGame* CScreen::getContainer() {
            return dynamic_cast<CGame*>(getStateMachine());
        }

        void CScreen::dropScene() {
            if (Scene) {
                Scene->drop();
                Scene = 0;
            }
        }

        void CScreen::initScene() {
            dropScene();
            Scene = getContainer()->createNewScene();
        }

        scene::ISceneManager* CScreen::getScene() {
            return Scene;
        }

        CScreen::~CScreen() {
            dropScene();
        }

        void CScreen::render() {
            Scene->drawAll();
        }

        void CScreen::init() {
            initScene();
        }

        CScreen::CScreen() : Scene(0), BackgroundColor(255,255,0,255) {

        }

    }
}
