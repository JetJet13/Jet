//
// Created by Johny Georges on 2026-09-30.
//

#ifndef JETLANG_TARGET_HELPER_H
#define JETLANG_TARGET_HELPER_H

#include <vector>
#include <string>
#include <filesystem>
#include "lld/Common/Driver.h"
#include "supported-targets.h"
#include "linker-arg-overrides.h"

LLD_HAS_DRIVER(elf)
LLD_HAS_DRIVER(macho)

#ifndef BUILD_TARGET
#define BUILD_TARGET "unknown"
#endif


class TargetHelper {
private:
    static std::vector<const char*> getX86_64MacosLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides);
    static std::vector<const char*> getAarch64MacosLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides);
    static std::vector<const char*> getX86_64LinuxGnuLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides);
    static std::vector<const char*> getAarch64LinuxGnuLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides);
    static std::vector<const char*> getX86_64LinuxMuslLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides);
    static std::vector<const char*> getAarch64LinuxMuslLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides);
public:
    static std::string getLLVMTarget();
    static std::vector<const char*> getLinkerArgs(std::string targetTriple, std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides);
    static std::array<lld::DriverDef, 2> getLinkerDrivers();
};

#endif //JETLANG_TARGET_HELPER_H
