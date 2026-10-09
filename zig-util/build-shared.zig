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

pub fn setup(exe: *std.Build.Step.Compile, b: *std.Build) void {
    exe.linkLibCpp();
    exe.addCSourceFiles(.{
        .root = b.path("src/shared"),
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