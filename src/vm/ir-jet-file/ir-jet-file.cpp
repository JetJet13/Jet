//
// Created by Johny Georges on 2024-11-04.
//

#include "ir-jet-file.h"

IRJetFile::IRJetFile(JetFile* jetFile, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    _jetFile = jetFile;
    _irModule = irModule;
    _scope = scope;
}

JetFile* IRJetFile::getFile() {
    return _jetFile;
}

std::shared_ptr<IRModuleNode> IRJetFile::getIRModule() {
    return _irModule;
}

std::shared_ptr<IRLookupTable> IRJetFile::getScope() {
    return _scope;
}

std::string IRJetFile::getModuleName() {
    if (_jetFile->isModule()) {
        return _jetFile->getFile()->getModule().value()->getName()->getIdentifier()->getId();
    }
    throw std::logic_error("no module name exists since jet file is not a module");
}