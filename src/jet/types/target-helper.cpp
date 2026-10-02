//
// Created by Johny Georges on 2026-09-30.
//

#include "target-helper.h"
#include "supported-llvm-targets.h"

std::string TargetHelper::getLLVMTarget() {
    std::string targetTriple = BUILD_TARGET;
    if (targetTriple == SUPPORTED_TARGETS.X86_MAC_OS) {
        return SUPPORTED_LLVM_TARGETS.X86_MAC_OS_TARGET_TRIPLE;
    } else if (targetTriple == SUPPORTED_TARGETS.X86_LINUX_GNU) {
        return SUPPORTED_LLVM_TARGETS.X86_LINUX_GNU_TARGET_TRIPLE;
    } else if (targetTriple == SUPPORTED_TARGETS.X86_LINUX_MUSL) {
        return SUPPORTED_LLVM_TARGETS.X86_LINUX_MUSL_TARGET_TRIPLE;
    } else if (targetTriple == SUPPORTED_TARGETS.ARM64_MAC_OS) {
        return SUPPORTED_LLVM_TARGETS.ARM64_MAC_OS_TARGET_TRIPLE;
    } else if (targetTriple == SUPPORTED_TARGETS.ARM64_LINUX_GNU) {
        return SUPPORTED_LLVM_TARGETS.ARM64_LINUX_GNU_TARGET_TRIPLE;
    } else if (targetTriple == SUPPORTED_TARGETS.ARM64_LINUX_MUSL) {
        return SUPPORTED_LLVM_TARGETS.ARM64_LINUX_MUSL_TARGET_TRIPLE;
    }

    throw std::logic_error("getLLVMTarget - unsupported target triple" + targetTriple);
}

std::vector<const char*> TargetHelper::getLinkerArgs(std::string targetTriple, std::string* objectFilename, std::string* outputFileName) {
    if (targetTriple == SUPPORTED_LLVM_TARGETS.X86_MAC_OS_TARGET_TRIPLE) {
        return TargetHelper::getMacosx86_64LinkerArgs(objectFilename, outputFileName);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.X86_LINUX_GNU_TARGET_TRIPLE) {
        return TargetHelper::getLinuxGnux86_64LinkerArgs(objectFilename, outputFileName);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.X86_LINUX_MUSL_TARGET_TRIPLE) {
        return TargetHelper::getLinuxMuslx86_64LinkerArgs(objectFilename, outputFileName);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.ARM64_MAC_OS_TARGET_TRIPLE) {
        return TargetHelper::getMacosAarch64LinkerArgs(objectFilename, outputFileName);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.ARM64_LINUX_GNU_TARGET_TRIPLE) {
        return TargetHelper::getLinuxGnuAarch64LinkerArgs(objectFilename, outputFileName);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.ARM64_LINUX_MUSL_TARGET_TRIPLE) {
        return TargetHelper::getLinuxMuslAarch64LinkerArgs(objectFilename, outputFileName);
    }

    throw std::logic_error("getLinkerArgs - unsupported target triple" + targetTriple);
}

std::array<lld::DriverDef, 2> TargetHelper::getLinkerDrivers() {
    lld::DriverDef macOsLinker = { lld::Darwin, lld::macho::link };
    lld::DriverDef linuxLinker = { lld::Gnu, lld::elf::link };
    return { macOsLinker, linuxLinker };
}

std::vector<const char*> TargetHelper::getMacosx86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
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

std::vector<const char*> TargetHelper::getMacosAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
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

std::vector<const char*> TargetHelper::getLinuxGnux86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
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

std::vector<const char*> TargetHelper::getLinuxGnuAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
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

std::vector<const char*> TargetHelper::getLinuxMuslx86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
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

std::vector<const char*> TargetHelper::getLinuxMuslAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName) {
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