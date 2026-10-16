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
// Created by Johny Georges on 2026-09-06.
//

#include "jet-cli.h"
#include "../shared/types/supported-targets.h"

int main (int argc, const char* argv[]) {
    CLI::App app{"JET CLI"};

    std::string target;

    auto targetOption = app.add_option("--target", target, "the target system")->required();
    targetOption->check(CLI::IsMember({
      SUPPORTED_TARGETS.X86_MAC_OS.c_str(),
      SUPPORTED_TARGETS.X86_LINUX_GNU.c_str(),
      SUPPORTED_TARGETS.X86_LINUX_MUSL.c_str(),
      SUPPORTED_TARGETS.ARM64_MAC_OS.c_str(),
      SUPPORTED_TARGETS.ARM64_LINUX_GNU.c_str(),
      SUPPORTED_TARGETS.ARM64_LINUX_MUSL.c_str(),
    }));
    CLI11_PARSE(app, argc, argv)

    std::string zigCommand = "zig build --prefix ./zig-out/" + target + " --build-file build.zig -j6 -Dtarget=" + target;
    std::system(zigCommand.c_str());

    return EXIT_SUCCESS;
}