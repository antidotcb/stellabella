#pragma once

#include <IEventReceiver.h>
#include <vector>

using namespace irr;
using std::vector;

namespace stellabellum {

    class InputReceiver: public IEventReceiver {
    public:
        // constructor
        InputReceiver();

        // default virtual destructor
        virtual ~InputReceiver() {}
    
        struct SMouseState {
            bool leftBtnPressed;
            bool rightBtnPressed;
            core::position2di position;

            SMouseState(): leftBtnPressed(false), rightBtnPressed(false) {}
        };

        // This is the one method that we have to implement
        virtual bool OnEvent(const SEvent& event);

        // used to check whether a key is being held down
        virtual bool isKeyPressed(EKEY_CODE keyCode) const {
            return m_keyPressed[keyCode];
        }

        // read-only accessor for joystick state
        virtual const SEvent::SJoystickEvent & getJoystickState(void) const {
            return m_joystickState;
        }

        // read-only accessor for mouse state
        virtual const SMouseState & getMouseState() const {
            return m_mouseState;
        }
    private:
        
        // array to store the current state of each key
        bool m_keyPressed[KEY_KEY_CODES_COUNT];

        // joystick state
        SEvent::SJoystickEvent m_joystickState;

        // mouse state
        SMouseState m_mouseState;
    };

}