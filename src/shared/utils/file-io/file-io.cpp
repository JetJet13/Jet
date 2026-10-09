// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
        return file;
    }
}