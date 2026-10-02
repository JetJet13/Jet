//
// Created by Johny Georges on 2026-09-30.
//

#ifndef JETLANG_SUPPORTED_TARGETS_H
#define JETLANG_SUPPORTED_TARGETS_H

#include <string>

struct SupportedTarget {
    std::string X86_MAC_OS;
    std::string X86_LINUX_GNU;
    std::string X86_LINUX_MUSL;
    std::string ARM64_MAC_OS;
    std::string ARM64_LINUX_GNU;
    std::string ARM64_LINUX_MUSL;
};

const SupportedTarget SUPPORTED_TARGETS = {
        .X86_MAC_OS = "x86_64-macos",
        .X86_LINUX_GNU = "x86_64-linux-gnu",
        .X86_LINUX_MUSL = "x86_64-linux-musl",
        .ARM64_MAC_OS = "aarch64-macos",
        .ARM64_LINUX_GNU = "aarch64-linux-gnu",
        .ARM64_LINUX_MUSL = "aarch64-linux-musl",
};
#endif //JETLANG_SUPPORTED_TARGETS_H
