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

    const cli11 = b.dependency("cli11", .{});
    const llvmIncludePath = b.fmt("zig-util/target/{s}/llvm/include", .{ target });
    const llvmLibraryPath = b.fmt("zig-util/target/{s}/llvm/lib", .{ target });
    const ncursesIncludePath = b.fmt("zig-util/target/{s}/sysroot/ncurses/include", .{ target });
    const ncursesLibraryPath = b.fmt("zig-util/target/{s}/sysroot/ncurses/lib", .{ target });
    const xml2IncludePath = b.fmt("zig-util/target/{s}/sysroot/xml2/include", .{ target });
    const xml2LibraryPath = b.fmt("zig-util/target/{s}/sysroot/xml2/lib", .{ target });
    const zlibIncludePath = b.fmt("zig-util/target/{s}/sysroot/zlib/include", .{ target });
    const zlibLibraryPath = b.fmt("zig-util/target/{s}/sysroot/zlib/lib", .{ target });
    const zstdIncludePath = b.fmt("zig-util/target/{s}/sysroot/zstd/include", .{ target });
    const zstdLibraryPath = b.fmt("zig-util/target/{s}/sysroot/zstd/lib", .{ target });

    // todo -  make llvm binary path dynamic based on target triple
    jetExe.linkLibCpp();
    jetDebugExe.linkLibCpp();
    jetExe.addIncludePath(cli11.path(""));
    jetDebugExe.addIncludePath(cli11.path(""));
    jetExe.addIncludePath(b.path(llvmIncludePath));
    jetDebugExe.addIncludePath(b.path(llvmIncludePath));
    jetExe.addLibraryPath(b.path(llvmLibraryPath));
    jetDebugExe.addLibraryPath(b.path(llvmLibraryPath));
    jetExe.addIncludePath(b.path(ncursesIncludePath));
    jetDebugExe.addIncludePath(b.path(ncursesIncludePath));
    jetExe.addLibraryPath(b.path(ncursesLibraryPath));
    jetDebugExe.addLibraryPath(b.path(ncursesLibraryPath));
    jetExe.addIncludePath(b.path(xml2IncludePath));
    jetDebugExe.addIncludePath(b.path(xml2IncludePath));
    jetExe.addLibraryPath(b.path(xml2LibraryPath));
    jetDebugExe.addLibraryPath(b.path(xml2LibraryPath));
    jetExe.addIncludePath(b.path(zlibIncludePath));
    jetDebugExe.addIncludePath(b.path(zlibIncludePath));
    jetExe.addLibraryPath(b.path(zlibLibraryPath));
    jetDebugExe.addLibraryPath(b.path(zlibLibraryPath));
    jetExe.addIncludePath(b.path(zstdIncludePath));
    jetDebugExe.addIncludePath(b.path(zstdIncludePath));
    jetExe.addLibraryPath(b.path(zstdLibraryPath));
    jetDebugExe.addLibraryPath(b.path(zstdLibraryPath));
    jetExe.linkSystemLibrary2("xml2", .{
        .preferred_link_mode = .static,
    });
    jetDebugExe.linkSystemLibrary2("xml2", .{
        .preferred_link_mode = .static,
    });
    jetExe.linkSystemLibrary2("ncurses", .{
        .preferred_link_mode = .static,
    });
    jetDebugExe.linkSystemLibrary2("ncurses", .{
        .preferred_link_mode = .static,
    });
    jetExe.linkSystemLibrary2("zlib", .{
        .preferred_link_mode = .static,
    });
    jetDebugExe.linkSystemLibrary2("zlib", .{
        .preferred_link_mode = .static,
    });
    jetExe.linkSystemLibrary2("zstd", .{
        .preferred_link_mode = .static,
    });
    jetDebugExe.linkSystemLibrary2("zstd", .{
        .preferred_link_mode = .static,
    });


    jetSharedLib.linkLibCpp();
    buildShared.setup(jetSharedLib, b);

    jetCoreLib.linkLibCpp();
    jetCoreLib.linkLibrary(jetSharedLib);
    buildCore.setup(jetCoreLib, b);

    jetVmLib.addIncludePath(b.path(llvmIncludePath));
    jetVmLib.addLibraryPath(b.path(llvmLibraryPath));
    jetVmLib.linkLibrary(jetCoreLib);
    jetVmLib.linkLibrary(jetSharedLib);
    jetVmLib.linkLibCpp();
    jetVmLib.root_module.addCMacro(buildTargetMacroKey, buildTargetMacroValue);
    buildVm.setup(jetVmLib, b);

    jetExe.addCSourceFiles(.{
        .root = b.path("src/jet"),
        .files = &.{
            "main.cpp",
            "types/target-helper.cpp"
        },
        .flags = &.{
            "-std=c++17",
        },
    });
    jetDebugExe.addCSourceFiles(.{
        .root = b.path("src/jet"),
        .files = &.{
            "debug-main.cpp",
            "types/target-helper.cpp"
        },
        .flags = &.{
            "-std=c++17",
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
    jetExe.linkSystemLibrary("lldCommon");
    jetExe.linkSystemLibrary("lldCOFF");
    jetExe.linkSystemLibrary("lldELF");
    jetExe.linkSystemLibrary("lldMachO");
    jetExe.linkSystemLibrary("lldMinGW");
    jetExe.linkSystemLibrary("lldWasm");
    jetExe.root_module.addCMacro(buildTargetMacroKey, buildTargetMacroValue);

    jetDebugExe.linkLibrary(jetCoreLib);
    jetDebugExe.linkLibrary(jetSharedLib);
    jetDebugExe.linkLibrary(jetVmLib);
    jetDebugExe.linkSystemLibrary("LLVMWindowsManifest");
    jetDebugExe.linkSystemLibrary("LLVMXRay");
    jetDebugExe.linkSystemLibrary("LLVMLibDriver");
    jetDebugExe.linkSystemLibrary("LLVMDlltoolDriver");
    jetDebugExe.linkSystemLibrary("LLVMCoverage");
    jetDebugExe.linkSystemLibrary("LLVMLineEditor");
    jetDebugExe.linkSystemLibrary("LLVMXCoreDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMXCoreCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMXCoreDesc");
    jetDebugExe.linkSystemLibrary("LLVMXCoreInfo");
    jetDebugExe.linkSystemLibrary("LLVMX86TargetMCA");
    jetDebugExe.linkSystemLibrary("LLVMX86Disassembler");
    jetDebugExe.linkSystemLibrary("LLVMX86AsmParser");
    jetDebugExe.linkSystemLibrary("LLVMX86CodeGen");
    jetDebugExe.linkSystemLibrary("LLVMX86Desc");
    jetDebugExe.linkSystemLibrary("LLVMX86Info");
    jetDebugExe.linkSystemLibrary("LLVMWebAssemblyDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMWebAssemblyAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMWebAssemblyCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMWebAssemblyUtils");
    jetDebugExe.linkSystemLibrary("LLVMWebAssemblyDesc");
    jetDebugExe.linkSystemLibrary("LLVMWebAssemblyInfo");
    jetDebugExe.linkSystemLibrary("LLVMVEDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMVEAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMVECodeGen");
    jetDebugExe.linkSystemLibrary("LLVMVEDesc");
    jetDebugExe.linkSystemLibrary("LLVMVEInfo");
    jetDebugExe.linkSystemLibrary("LLVMSystemZDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMSystemZAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMSystemZCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMSystemZDesc");
    jetDebugExe.linkSystemLibrary("LLVMSystemZInfo");
    jetDebugExe.linkSystemLibrary("LLVMSparcDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMSparcAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMSparcCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMSparcDesc");
    jetDebugExe.linkSystemLibrary("LLVMSparcInfo");
    jetDebugExe.linkSystemLibrary("LLVMRISCVTargetMCA");
    jetDebugExe.linkSystemLibrary("LLVMRISCVDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMRISCVAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMRISCVCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMRISCVDesc");
    jetDebugExe.linkSystemLibrary("LLVMRISCVInfo");
    jetDebugExe.linkSystemLibrary("LLVMPowerPCDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMPowerPCAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMPowerPCCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMPowerPCDesc");
    jetDebugExe.linkSystemLibrary("LLVMPowerPCInfo");
    jetDebugExe.linkSystemLibrary("LLVMNVPTXCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMNVPTXDesc");
    jetDebugExe.linkSystemLibrary("LLVMNVPTXInfo");
    jetDebugExe.linkSystemLibrary("LLVMMSP430Disassembler");
    jetDebugExe.linkSystemLibrary("LLVMMSP430AsmParser");
    jetDebugExe.linkSystemLibrary("LLVMMSP430CodeGen");
    jetDebugExe.linkSystemLibrary("LLVMMSP430Desc");
    jetDebugExe.linkSystemLibrary("LLVMMSP430Info");
    jetDebugExe.linkSystemLibrary("LLVMMipsDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMMipsAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMMipsCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMMipsDesc");
    jetDebugExe.linkSystemLibrary("LLVMMipsInfo");
    jetDebugExe.linkSystemLibrary("LLVMLoongArchDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMLoongArchAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMLoongArchCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMLoongArchDesc");
    jetDebugExe.linkSystemLibrary("LLVMLoongArchInfo");
    jetDebugExe.linkSystemLibrary("LLVMLanaiDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMLanaiCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMLanaiAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMLanaiDesc");
    jetDebugExe.linkSystemLibrary("LLVMLanaiInfo");
    jetDebugExe.linkSystemLibrary("LLVMHexagonDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMHexagonCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMHexagonAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMHexagonDesc");
    jetDebugExe.linkSystemLibrary("LLVMHexagonInfo");
    jetDebugExe.linkSystemLibrary("LLVMBPFDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMBPFAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMBPFCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMBPFDesc");
    jetDebugExe.linkSystemLibrary("LLVMBPFInfo");
    jetDebugExe.linkSystemLibrary("LLVMAVRDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMAVRAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMAVRCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMAVRDesc");
    jetDebugExe.linkSystemLibrary("LLVMAVRInfo");
    jetDebugExe.linkSystemLibrary("LLVMARMDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMARMAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMARMCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMARMDesc");
    jetDebugExe.linkSystemLibrary("LLVMARMUtils");
    jetDebugExe.linkSystemLibrary("LLVMARMInfo");
    jetDebugExe.linkSystemLibrary("LLVMAMDGPUTargetMCA");
    jetDebugExe.linkSystemLibrary("LLVMAMDGPUDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMAMDGPUAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMAMDGPUCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMAMDGPUDesc");
    jetDebugExe.linkSystemLibrary("LLVMAMDGPUUtils");
    jetDebugExe.linkSystemLibrary("LLVMAMDGPUInfo");
    jetDebugExe.linkSystemLibrary("LLVMAArch64Disassembler");
    jetDebugExe.linkSystemLibrary("LLVMAArch64AsmParser");
    jetDebugExe.linkSystemLibrary("LLVMAArch64CodeGen");
    jetDebugExe.linkSystemLibrary("LLVMAArch64Desc");
    jetDebugExe.linkSystemLibrary("LLVMAArch64Utils");
    jetDebugExe.linkSystemLibrary("LLVMAArch64Info");
    jetDebugExe.linkSystemLibrary("LLVMOrcJIT");
    jetDebugExe.linkSystemLibrary("LLVMWindowsDriver");
    jetDebugExe.linkSystemLibrary("LLVMMCJIT");
    jetDebugExe.linkSystemLibrary("LLVMJITLink");
    jetDebugExe.linkSystemLibrary("LLVMInterpreter");
    jetDebugExe.linkSystemLibrary("LLVMExecutionEngine");
    jetDebugExe.linkSystemLibrary("LLVMRuntimeDyld");
    jetDebugExe.linkSystemLibrary("LLVMOrcTargetProcess");
    jetDebugExe.linkSystemLibrary("LLVMOrcShared");
    jetDebugExe.linkSystemLibrary("LLVMDWP");
    jetDebugExe.linkSystemLibrary("LLVMDebugInfoLogicalView");
    jetDebugExe.linkSystemLibrary("LLVMDebugInfoGSYM");
    jetDebugExe.linkSystemLibrary("LLVMOption");
    jetDebugExe.linkSystemLibrary("LLVMObjectYAML");
    jetDebugExe.linkSystemLibrary("LLVMObjCopy");
    jetDebugExe.linkSystemLibrary("LLVMMCA");
    jetDebugExe.linkSystemLibrary("LLVMMCDisassembler");
    jetDebugExe.linkSystemLibrary("LLVMLTO");
    jetDebugExe.linkSystemLibrary("LLVMPasses");
    jetDebugExe.linkSystemLibrary("LLVMCFGuard");
    jetDebugExe.linkSystemLibrary("LLVMCoroutines");
    jetDebugExe.linkSystemLibrary("LLVMipo");
    jetDebugExe.linkSystemLibrary("LLVMVectorize");
    jetDebugExe.linkSystemLibrary("LLVMLinker");
    jetDebugExe.linkSystemLibrary("LLVMInstrumentation");
    jetDebugExe.linkSystemLibrary("LLVMFrontendOpenMP");
    jetDebugExe.linkSystemLibrary("LLVMFrontendOpenACC");
    jetDebugExe.linkSystemLibrary("LLVMFrontendHLSL");
    jetDebugExe.linkSystemLibrary("LLVMExtensions");
    jetDebugExe.linkSystemLibrary("LLVMDWARFLinkerParallel");
    jetDebugExe.linkSystemLibrary("LLVMDWARFLinker");
    jetDebugExe.linkSystemLibrary("LLVMGlobalISel");
    jetDebugExe.linkSystemLibrary("LLVMMIRParser");
    jetDebugExe.linkSystemLibrary("LLVMAsmPrinter");
    jetDebugExe.linkSystemLibrary("LLVMSelectionDAG");
    jetDebugExe.linkSystemLibrary("LLVMCodeGen");
    jetDebugExe.linkSystemLibrary("LLVMTarget");
    jetDebugExe.linkSystemLibrary("LLVMObjCARCOpts");
    jetDebugExe.linkSystemLibrary("LLVMCodeGenTypes");
    jetDebugExe.linkSystemLibrary("LLVMIRPrinter");
    jetDebugExe.linkSystemLibrary("LLVMInterfaceStub");
    jetDebugExe.linkSystemLibrary("LLVMFileCheck");
    jetDebugExe.linkSystemLibrary("LLVMFuzzMutate");
    jetDebugExe.linkSystemLibrary("LLVMScalarOpts");
    jetDebugExe.linkSystemLibrary("LLVMInstCombine");
    jetDebugExe.linkSystemLibrary("LLVMAggressiveInstCombine");
    jetDebugExe.linkSystemLibrary("LLVMTransformUtils");
    jetDebugExe.linkSystemLibrary("LLVMBitWriter");
    jetDebugExe.linkSystemLibrary("LLVMAnalysis");
    jetDebugExe.linkSystemLibrary("LLVMProfileData");
    jetDebugExe.linkSystemLibrary("LLVMSymbolize");
    jetDebugExe.linkSystemLibrary("LLVMDebugInfoBTF");
    jetDebugExe.linkSystemLibrary("LLVMDebugInfoPDB");
    jetDebugExe.linkSystemLibrary("LLVMDebugInfoMSF");
    jetDebugExe.linkSystemLibrary("LLVMDebugInfoDWARF");
    jetDebugExe.linkSystemLibrary("LLVMObject");
    jetDebugExe.linkSystemLibrary("LLVMTextAPI");
    jetDebugExe.linkSystemLibrary("LLVMMCParser");
    jetDebugExe.linkSystemLibrary("LLVMIRReader");
    jetDebugExe.linkSystemLibrary("LLVMAsmParser");
    jetDebugExe.linkSystemLibrary("LLVMMC");
    jetDebugExe.linkSystemLibrary("LLVMDebugInfoCodeView");
    jetDebugExe.linkSystemLibrary("LLVMBitReader");
    jetDebugExe.linkSystemLibrary("LLVMFuzzerCLI");
    jetDebugExe.linkSystemLibrary("LLVMCore");
    jetDebugExe.linkSystemLibrary("LLVMRemarks");
    jetDebugExe.linkSystemLibrary("LLVMBitstreamReader");
    jetDebugExe.linkSystemLibrary("LLVMBinaryFormat");
    jetDebugExe.linkSystemLibrary("LLVMTargetParser");
    jetDebugExe.linkSystemLibrary("LLVMTableGen");
    jetDebugExe.linkSystemLibrary("LLVMSupport");
    jetDebugExe.linkSystemLibrary("LLVMDemangle");
    jetDebugExe.linkSystemLibrary("lldCommon");
    jetDebugExe.linkSystemLibrary("lldCOFF");
    jetDebugExe.linkSystemLibrary("lldELF");
    jetDebugExe.linkSystemLibrary("lldMachO");
    jetDebugExe.linkSystemLibrary("lldMinGW");
    jetDebugExe.linkSystemLibrary("lldWasm");
    jetDebugExe.root_module.addCMacro(buildTargetMacroKey, buildTargetMacroValue);

    b.installArtifact(jetExe);
    b.installArtifact(jetDebugExe);
}