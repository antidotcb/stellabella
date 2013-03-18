#pragma once

#include <irrlicht.h>
using namespace irr;

#include "Screen.h"

namespace stellabellum {

    class CMainGameScreen: public game::CScreen {
    public:    
        static const int DefaultScreenID = 0;
        
        CMainGameScreen();

        virtual void init();
        virtual void enter();
        virtual void leave();

        virtual void update( const f32 delta );

        virtual int getId() inline const { return DefaultScreenID; }
    
    private:
         game::CWorld * World;
    };

}