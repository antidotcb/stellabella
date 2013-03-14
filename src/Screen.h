#pragma once

#include <irrlicht.h>
using namespace irr;

#include "State.h"
#include "Game.h"

namespace stellabellum {

    class Screen: public State {
    public:
        Screen(): m_scene(0), m_bgColor(255,255,0,255) {}

        virtual void init() {
            initScene();
        }

        virtual void render() {
            m_scene->drawAll();
        }

        virtual ~Screen() {
            dropScene();

        }

        const video::SColor & getBgColor() inline const { return m_bgColor; }
    protected:
        void initScene() {
            dropScene();
            m_scene = getGame()->createNewScene();
        }

        void dropScene() {
            if (m_scene) {
                m_scene->drop();
                m_scene = 0;
            }
        }

        virtual Game * getGame()  {
            return dynamic_cast<Game*>(_getStateMachine());
        }

        void setBgColor(const video::SColor & color) {
            m_bgColor = color;
        }

        scene::ISceneManager * getScene() {
            return m_scene;
        }
    private:
        scene::ISceneManager* m_scene;
        video::SColor m_bgColor;
    };
}