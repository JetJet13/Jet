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
    const jetVmLib = b.addStaticLibrary(.{
        .name = "jet-vm",
        .target = b.resolveTargetQuery(targetTriple),
        .optimize = optimize
    });

    // todo -  make llvm binary path dynamic based on target triple
    jetExe.linkLibC();
    jetExe.linkLibCpp();
    jetExe.addIncludePath(b.path("zig-util/target/macos-arm64/llvm/include"));
    jetExe.addLibraryPath(b.path("zig-util/target/macos-arm64/llvm/lib"));
    jetExe.addIncludePath(b.path("zig-util/target/macos-arm64/sysroot/ncurses/include"));
    jetExe.addLibraryPath(b.path("zig-util/target/macos-arm64/sysroot/ncurses/lib"));
    jetExe.addIncludePath(b.path("zig-util/target/macos-arm64/sysroot/xml2/include"));
    jetExe.addLibraryPath(b.path("zig-util/target/macos-arm64/sysroot/xml2/lib"));
    jetExe.addIncludePath(b.path("zig-util/target/macos-arm64/sysroot/zlib/include"));
    jetExe.addLibraryPath(b.path("zig-util/target/macos-arm64/sysroot/zlib/lib"));
    jetExe.addIncludePath(b.path("zig-util/target/macos-arm64/sysroot/zstd/include"));
    jetExe.addLibraryPath(b.path("zig-util/target/macos-arm64/sysroot/zstd/lib"));
    jetExe.linkSystemLibrary("ncurses");
    jetExe.linkSystemLibrary("xml2");
    jetExe.linkSystemLibrary("zlib");
    jetExe.linkSystemLibrary("zstd");

    jetSharedLib.linkLibCpp();
    buildShared.setup(jetSharedLib, b);

    jetCoreLib.linkLibCpp();
    jetCoreLib.linkLibrary(jetSharedLib);
    buildCore.setup(jetCoreLib, b);

    jetVmLib.addIncludePath(b.path("zig-util/target/macos-arm64/llvm/include"));
    jetVmLib.addLibraryPath(b.path("zig-util/target/macos-arm64/llvm/lib"));
    jetVmLib.linkSystemLibrary("LLVMSupport");
    jetVmLib.linkSystemLibrary("LLVMCore");
    jetVmLib.linkSystemLibrary("LLVMIRReader");
    jetVmLib.linkSystemLibrary("LLVMIRPrinter");
    jetVmLib.linkSystemLibrary("LLVMLinker");
    jetVmLib.linkLibrary(jetCoreLib);
    jetVmLib.linkLibrary(jetSharedLib);
    jetVmLib.linkLibCpp();
    buildVm.setup(jetVmLib, b);

    jetExe.addCSourceFiles(.{
        .root = b.path("src/jet"),
        .files = &.{
            "main.cpp",
        },
        .flags = &.{
            "-std=c++17"
        },
    });

    jetExe.linkLibrary(jetCoreLib);
    jetExe.linkLibrary(jetSharedLib);
    jetExe.linkLibrary(jetVmLib);
    jetExe.linkSystemLibrary("LLVMWindowsManifest");
    jetExe.linkSystemLibrary("LLVMXRay");
    jetExe.linkSystemLibrary("LLVMLibDriver");
    jetExe.linkSystemLibrary("LLVMDlltoolDriver");
    jetExe.linkSystemLibrary("LLVMCoverage");
    jetExe.linkSystemLibrary("LLVMLineEditor");
    jetExe.linkSystemLibrary("LLVMXCoreDisassembler");
    jetExe.linkSystemLibrary("LLVMXCoreCodeGen");
    jetExe.linkSystemLibrary("LLVMXCoreDesc");
    jetExe.linkSystemLibrary("LLVMXCoreInfo");
    jetExe.linkSystemLibrary("LLVMX86TargetMCA");
    jetExe.linkSystemLibrary("LLVMX86Disassembler");
    jetExe.linkSystemLibrary("LLVMX86AsmParser");
    jetExe.linkSystemLibrary("LLVMX86CodeGen");
    jetExe.linkSystemLibrary("LLVMX86Desc");
    jetExe.linkSystemLibrary("LLVMX86Info");
    jetExe.linkSystemLibrary("LLVMWebAssemblyDisassembler");
    jetExe.linkSystemLibrary("LLVMWebAssemblyAsmParser");
    jetExe.linkSystemLibrary("LLVMWebAssemblyCodeGen");
    jetExe.linkSystemLibrary("LLVMWebAssemblyUtils");
    jetExe.linkSystemLibrary("LLVMWebAssemblyDesc");
    jetExe.linkSystemLibrary("LLVMWebAssemblyInfo");
    jetExe.linkSystemLibrary("LLVMVEDisassembler");
    jetExe.linkSystemLibrary("LLVMVEAsmParser");
    jetExe.linkSystemLibrary("LLVMVECodeGen");
    jetExe.linkSystemLibrary("LLVMVEDesc");
    jetExe.linkSystemLibrary("LLVMVEInfo");
    jetExe.linkSystemLibrary("LLVMSystemZDisassembler");
    jetExe.linkSystemLibrary("LLVMSystemZAsmParser");
    jetExe.linkSystemLibrary("LLVMSystemZCodeGen");
    jetExe.linkSystemLibrary("LLVMSystemZDesc");
    jetExe.linkSystemLibrary("LLVMSystemZInfo");
    jetExe.linkSystemLibrary("LLVMSparcDisassembler");
    jetExe.linkSystemLibrary("LLVMSparcAsmParser");
    jetExe.linkSystemLibrary("LLVMSparcCodeGen");
    jetExe.linkSystemLibrary("LLVMSparcDesc");
    jetExe.linkSystemLibrary("LLVMSparcInfo");
    jetExe.linkSystemLibrary("LLVMRISCVTargetMCA");
    jetExe.linkSystemLibrary("LLVMRISCVDisassembler");
    jetExe.linkSystemLibrary("LLVMRISCVAsmParser");
    jetExe.linkSystemLibrary("LLVMRISCVCodeGen");
    jetExe.linkSystemLibrary("LLVMRISCVDesc");
    jetExe.linkSystemLibrary("LLVMRISCVInfo");
    jetExe.linkSystemLibrary("LLVMPowerPCDisassembler");
    jetExe.linkSystemLibrary("LLVMPowerPCAsmParser");
    jetExe.linkSystemLibrary("LLVMPowerPCCodeGen");
    jetExe.linkSystemLibrary("LLVMPowerPCDesc");
    jetExe.linkSystemLibrary("LLVMPowerPCInfo");
    jetExe.linkSystemLibrary("LLVMNVPTXCodeGen");
    jetExe.linkSystemLibrary("LLVMNVPTXDesc");
    jetExe.linkSystemLibrary("LLVMNVPTXInfo");
    jetExe.linkSystemLibrary("LLVMMSP430Disassembler");
    jetExe.linkSystemLibrary("LLVMMSP430AsmParser");
    jetExe.linkSystemLibrary("LLVMMSP430CodeGen");
    jetExe.linkSystemLibrary("LLVMMSP430Desc");
    jetExe.linkSystemLibrary("LLVMMSP430Info");
    jetExe.linkSystemLibrary("LLVMMipsDisassembler");
    jetExe.linkSystemLibrary("LLVMMipsAsmParser");
    jetExe.linkSystemLibrary("LLVMMipsCodeGen");
    jetExe.linkSystemLibrary("LLVMMipsDesc");
    jetExe.linkSystemLibrary("LLVMMipsInfo");
    jetExe.linkSystemLibrary("LLVMLoongArchDisassembler");
    jetExe.linkSystemLibrary("LLVMLoongArchAsmParser");
    jetExe.linkSystemLibrary("LLVMLoongArchCodeGen");
    jetExe.linkSystemLibrary("LLVMLoongArchDesc");
    jetExe.linkSystemLibrary("LLVMLoongArchInfo");
    jetExe.linkSystemLibrary("LLVMLanaiDisassembler");
    jetExe.linkSystemLibrary("LLVMLanaiCodeGen");
    jetExe.linkSystemLibrary("LLVMLanaiAsmParser");
    jetExe.linkSystemLibrary("LLVMLanaiDesc");
    jetExe.linkSystemLibrary("LLVMLanaiInfo");
    jetExe.linkSystemLibrary("LLVMHexagonDisassembler");
    jetExe.linkSystemLibrary("LLVMHexagonCodeGen");
    jetExe.linkSystemLibrary("LLVMHexagonAsmParser");
    jetExe.linkSystemLibrary("LLVMHexagonDesc");
    jetExe.linkSystemLibrary("LLVMHexagonInfo");
    jetExe.linkSystemLibrary("LLVMBPFDisassembler");
    jetExe.linkSystemLibrary("LLVMBPFAsmParser");
    jetExe.linkSystemLibrary("LLVMBPFCodeGen");
    jetExe.linkSystemLibrary("LLVMBPFDesc");
    jetExe.linkSystemLibrary("LLVMBPFInfo");
    jetExe.linkSystemLibrary("LLVMAVRDisassembler");
    jetExe.linkSystemLibrary("LLVMAVRAsmParser");
    jetExe.linkSystemLibrary("LLVMAVRCodeGen");
    jetExe.linkSystemLibrary("LLVMAVRDesc");
    jetExe.linkSystemLibrary("LLVMAVRInfo");
    jetExe.linkSystemLibrary("LLVMARMDisassembler");
    jetExe.linkSystemLibrary("LLVMARMAsmParser");
    jetExe.linkSystemLibrary("LLVMARMCodeGen");
    jetExe.linkSystemLibrary("LLVMARMDesc");
    jetExe.linkSystemLibrary("LLVMARMUtils");
    jetExe.linkSystemLibrary("LLVMARMInfo");
    jetExe.linkSystemLibrary("LLVMAMDGPUTargetMCA");
    jetExe.linkSystemLibrary("LLVMAMDGPUDisassembler");
    jetExe.linkSystemLibrary("LLVMAMDGPUAsmParser");
    jetExe.linkSystemLibrary("LLVMAMDGPUCodeGen");
    jetExe.linkSystemLibrary("LLVMAMDGPUDesc");
    jetExe.linkSystemLibrary("LLVMAMDGPUUtils");
    jetExe.linkSystemLibrary("LLVMAMDGPUInfo");
    jetExe.linkSystemLibrary("LLVMAArch64Disassembler");
    jetExe.linkSystemLibrary("LLVMAArch64AsmParser");
    jetExe.linkSystemLibrary("LLVMAArch64CodeGen");
    jetExe.linkSystemLibrary("LLVMAArch64Desc");
    jetExe.linkSystemLibrary("LLVMAArch64Utils");
    jetExe.linkSystemLibrary("LLVMAArch64Info");
    jetExe.linkSystemLibrary("LLVMOrcJIT");
    jetExe.linkSystemLibrary("LLVMWindowsDriver");
    jetExe.linkSystemLibrary("LLVMMCJIT");
    jetExe.linkSystemLibrary("LLVMJITLink");
    jetExe.linkSystemLibrary("LLVMInterpreter");
    jetExe.linkSystemLibrary("LLVMExecutionEngine");
    jetExe.linkSystemLibrary("LLVMRuntimeDyld");
    jetExe.linkSystemLibrary("LLVMOrcTargetProcess");
    jetExe.linkSystemLibrary("LLVMOrcShared");
    jetExe.linkSystemLibrary("LLVMDWP");
    jetExe.linkSystemLibrary("LLVMDebugInfoLogicalView");
    jetExe.linkSystemLibrary("LLVMDebugInfoGSYM");
    jetExe.linkSystemLibrary("LLVMOption");
    jetExe.linkSystemLibrary("LLVMObjectYAML");
    jetExe.linkSystemLibrary("LLVMObjCopy");
    jetExe.linkSystemLibrary("LLVMMCA");
    jetExe.linkSystemLibrary("LLVMMCDisassembler");
    jetExe.linkSystemLibrary("LLVMLTO");
    jetExe.linkSystemLibrary("LLVMPasses");
    jetExe.linkSystemLibrary("LLVMCFGuard");
    jetExe.linkSystemLibrary("LLVMCoroutines");
    jetExe.linkSystemLibrary("LLVMipo");
    jetExe.linkSystemLibrary("LLVMVectorize");
    jetExe.linkSystemLibrary("LLVMLinker");
    jetExe.linkSystemLibrary("LLVMInstrumentation");
    jetExe.linkSystemLibrary("LLVMFrontendOpenMP");
    jetExe.linkSystemLibrary("LLVMFrontendOpenACC");
    jetExe.linkSystemLibrary("LLVMFrontendHLSL");
    jetExe.linkSystemLibrary("LLVMExtensions");
    jetExe.linkSystemLibrary("LLVMDWARFLinkerParallel");
    jetExe.linkSystemLibrary("LLVMDWARFLinker");
    jetExe.linkSystemLibrary("LLVMGlobalISel");
    jetExe.linkSystemLibrary("LLVMMIRParser");
    jetExe.linkSystemLibrary("LLVMAsmPrinter");
    jetExe.linkSystemLibrary("LLVMSelectionDAG");
    jetExe.linkSystemLibrary("LLVMCodeGen");
    jetExe.linkSystemLibrary("LLVMTarget");
    jetExe.linkSystemLibrary("LLVMObjCARCOpts");
    jetExe.linkSystemLibrary("LLVMCodeGenTypes");
    jetExe.linkSystemLibrary("LLVMIRPrinter");
    jetExe.linkSystemLibrary("LLVMInterfaceStub");
    jetExe.linkSystemLibrary("LLVMFileCheck");
    jetExe.linkSystemLibrary("LLVMFuzzMutate");
    jetExe.linkSystemLibrary("LLVMScalarOpts");
    jetExe.linkSystemLibrary("LLVMInstCombine");
    jetExe.linkSystemLibrary("LLVMAggressiveInstCombine");
    jetExe.linkSystemLibrary("LLVMTransformUtils");
    jetExe.linkSystemLibrary("LLVMBitWriter");
    jetExe.linkSystemLibrary("LLVMAnalysis");
    jetExe.linkSystemLibrary("LLVMProfileData");
    jetExe.linkSystemLibrary("LLVMSymbolize");
    jetExe.linkSystemLibrary("LLVMDebugInfoBTF");
    jetExe.linkSystemLibrary("LLVMDebugInfoPDB");
    jetExe.linkSystemLibrary("LLVMDebugInfoMSF");
    jetExe.linkSystemLibrary("LLVMDebugInfoDWARF");
    jetExe.linkSystemLibrary("LLVMObject");
    jetExe.linkSystemLibrary("LLVMTextAPI");
    jetExe.linkSystemLibrary("LLVMMCParser");
    jetExe.linkSystemLibrary("LLVMIRReader");
    jetExe.linkSystemLibrary("LLVMAsmParser");
    jetExe.linkSystemLibrary("LLVMMC");
    jetExe.linkSystemLibrary("LLVMDebugInfoCodeView");
    jetExe.linkSystemLibrary("LLVMBitReader");
    jetExe.linkSystemLibrary("LLVMFuzzerCLI");
    jetExe.linkSystemLibrary("LLVMCore");
    jetExe.linkSystemLibrary("LLVMRemarks");
    jetExe.linkSystemLibrary("LLVMBitstreamReader");
    jetExe.linkSystemLibrary("LLVMBinaryFormat");
    jetExe.linkSystemLibrary("LLVMTargetParser");
    jetExe.linkSystemLibrary("LLVMTableGen");
    jetExe.linkSystemLibrary("LLVMSupport");
    jetExe.linkSystemLibrary("LLVMDemangle");

    b.installArtifact(jetExe);
}