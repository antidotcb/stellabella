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
            m_scene = getGame()->createNewScene();
        }

        virtual void render() {
            m_scene->drawAll();
        }

        virtual ~Screen() {
            m_scene->drop();
        }

        const video::SColor & getBgColor() inline const { return m_bgColor; }
    protected:
        virtual Game * getGame()  {
            return dynamic_cast<Game*>(_getStateMachine());
        }

        scene::ISceneManager* m_scene;
        video::SColor m_bgColor;
    };
}