#pragma once

namespace stellabellum {
    namespace states {

        class CStateMachine;

        class CState {
        public:
            CState();
            virtual ~CState(void);

            virtual void enter() = 0;
            virtual void leave() = 0;
            virtual void init() = 0;

            virtual void update(const f32 delta) = 0;

            virtual int getId() const = 0;            
        protected:
            virtual CStateMachine* getStateMachine() inline const {
                return Machine;
            }

        private:
            void setup(CStateMachine* machine);

            bool IsInited;
            CStateMachine* Machine;

            friend class CStateMachine;
        };

    }
}