//
// Created by Johny Georges on 2024-11-04.
//

#include "ir-jet-file.h"

IRJetFile::IRJetFile(JetFile* jetFile, IRModuleNode* irModule) {
    _jetFile = jetFile;
    _irModule = irModule;
}

JetFile* IRJetFile::getFile() {
    return _jetFile;
}

IRModuleNode* IRJetFile::getModule() {
    return _irModule;
}