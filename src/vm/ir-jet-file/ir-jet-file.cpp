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
// Created by Johny Georges on 2024-11-04.
//

#include "ir-jet-file.h"

IRJetFile::IRJetFile(std::shared_ptr<JetFile> jetFile, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    _jetFile = jetFile;
    _irModule = irModule;
    _scope = scope;
}

std::shared_ptr<JetFile> IRJetFile::getFile() {
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