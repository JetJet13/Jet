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

#ifndef JETLANG_JET_FILE_H
#define JETLANG_JET_FILE_H

#include <set>
#include "../ast/ast-nodes/ast-file-node.h"
#include "../pre-processor/semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table.h"
#include "../pre-processor/semantic-analyzer/type-checker/types/type-checker-result/type-checker-result.h"

class JetFile {
private:
    std::string _id;
    std::shared_ptr<ASTFileNode> _astFileNode;
    std::shared_ptr<TypeSignatureLookupTable> _fileScope;
    TypeCheckerResult _typeCheckerResult;
    std::set<std::shared_ptr<JetFile>> _importedJetFiles;
public:
    JetFile(std::shared_ptr<ASTFileNode> astFileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope, TypeCheckerResult typeCheckerResult, std::set<std::shared_ptr<JetFile>> importedJetFiles);
    JetFile(std::shared_ptr<ASTFileNode> astFileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope, TypeCheckerResult typeCheckerResult);
    std::string getId();
    std::shared_ptr<ASTFileNode> getFile();
    std::shared_ptr<TypeSignatureLookupTable> getScope();
    TypeCheckerResult* getTypeCheckerResult();
    void addImportedFile(std::shared_ptr<JetFile> jetFile);
    std::set<std::shared_ptr<JetFile>>* getImportedFiles();
    bool isModule();
    bool hasImports();
    void print();
};

#endif //JETLANG_JET_FILE_H
