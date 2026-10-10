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
// Created by Johny Georges on 2026-10-02.
//

#ifndef JETLANG_LINKER_ARG_BUILDER_H
#define JETLANG_LINKER_ARG_BUILDER_H

#include <string>
#include <optional>
#include <vector>
#include <utility>

class LinkerArgBuilder {
private:
    std::string _macosSysLibFileOverride;
    std::string _macosSysLibFileDefault;

    std::string _linuxDynamicLinkerFileOverride;
    std::string _linuxDynamicLinkerFileDefault;

    std::string _linuxMultiArchDirectoryOverride;
    std::string _linuxMultiArchDirectoryDefault;

    std::string _linuxLibDirectoryOverride;
    std::string _linuxLibDirectoryDefault;

    std::vector<std::string> _args;
public:
    LinkerArgBuilder(std::string macosSysLibFileOverride, std::string linuxDynamicLinkerFileOverride, std::string linuxMultiArchDirectoryOverride, std::string linuxLibDirectoryOverride);
    std::string getMacOsSysLibFile();
    std::string getLinuxDynamicLinkerFile();
    std::string getLinuxMultiArchDirectory();
    std::string getLinuxLibDirectory();
    LinkerArgBuilder* setMacOsSysLibFileDefault(std::string defaultMacosSysLibFile);
    LinkerArgBuilder* setLinuxDynamicLinkerFileDefault(std::string defaultLinuxDynamicLinkerFile);
    LinkerArgBuilder* setLinuxMultiArchDirectoryDefault(std::string defaultLinuxMultiArchDirectory);
    LinkerArgBuilder* setLinuxLibDirectoryDefault(std::string defaultLinuxLibDirectory);
    LinkerArgBuilder* addArg(std::string arg);
    std::vector<const char*> build();
};

#endif //JETLANG_LINKER_ARG_BUILDER_H
