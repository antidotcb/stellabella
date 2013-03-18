#include "stellabellum.h"
#include "Game.h"
#include "Screen.h"
#include "Input.h"

namespace stellabellum {
    namespace game {

        CGame::CGame(const SOptions & options)
            : Options(options),
            Controls(&Input),
            RocketMesh(0)
        {
            init();
        }

        void CGame::run()
        {
            u32 then = Device->getTimer()->getTime();

            while(Device->run()) {                
                const u32 now = Device->getTimer()->getTime();        
                const f32 frameDeltaTime = (f32)(now - then) / 1000.f;

                updateFPS();

                update(frameDeltaTime);

                render();

                then = now;
            }
        }

        CGame::~CGame() {
            Device->drop();
        }

        void CGame::init() {
            core::dimension2d<u32> windowSize(Options.Width, Options.Height);
            
            Device = createDevice(Options.Driver, windowSize, 16,
                false, false, false, dynamic_cast<IEventReceiver*>(&Input));

            if (!Device) {
                throw std::exception("Cannot initialize rendering device.");
            }

            Input.initGamepads(Device);

            Driver = Device->getVideoDriver();
            Scene = Device->getSceneManager();
        }

        void CGame::render() {
            CScreen* scr = getActiveScreen();

            if (scr) {
                Driver->beginScene(true, true, scr->getBgColor());
                scr->render();
                Driver->endScene();
            }
        }

        CScreen* CGame::getActiveScreen() {
            return dynamic_cast<CScreen *>(getCurrentState());
        }

        void CGame::updateFPS() {
            int fps = Driver->getFPS();
            if (FramesPerSecond != fps) {
                FramesPerSecond = fps;

                core::stringw tmp(Title);
                tmp += L" - [";
                tmp += Driver->getName();
                tmp += L"] fps: ";
                tmp += fps;

                Device->setWindowCaption(tmp.c_str());
            }
        }

        ISceneManager* CGame::createNewScene() {
            ISceneManager* scene = Scene->createNewSceneManager();
            return scene;
        }

        scene::IAnimatedMesh* CGame::getRocketMesh() {
            if (!RocketMesh) {
                RocketMesh = Scene->getMesh("d:\\xpn_2013\\export\\rocket.X");
            }

            return RocketMesh;
        }

        const wchar_t* CGame::Title = L"Stella Bellum";

    }
}