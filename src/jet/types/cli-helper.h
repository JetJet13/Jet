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
// Created by Johny Georges on 2026-10-03.
//

#ifndef JETLANG_CLI_HELPER_H
#define JETLANG_CLI_HELPER_H

#define CLI11_ENABLE_EXTRA_VALIDATORS 1
#define CLI11_HAS_FILESYSTEM 1

#include <string>
#include "../cli11/CLI11.hpp"

class CliHelper {
private:
    CLI::App* _app;
public:
    CliHelper(CLI::App* app);
    CliHelper* addFilePathOption(std::string &filePathVar);
    CliHelper* addOutDirOption(std::string &outDirVar);
    CliHelper* addMacosSysLibDirOption(std::string &macosSysLibDirectoryOverrideVar);
    CliHelper* addLinuxDynamicLinkerPathOverrideOption(std::string &linuxDynamicLinkerPathOverrideVar);
    CliHelper* addLinuxMultiArchPathOverrideOption(std::string &linuxMultiArchPathOverrideVar);
    CliHelper* addLinuxLibDirOverrideOption(std::string &linuxLibDirOverrideVar);
    CliHelper* addIncludeObjectFileFlag(bool &includeObjectFileVar);
    CliHelper* addPrintIRFlag(bool &printIRVar);
};

#endif //JETLANG_CLI_HELPER_H
