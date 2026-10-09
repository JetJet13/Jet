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
// Created by Johny Georges on 2026-09-30.
//

#ifndef JETLANG_TARGET_HELPER_H
#define JETLANG_TARGET_HELPER_H

#include <vector>
#include <string>
#include <filesystem>
#include <utility>
#include "supported-llvm-targets.h"
#include "lld/Common/Driver.h"
#include "supported-targets.h"
#include "linker-arg-builder.h"

LLD_HAS_DRIVER(elf)
LLD_HAS_DRIVER(macho)

#ifndef BUILD_TARGET
#define BUILD_TARGET "unknown"
#endif


class TargetHelper {
private:
    static void generateX86_64MacosLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder);
    static void generateAarch64MacosLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder);
    static void generateX86_64LinuxGnuLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder);
    static void generateAarch64LinuxGnuLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder);
    static void generateX86_64LinuxMuslLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder);
    static void generateAarch64LinuxMuslLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder);
public:
    static std::string getLLVMTarget();
    static void generateLinkerArgs(std::string targetTriple, std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder);
    static std::array<lld::DriverDef, 2> getLinkerDrivers();
};

#endif //JETLANG_TARGET_HELPER_H
