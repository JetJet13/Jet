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
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_RECOGNIZER_RESULT_H
#define JETLANG_RECOGNIZER_RESULT_H

#include "../../../ast/ast-nodes/ast-node.h"
#include "types/recognizer-action.h"

class RecognizerResult {
private:
    RecognizerAction _recognizerAction;
    ASTNodeType _targetAstNodeType;
    uint64_t _numReducedNodes;
public:
    RecognizerResult(RecognizerAction recognizerAction, uint64_t numReducedNodes = 0, ASTNodeType targetAstNodeType = AST_NULL_NODE);
    ASTNodeType getTargetAstNodeType();
    int getNumReducedNodes();
    bool reduce();
    bool shift();
    bool pop();
};

#endif //JETLANG_RECOGNIZER_RESULT_H
