//
// Created by Johny Georges on 2026-09-30.
//

#ifndef JETLANG_TARGET_LINKER_HELPER_H
#define JETLANG_TARGET_LINKER_HELPER_H

#include <vector>
#include <string>
#include <filesystem>
#include "supported-targets.h"

class TargetLinkerHelper {
private:
    static std::vector<const char*> getMacosx86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
    static std::vector<const char*> getMacosAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
    static std::vector<const char*> getLinuxGnux86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
    static std::vector<const char*> getLinuxGnuAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
    static std::vector<const char*> getLinuxMuslx86_64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
    static std::vector<const char*> getLinuxMuslAarch64LinkerArgs(std::string* objectFilename, std::string* outputFileName);
public:
    static std::vector<const char*> getArgs(std::string targetTriple, std::string* objectFilename, std::string* outputFileName);
};

#endif //JETLANG_TARGET_LINKER_HELPER_H
