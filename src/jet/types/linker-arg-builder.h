//
// Created by Johny Georges on 2026-10-02.
//

#ifndef JETLANG_LINKER_ARG_BUILDER_H
#define JETLANG_LINKER_ARG_BUILDER_H

#include <string>
#include <optional>
#include <vector>

class LinkerArgBuilder {
private:
    std::string _macosSysLibFileOverride;
    std::string _macosSysLibFileDefault;

    std::string _linuxDynamicLinkerFileOverride;
    std::string _linuxDynamicLinkerFileDefault;

    std::string _linuxMultiArchDirectoryOverride;
    std::string _linuxMultiArchDirectoryDefault;

    std::string _linuxLibDirectoryOverride;
    std::string _linuxLibDirectoryDefault;

    std::vector<std::string> _args;
public:
    LinkerArgBuilder(std::string macosSysLibFileOverride, std::string linuxDynamicLinkerFileOverride, std::string linuxMultiArchDirectoryOverride, std::string linuxLibDirectoryOverride);
    std::string getMacOsSysLibFile();
    std::string getLinuxDynamicLinkerFile();
    std::string getLinuxMultiArchDirectory();
    std::string getLinuxLibDirectory();
    LinkerArgBuilder* setMacOsSysLibFileDefault(std::string defaultMacosSysLibFile);
    LinkerArgBuilder* setLinuxDynamicLinkerFileDefault(std::string defaultLinuxDynamicLinkerFile);
    LinkerArgBuilder* setLinuxMultiArchDirectoryDefault(std::string defaultLinuxMultiArchDirectory);
    LinkerArgBuilder* setLinuxLibDirectoryDefault(std::string defaultLinuxLibDirectory);
    LinkerArgBuilder* addArg(std::string arg);
    std::vector<const char*> build();
};

#endif //JETLANG_LINKER_ARG_BUILDER_H
