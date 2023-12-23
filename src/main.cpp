//
// Created by Johny Georges on 2023-12-19.
//

#include "main.h"
#include "shared/types/exit-status.enum.h"
#include "shared/utils/logger/logger.h"
#include "shared/utils/file-io/file-io.h"

int main (int argc, const char* argv[]) {
    if (argc == 1) {
        Logger::log("no file provided...starting REPL");
        Logger::log("nevermind...REPL is not ready...exiting.");
    } else if (argc == 2) {
        const char* filePath = argv[1];
        Logger::log("executing file:", filePath);
        FileIO::readFile(filePath);
    } else {
        Logger::log("too many arguments..exiting");
    }

    return EXIT_STATUS_OK;
}