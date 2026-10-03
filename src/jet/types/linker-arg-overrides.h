//
// Created by Johny Georges on 2026-10-02.
//

#ifndef JETLANG_LINKER_ARG_OVERRIDES_H
#define JETLANG_LINKER_ARG_OVERRIDES_H

#include <string>
#include <optional>

class LinkerArgOverrides {
private:
    std::string _macosSysLibFile;
    std::string _macosSysLibFileDefault;

    std::string _linuxDynamicLinkerFile;
    std::string _linuxDynamicLinkerFileDefault;

    std::string _linuxMultiArchDirectory;
    std::string _linuxMultiArchDirectoryDefault;

    std::string _linuxLibDirectory;
    std::string _linuxLibDirectoryDefault;
public:
    LinkerArgOverrides(std::string macosSysLibFileOverride, std::string linuxDynamicLinkerFileOverride, std::string linuxMultiArchDirectoryOverride, std::string linuxLibDirectoryOverride);
    std::string* getMacOsSysLibFile();
    std::string* getLinuxDynamicLinkerFile();
    std::string* getLinuxMultiArchDirectory();
    std::string* getLinuxLibDirectory();
    LinkerArgOverrides* setMacOsSysLibFileDefault(std::string defaultMacosSysLibFile);
    LinkerArgOverrides* setLinuxDynamicLinkerFileDefault(std::string defaultLinuxDynamicLinkerFile);
    LinkerArgOverrides* setLinuxMultiArchDirectoryDefault(std::string defaultLinuxMultiArchDirectory);
    LinkerArgOverrides* setLinuxLibDirectoryDefault(std::string defaultLinuxLibDirectory);
};

#endif //JETLANG_LINKER_ARG_OVERRIDES_H
