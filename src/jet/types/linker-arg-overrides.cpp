//
// Created by Johny Georges on 2026-10-02.
//

#include "linker-arg-overrides.h"

#include <utility>

LinkerArgOverrides::LinkerArgOverrides(std::string macosSysLibFileOverride, std::string linuxDynamicLinkerFileOverride, std::string linuxMultiArchDirectoryOverride, std::string linuxLibDirectoryOverride) {
    _macosSysLibFile = std::move(macosSysLibFileOverride);
    _linuxDynamicLinkerFile = std::move(linuxDynamicLinkerFileOverride);
    _linuxMultiArchDirectory = std::move(linuxMultiArchDirectoryOverride);
    _linuxLibDirectory = std::move(linuxLibDirectoryOverride);
}

std::string* LinkerArgOverrides::getMacOsSysLibFile() {
    if (_macosSysLibFile.empty()) {
        return &_macosSysLibFileDefault;
    }
    return &_macosSysLibFile;
}

std::string* LinkerArgOverrides::getLinuxDynamicLinkerFile() {
    if (_linuxDynamicLinkerFile.empty()) {
        return &_linuxDynamicLinkerFileDefault;
    }
    return &_linuxDynamicLinkerFile;
}

std::string* LinkerArgOverrides::getLinuxMultiArchDirectory() {
    if (_linuxMultiArchDirectory.empty()) {
        return &_linuxMultiArchDirectoryDefault;
    }
    return &_linuxMultiArchDirectory;
}

std::string* LinkerArgOverrides::getLinuxLibDirectory() {
    if (_linuxLibDirectory.empty()) {
        return &_linuxLibDirectoryDefault;
    }
    return &_linuxLibDirectory;
}

LinkerArgOverrides* LinkerArgOverrides::setMacOsSysLibFileDefault(std::string defaultMacosSysLibFile) {
    _macosSysLibFileDefault = std::move(defaultMacosSysLibFile);
    return this;
}

LinkerArgOverrides* LinkerArgOverrides::setLinuxDynamicLinkerFileDefault(std::string defaultLinuxDynamicLinkerFile) {
    _linuxDynamicLinkerFileDefault = std::move(defaultLinuxDynamicLinkerFile);
    return this;
}

LinkerArgOverrides* LinkerArgOverrides::setLinuxMultiArchDirectoryDefault(std::string defaultLinuxMultiArchDirectory) {
    _linuxMultiArchDirectoryDefault = std::move(defaultLinuxMultiArchDirectory);
    return this;
}

LinkerArgOverrides* LinkerArgOverrides::setLinuxLibDirectoryDefault(std::string defaultLinuxLibDirectory) {
    _linuxLibDirectoryDefault = std::move(defaultLinuxLibDirectory);
    return this;
}