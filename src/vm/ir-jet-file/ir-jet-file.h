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

#ifndef JETLANG_IR_JET_FILE_H
#define JETLANG_IR_JET_FILE_H

#include "../../core/jet-file/jet-file.h"
#include "../ir-nodes/ir-module-node.h"
#include "../ir-lookup-table/ir-lookup-table.h"
#include "../ir-nodes/ir-function-nodes/ir-function-node.h"

class IRJetFile {
private:
    std::shared_ptr<JetFile> _jetFile;
    std::shared_ptr<IRModuleNode> _irModule;
    std::shared_ptr<IRLookupTable> _scope;
public:
    IRJetFile(std::shared_ptr<JetFile> jetFile, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    std::shared_ptr<JetFile> getFile();
    std::shared_ptr<IRModuleNode> getIRModule();
    std::shared_ptr<IRLookupTable> getScope();
    std::string getModuleName();
};

#endif //JETLANG_IR_JET_FILE_H
