const std = @import("std");

pub fn build(b: *std.Build) void {
    const supportedTargets = .{
        "x86_64-macos",        // MacOS x64
        "aarch64-macos",       // MacOS arm64
        "x86_64-linux-gnu",    // Linux x64
        "aarch64-linux-gnu",   // Linux arm64
        "x86_64-windows-msvc", // Windows x64
        "aarch64-windows-msvc" // Windows arm64
    };
    const target = b.option([]const u8, "target", "specify the OS target to build for.")
        orelse "";

    const optimize = b.standardOptimizeOption(.{});

    if (std.mem.eql(u8, target, supportedTargets[0])) {

    } else if (std.mem.eql(u8, target, supportedTargets[1])) {
        const exe = b.addExecutable(.{
            .name = "jet",
            .target = b.resolveTargetQuery(.{
                .cpu_arch = .aarch64,
                .os_tag = .macos,
            }),
            .optimize = optimize
        });

        exe.addCSourceFiles(.{
            .files = &.{
                "../../main.cpp",
            },
            .flags = &.{
                "-std=c++17"
            },
        });

        exe.linkLibCpp();

        exe.addLibraryPath(b.path("../../../../builds/debug/macos-arm64/src/core"));
        exe.linkSystemLibrary("jet-core");
        exe.addLibraryPath(b.path("../../../../builds/debug/macos-arm64/src/shared"));
        exe.linkSystemLibrary("jet-shared");
        exe.addLibraryPath(b.path("../../../../builds/debug/macos-arm64/src/vm"));
        exe.linkSystemLibrary("jet-vm");

        exe.addIncludePath(b.path("target-llvm-binaries/macos-arm64/include"));
        exe.addLibraryPath(b.path("target-llvm-binaries/macos-arm64/lib"));

        exe.linkSystemLibrary("LLVMCore");
        exe.linkSystemLibrary("LLVMSupport");
        exe.linkSystemLibrary("LLVMIRReader");
        exe.linkSystemLibrary("LLVMIRPrinter");
        exe.linkSystemLibrary("LLVMLinker");

        b.installArtifact(exe);
    } else if (std.mem.eql(u8, target, supportedTargets[2])) {

    } else if (std.mem.eql(u8, target, supportedTargets[3])) {

    } else if (std.mem.eql(u8, target, supportedTargets[4])) {

    } else if (std.mem.eql(u8, target, supportedTargets[5])) {

    } else if (std.mem.eql(u8, target, "")) {
        @panic("Error: You must provide a target option '-Dtarget=[target]'");
    } else {
        @panic("OS target provided is not supported");
    }
}