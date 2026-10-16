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
