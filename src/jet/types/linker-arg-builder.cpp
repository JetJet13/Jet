//
// Created by Johny Georges on 2026-10-02.
//

#include "linker-arg-builder.h"

#include <utility>

LinkerArgBuilder::LinkerArgBuilder(std::string macosSysLibFileOverride, std::string linuxDynamicLinkerFileOverride, std::string linuxMultiArchDirectoryOverride, std::string linuxLibDirectoryOverride) {
    _macosSysLibFileOverride = std::move(macosSysLibFileOverride);
    _linuxDynamicLinkerFileOverride = std::move(linuxDynamicLinkerFileOverride);
    _linuxMultiArchDirectoryOverride = std::move(linuxMultiArchDirectoryOverride);
    _linuxLibDirectoryOverride = std::move(linuxLibDirectoryOverride);
    _args = std::vector<std::string>();
}

std::string LinkerArgBuilder::getMacOsSysLibFile() {
    if (_macosSysLibFileOverride.empty()) {
        return _macosSysLibFileDefault;
    }
    return _macosSysLibFileOverride;
}

std::string LinkerArgBuilder::getLinuxDynamicLinkerFile() {
    if (_linuxDynamicLinkerFileOverride.empty()) {
        return _linuxDynamicLinkerFileDefault;
    }
    return _linuxDynamicLinkerFileOverride;
}

std::string LinkerArgBuilder::getLinuxMultiArchDirectory() {
    if (_linuxMultiArchDirectoryOverride.empty()) {
        return _linuxMultiArchDirectoryDefault;
    }
    return _linuxMultiArchDirectoryOverride;
}

std::string LinkerArgBuilder::getLinuxLibDirectory() {
    if (_linuxLibDirectoryOverride.empty()) {
        return _linuxLibDirectoryDefault;
    }
    return _linuxLibDirectoryOverride;
}

LinkerArgBuilder* LinkerArgBuilder::setMacOsSysLibFileDefault(std::string defaultMacosSysLibFile) {
    _macosSysLibFileDefault = std::move(defaultMacosSysLibFile);
    return this;
}

LinkerArgBuilder* LinkerArgBuilder::setLinuxDynamicLinkerFileDefault(std::string defaultLinuxDynamicLinkerFile) {
    _linuxDynamicLinkerFileDefault = std::move(defaultLinuxDynamicLinkerFile);
    return this;
}

LinkerArgBuilder* LinkerArgBuilder::setLinuxMultiArchDirectoryDefault(std::string defaultLinuxMultiArchDirectory) {
    _linuxMultiArchDirectoryDefault = std::move(defaultLinuxMultiArchDirectory);
    return this;
}

LinkerArgBuilder* LinkerArgBuilder::setLinuxLibDirectoryDefault(std::string defaultLinuxLibDirectory) {
    _linuxLibDirectoryDefault = std::move(defaultLinuxLibDirectory);
    return this;
}

LinkerArgBuilder* LinkerArgBuilder::addArg(std::string arg) {
    _args.push_back(std::move(arg));
    return this;
}

std::vector<const char*> LinkerArgBuilder::build() {
    auto args = std::vector<const char*>();
    for (const auto &arg : _args) {
        args.push_back(arg.c_str());
    }
    return args;
}