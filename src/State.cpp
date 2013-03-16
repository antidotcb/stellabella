#include "stellabellum.h"
#include "State.h"

namespace stellabellum {
    namespace states {

        stellabellum::states::State::State()
            :m_inited(false),
            m_machine(0) {}

        stellabellum::states::State::~State() {}

        void State::setup(StateMachine* machine) {
            if (machine) {
                m_machine = machine;
            } else {
                throw std::exception("Null pointer as state machine.");
            }

            if (!m_inited) {
                init();
                m_inited = true;
            }
        }

    }
}