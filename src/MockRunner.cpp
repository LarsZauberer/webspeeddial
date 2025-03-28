#include "MockRunner.h"
MockRunner::MockRunner(std::string *data) {
            if (!data) {
                mock_data = NULL;
                f = NULL;
                return;
            }
            mock_data = data;
            f = fmemopen(data->data(), data->size(), "r"); 
}

FILE *MockRunner::run() {
    return f;
}

void MockRunner::close() {
    fclose(f);
}
