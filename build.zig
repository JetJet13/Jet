const std = @import("std");
const buildCore = @import("zig-util/build-core.zig");
const buildShared = @import("zig-util/build-shared.zig");
const buildVm = @import("zig-util/build-vm.zig");

pub fn build(b: *std.Build) void {
    const target = b.option([]const u8, "target", "specify the OS target to build for.")
        orelse "";
    const targetTriple = std.Target.Query.parse(.{
        .arch_os_abi = target,
    }) catch unreachable;

    const optimize = b.standardOptimizeOption(.{});

    const jetExe = b.addExecutable(.{
        .name = "jet",
        .target = b.resolveTargetQuery(targetTriple),
        .optimize = optimize
    });
    const jetCoreLib = b.addStaticLibrary(.{
        .name = "jet-core",
        .target = b.resolveTargetQuery(targetTriple),
        .optimize = optimize
    });
    const jetSharedLib = b.addStaticLibrary(.{
        .name = "jet-shared",
        .target = b.resolveTargetQuery(targetTriple),
        .optimize = optimize
    });
    // const jetVmLib = b.addStaticLibrary(.{
    //     .name = "jet-vm",
    //     .target = b.resolveTargetQuery(targetTriple),
    //     .optimize = optimize
    // });

    // todo -  make llvm binary path dynamic based on target triple
    jetExe.addIncludePath(b.path("zig-util/target-llvm-binaries/macos-arm64/include"));
    jetExe.addLibraryPath(b.path("zig-util/target-llvm-binaries/macos-arm64/lib"));
    jetExe.linkLibCpp();

    jetSharedLib.linkLibCpp();
    buildShared.setup(jetSharedLib, b);

    jetCoreLib.linkLibCpp();
    jetCoreLib.linkLibrary(jetSharedLib);
    buildCore.setup(jetCoreLib, b);

    // jetVmLib.addIncludePath(b.path("zig-util/target-llvm-binaries/macos-arm64/include"));
    // jetVmLib.addLibraryPath(b.path("zig-util/target-llvm-binaries/macos-arm64/lib"));
    // jetVmLib.linkSystemLibrary("LLVMSupport");
    // jetVmLib.linkSystemLibrary("LLVMCore");
    // jetVmLib.linkSystemLibrary("LLVMIRReader");
    // jetVmLib.linkSystemLibrary("LLVMIRPrinter");
    // jetVmLib.linkSystemLibrary("LLVMLinker");
    // jetVmLib.linkLibrary(jetCoreLib);
    // jetVmLib.linkLibrary(jetSharedLib);
    // jetVmLib.linkLibCpp();
    // buildVm.setup(jetVmLib, b);

    jetExe.addCSourceFiles(.{
        .root = b.path("src/jet"),
        .files = &.{
            "main.cpp",
        },
        .flags = &.{
            "-std=c++17"
        },
    });

    jetExe.linkSystemLibrary("LLVMCore");
    jetExe.linkSystemLibrary("LLVMSupport");
    jetExe.linkSystemLibrary("LLVMIRReader");
    jetExe.linkSystemLibrary("LLVMIRPrinter");
    jetExe.linkSystemLibrary("LLVMLinker");
    jetExe.linkLibrary(jetCoreLib);
    jetExe.linkLibrary(jetSharedLib);
    // jetExe.linkLibrary(jetVmLib);

    b.installArtifact(jetExe);
}