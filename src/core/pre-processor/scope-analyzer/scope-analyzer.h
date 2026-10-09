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
// Created by Johny Georges on 2025-11-18.
//

#ifndef JETLANG_SCOPE_ANALYZER_H
#define JETLANG_SCOPE_ANALYZER_H

#include "../../ast/ast-nodes/ast-file-node.h"
#include "../../ast/ast-nodes/ast-function-nodes/ast-function-block-node.h"
#include "../../ast/ast-nodes/ast-control-flow-nodes/ast-control-flow-block-node.h"
#include "../../ast-lookup-table/ast-lookup-table.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"

class ScopeAnalyzer {
private:
    bool _debugMode = false;
    void traverse(std::shared_ptr<ASTNode> startNode, std::shared_ptr<ASTLookupTable> startScope);
public:
    void switchToDebugMode();
    void process(std::shared_ptr<ASTFileNode> fileNode);
};

#endif //JETLANG_SCOPE_ANALYZER_H
