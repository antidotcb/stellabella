#pragma once

namespace stellabellum {
    namespace game {

        class CInput: public IEventReceiver {
        public:
            CInput();

            virtual ~CInput();

            virtual bool OnEvent(const SEvent& event);

            typedef SEvent::SJoystickEvent SGamepadState;

            struct SMouseState {
                bool LeftBtnPressed;
                bool RightBtnPressed;
                core::position2di Position;

                SMouseState();
            };

            virtual bool isKeyPressed(const EKEY_CODE keyCode) const;
            
            virtual const SMouseState& getMouseState() const;

            virtual const SGamepadState& getGamepadState(const u32 joy) const;
            
            virtual const bool isGamepadAvailable(const u32 joy) const;

            virtual void initGamepads(IrrlichtDevice* device);

        private:
            core::array<SJoystickInfo> GamepadInfos;
            u32 GamepadCount;

            bool IsKeyPressed[KEY_KEY_CODES_COUNT];
            core::array<SGamepadState> GamepadStates;
            SMouseState MouseState;
        };


        class CControls {
        public:
            CControls(game::CInput* input);

            bool isFirePressed() const;

            void getMovement(core::vector2df& movement) const;

        private:
            const f32 getDeadZone() inline const        { return DeadZone ; }

            const EKEY_CODE getUpKey() inline const     { return UpKey; }
            const EKEY_CODE getDownKey() inline const   { return DownKey; }
            const EKEY_CODE getLeftKey() inline const   { return LeftKey; }
            const EKEY_CODE getRightKey() inline const  { return RightKey; }
            const EKEY_CODE getFireKey() inline const   { return FireKey; }

            const u32 getFireButton() inline const      { return FireButton; }
            const u32 getHorizontalAxis() inline const  { return AxisH; }
            const u32 getVerticalAxis() inline const    { return AxisV; }

            bool getGamepadMovement(core::vector2df& movement) const;

            u32 Gamepad;

            game::CInput* Input;

            static const EKEY_CODE FireKey    = KEY_SPACE;
            static const EKEY_CODE UpKey      = KEY_UP;
            static const EKEY_CODE DownKey    = KEY_DOWN;
            static const EKEY_CODE LeftKey    = KEY_LEFT;
            static const EKEY_CODE RightKey   = KEY_RIGHT;

            static const u32 FireButton = 0;

            static const u32 AxisH = game::CInput::SGamepadState::AXIS_X;
            static const u32 AxisV = game::CInput::SGamepadState::AXIS_Y;

            static const f32 DeadZone;
        };
    }
}