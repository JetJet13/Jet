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
        "x86_64-linux-gnu",    // Linux x64
        "aarch64-linux-gnu",   // Linux arm64
        "x86_64-windows-msvc", // Windows x64
        "aarch64-windows-msvc" // Windows arm64
    }));
    CLI11_PARSE(app, argc, argv);

    std::string configureCommand = "cmake -S . -B ./builds/debug/macos-arm64 -DCMAKE_OSX_ARCHITECTURES=arm64";
    std::string buildCommand = "cmake --build builds/debug/macos-arm64 --target jet -j 6";

    std::system(configureCommand.c_str());
    std::system(buildCommand.c_str());

    std::string zigCommand = "zig build --build-file ./src/jet/cli/zig-build/build.zig -Dtarget=" + target;
    std::system(zigCommand.c_str());

    return EXIT_SUCCESS;
}