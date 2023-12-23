//
// Created by Johny Georges on 2023-12-23.
//

#include <fstream>
#include "file-io.h"
#include "shared/utils/logger/logger.h"
#include "shared/types/exit-status.enum.h"

namespace FileIO {
    char* readFile(const char* path) {
        FILE* file = fopen(path, "r");
        if (file == nullptr) {
            Logger::log("file not found:", path);
            Logger::log("exiting...");
            exit(EXIT_STATUS_FILE_IO_ERROR);
        }
        return (char*)'c';
    }
}