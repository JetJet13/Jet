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
// Created by Johny Georges on 2024-05-30.
//

#include "source-code-builder.h"
#include "../../ast-nodes/ast-node.h"
#include "../../../../shared/types/basic-character-type.h"
#include "../../../../shared/utils/logger/logger.h"

SourceCodeBuilder::SourceCodeBuilder() {
    _sourceCode = "";
}

SourceCodeBuilder* SourceCodeBuilder::add(std::shared_ptr<ASTNode> node) {
    auto lastLine = _lastNode.has_value()
            ? _lastNode.value()->getEndPosition()->getLine()
            : node->getStartPosition()->getLine();
    auto lastColumn = _lastNode.has_value()
            ? _lastNode.value()->getEndPosition()->getColumn()
            : node->getStartPosition()->getColumn();
    auto lineDelta = node->getStartPosition()->getLine() - lastLine;
    auto columnDelta = lineDelta == 0
            ? node->getStartPosition()->getColumn() - lastColumn
            : node->getStartPosition()->getColumn();
    for (uint64_t i = 0; i < lineDelta; ++i) {
        _sourceCode += NEW_LINE;
    }
    for (uint64_t i = 0; i < columnDelta; ++i) {
        _sourceCode += WHITE_SPACE;
    }
    _sourceCode += node->toSourceCode();
    _lastNode = node;
    return this;
}

std::string SourceCodeBuilder::build() {
    return _sourceCode;
}