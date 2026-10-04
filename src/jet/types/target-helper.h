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
