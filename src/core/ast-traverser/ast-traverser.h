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
// Created by Johny Georges on 2024-05-10.
//

#ifndef JETLANG_AST_TRAVERSER_H
#define JETLANG_AST_TRAVERSER_H

#include <stack>
#include <optional>
#include "../ast/ast-nodes/ast-node.h"

class ASTTraverser {
private:
    std::stack<std::shared_ptr<ASTNode>> _stack;
    bool _hasMore;
    bool _insertTerminatorNodeAfterNext;
public:
    ASTTraverser();
    void init(std::shared_ptr<ASTNode> startNode);
    void reset();
    void insertTerminatorNodeAfterNext();
    std::optional<std::shared_ptr<ASTNode>> next();
    std::optional<std::shared_ptr<ASTNode>> peek();
    bool hasMore();
};

#endif //JETLANG_AST_TRAVERSER_H
