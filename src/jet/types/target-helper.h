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

LLD_HAS_DRIVER(elf)
LLD_HAS_DRIVER(macho)

#ifndef BUILD_TARGET
#define BUILD_TARGET "unknown"
#endif


class TargetHelper {
private:
    static std::vector<const char*> getMacosx86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
    static std::vector<const char*> getMacosAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
    static std::vector<const char*> getLinuxGnux86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
    static std::vector<const char*> getLinuxGnuAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
    static std::vector<const char*> getLinuxMuslx86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
    static std::vector<const char*> getLinuxMuslAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
public:
    static std::string getLLVMTarget();
    static std::vector<const char*> getLinkerArgs(std::string targetTriple, std::string* objectFilename, std::string* outputFileName);
    static std::array<lld::DriverDef, 2> getLinkerDrivers();
};

#endif //JETLANG_TARGET_HELPER_H
