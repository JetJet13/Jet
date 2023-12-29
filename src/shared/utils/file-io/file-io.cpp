//
// Created by Johny Georges on 2023-12-23.
//

#include <fstream>
#include "../logger/logger.h"
#include "../../types/exit-status.enum.h"


namespace FileIO {
    std::ifstream readFile(std::string &path) {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            Logger::log("file not found:", path);
            Logger::log("exiting...");
            exit(EXIT_STATUS_FILE_IO_ERROR);
        }
        Logger::log("opened file", path);
        Logger::log("don't forget to close it when you're done!");
        return file;
    }
}