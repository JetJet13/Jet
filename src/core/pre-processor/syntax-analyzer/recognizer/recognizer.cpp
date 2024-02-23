//
// Created by Johny Georges on 2024-02-08.
//

#include "recognizer.h"
#include "../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-type-node.h"
#include "../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-init-node.h"
#include "../../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"


Recognizer::Recognizer(Handle* handle) {
    _handle = handle;
}

std::optional<ReduceNode*> Recognizer::recognizeVariableTypeNode() {
    int variableInitNodeSize = 3;
    if (_handle->size() != variableInitNodeSize) {
        return {};
    }

    auto firstNodeOk = _handle->at(0).value()->getNodeType() == AST_VARIABLE_TYPE_NODE;
    auto secondNodeOk = _handle->at(1).value()->getNodeType() == AST_IDENTIFIER_NODE;
    auto thirdNodeOk = _handle->at(2).value()->getNodeType() == AST_ASSIGNMENT_OPERATOR_NODE;

    if (firstNodeOk && secondNodeOk && thirdNodeOk) {
        return new ReduceNode(
                new ASTVariableInitNode((ASTVariableTypeNode*)_handle->at(0).value(),
                                        (ASTIdentifierNode*)_handle->at(1).value()
                                        ),
                variableInitNodeSize);
    }
    return {};
}

std::optional<ReduceNode*> Recognizer::recognizeIntLiteralNode() {
    if (_handle->size() == 1) {
        return {};
    } else if (_handle->size() == 2) {
        return this->isLiteralAssignment();
    } else if (_handle->size() == 3 && ASTNodeUtils::isBinaryOperatorNode(_handle->at(1).value())) {

    }


}

std::optional<ReduceNode*> Recognizer::isLiteralAssignment() {
    if (_handle->size() != 2) {
        return {};
    }


    if (ASTNodeUtils::isLiteralNode(_handle->at(0).value()) &&
    ASTNodeUtils::isTerminatorNode(_handle->at(1).value())) {
        return new ReduceNode(_handle->at(0).value(), 1);
    }
    return {};
}

std::optional<ReduceNode*> Recognizer::recognize() {
    if (_handle->isEmpty()) {
        return {};
    }
    auto firstNode = _handle->at(0);
    switch (firstNode.value()->getNodeType()) {
        case AST_VARIABLE_TYPE_NODE:
           return this->recognizeVariableTypeNode();
        case AST_INT_LITERAL_NODE:

        default:
            return {};
    }
}