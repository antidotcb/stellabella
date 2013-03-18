#include "stellabellum.h"
#include "State.h"

namespace stellabellum {
    namespace states {

        stellabellum::states::CState::CState()
            :IsInited(false),
            Machine(0) {}

        stellabellum::states::CState::~CState() {}

        void CState::setup(CStateMachine* machine) {
            if (machine) {
                Machine = machine;
            } else {
                throw std::exception("Null pointer as state machine.");
            }

            if (!IsInited) {
                init();
                IsInited = true;
            }
        }

    }
}