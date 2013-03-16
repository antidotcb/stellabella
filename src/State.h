#pragma once

namespace stellabellum {
    namespace states {

        class StateMachine;

        class State {
        public:
            State();
            virtual ~State(void);

            virtual void enter() = 0;
            virtual void leave() = 0;
            virtual void init() = 0;

            virtual void update(const f32 delta) = 0;

            virtual int getId() = 0;            
        protected:
            virtual StateMachine* getStateMachine() inline const {
                return m_machine;
            }

        private:
            void setup(StateMachine* machine);

            bool m_inited;
            StateMachine* m_machine;

            friend class StateMachine;
        };

    }
}