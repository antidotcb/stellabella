#pragma once

#include <irrlicht.h>
using namespace irr;

#include "State.h"
#include "Game.h"

namespace stellabellum {
    namespace game {

    class CScreen: public states::CState {
    public:
        CScreen();

        virtual ~CScreen();

        const video::SColor& getBgColor() inline const { return BackgroundColor; }
            
            
            virtual void init();

        virtual void render();

 
    protected:

        scene::ISceneManager* getScene();

        void initScene();

        void dropScene();

        virtual CGame* getContainer();

        void setBgColor(const video::SColor& color);

    private:
        video::SColor BackgroundColor;
        scene::ISceneManager* Scene;
    };

    }
}