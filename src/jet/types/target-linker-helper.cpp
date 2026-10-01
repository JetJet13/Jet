//
// Created by Johny Georges on 2026-09-30.
//

#include "target-linker-helper.h"
#include "../../shared/utils/logger/logger.h"

std::vector<const char*> TargetLinkerHelper::getArgs(std::string targetTriple, std::string* objectFilename, std::string* outputFileName) {
    if (targetTriple == SUPPORTED_TARGETS.X86_MAC_OS_TARGET_TRIPLE) {
        return TargetLinkerHelper::getMacosx86_64LinkerArgs(objectFilename, outputFileName);
    } else if (targetTriple == SUPPORTED_TARGETS.X86_LINUX_GNU_TARGET_TRIPLE) {
        return TargetLinkerHelper::getLinuxGnux86_64LinkerArgs(objectFilename, outputFileName);
    } else if (targetTriple == SUPPORTED_TARGETS.X86_LINUX_MUSL_TARGET_TRIPLE) {
        return TargetLinkerHelper::getLinuxMuslx86_64LinkerArgs(objectFilename, outputFileName);
    } else if (targetTriple == SUPPORTED_TARGETS.ARM64_MAC_OS_TARGET_TRIPLE) {
        return TargetLinkerHelper::getMacosAarch64LinkerArgs(objectFilename, outputFileName);
    } else if (targetTriple == SUPPORTED_TARGETS.ARM64_LINUX_GNU_TARGET_TRIPLE) {
        return TargetLinkerHelper::getLinuxGnuAarch64LinkerArgs(objectFilename, outputFileName);
    } else if (targetTriple == SUPPORTED_TARGETS.ARM64_LINUX_MUSL_TARGET_TRIPLE) {
        return TargetLinkerHelper::getLinuxMuslAarch64LinkerArgs(objectFilename, outputFileName);
    }

    Logger::log("unsupported target triple", targetTriple, "returning empty list of linker args");
    return {};
}

std::vector<const char*> TargetLinkerHelper::getMacosx86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
    return {
        "ld64.lld",
        "-arch", "x86_64",
        "-platform_version", "macos", "12.7", "13.0",
        "-lc++",
        "-lSystem",
        "-syslibroot", "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk",
        objectFilename->c_str(),
        "-o", outputFileName->c_str()
    };
}

std::vector<const char*> TargetLinkerHelper::getMacosAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
    return {
        "ld64.lld",
        "-v",
        "-arch", "arm64",
        "-platform_version", "macos", "26.0", "26.0",
        "-L /usr/local/llvm-17/lib",
        "-lc++",
        "-lSystem",
        "-syslibroot", "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk",
        objectFilename->c_str(),
        "-o", outputFileName->c_str()
    };
}

std::vector<const char*> TargetLinkerHelper::getLinuxGnux86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
    return {
        "ld.lld",
        "-t",
        "-z", "relro",
        "-m", "elf_x86_64",
        "-dynamic-linker", "/lib64/ld-linux-x86-64.so.2",
        "/usr/lib/x86_64-linux-gnu/crt1.o",
        "/usr/lib/x86_64-linux-gnu/crti.o",
        "-L/usr/lib/x86_64-linux-gnu",
        "-L/usr/lib",
        "-lc++",
        "-lc++abi",
        "-lunwind",
        "-lm",
        "-lc",
        objectFilename->c_str(),
        "-o", outputFileName->c_str(),
        "/usr/lib/x86_64-linux-gnu/crtn.o",
    };
}

std::vector<const char*> TargetLinkerHelper::getLinuxGnuAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
    return {
        "ld.lld",
        "-t",
        "-z", "relro",
        "-m", "aarch64elf",
        "-dynamic-linker", "/lib/ld-linux-aarch64.so.1",
        "/usr/lib/aarch64-linux-gnu/crt1.o",
        "/usr/lib/aarch64-linux-gnu/crti.o",
        "-L/usr/lib/aarch64-linux-gnu",
        "-L/usr/lib",
        "-lc++",
        "-lc++abi",
        "-lunwind",
        "-lm",
        "-lc",
        objectFilename->c_str(),
        "-o", outputFileName->c_str(),
        "/usr/lib/aarch64-linux-gnu/crtn.o",
    };
}

std::vector<const char*> TargetLinkerHelper::getLinuxMuslx86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
    return {
        "ld.lld",
        "-t",
        "-z", "relro",
        "-m", "elf_x86_64",
        "-dynamic-linker", "/lib/ld-musl-x86_64.so.1",
        "/usr/lib/crt1.o",
        "/usr/lib/crti.o",
        "-L/usr/lib",
        "-lc++",
        "-lc++abi",
        "-lm",
        "-lc",
        objectFilename->c_str(),
        "-o", outputFileName->c_str(),
        "/usr/lib/crtn.o",
    };
}

std::vector<const char*> TargetLinkerHelper::getLinuxMuslAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
    return {
        "ld.lld",
        "-t",
        "-z", "relro",
        "-m", "aarch64linux",
        "-dynamic-linker", "/lib/ld-musl-aarch64.so.1",
        "/usr/lib/crt1.o",
        "/usr/lib/crti.o",
        "-L/usr/lib",
        "-lc++",
        "-lc++abi",
        "-lm",
        "-lc",
        objectFilename->c_str(),
        "-o", outputFileName->c_str(),
        "/usr/lib/crtn.o",
    };
}