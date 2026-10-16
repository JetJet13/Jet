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
