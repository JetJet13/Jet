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

std::vector<const char*> TargetHelper::getLinkerArgs(std::string targetTriple, std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides) {
    if (targetTriple == SUPPORTED_LLVM_TARGETS.X86_MAC_OS_TARGET_TRIPLE) {
        return TargetHelper::getX86_64MacosLinkerArgs(objectFilename, outputFileName, linkerArgOverrides);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.X86_LINUX_GNU_TARGET_TRIPLE) {
        return TargetHelper::getX86_64LinuxGnuLinkerArgs(objectFilename, outputFileName, linkerArgOverrides);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.X86_LINUX_MUSL_TARGET_TRIPLE) {
        return TargetHelper::getX86_64LinuxMuslLinkerArgs(objectFilename, outputFileName, linkerArgOverrides);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.ARM64_MAC_OS_TARGET_TRIPLE) {
        return TargetHelper::getAarch64MacosLinkerArgs(objectFilename, outputFileName, linkerArgOverrides);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.ARM64_LINUX_GNU_TARGET_TRIPLE) {
        return TargetHelper::getAarch64LinuxGnuLinkerArgs(objectFilename, outputFileName, linkerArgOverrides);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.ARM64_LINUX_MUSL_TARGET_TRIPLE) {
        return TargetHelper::getAarch64LinuxMuslLinkerArgs(objectFilename, outputFileName, linkerArgOverrides);
    }

    throw std::logic_error("getLinkerArgs - unsupported target triple" + targetTriple);
}

std::array<lld::DriverDef, 2> TargetHelper::getLinkerDrivers() {
    lld::DriverDef macOsLinker = { lld::Darwin, lld::macho::link };
    lld::DriverDef linuxLinker = { lld::Gnu, lld::elf::link };
    return { macOsLinker, linuxLinker };
}

std::vector<const char*> TargetHelper::getX86_64MacosLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides) {
    linkerArgOverrides->setMacOsSysLibFileDefault("/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk");
    return {
        "ld64.lld",
        "-arch", "x86_64",
        "-platform_version", "macos", "12.7", "13.0",
        "-syslibroot", linkerArgOverrides->getMacOsSysLibFile()->c_str(),
        "-lc++",
        "-lSystem",
        objectFilename->c_str(),
        "-o", outputFileName->c_str()
    };
}

std::vector<const char*> TargetHelper::getAarch64MacosLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides) {
    linkerArgOverrides->setMacOsSysLibFileDefault("/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk");
    return {
        "ld64.lld",
        "-v",
        "-arch", "arm64",
        "-platform_version", "macos", "12.7", "13.0",
        "-syslibroot", linkerArgOverrides->getMacOsSysLibFile()->c_str(),
        "-lc++",
        "-lSystem",
        objectFilename->c_str(),
        "-o", outputFileName->c_str()
    };
}

std::vector<const char*> TargetHelper::getX86_64LinuxGnuLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides) {
    linkerArgOverrides->setLinuxMultiArchDirectoryDefault("/usr/lib/x86_64-linux-gnu");
    linkerArgOverrides->setLinuxDynamicLinkerFileDefault("/lib64/ld-linux-x86-64.so.2");
    linkerArgOverrides->setLinuxLibDirectoryDefault("/usr/lib");
    auto multiArchPath = std::filesystem::path(*linkerArgOverrides->getLinuxMultiArchDirectory());
    auto multiArchArg = "-L" + multiArchPath.string();
    auto dynamicLinkerPath = linkerArgOverrides->getLinuxDynamicLinkerFile();
    auto libPath = linkerArgOverrides->getLinuxLibDirectory();
    auto libArg = "-L" + libPath;
    return {
        "ld.lld",
        "-t",
        "-z", "relro",
        "-m", "elf_x86_64",
        "-dynamic-linker", dynamicLinkerPath.c_str(),
        multiArchPath.append("crt1.o").c_str(),
        multiArchPath.append("crti.o").c_str(),
        ("-L" + multiArchPath.string()).c_str(),
        ("-L" + libPath).c_str(),
        "-lc++",
        "-lc++abi",
        "-lunwind",
        "-lm",
        "-lc",
        objectFilename->c_str(),
        "-o", outputFileName->c_str(),
        multiArchPath.append("crtn.o").c_str(),
    };
}

std::vector<const char*> TargetHelper::getAarch64LinuxGnuLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides) {
    auto multiArchPath = std::filesystem::path(
            linkerArgOverrides->getLinuxMultiArchDirectory("/usr/lib/aarch64-linux-gnu"));
    auto dynamicLinkerPath = linkerArgOverrides->getLinuxDynamicLinkerFile("/lib/ld-linux-aarch64.so.1");
    auto libPath = linkerArgOverrides->getLinuxLibDirectory("/usr/lib");
    return {
        "ld.lld",
        "-t",
        "-z", "relro",
        "-m", "aarch64elf",
        "-dynamic-linker", dynamicLinkerPath.c_str(),
        multiArchPath.append("crt1.o").c_str(),
        multiArchPath.append("crti.o").c_str(),
        ("-L" + multiArchPath.string()).c_str(),
        ("-L" + libPath).c_str(),
        "-lc++",
        "-lc++abi",
        "-lunwind",
        "-lm",
        "-lc",
        objectFilename->c_str(),
        "-o", outputFileName->c_str(),
        multiArchPath.append("crtn.o").c_str(),
    };
}

std::vector<const char*> TargetHelper::getX86_64LinuxMuslLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides) {
    auto multiArchPath = std::filesystem::path(linkerArgOverrides->getLinuxMultiArchDirectory("/usr/lib"));
    auto dynamicLinkerPath = linkerArgOverrides->getLinuxDynamicLinkerFile("/lib/ld-musl-x86_64.so.1");
    auto libPath = linkerArgOverrides->getLinuxLibDirectory("/usr/lib");
    return {
        "ld.lld",
        "-t",
        "-z", "relro",
        "-m", "elf_x86_64",
        "-dynamic-linker", dynamicLinkerPath.c_str(),
        multiArchPath.append("crt1.o").c_str(),
        multiArchPath.append("crti.o").c_str(),
        ("-L" + multiArchPath.string()).c_str(),
        ("-L" + libPath).c_str(),
        "-lc++",
        "-lc++abi",
        "-lm",
        "-lc",
        objectFilename->c_str(),
        "-o", outputFileName->c_str(),
        multiArchPath.append("crtn.o").c_str(),
    };
}

std::vector<const char*> TargetHelper::getAarch64LinuxMuslLinkerArgs(std::string* objectFilename, std::string* outputFileName, LinkerArgOverrides* linkerArgOverrides) {
    auto multiArchPath = std::filesystem::path(linkerArgOverrides->getLinuxMultiArchDirectory("/usr/lib"));
    auto dynamicLinkerPath = linkerArgOverrides->getLinuxDynamicLinkerFile("/lib/ld-musl-aarch64.so.1");
    auto libPath = linkerArgOverrides->getLinuxLibDirectory("/usr/lib");
    return {
        "ld.lld",
        "-t",
        "-z", "relro",
        "-m", "aarch64linux",
        "-dynamic-linker", dynamicLinkerPath.c_str(),
        multiArchPath.append("crt1.o").c_str(),
        multiArchPath.append("crti.o").c_str(),
        ("-L" + multiArchPath.string()).c_str(),
        ("-L" + libPath).c_str(),
        "-lc++",
        "-lc++abi",
        "-lm",
        "-lc",
        objectFilename->c_str(),
        "-o", outputFileName->c_str(),
        multiArchPath.append("crtn.o").c_str(),
    };
}