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
    ->check(CLI::ReadPermissions);
    return this;
}

CliHelper* CliHelper::addOutDirOption(std::string &outDirVar) {
    _app->add_option("--outdir", outDirVar, "the output directory. Defaults to entry jet file parent directory")
    ->check(CLI::ExistingDirectory)
    ->check(CLI::WritePermissions);
    return this;
}

CliHelper* CliHelper::addMacosSysLibDirOption(std::string &macosSysLibDirectoryOverrideVar) {
    _app->add_option("--macosSysLibDir", macosSysLibDirectoryOverrideVar, "override the macos sys-lib file. e.g. '/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk'")
    ->check(CLI::ExistingFile)
    ->check(CLI::ReadPermissions);
    return this;
}

CliHelper* CliHelper::addLinuxDynamicLinkerPathOverrideOption(std::string &linuxDynamicLinkerPathOverrideVar) {
    _app->add_option("--linuxDyLink", linuxDynamicLinkerPathOverrideVar, "override the linker dynamic linker path for linux distributions. e.g. /lib/ld-linux-aarch64.so.1, /lib64/ld-linux-x86-64.so.2, /lib/ld-musl-x86_64.so.1")
    ->check(CLI::ExistingDirectory)
    ->check(CLI::ReadPermissions);
    return this;
}

CliHelper* CliHelper::addLinuxMultiArchPathOverrideOption(std::string &linuxMultiArchPathOverrideVar) {
    _app->add_option("--linuxMultiArch", linuxMultiArchPathOverrideVar, "override the linker multi-arch path for linux distributions. e.g. /usr/lib/x86_64-linux-gnu, /usr/lib/aarch64-linux-gnu")
    ->check(CLI::ExistingDirectory)
    ->check(CLI::ReadPermissions);
    return this;
}

CliHelper* CliHelper::addLinuxLibDirOverrideOption(std::string &linuxLibDirOverrideVar) {
    _app->add_option("--linuxLibDir", linuxLibDirOverrideVar, "override the linker lib directory (-L) for linux distributions. e.g. /usr/lib")
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