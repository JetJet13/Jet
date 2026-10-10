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

#include "target-helper.h"

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
    throw std::logic_error("getLLVMTarget - unsupported target triple: " + targetTriple);
}

void TargetHelper::generateLinkerArgs(std::string targetTriple, std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder) {
    if (targetTriple == SUPPORTED_LLVM_TARGETS.X86_MAC_OS_TARGET_TRIPLE) {
        return TargetHelper::generateX86_64MacosLinkerArgs(objectFilename, outputFileName, linkerArgBuilder);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.X86_LINUX_GNU_TARGET_TRIPLE) {
        return TargetHelper::generateX86_64LinuxGnuLinkerArgs(objectFilename, outputFileName, linkerArgBuilder);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.X86_LINUX_MUSL_TARGET_TRIPLE) {
        return TargetHelper::generateX86_64LinuxMuslLinkerArgs(objectFilename, outputFileName, linkerArgBuilder);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.ARM64_MAC_OS_TARGET_TRIPLE) {
        return TargetHelper::generateAarch64MacosLinkerArgs(objectFilename, outputFileName, linkerArgBuilder);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.ARM64_LINUX_GNU_TARGET_TRIPLE) {
        return TargetHelper::generateAarch64LinuxGnuLinkerArgs(objectFilename, outputFileName, linkerArgBuilder);
    } else if (targetTriple == SUPPORTED_LLVM_TARGETS.ARM64_LINUX_MUSL_TARGET_TRIPLE) {
        return TargetHelper::generateAarch64LinuxMuslLinkerArgs(objectFilename, outputFileName, linkerArgBuilder);
    }

    throw std::logic_error("generateLinkerArgs - unsupported target triple: " + targetTriple);
}

std::array<lld::DriverDef, 2> TargetHelper::getLinkerDrivers() {
    lld::DriverDef macOsLinker = { lld::Darwin, lld::macho::link };
    lld::DriverDef linuxLinker = { lld::Gnu, lld::elf::link };
    return { macOsLinker, linuxLinker };
}

void TargetHelper::generateX86_64MacosLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder) {
    linkerArgBuilder
    ->setMacOsSysLibFileDefault("/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")
    ->addArg("ld64.lld")
    ->addArg("-arch")->addArg("x86_64")
    ->addArg("-platform_version")->addArg("macos")->addArg("12.7")->addArg("13.0")
    ->addArg("-syslibroot")->addArg(linkerArgBuilder->getMacOsSysLibFile())
    ->addArg("-lc++")
    ->addArg("-lSystem")
    ->addArg(std::move(objectFilename))
    ->addArg("-o")->addArg(std::move(outputFileName));
}

void TargetHelper::generateAarch64MacosLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder) {
    linkerArgBuilder
    ->setMacOsSysLibFileDefault("/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")
    ->addArg("ld64.lld")
    ->addArg("-arch")->addArg("arm64")
    ->addArg("-platform_version")->addArg("macos")->addArg("12.7")->addArg("13.0")
    ->addArg("-syslibroot")->addArg(linkerArgBuilder->getMacOsSysLibFile())
    ->addArg("-lc++")
    ->addArg("-lSystem")
    ->addArg(std::move(objectFilename))
    ->addArg("-o")->addArg(std::move(outputFileName));
}

void TargetHelper::generateX86_64LinuxGnuLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder) {
    linkerArgBuilder
    ->setLinuxMultiArchDirectoryDefault("/usr/lib/x86_64-linux-gnu")
    ->setLinuxDynamicLinkerFileDefault("/lib64/ld-linux-x86-64.so.2")
    ->setLinuxLibDirectoryDefault("/usr/lib");

    linkerArgBuilder
    ->addArg("ld.lld")
    ->addArg("-z")->addArg("relro")
    ->addArg("-m")->addArg("elf_x86_64")
    ->addArg("-dynamic-linker")->addArg(linkerArgBuilder->getLinuxDynamicLinkerFile())
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crt1.o"))
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crti.o"))
    ->addArg("-L" + std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).string())
    ->addArg("-L" + linkerArgBuilder->getLinuxLibDirectory())
    ->addArg("-lc++")
    ->addArg("-lc++abi")
    ->addArg("-lunwind")
    ->addArg("-lm")
    ->addArg("-lc")
    ->addArg(std::move(objectFilename))
    ->addArg("-o")->addArg(std::move(outputFileName))
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crtn.o"));
}

void TargetHelper::generateAarch64LinuxGnuLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder) {
    linkerArgBuilder
    ->setLinuxMultiArchDirectoryDefault("/usr/lib/aarch64-linux-gnu")
    ->setLinuxDynamicLinkerFileDefault("/lib/ld-linux-aarch64.so.1")
    ->setLinuxLibDirectoryDefault("/usr/lib");

    linkerArgBuilder
    ->addArg("ld.lld")
    ->addArg("-z")->addArg("relro")
    ->addArg("-m")->addArg("aarch64elf")
    ->addArg("-dynamic-linker")->addArg(linkerArgBuilder->getLinuxDynamicLinkerFile())
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crt1.o"))
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crti.o"))
    ->addArg("-L" + std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).string())
    ->addArg("-L" + linkerArgBuilder->getLinuxLibDirectory())
    ->addArg("-lc++")
    ->addArg("-lc++abi")
    ->addArg("-lunwind")
    ->addArg("-lm")
    ->addArg("-lc")
    ->addArg(std::move(objectFilename))
    ->addArg("-o")->addArg(std::move(outputFileName))
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crtn.o"));
}

void TargetHelper::generateX86_64LinuxMuslLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder) {
    linkerArgBuilder
    ->setLinuxMultiArchDirectoryDefault("/usr/lib")
    ->setLinuxDynamicLinkerFileDefault("/lib/ld-musl-x86_64.so.1")
    ->setLinuxLibDirectoryDefault("/usr/lib");

    linkerArgBuilder
    ->addArg("ld.lld")
    ->addArg("-z")->addArg("relro")
    ->addArg("-m")->addArg("elf_x86_64")
    ->addArg("-dynamic-linker")->addArg(linkerArgBuilder->getLinuxDynamicLinkerFile())
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crt1.o"))
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crti.o"))
    ->addArg("-L" + std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).string())
    ->addArg("-L" + linkerArgBuilder->getLinuxLibDirectory())
    ->addArg("-lc++")
    ->addArg("-lc++abi")
    ->addArg("-lm")
    ->addArg("-lc")
    ->addArg(std::move(objectFilename))
    ->addArg("-o")->addArg(std::move(outputFileName))
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crtn.o"));
}

void TargetHelper::generateAarch64LinuxMuslLinkerArgs(std::string objectFilename, std::string outputFileName, LinkerArgBuilder* linkerArgBuilder) {
    linkerArgBuilder
    ->setLinuxMultiArchDirectoryDefault("/usr/lib")
    ->setLinuxDynamicLinkerFileDefault("/lib/ld-musl-aarch64.so.1")
    ->setLinuxLibDirectoryDefault("/usr/lib");

    linkerArgBuilder
    ->addArg("ld.lld")
    ->addArg("-z")->addArg("relro")
    ->addArg("-m")->addArg("aarch64linux")
    ->addArg("-dynamic-linker")->addArg(linkerArgBuilder->getLinuxDynamicLinkerFile())
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crt1.o"))
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crti.o"))
    ->addArg("-L" + std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).string())
    ->addArg("-L" + linkerArgBuilder->getLinuxLibDirectory())
    ->addArg("-lc++")
    ->addArg("-lc++abi")
    ->addArg("-lm")
    ->addArg("-lc")
    ->addArg(std::move(objectFilename))
    ->addArg("-o")->addArg(std::move(outputFileName))
    ->addArg(std::filesystem::path(linkerArgBuilder->getLinuxMultiArchDirectory()).append("crtn.o"));
}