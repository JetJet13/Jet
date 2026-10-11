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

//
// Created by Johny Georges on 2026-10-03.
//

#include "cli-helper.h"

CliHelper::CliHelper(CLI::App* app) {
    _app = app;
}

CliHelper* CliHelper::addFilePathOption(std::string &filePathVar) {
    _app->add_option("filePath", filePathVar, "the entry jet file path")->required()
    ->check(CLI::ExistingFile)
    ->check(CLI::ReadPermissions)
    ->check([](const std::string &filePath) {
        auto path = std::filesystem::path(filePath);
        if (!path.has_extension() || path.extension().string() != ".jet") {
            return "Invalid file provided. File must have .jet extension.";
        }
        return "";
    });
    return this;
}

CliHelper* CliHelper::addOutDirOption(std::string &outDirVar) {
    _app->add_option("--out-dir", outDirVar, "the output directory. Defaults to jet file parent directory")
    ->check(CLI::ExistingDirectory)
    ->check(CLI::WritePermissions);
    return this;
}

CliHelper* CliHelper::addMacosSysLibFileOption(std::string &macosSysLibFileOverrideVar) {
    _app->add_option("--macos-sys-lib-dir", macosSysLibFileOverrideVar, "override the macos sys-lib file (for macos only) e.g. '/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk'")
    ->check(CLI::ExistingFile)
    ->check(CLI::ReadPermissions);
    return this;
}

CliHelper* CliHelper::addLinuxDynamicLinkerFileOverrideOption(std::string &linuxDynamicLinkerFileOverrideVar) {
    _app->add_option("--linux-dy-link", linuxDynamicLinkerFileOverrideVar, "override the linker dynamic linker file (for linux distributions only) e.g. /lib/ld-linux-aarch64.so.1, /lib64/ld-linux-x86-64.so.2, /lib/ld-musl-x86_64.so.1")
    ->check(CLI::ExistingFile)
    ->check(CLI::ReadPermissions);
    return this;
}

CliHelper* CliHelper::addLinuxMultiArchPathOverrideOption(std::string &linuxMultiArchPathOverrideVar) {
    _app->add_option("--linux-multi-arch-dir", linuxMultiArchPathOverrideVar, "override the linker multi-arch directory (for linux distributions only) e.g. /usr/lib/x86_64-linux-gnu, /usr/lib/aarch64-linux-gnu")
    ->check(CLI::ExistingDirectory)
    ->check(CLI::ReadPermissions);
    return this;
}

CliHelper* CliHelper::addLinuxLibDirOverrideOption(std::string &linuxLibDirOverrideVar) {
    _app->add_option("--linux-lib-dir", linuxLibDirOverrideVar, "override the linker lib directory (-L) (for linux distributions only) e.g. /usr/lib")
    ->check(CLI::ExistingDirectory)
    ->check(CLI::ReadPermissions);
    return this;
}

CliHelper* CliHelper::addIncludeObjectFileFlag(bool &includeObjectFileVar) {
    _app->add_flag("--obj", includeObjectFileVar, "include object file in output");
    return this;
}

CliHelper* CliHelper::addPrintIRFlag(bool &printIRVar) {
    _app->add_flag("--print-ir", printIRVar, "print generated IR");
    return this;
}