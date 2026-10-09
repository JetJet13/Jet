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
// Created by Johny Georges on 2024-04-06.
//

#include "ast-less-than-base-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-type-nodes/ast-type-parameter-list-start-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-comparator-operator-node.h"

ASTLessThanBaseNode::ASTLessThanBaseNode(std::shared_ptr<Lexeme> lexeme) {
    _lexeme = lexeme;
}

std::shared_ptr<Lexeme> ASTLessThanBaseNode::getLexeme() {
    return _lexeme;
}

std::shared_ptr<ASTNode> ASTLessThanBaseNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode,
                                                    std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {

    if (prevNode && prevNode.value()->isOneOf({ AST_FUNCTION_NODE, AST_PROCEDURE_NODE, AST_TUPLE_NODE, AST_SHARED_NODE })) {
        return std::make_shared<ASTTypeParameterListStartNode>(this->getLexeme());
    }

    return std::make_shared<ASTBinaryComparatorOperatorNode>(_lexeme);
}

ASTNodeType ASTLessThanBaseNode::getNodeType() {
    return AST_LESS_THAN_BASE_NODE;
}

std::string ASTLessThanBaseNode::toString() {
    return "LESS_THAN";
}

bool ASTLessThanBaseNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLessThanBaseNode>(other);
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTLessThanBaseNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}