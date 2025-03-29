#include "webspeeddial/Runner.h"
#include <cstdio>
#include <iostream>
FILE* Runner::run() {
    this->f = popen(this->cmd->data(), "r");
    if (!this->f) {
        if (!this->err) {
            std::cout << this->err << std::endl;
        }
        return NULL;
    }
    return this->f;
}

void Runner::close() {
    if (!this->f) {
        return;
    }
    pclose(this->f);
    this->f = NULL;
}
