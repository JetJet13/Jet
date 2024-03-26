//
// Created by Johny Georges on 2024-03-23.
//

#include "recognizer.h"
#include "../../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"

Recognizer::Recognizer() {
    _syntaxDfa = new SyntaxDfa();
}

RecognizerResult* Recognizer::recognize(Handle* handle) {
    auto mode = this->determineMode(handle);
    auto predecessor = handle->getPrevNodeFor(0);
    auto successor = handle->getNextNodeFor(0);
    auto startNode = _syntaxDfa->findStartNode(handle->first());

    if (handle->isEmpty() && this->isEndNode(handle->getLastReducedNode())) {
        return new RecognizerResult(RECOGNIZER_ACTION_POP);
    } else if (handle->isArrayEnclosed()) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_ARRAY_NODE);
    } else if (handle->isStructEnclosed()) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_STRUCT_EXPRESSION_NODE);
    } else if (handle->isFunctionParameterListEnclosed()) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_FUNCTION_PARAMETER_LIST_NODE);
    } else if (handle->isFunctionArgumentListEnclosed()) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_FUNCTION_ARGUMENT_LIST_NODE);
    } else if (handle->isEnumKeyValueListEnclosed()) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_ENUM_KEY_VALUE_LIST_NODE);
    }

    if (mode == RM_BACKTRACK) {
        if (handle->size() == 1) {
            return new RecognizerResult(RECOGNIZER_ACTION_POP);
        } else if (predecessor && successor && predecessor.value()->isSameNodeTypeAs(successor.value()) && predecessor.value()->isHigherPriorityThan(successor.value())) {
            return new RecognizerResult(RECOGNIZER_ACTION_POP);
        } else if (handle->first().has_value() && ASTNodeUtils::isExpressionNode(handle->first().value()) && !predecessor && successor && successor.value()->is(AST_TERMINATOR_NODE)) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, AST_EXPRESSION_STATEMENT_NODE);
        }
    }

    if (mode == RM_NORMAL) {
        if (startNode && startNode.value()->alwaysReduceSelf()) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, handle->first().value()->getNodeType());
        }

        if (startNode && successor && startNode.value()->shouldReduceSelfFor(successor.value()->getNodeType())) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, handle->first().value()->getNodeType());
        }
    }

    if (startNode && predecessor && startNode.value()->shouldReduceToTargetWhenPrevNodeIs(predecessor.value()->getNodeType())) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, startNode.value()->getReduceTargetForPrevNode(predecessor.value()->getNodeType()).value());
    } else if (startNode && successor && startNode.value()->shouldReduceToTargetWhenNextNodeIs(successor.value()->getNodeType())) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, startNode.value()->getReduceTargetForNextNode(successor.value()->getNodeType()).value());
    } else if (startNode && predecessor && startNode.value()->shouldBacktrackTo(predecessor.value()->getNodeType())) {
        return new RecognizerResult(RECOGNIZER_ACTION_POP);
    }
    auto dfa = _syntaxDfa->getDFA();
    for (int i = 0; i < handle->size(); i++) {
        auto nodeType = handle->at(i).value()->getNodeType();
        if (i == 0) {
            dfa->init(nodeType);
        } else {
            dfa->determine(nodeType);
        }

        auto currentDfaState = dfa->getCurrentState();
        if (currentDfaState && currentDfaState.value()->hasTargetAstNodeType()) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, i + 1, currentDfaState.value()->getTargetAstNodeType().value());
        } else if (mode == RM_BACKTRACK && !currentDfaState) {
            return new RecognizerResult(RECOGNIZER_ACTION_POP);
        } else if (mode == RM_NORMAL && !currentDfaState) {
            return new RecognizerResult(RECOGNIZER_ACTION_SHIFT);
        }
    }

    return new RecognizerResult(RECOGNIZER_ACTION_SHIFT);
}

RecognizerMode Recognizer::determineMode(Handle* handle) {
    if (isBacktrackNode(handle->last())) {
        return RM_BACKTRACK;
    }
    return RM_NORMAL;
}

bool Recognizer::isBacktrackNode(std::optional<ASTNode*> astNode) {
    return astNode.has_value() && astNode.value()->isOneOf({
        AST_TERMINATOR_NODE,
        AST_RIGHT_BRACKET_NODE,
        AST_GROUP_END_NODE,
        AST_STRUCT_END_NODE,
        AST_FUNCTION_BLOCK_NODE,
        AST_FUNCTION_PARAMETER_LIST_END_NODE,
        AST_FUNCTION_ARGUMENT_LIST_END_NODE,
        AST_ENUM_KEY_VALUE_LIST_NODE,
        AST_ENUM_KEY_VALUE_LIST_END_NODE
    });
}

bool Recognizer::isEndNode(std::optional<ASTNode*> astNode) {
    return astNode.has_value() && astNode.value()->isOneOf({ AST_BLOCK_NODE, AST_ENUM_KEY_VALUE_LIST_NODE });
}