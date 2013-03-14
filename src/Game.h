#pragma once

#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace video;
using namespace scene;

#include "StateMachine.h"
#include "InputReceiver.h"

namespace stellabellum {

    class InputReceiver;
    class Screen;

    class Game : public StateMachine
    {
    protected:
        static const u32 DefaultWidth = 1024;
        static const u32 DefaultHeight = 768;
        static const video::E_DRIVER_TYPE DefaultDriverType = video::EDT_OPENGL;

    public:
        struct Options {
            u32 Width;
            u32 Height;
            video::E_DRIVER_TYPE Driver;
            Options():
            Width(DefaultWidth),
                Height(DefaultHeight),
                Driver(DefaultDriverType) {}
        };

        Game(Options & options);
        ~Game();

        void run();

        ISceneManager * createNewScene();

        IrrlichtDevice * getDevice() { return m_device; }

        const int & getFPS() const { return m_fps;}
        const InputReceiver * getInput() const { return &m_receiver; }

        video::ITexture * getRocketTexture(core::stringw texture) {
            return m_driver->getTexture("d:\\xpn_2013\\export\\rocket.tga");
        }

        video::ITexture * getAsteroidTexture(core::stringw texture) {
            return m_driver->getTexture("d:\\xpn_2013\\export\\asteroid.tga");
        }

        video::ITexture * getPlayerTexture(core::stringw texture) {
            return m_driver->getTexture("d:\\xpn_2013\\export\\fighter.tga");
        }
    protected:
        void init();
        void updateFPS();
        void render();

        Screen * getActiveScreen();
    private:
        Options m_options;

        InputReceiver m_receiver;

        IrrlichtDevice* m_device;
        video::IVideoDriver* m_driver;
        scene::ISceneManager* m_scene;
        core::array<SJoystickInfo> m_joystickInfo;

        static const TCHAR * m_title;

        int m_fps;
    };

}