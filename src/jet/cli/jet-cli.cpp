//
// Created by Johny Georges on 2026-09-06.
//

#include "jet-cli.h"

int main (int argc, const char* argv[]) {
    CLI::App app{"JET Cross-Compiler"};

    std::string target;

    auto targetOption = app.add_option("--target", target, "the target system")->required();
    targetOption->check(CLI::IsMember({
        "x86_64-macos",        // MacOS x64
        "aarch64-macos",       // MacOS arm64
        "x86_64-linux-gnu",    // Linux GNU x64
        "aarch64-linux-gnu",   // Linux GNU arm64
        "x86_64-unknown-musl", // Linux MUSL x64
        "aarch64-unknown-musl" // Linux MUSL arm64
    }));
    CLI11_PARSE(app, argc, argv);

    std::string zigCommand = "zig build --build-file build.zig -j8 -Dtarget=" + target;
    std::system(zigCommand.c_str());

    return EXIT_SUCCESS;
}