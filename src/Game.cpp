#include "StdAfx.h"
#include "Game.h"
#include "Screen.h"

namespace stellabellum {
    Game::Game(Options & options): m_options(options) {
        _initialize();
    }

    void Game::run()
    {
        u32 then = m_device->getTimer()->getTime();

        // main loop
        while(m_device->run()) {
            // Work out a frame delta time.
            const u32 now = m_device->getTimer()->getTime();        
            const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds

            _updateFPS();

            update(frameDeltaTime);

            _render();


            Sleep(0);
        }
    }

    Game::~Game() {
        m_device->drop();
    }

    void Game::_initialize() {
        core::dimension2d<u32> windowSize(m_options.Width, m_options.Height);
        // creation of rendering device
        m_device = createDevice(m_options.Driver, windowSize, 16,
            false, false, false, &m_receiver);

        if (!m_device) {
            DebugBreak();
            throw std::exception("Cannot initialize rendering device.");
        }

        m_driver = m_device->getVideoDriver();
        m_scene = m_device->getSceneManager();
    }

    void Game::_render() {
        Screen * scr = _getCurrentScreen();

        if (scr) {
            m_driver->beginScene(true, true, scr->getBgColor());
            scr->render();
            m_driver->endScene();
        }
    }

    Screen * Game::_getCurrentScreen() {
        return dynamic_cast<Screen *>(_getCurrentState());
    }

    void Game::_updateFPS() {
        int fps = m_driver->getFPS();
        if (m_fps != fps) {
            m_fps = fps;

            core::stringw tmp(m_title);
            tmp += L" - [";
            tmp += m_driver->getName();
            tmp += L"] fps: ";
            tmp += fps;

            m_device->setWindowCaption(tmp.c_str());
        }
    }

    ISceneManager * Game::createNewScene() {
        return m_scene->createNewSceneManager();
    }

    const TCHAR * Game::m_title = L"Stella Bellum";

}