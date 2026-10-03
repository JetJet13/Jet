const std = @import("std");

pub fn setup(exe: *std.Build.Step.Compile, b: *std.Build, target: []const u8) void {
    exe.addCSourceFiles(.{
        .root = b.path("src/jet"),
        .files = &.{
            "main.cpp",
            "types/target-helper.cpp",
            "types/linker-arg-overrides.cpp"
        },
        .flags = &.{
            "-std=c++17",
        },
    });
    setupDeps(exe, b, target);
    linkLLVM(exe, b, target);
}

pub fn setupDebug(exe: *std.Build.Step.Compile, b: *std.Build, target: []const u8) void {
    exe.addCSourceFiles(.{
        .root = b.path("src/jet"),
        .files = &.{
            "debug-main.cpp",
            "types/target-helper.cpp",
            "types/linker-arg-overrides.cpp"
        },
        .flags = &.{
            "-std=c++17",
        },
    });
    setupDeps(exe, b, target);
    linkLLVM(exe, b, target);
}

pub fn setupDeps(exe: *std.Build.Step.Compile, b: *std.Build, target: []const u8) void {
    const ncursesIncludePath = b.fmt("zig-util/target/{s}/sysroot/ncurses/include", .{ target });
    const ncursesLibraryPath = b.fmt("zig-util/target/{s}/sysroot/ncurses/lib", .{ target });
    const xml2IncludePath = b.fmt("zig-util/target/{s}/sysroot/xml2/include", .{ target });
    const xml2LibraryPath = b.fmt("zig-util/target/{s}/sysroot/xml2/lib", .{ target });
    const zlibIncludePath = b.fmt("zig-util/target/{s}/sysroot/zlib/include", .{ target });
    const zlibLibraryPath = b.fmt("zig-util/target/{s}/sysroot/zlib/lib", .{ target });
    const zstdIncludePath = b.fmt("zig-util/target/{s}/sysroot/zstd/include", .{ target });
    const zstdLibraryPath = b.fmt("zig-util/target/{s}/sysroot/zstd/lib", .{ target });

    exe.linkLibCpp();
    exe.addIncludePath(b.path("../src/jet/cli11"));
    exe.addIncludePath(b.path(ncursesIncludePath));
    exe.addLibraryPath(b.path(ncursesLibraryPath));
    exe.addIncludePath(b.path(xml2IncludePath));
    exe.addLibraryPath(b.path(xml2LibraryPath));
    exe.addIncludePath(b.path(zlibIncludePath));
    exe.addLibraryPath(b.path(zlibLibraryPath));
    exe.addIncludePath(b.path(zstdIncludePath));
    exe.addLibraryPath(b.path(zstdLibraryPath));
    exe.linkSystemLibrary2("xml2", .{
        .preferred_link_mode = .static,
    });
    
    exe.linkSystemLibrary2("ncurses", .{
        .preferred_link_mode = .static,
    });
    
    exe.linkSystemLibrary2("zlib", .{
        .preferred_link_mode = .static,
    });
    
    exe.linkSystemLibrary2("zstd", .{
        .preferred_link_mode = .static,
    });
}

pub fn linkLLVM(exe: *std.Build.Step.Compile, b: *std.Build, target: []const u8) void {
    const llvmIncludePath = b.fmt("zig-util/target/{s}/llvm/include", .{ target });
    const llvmLibraryPath = b.fmt("zig-util/target/{s}/llvm/lib", .{ target });

    exe.addIncludePath(b.path(llvmIncludePath));
    exe.addLibraryPath(b.path(llvmLibraryPath));
    exe.linkSystemLibrary("LLVMWindowsManifest");
    exe.linkSystemLibrary("LLVMXRay");
    exe.linkSystemLibrary("LLVMLibDriver");
    exe.linkSystemLibrary("LLVMDlltoolDriver");
    exe.linkSystemLibrary("LLVMCoverage");
    exe.linkSystemLibrary("LLVMLineEditor");
    exe.linkSystemLibrary("LLVMXCoreDisassembler");
    exe.linkSystemLibrary("LLVMXCoreCodeGen");
    exe.linkSystemLibrary("LLVMXCoreDesc");
    exe.linkSystemLibrary("LLVMXCoreInfo");
    exe.linkSystemLibrary("LLVMX86TargetMCA");
    exe.linkSystemLibrary("LLVMX86Disassembler");
    exe.linkSystemLibrary("LLVMX86AsmParser");
    exe.linkSystemLibrary("LLVMX86CodeGen");
    exe.linkSystemLibrary("LLVMX86Desc");
    exe.linkSystemLibrary("LLVMX86Info");
    exe.linkSystemLibrary("LLVMWebAssemblyDisassembler");
    exe.linkSystemLibrary("LLVMWebAssemblyAsmParser");
    exe.linkSystemLibrary("LLVMWebAssemblyCodeGen");
    exe.linkSystemLibrary("LLVMWebAssemblyUtils");
    exe.linkSystemLibrary("LLVMWebAssemblyDesc");
    exe.linkSystemLibrary("LLVMWebAssemblyInfo");
    exe.linkSystemLibrary("LLVMVEDisassembler");
    exe.linkSystemLibrary("LLVMVEAsmParser");
    exe.linkSystemLibrary("LLVMVECodeGen");
    exe.linkSystemLibrary("LLVMVEDesc");
    exe.linkSystemLibrary("LLVMVEInfo");
    exe.linkSystemLibrary("LLVMSystemZDisassembler");
    exe.linkSystemLibrary("LLVMSystemZAsmParser");
    exe.linkSystemLibrary("LLVMSystemZCodeGen");
    exe.linkSystemLibrary("LLVMSystemZDesc");
    exe.linkSystemLibrary("LLVMSystemZInfo");
    exe.linkSystemLibrary("LLVMSparcDisassembler");
    exe.linkSystemLibrary("LLVMSparcAsmParser");
    exe.linkSystemLibrary("LLVMSparcCodeGen");
    exe.linkSystemLibrary("LLVMSparcDesc");
    exe.linkSystemLibrary("LLVMSparcInfo");
    exe.linkSystemLibrary("LLVMRISCVTargetMCA");
    exe.linkSystemLibrary("LLVMRISCVDisassembler");
    exe.linkSystemLibrary("LLVMRISCVAsmParser");
    exe.linkSystemLibrary("LLVMRISCVCodeGen");
    exe.linkSystemLibrary("LLVMRISCVDesc");
    exe.linkSystemLibrary("LLVMRISCVInfo");
    exe.linkSystemLibrary("LLVMPowerPCDisassembler");
    exe.linkSystemLibrary("LLVMPowerPCAsmParser");
    exe.linkSystemLibrary("LLVMPowerPCCodeGen");
    exe.linkSystemLibrary("LLVMPowerPCDesc");
    exe.linkSystemLibrary("LLVMPowerPCInfo");
    exe.linkSystemLibrary("LLVMNVPTXCodeGen");
    exe.linkSystemLibrary("LLVMNVPTXDesc");
    exe.linkSystemLibrary("LLVMNVPTXInfo");
    exe.linkSystemLibrary("LLVMMSP430Disassembler");
    exe.linkSystemLibrary("LLVMMSP430AsmParser");
    exe.linkSystemLibrary("LLVMMSP430CodeGen");
    exe.linkSystemLibrary("LLVMMSP430Desc");
    exe.linkSystemLibrary("LLVMMSP430Info");
    exe.linkSystemLibrary("LLVMMipsDisassembler");
    exe.linkSystemLibrary("LLVMMipsAsmParser");
    exe.linkSystemLibrary("LLVMMipsCodeGen");
    exe.linkSystemLibrary("LLVMMipsDesc");
    exe.linkSystemLibrary("LLVMMipsInfo");
    exe.linkSystemLibrary("LLVMLoongArchDisassembler");
    exe.linkSystemLibrary("LLVMLoongArchAsmParser");
    exe.linkSystemLibrary("LLVMLoongArchCodeGen");
    exe.linkSystemLibrary("LLVMLoongArchDesc");
    exe.linkSystemLibrary("LLVMLoongArchInfo");
    exe.linkSystemLibrary("LLVMLanaiDisassembler");
    exe.linkSystemLibrary("LLVMLanaiCodeGen");
    exe.linkSystemLibrary("LLVMLanaiAsmParser");
    exe.linkSystemLibrary("LLVMLanaiDesc");
    exe.linkSystemLibrary("LLVMLanaiInfo");
    exe.linkSystemLibrary("LLVMHexagonDisassembler");
    exe.linkSystemLibrary("LLVMHexagonCodeGen");
    exe.linkSystemLibrary("LLVMHexagonAsmParser");
    exe.linkSystemLibrary("LLVMHexagonDesc");
    exe.linkSystemLibrary("LLVMHexagonInfo");
    exe.linkSystemLibrary("LLVMBPFDisassembler");
    exe.linkSystemLibrary("LLVMBPFAsmParser");
    exe.linkSystemLibrary("LLVMBPFCodeGen");
    exe.linkSystemLibrary("LLVMBPFDesc");
    exe.linkSystemLibrary("LLVMBPFInfo");
    exe.linkSystemLibrary("LLVMAVRDisassembler");
    exe.linkSystemLibrary("LLVMAVRAsmParser");
    exe.linkSystemLibrary("LLVMAVRCodeGen");
    exe.linkSystemLibrary("LLVMAVRDesc");
    exe.linkSystemLibrary("LLVMAVRInfo");
    exe.linkSystemLibrary("LLVMARMDisassembler");
    exe.linkSystemLibrary("LLVMARMAsmParser");
    exe.linkSystemLibrary("LLVMARMCodeGen");
    exe.linkSystemLibrary("LLVMARMDesc");
    exe.linkSystemLibrary("LLVMARMUtils");
    exe.linkSystemLibrary("LLVMARMInfo");
    exe.linkSystemLibrary("LLVMAMDGPUTargetMCA");
    exe.linkSystemLibrary("LLVMAMDGPUDisassembler");
    exe.linkSystemLibrary("LLVMAMDGPUAsmParser");
    exe.linkSystemLibrary("LLVMAMDGPUCodeGen");
    exe.linkSystemLibrary("LLVMAMDGPUDesc");
    exe.linkSystemLibrary("LLVMAMDGPUUtils");
    exe.linkSystemLibrary("LLVMAMDGPUInfo");
    exe.linkSystemLibrary("LLVMAArch64Disassembler");
    exe.linkSystemLibrary("LLVMAArch64AsmParser");
    exe.linkSystemLibrary("LLVMAArch64CodeGen");
    exe.linkSystemLibrary("LLVMAArch64Desc");
    exe.linkSystemLibrary("LLVMAArch64Utils");
    exe.linkSystemLibrary("LLVMAArch64Info");
    exe.linkSystemLibrary("LLVMOrcJIT");
    exe.linkSystemLibrary("LLVMWindowsDriver");
    exe.linkSystemLibrary("LLVMMCJIT");
    exe.linkSystemLibrary("LLVMJITLink");
    exe.linkSystemLibrary("LLVMInterpreter");
    exe.linkSystemLibrary("LLVMExecutionEngine");
    exe.linkSystemLibrary("LLVMRuntimeDyld");
    exe.linkSystemLibrary("LLVMOrcTargetProcess");
    exe.linkSystemLibrary("LLVMOrcShared");
    exe.linkSystemLibrary("LLVMDWP");
    exe.linkSystemLibrary("LLVMDebugInfoLogicalView");
    exe.linkSystemLibrary("LLVMDebugInfoGSYM");
    exe.linkSystemLibrary("LLVMOption");
    exe.linkSystemLibrary("LLVMObjectYAML");
    exe.linkSystemLibrary("LLVMObjCopy");
    exe.linkSystemLibrary("LLVMMCA");
    exe.linkSystemLibrary("LLVMMCDisassembler");
    exe.linkSystemLibrary("LLVMLTO");
    exe.linkSystemLibrary("LLVMPasses");
    exe.linkSystemLibrary("LLVMCFGuard");
    exe.linkSystemLibrary("LLVMCoroutines");
    exe.linkSystemLibrary("LLVMipo");
    exe.linkSystemLibrary("LLVMVectorize");
    exe.linkSystemLibrary("LLVMLinker");
    exe.linkSystemLibrary("LLVMInstrumentation");
    exe.linkSystemLibrary("LLVMFrontendOpenMP");
    exe.linkSystemLibrary("LLVMFrontendOpenACC");
    exe.linkSystemLibrary("LLVMFrontendHLSL");
    exe.linkSystemLibrary("LLVMExtensions");
    exe.linkSystemLibrary("LLVMDWARFLinkerParallel");
    exe.linkSystemLibrary("LLVMDWARFLinker");
    exe.linkSystemLibrary("LLVMGlobalISel");
    exe.linkSystemLibrary("LLVMMIRParser");
    exe.linkSystemLibrary("LLVMAsmPrinter");
    exe.linkSystemLibrary("LLVMSelectionDAG");
    exe.linkSystemLibrary("LLVMCodeGen");
    exe.linkSystemLibrary("LLVMTarget");
    exe.linkSystemLibrary("LLVMObjCARCOpts");
    exe.linkSystemLibrary("LLVMCodeGenTypes");
    exe.linkSystemLibrary("LLVMIRPrinter");
    exe.linkSystemLibrary("LLVMInterfaceStub");
    exe.linkSystemLibrary("LLVMFileCheck");
    exe.linkSystemLibrary("LLVMFuzzMutate");
    exe.linkSystemLibrary("LLVMScalarOpts");
    exe.linkSystemLibrary("LLVMInstCombine");
    exe.linkSystemLibrary("LLVMAggressiveInstCombine");
    exe.linkSystemLibrary("LLVMTransformUtils");
    exe.linkSystemLibrary("LLVMBitWriter");
    exe.linkSystemLibrary("LLVMAnalysis");
    exe.linkSystemLibrary("LLVMProfileData");
    exe.linkSystemLibrary("LLVMSymbolize");
    exe.linkSystemLibrary("LLVMDebugInfoBTF");
    exe.linkSystemLibrary("LLVMDebugInfoPDB");
    exe.linkSystemLibrary("LLVMDebugInfoMSF");
    exe.linkSystemLibrary("LLVMDebugInfoDWARF");
    exe.linkSystemLibrary("LLVMObject");
    exe.linkSystemLibrary("LLVMTextAPI");
    exe.linkSystemLibrary("LLVMMCParser");
    exe.linkSystemLibrary("LLVMIRReader");
    exe.linkSystemLibrary("LLVMAsmParser");
    exe.linkSystemLibrary("LLVMMC");
    exe.linkSystemLibrary("LLVMDebugInfoCodeView");
    exe.linkSystemLibrary("LLVMBitReader");
    exe.linkSystemLibrary("LLVMFuzzerCLI");
    exe.linkSystemLibrary("LLVMCore");
    exe.linkSystemLibrary("LLVMRemarks");
    exe.linkSystemLibrary("LLVMBitstreamReader");
    exe.linkSystemLibrary("LLVMBinaryFormat");
    exe.linkSystemLibrary("LLVMTargetParser");
    exe.linkSystemLibrary("LLVMTableGen");
    exe.linkSystemLibrary("LLVMSupport");
    exe.linkSystemLibrary("LLVMDemangle");
    exe.linkSystemLibrary("lldCommon");
    exe.linkSystemLibrary("lldCOFF");
    exe.linkSystemLibrary("lldELF");
    exe.linkSystemLibrary("lldMachO");
    exe.linkSystemLibrary("lldMinGW");
    exe.linkSystemLibrary("lldWasm");
}