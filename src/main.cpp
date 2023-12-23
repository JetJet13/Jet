//
// Created by Johny Georges on 2023-12-19.
//

#include "main.h"
#include "shared/types/exit-status.enum.h"
#include "shared/utils/logger/logger.h"

int main (int argc, const char* argv[]) {
    if (argc == 1) {
        Logger::log("no file provided...starting REPL");
    }

    Logger::log(argv, argc, "Arg: ");

    return EXIT_STATUS_OK;
}