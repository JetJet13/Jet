//
// Created by Johny Georges on 2026-09-06.
//

#include "jet-cli.h"
#include "../types/supported-targets.h"

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

    std::string zigCommand = "zig build --prefix ./zig-out/" + target + " --build-file build.zig -j8 -Dtarget=" + target;
    std::system(zigCommand.c_str());

    return EXIT_SUCCESS;
}