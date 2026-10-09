//
// Created by Johny Georges on 2026-10-03.
//

#ifndef JETLANG_CLI_HELPER_H
#define JETLANG_CLI_HELPER_H

#define CLI11_ENABLE_EXTRA_VALIDATORS 1
#define CLI11_HAS_FILESYSTEM 1

#include <string>
#include "../cli11/CLI11.hpp"

class CliHelper {
private:
    CLI::App* _app;
public:
    CliHelper(CLI::App* app);
    CliHelper* addFilePathOption(std::string &filePathVar);
    CliHelper* addOutDirOption(std::string &outDirVar);
    CliHelper* addMacosSysLibDirOption(std::string &macosSysLibDirectoryOverrideVar);
    CliHelper* addLinuxDynamicLinkerPathOverrideOption(std::string &linuxDynamicLinkerPathOverrideVar);
    CliHelper* addLinuxMultiArchPathOverrideOption(std::string &linuxMultiArchPathOverrideVar);
    CliHelper* addLinuxLibDirOverrideOption(std::string &linuxLibDirOverrideVar);
    CliHelper* addIncludeObjectFileFlag(bool &includeObjectFileVar);
};

#endif //JETLANG_CLI_HELPER_H
