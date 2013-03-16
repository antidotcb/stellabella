#include "stellabellum.h"
#include "Screen.h"
#include "Game.h"

namespace stellabellum {
    namespace game {

        void Screen::setBgColor(const video::SColor& color) {
            m_backgroundColor = color;
        }

        Game* Screen::getContainer() {
            return dynamic_cast<Game*>(getStateMachine());
        }

        void Screen::dropScene() {
            if (m_scene) {
                m_scene->drop();
                m_scene = 0;
            }
        }

        void Screen::initScene() {
            dropScene();
            m_scene = getContainer()->createNewScene();
        }

        scene::ISceneManager* Screen::getScene() {
            return m_scene;
        }

        Screen::~Screen() {
            dropScene();
        }

        void Screen::render() {
            m_scene->drawAll();
        }

        void Screen::init() {
            initScene();
        }

        Screen::Screen() : m_scene(0), m_backgroundColor(255,255,0,255) {

        }

    }
}
