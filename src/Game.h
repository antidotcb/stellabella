#pragma once

#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace video;
using namespace scene;

#include "StateMachine.h"
#include "Input.h"

namespace stellabellum {

    namespace game {

        class Input;
        class Screen;
        class PlayerControl;

        class Game : public states::StateMachine
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

            Game(Options& options);
            ~Game();

            void run();

            ISceneManager* createNewScene();

            const int& getFPS() const { return m_fps;}

            IrrlichtDevice* getDevice() const { return m_device; }            
            /*
            video::ITexture* getRocketTexture(core::stringw texture) {
                return m_driver->getTexture("d:\\xpn_2013\\export\\rocket.tga");
            }

            video::ITexture* getAsteroidTexture(core::stringw texture) {
                return m_driver->getTexture("d:\\xpn_2013\\export\\asteroid.tga");
            }
            */

            video::ITexture* getPlayerTexture(core::stringw texture) {
                return m_driver->getTexture("d:\\xpn_2013\\export\\fighter.tga");
            }

            const PlayerControl& getPlayerControl() inline const { return m_playerControl; }
        protected:
            void init();
            void updateFPS();
            void render();

            Screen* getActiveScreen();

            const Input& getRawInput() const { return m_input; }
        private:
            Options m_options;
            Input m_input;
            PlayerControl m_playerControl;

            IrrlichtDevice* m_device;
            video::IVideoDriver* m_driver;
            scene::ISceneManager* m_scene;
            

            static const wchar_t* m_title;

            int m_fps;
        };

    }
}