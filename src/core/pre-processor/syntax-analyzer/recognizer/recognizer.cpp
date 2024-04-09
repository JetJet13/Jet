//
// Created by Johny Georges on 2024-03-23.
//

#include "recognizer.h"
#include "../../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../ast/ast-nodes/ast-null-node.h"
#include "../../../../shared/utils/logger/logger.h"

Recognizer::Recognizer() {
    _syntaxDfa = new SyntaxDfa();
}

RecognizerResult* Recognizer::recognize(Handle* handle) {
    auto mode = this->determineMode(handle);
    auto predecessor = handle->getPrevNodeFor(0);
    auto successor = handle->getNextNodeFor(0);
    auto startNode = _syntaxDfa->findStartNode(handle->first());

    if (handle->isEmpty() && this->isEndNode(handle->getLastReducedNode(), handle->getPeekNode())) {
        Logger::log("found end node...popping");
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
    } else if (handle->isTupleListEnclosed()) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_TUPLE_LIST_NODE);
    } else if (handle->isLambdaTypeParameterListEnclosed()) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, handle->size(), AST_TYPE_PARAMETER_LIST_NODE);
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

    if (startNode && predecessor && successor && startNode.value()->shouldReduceToTargetWhenPrevNodeAndNextNodeIs(predecessor.value()->getNodeType(), successor.value()->getNodeType())) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, startNode.value()->getReduceTargetForPrevNodeAndNextNode(predecessor.value()->getNodeType(), successor.value()->getNodeType()).value());
    } else if (startNode && predecessor && startNode.value()->shouldReduceToTargetWhenPrevNodeIs(predecessor.value()->getNodeType())) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, startNode.value()->getReduceTargetForPrevNode(predecessor.value()->getNodeType()).value());
    } else if (startNode && successor && startNode.value()->shouldReduceToTargetWhenNextNodeIs(successor.value()->getNodeType())) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, startNode.value()->getReduceTargetForNextNode(successor.value()->getNodeType()).value());
    } else if (startNode && predecessor && startNode.value()->shouldBacktrackTo(predecessor.value()->getNodeType())) {
        return new RecognizerResult(RECOGNIZER_ACTION_POP);
    }
    auto dfa = _syntaxDfa->getDFA();
    dfa->reset();
    for (int i = 0; i < handle->size(); i++) {
        auto nodeType = handle->at(i).value()->getNodeType();
        auto nextNodeType = handle->at(i+1).value_or(new ASTNullNode())->getNodeType();
        if (i == 0) {
            dfa->init(nodeType);
        } else {
            dfa->determine(nodeType, nextNodeType);
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

    if (dfa->getCurrentState()) {
        auto nilTransition = dfa->getCurrentState().value()->findNilTransition();
        while (nilTransition.has_value()) {
            auto nextTransition = nilTransition.value()->findNilTransition();
            if (!nextTransition) {
                break;
            }
            nilTransition = nextTransition;
        }

        if (nilTransition && nilTransition.value()->hasTargetAstNodeType()) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, handle->size(), nilTransition.value()->getTargetAstNodeType().value());
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
                                                                   AST_ENUM_KEY_VALUE_LIST_END_NODE,
                                                                   AST_TUPLE_LIST_END_NODE,
                                                                   AST_TYPE_PARAMETER_LIST_END_NODE,
                                                                   AST_CONTROL_FLOW_BLOCK_NODE,
                                                                   AST_CONTROL_FLOW_START_NODE,
    });
}

bool Recognizer::isEndNode(std::optional<ASTNode*> lastReducedNode, std::optional<ASTNode*> peekNode) {
    if (lastReducedNode &&
        lastReducedNode.value()->isOneOf({
                                                 AST_BLOCK_NODE,
                                                 AST_ENUM_KEY_VALUE_LIST_NODE,
                                                 AST_ELSE_BLOCK_NODE,
                                                 AST_FINALLY_BLOCK_NODE,
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