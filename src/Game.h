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

        class CGame : public states::CStateMachine
        {
        protected:
            static const u32 DefaultWidth = 1900;
            static const u32 DefaultHeight = 1000;
            static const video::E_DRIVER_TYPE DefaultDriverType = video::EDT_OPENGL;

        public:
            struct SOptions {
                u32 Width;
                u32 Height;
                video::E_DRIVER_TYPE Driver;
                SOptions():
                Width(DefaultWidth),
                    Height(DefaultHeight),
                    Driver(DefaultDriverType) {}
            };

            CGame(const SOptions& options);
            ~CGame();

            void run();

            ISceneManager* createNewScene();

            const int& getFPS() inline const { return FramesPerSecond; }

            IrrlichtDevice* getDevice() const { return Device; }            

            scene::IAnimatedMesh* getRocketMesh();

            video::ITexture* getRocketTexture() {
                return Driver->getTexture("d:\\xpn_2013\\export\\rocket.tga");
            }

            video::ITexture* getAsteroidTexture() {
                return Driver->getTexture("d:\\xpn_2013\\export\\asteroid.tga");
            }

            video::ITexture* getPlayerTexture() {
                return Driver->getTexture("d:\\xpn_2013\\export\\fighter.tga");
            }

            const CControls& getControls() inline const { return Controls; }

            const u32& getWidth() inline const { return Options.Width; }
            const u32& getHeight() inline const { return Options.Height; }
        protected:
            void init();
            void updateFPS();
            void render();

            CScreen* getActiveScreen();

            const CInput& getRawInput() const { return Input; }
        private:
            SOptions Options;
            CInput Input;
            CControls Controls;

            IrrlichtDevice* Device;
            video::IVideoDriver* Driver;
            scene::ISceneManager* Scene;

            static const wchar_t* Title;

            scene::IAnimatedMesh* RocketMesh;

            int FramesPerSecond;
        };

    }
}