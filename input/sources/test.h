#ifndef INPUT_SOURCES_TEST_H
#define INPUT_SOURCES_TEST_H

#include "input/sources/base.h"

namespace Input{ namespace Sources {

    class Test : public Base {
        public:
        Test();

        private:
        virtual void init_events(void);
    };
} }

#endif
