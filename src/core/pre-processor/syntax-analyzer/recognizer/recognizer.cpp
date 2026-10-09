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
// Created by Johny Georges on 2024-03-23.
//

#include "recognizer.h"
#include "../../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../ast/ast-nodes/ast-null-node.h"
#include "../../../../shared/utils/logger/logger.h"

Recognizer::Recognizer() {
    _syntaxDfa = SyntaxDfa();
}

std::shared_ptr<RecognizerResult> Recognizer::recognize(Handle* handle) {
    auto mode = this->determineMode(handle);
    auto predecessor = handle->getPrevNodeFor(0);
    auto successor = handle->getNextNodeFor(0);
    auto startNode = _syntaxDfa.findStartNode(handle->first());

    if (handle->isEmpty() && this->isEndNode(handle->getLastReducedNode(), handle->getPeekNode())) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_POP);
    } else if (handle->isArrayEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_ARRAY_NODE);
    } else if (handle->isStructEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_STRUCT_EXPRESSION_NODE);
    } else if (handle->isStructTypeEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_STRUCT_TYPE_NODE);
    } else if (handle->isTupleTypeEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_TUPLE_TYPE_NODE);
    } else if (handle->isFunctionParameterListEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_FUNCTION_PARAMETER_LIST_NODE);
    } else if (handle->isFunctionArgumentListEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_FUNCTION_ARGUMENT_LIST_NODE);
    } else if (handle->isEnumKeyValueListEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_ENUM_KEY_VALUE_LIST_NODE);
    } else if (handle->isInterfacePropertyListEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_INTERFACE_PROPERTY_LIST_NODE);
    } else if (handle->isImplementsInterfaceListEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_IMPLEMENTS_INTERFACE_LIST_NODE);
    } else if (handle->isTupleListEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_TUPLE_EXPRESSION_NODE);
    } else if (handle->isModuleListEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_MODULE_LIST_NODE);
    } else if (handle->isImportModuleListEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_IMPORT_MODULE_LIST_NODE);
    } else if (handle->isLambdaTypeParameterListEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_LAMBDA_TYPE_PARAMETER_LIST_NODE);
    } else if (handle->isTypeParameterListEnclosed()) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_TYPE_PARAMETER_LIST_NODE);
    }

    if (mode == RM_BACKTRACK) {
        if (handle->size() == 1) {
            return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_POP);
        } else if (predecessor && successor && predecessor.value()->isSameNodeTypeAs(successor.value()) && predecessor.value()->isHigherPriorityThan(successor.value())) {
            return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_POP);
        } else if (handle->first().has_value() && ASTNodeUtils::isExpressionNode(handle->first().value()) && !predecessor && successor && successor.value()->is(AST_TERMINATOR_NODE)) {
            return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, 1, AST_EXPRESSION_STATEMENT_NODE);
        }
    }

    if (mode == RM_NORMAL) {
        if (startNode && startNode.value()->alwaysReduceSelf()) {
            return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, 1, handle->first().value()->getNodeType());
        }

        if (startNode && successor && startNode.value()->shouldReduceSelfFor(successor.value()->getNodeType())) {
            return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, 1, handle->first().value()->getNodeType());
        }
    }

    if (startNode && predecessor && successor && startNode.value()->shouldReduceToTargetWhenPrevNodeAndNextNodeIs(predecessor.value()->getNodeType(), successor.value()->getNodeType())) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, 1, startNode.value()->getReduceTargetForPrevNodeAndNextNode(predecessor.value()->getNodeType(), successor.value()->getNodeType()).value());
    } else if (startNode && predecessor && startNode.value()->shouldReduceToTargetWhenPrevNodeIs(predecessor.value()->getNodeType())) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, 1, startNode.value()->getReduceTargetForPrevNode(predecessor.value()->getNodeType()).value());
    } else if (startNode && successor && startNode.value()->shouldReduceToTargetWhenNextNodeIs(successor.value()->getNodeType())) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, 1, startNode.value()->getReduceTargetForNextNode(successor.value()->getNodeType()).value());
    } else if (startNode && predecessor && startNode.value()->shouldBacktrackTo(predecessor.value()->getNodeType())) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_POP);
    } else if (startNode && predecessor && successor && startNode.value()->shouldBacktrackWhenPrevNodeAndNextNodeAre(predecessor.value()->getNodeType(), successor.value()->getNodeType())) {
        return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_POP);
    }
    auto dfa = _syntaxDfa.getDFA();
    dfa->reset();
    for (uint64_t i = 0; i < handle->size(); i++) {
        auto nodeType = handle->at(i).value()->getNodeType();
        auto nextNodeType = handle->at(i+1).value_or(std::make_shared<ASTNullNode>())->getNodeType();
        if (i == 0) {
            dfa->init(nodeType);
        } else {
            dfa->determine(nodeType);
        }

        if (handle->hasOneAndOnlyNode()) {
            dfa->determine(AST_ANY_NODE);
        }

        auto currentDfaState = dfa->getCurrentState();
        if (currentDfaState && currentDfaState.value()->hasTargetAstNodeType()) {
            auto reduceCount = currentDfaState.value()->isAnyNode() && !handle->hasOneAndOnlyNode() ? i : i + 1;
            return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_REDUCE, reduceCount, currentDfaState.value()->getTargetAstNodeType().value());
        } else if (mode == RM_BACKTRACK && !currentDfaState) {
            return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_POP);
        } else if (mode == RM_NORMAL && !currentDfaState) {
            return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_SHIFT);
        }
    }
    return std::make_shared<RecognizerResult>(RECOGNIZER_ACTION_SHIFT);
}

RecognizerMode Recognizer::determineMode(Handle* handle) {
    if (isBacktrackNode(handle->last())) {
        return RM_BACKTRACK;
    }
    return RM_NORMAL;
}

bool Recognizer::isBacktrackNode(std::optional<std::shared_ptr<ASTNode>> astNode) {
    return astNode.has_value() && astNode.value()->isOneOf({
                                                                   AST_TERMINATOR_NODE,
                                                                   AST_RIGHT_BRACKET_NODE,
                                                                   AST_ARRAY_TYPE_END_NODE,
                                                                   AST_GROUP_END_NODE,
                                                                   AST_STRUCT_END_NODE,
                                                                   AST_STRUCT_TYPE_END_NODE,
                                                                   AST_TUPLE_TYPE_END_NODE,
                                                                   AST_INTERFACE_PROPERTY_LIST_NODE,
                                                                   AST_INTERFACE_END_NODE,
                                                                   AST_FUNCTION_BLOCK_NODE,
                                                                   AST_FUNCTION_PARAMETER_LIST_END_NODE,
                                                                   AST_FUNCTION_ARGUMENT_LIST_END_NODE,
                                                                   AST_ENUM_KEY_VALUE_LIST_NODE,
                                                                   AST_ENUM_KEY_VALUE_LIST_END_NODE,
                                                                   AST_TUPLE_LIST_END_NODE,
                                                                   AST_TYPE_PARAMETER_LIST_END_NODE,
                                                                   AST_LAMBDA_TYPE_PARAMETER_LIST_END_NODE,
                                                                   AST_MODULE_LIST_NODE,
                                                                   AST_MODULE_LIST_END_NODE,
                                                                   AST_MODULE_ALIAS_NAME_NODE,
                                                                   AST_IMPORT_MODULE_LIST_NODE,
                                                                   AST_IMPORT_MODULE_LIST_END_NODE,
                                                                   AST_IMPORT_MODULE_ALIAS_NAME_NODE,
                                                                   AST_CONTROL_FLOW_BLOCK_NODE,
                                                                   AST_CONTROL_FLOW_START_NODE,
                                                                   AST_ASSIGNMENT_OPERATOR_NODE,
                                                                   AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE,
                                                                   AST_IMPORT_PATH_NODE,
                                                                   AST_IMPORT_WILDCARD_NODE,
                                                                   AST_CLASS_BLOCK_END_NODE,
                                                                   AST_CLASS_BLOCK_NODE,
                                                                   AST_IMPLEMENTS_INTERFACE_NAME_LAST_NODE
    });
}

bool Recognizer::isEndNode(std::optional<std::shared_ptr<ASTNode>> lastReducedNode, std::optional<std::shared_ptr<ASTNode>> peekNode) {
    if (lastReducedNode &&
        lastReducedNode.value()->isOneOf({
             AST_BLOCK_NODE,
             AST_ENUM_KEY_VALUE_LIST_NODE,
             AST_INTERFACE_PROPERTY_LIST_NODE,
             AST_MODULE_LIST_NODE,
             AST_IMPORT_MODULE_LIST_NODE,
             AST_ELSE_BLOCK_NODE,
             AST_FINALLY_BLOCK_NODE,
             AST_CLASS_BLOCK_NODE,
             AST_LAMBDA_RETURN_EXPRESSION_NODE,
             AST_TYPE_PARAMETER_LIST_NODE
        })) {
        return true;
    } else if (lastReducedNode &&
        lastReducedNode.value()->isOneOf({ AST_IF_BLOCK_NODE, AST_ELSE_IF_BLOCK_NODE }) &&
        (!peekNode || !peekNode.value()->is(AST_ELSE_NODE))) {
        return true;
    } else if (lastReducedNode &&
                lastReducedNode.value()->isOneOf({ AST_CATCH_BLOCK_NODE }) &&
                (!peekNode || !peekNode.value()->is(AST_FINALLY_NODE))) {
        return true;
    }

    return false;
}