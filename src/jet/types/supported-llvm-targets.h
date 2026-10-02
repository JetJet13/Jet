//
// Created by Johny Georges on 2026-10-01.
//

#ifndef JETLANG_SUPPORTED_LLVM_TARGETS_H
#define JETLANG_SUPPORTED_LLVM_TARGETS_H

#include <string>

struct SupportedLLVMTarget {
    std::string X86_MAC_OS_TARGET_TRIPLE;
    std::string X86_LINUX_GNU_TARGET_TRIPLE;
    std::string X86_LINUX_MUSL_TARGET_TRIPLE;
    std::string ARM64_MAC_OS_TARGET_TRIPLE;
    std::string ARM64_LINUX_GNU_TARGET_TRIPLE;
    std::string ARM64_LINUX_MUSL_TARGET_TRIPLE;
};

const SupportedLLVMTarget SUPPORTED_LLVM_TARGETS = {
        .X86_MAC_OS_TARGET_TRIPLE = "x86_64-apple-darwin",
        .X86_LINUX_GNU_TARGET_TRIPLE = "x86_64-unknown-linux-gnu",
        .X86_LINUX_MUSL_TARGET_TRIPLE = "x86_64-unknown-linux-musl",
        .ARM64_MAC_OS_TARGET_TRIPLE = "aarch64-apple-darwin",
        .ARM64_LINUX_GNU_TARGET_TRIPLE = "aarch64-unknown-linux-gnu",
        .ARM64_LINUX_MUSL_TARGET_TRIPLE = "aarch64-unknown-linux-musl",
};

#endif //JETLANG_SUPPORTED_LLVM_TARGETS_H
