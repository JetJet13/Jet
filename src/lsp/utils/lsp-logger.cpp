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
// Created by Johny Georges on 2026-10-30.
//

#include "lsp-logger.h"

void LspLogger::log(Level level, std::wstring&& msg) {
    std::wcout << msg << std::endl;
}

void LspLogger::log(Level level, const std::wstring& msg) {
    std::wcout << msg << std::endl;
}

void LspLogger::log(Level level, std::string&& msg) {
    std::cout << msg << std::endl;
}

void LspLogger::log(Level level, const std::string& msg) {
    std::cout << msg << std::endl;
}