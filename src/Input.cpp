#include "stellabellum.h"
#include "Input.h"

namespace stellabellum {
    namespace game {

        Input::Input()
            : m_GamepadCount(0)
        {
            for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                m_keyPressed[i] = false;
        }

        Input::~Input() {
            // empty
        }

        bool Input::OnEvent(const SEvent& event) {
            if (event.EventType == irr::EET_KEY_INPUT_EVENT)
                m_keyPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;

            if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
            {
                switch(event.MouseInput.Event)
                {
                case EMIE_RMOUSE_PRESSED_DOWN:
                    m_mouseState.RightBtnPressed = true;
                    break;

                case EMIE_RMOUSE_LEFT_UP:
                    m_mouseState.RightBtnPressed = false;
                    break;

                case EMIE_LMOUSE_PRESSED_DOWN:
                    m_mouseState.LeftBtnPressed = true;
                    break;

                case EMIE_LMOUSE_LEFT_UP:
                    m_mouseState.LeftBtnPressed = false;
                    break;

                case EMIE_MOUSE_MOVED:
                    m_mouseState.Position.X = event.MouseInput.X;
                    m_mouseState.Position.Y = event.MouseInput.Y;
                    break;

                default:
                    break;
                }
            }

            for (u32 i = 0; i < m_GamepadCount; i++) {
                if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
                    && event.JoystickEvent.Joystick == i) {
                        m_GamepadState[i] = event.JoystickEvent;
                }
            }

            return false;
        }

        const Input::MouseState& Input::getMouseState() const {
            return m_mouseState;
        }

        bool Input::isKeyPressed(const EKEY_CODE keyCode) const {
            return m_keyPressed[keyCode];
        }

        const Input::GamepadState& Input::getGamepadState(const u32 j) const {
            return m_GamepadState[j];
        }

        const bool Input::isGamepadAvailable( const u32 j ) const {
            return j < m_GamepadCount;
        }

        void Input::initGamepads(IrrlichtDevice* device) {
            device->activateJoysticks(m_GamepadInfo);

            m_GamepadCount = m_GamepadInfo.size();
            for(int i = m_GamepadCount; i--;) {
                m_GamepadState.push_back(GamepadState());
            }
        }


        Input::MouseState::MouseState()
            :LeftBtnPressed(false),
            RightBtnPressed(false) {}


        PlayerControl::PlayerControl(game::Input* input)
            : m_input(input),
            m_GamepadNum(0)
        {
        }

        bool PlayerControl::isFirePressed() const {
            bool keyPressed = m_input->isKeyPressed(getFireKey());
            bool buttonPressed = false;

            if (m_input->isGamepadAvailable(m_GamepadNum)) {
                const Input::GamepadState& joyState =
                    m_input->getGamepadState(m_GamepadNum);

                buttonPressed = joyState.IsButtonPressed(getFireButton());
            }

            return  keyPressed || buttonPressed;
        }

        void PlayerControl::getMovement(core::vector2df& movement) const {            
            if (!getGamepadMovement(movement)) {
                const Input::MouseState& mState = m_input->getMouseState();
                
                if (m_input->isKeyPressed(getLeftKey())) {
                    movement.X -= 1.f;
                }

                if (m_input->isKeyPressed(getRightKey())) {
                    movement.X += 1.f;
                }

                if (m_input->isKeyPressed(getUpKey())) {
                    movement.Y += 1.f;
                }

                if (m_input->isKeyPressed(getDownKey())) {
                    movement.Y -= 1.f;
                }
            }
        }

        bool PlayerControl::getGamepadMovement(core::vector2df& movement) const {
            if (!m_input->isGamepadAvailable(m_GamepadNum)) {
                return false;
            }

            const stellabellum::game::Input::GamepadState & joyState = 
                m_input->getGamepadState(m_GamepadNum);

            f32 deadZone = getDeadZone();

            f32 hMove = 0.f;
            f32 vMove = 0.f;

            u32 vAxis = getVerticalAxis();
            vMove = (f32) joyState.Axis[vAxis] / -32767.f;
            vMove = (fabs(vMove) < m_deadZone) ? 0.f : vMove;

            u32 hAxis = getHorizontalAxis();
            hMove = (f32) joyState.Axis[hAxis] / 32767.f;
            hMove = (fabs(hMove) < m_deadZone) ? 0.f : hMove;

            if (core::equals(hMove, 0.f) && core::equals(vMove, 0.f)) {
                return false;
            } else {
                movement.X = hMove;
                movement.Y = vMove;

                return true;
            }
        }

        const f32 PlayerControl::m_deadZone = 0.05f;

    }
}