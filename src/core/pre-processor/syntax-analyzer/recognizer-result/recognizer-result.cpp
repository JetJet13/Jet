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

#include "recognizer-result.h"

RecognizerResult::RecognizerResult(RecognizerAction recognizerAction, uint64_t numReducedNodes, ASTNodeType targetAstNodeType) {
    _recognizerAction = recognizerAction;
    _targetAstNodeType = targetAstNodeType;
    _numReducedNodes = numReducedNodes;
}

ASTNodeType RecognizerResult::getTargetAstNodeType() {
    return _targetAstNodeType;
}

int RecognizerResult::getNumReducedNodes() {
    return _numReducedNodes;
}

bool RecognizerResult::reduce() {
    return _recognizerAction == RECOGNIZER_ACTION_REDUCE;
}

bool RecognizerResult::shift() {
    return _recognizerAction == RECOGNIZER_ACTION_SHIFT;
}

bool RecognizerResult::pop() {
    return _recognizerAction == RECOGNIZER_ACTION_POP;
}
