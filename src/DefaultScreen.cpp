#include "StdAfx.h"
#include "stellabellum.h"
#include "DefaultScreen.h"
#include "Asteroid.h"
#include "World.h"
#include "Input.h"


namespace stellabellum {

    CMainGameScreen::CMainGameScreen( void )
        : CScreen()
    {
        setBgColor(video::SColor(255, 0, 0, 0));
    }

    void CMainGameScreen::enter() {
        getScene()->clear();
        World = new game::CWorld(getScene(), getContainer());
        
        core::vector3df playerPosition(0,-200,0);
        World->addEntity(World->createPlayer(playerPosition));
    }

    void CMainGameScreen::leave() {
        delete World;
        World = 0;

        getScene()->clear();
    }

    void CMainGameScreen::update(const f32 delta) {        
        /*if (getContainer()->getInput()->isKeyPressed(KEY_BACK)) {
            leave();
            enter();
        }*/

        World->update(delta);
    }

    void CMainGameScreen::init() {
        CScreen::init();        
        
        /*
        
        getScene()->getMesh("d:\\xpn_2013\\export\\asteroid.X");        

        getScene()->getMesh("d:\\xpn_2013\\export\\enemies_01.X");
        getScene()->getMesh("d:\\xpn_2013\\export\\enemies_02.X");
        mgetScene()->getMesh("d:\\xpn_2013\\export\\enemies_03.X");
        getScene()->getMesh("d:\\xpn_2013\\export\\enemies_04.X");

        getScene()->getMesh("d:\\xpn_2013\\export\\rocket.X");
        
        */
    }

}