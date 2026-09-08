const std = @import("std");

pub fn setup(exe: *std.Build.Step.Compile, b: *std.Build) void {
    exe.addCSourceFiles(.{
        .root = b.path("../../../shared"),
        .flags = &.{
            "-std=c++17"
        },
        .files = &.{
            
            "hash-table/hash-table.cpp",
            
            
            "utils/file-io/file-io.cpp",
            
            "utils/logger/logger.cpp",
            
            "utils/md5/md5.cpp",
            
            "utils/to-string/to-string.cpp",
            
            
            "utils/function-id-generator/function-id-generator.cpp",
            
        },
    });
}