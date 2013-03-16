#pragma once

#include <irrlicht.h>
using namespace irr;

#include "State.h"
#include "Game.h"

namespace stellabellum {
    namespace game {

    class Screen: public states::State {
    public:
        Screen();

        virtual ~Screen();

        const video::SColor& getBgColor() inline const { return m_backgroundColor; }
            
            
            virtual void init();

        virtual void render();

 
    protected:

        scene::ISceneManager* getScene();

        void initScene();

        void dropScene();

        virtual Game* getContainer();

        void setBgColor(const video::SColor& color);

    private:
        video::SColor m_backgroundColor;
        scene::ISceneManager* m_scene;
    };

    }
}