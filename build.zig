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


const std = @import("std");
const buildCore = @import("zig-util/build-core.zig");
const buildShared = @import("zig-util/build-shared.zig");
const buildVm = @import("zig-util/build-vm.zig");
const buildJetExe = @import("zig-util/build-jet-exe.zig");

pub fn build(b: *std.Build) void {
    const target = b.option([]const u8, "target", "specify the OS target to build for.")
        orelse "";
    const targetTriple = std.Target.Query.parse(.{
        .arch_os_abi = target,
    }) catch unreachable;
    const buildTargetMacroKey = "BUILD_TARGET";
    const buildTargetMacroValue = b.fmt("\"{s}\"", .{ target });

    const optimize = b.standardOptimizeOption(.{});

    const jetExe = b.addExecutable(.{
        .name = "jet",
        .target = b.resolveTargetQuery(targetTriple),
        .optimize = optimize
    });
    const jetDebugExe = b.addExecutable(.{
        .name = "jet-debug",
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
    const jetVmLib = b.addStaticLibrary(.{
        .name = "jet-vm",
        .target = b.resolveTargetQuery(targetTriple),
        .optimize = optimize
    });

    buildShared.setup(jetSharedLib, b);

    jetCoreLib.linkLibrary(jetSharedLib);
    buildCore.setup(jetCoreLib, b);

    jetVmLib.linkLibrary(jetCoreLib);
    jetVmLib.linkLibrary(jetSharedLib);
    buildVm.setup(jetVmLib, b);
    jetVmLib.root_module.addCMacro(buildTargetMacroKey, buildTargetMacroValue);
    buildJetExe.linkLLVM(jetVmLib, b, target);

    jetExe.linkLibrary(jetCoreLib);
    jetExe.linkLibrary(jetSharedLib);
    jetExe.linkLibrary(jetVmLib);
    jetExe.root_module.addCMacro(buildTargetMacroKey, buildTargetMacroValue);
    buildJetExe.setup(jetExe, b, target);

    jetDebugExe.linkLibrary(jetCoreLib);
    jetDebugExe.linkLibrary(jetSharedLib);
    jetDebugExe.linkLibrary(jetVmLib);
    jetDebugExe.root_module.addCMacro(buildTargetMacroKey, buildTargetMacroValue);
    buildJetExe.setupDebug(jetDebugExe, b, target);

    b.installArtifact(jetExe);
    b.installArtifact(jetDebugExe);
}