//
// Created by Johny Georges on 2024-02-14.
//

#include "syntax-dfa.h"
#include "../../../dfa/dfa-node-factory.h"
#include "../../../dfa/dfa-transition-factory.h"
#include "../../../../shared/utils/logger/logger.h"

SyntaxDfa::SyntaxDfa() {
    _dfa = new DFA();
    this->init();
}

RecognizerResult* SyntaxDfa::recognize(Handle handle) {
    if (handle.isTerminatorOnlyNode()) {
        return new RecognizerResult(RECOGNIZER_ACTION_POP);
    } else if (handle.isEmpty()) {
        return new RecognizerResult(RECOGNIZER_ACTION_SHIFT);
    } else if (!handle.isTerminatorMode()) {
        auto startNode = _dfa->findStartNode(handle.first().value()->getNodeType());
        if (startNode && startNode.value()->alwaysReduceSelf()) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, handle.first().value()->getNodeType());
        }

        auto successor = handle.getNextNodeFor(0);
        if (successor && _dfa->isValidSuccessorForNode(handle.first().value()->getNodeType(), successor.value()->getNodeType())) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, handle.first().value()->getNodeType());
        }
    }

    auto predecessor = handle.getPrevNodeFor(0);
    if (predecessor && _dfa->isValidPredecessorForNode(handle.first().value()->getNodeType(), predecessor.value()->getNodeType())) {
        return new RecognizerResult(RECOGNIZER_ACTION_POP);
    }
    for (int i = 0; i < handle.size(); i++) {
        auto nodeType = handle.at(i).value()->getNodeType();
        if (i == 0) {
            _dfa->init(nodeType);
        } else {
            _dfa->determine(nodeType);
        }

        auto currentDfaState = _dfa->getCurrentState();
        if (currentDfaState && currentDfaState.value()->hasTargetAstNodeType()) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, i + 1, currentDfaState.value()->getTargetAstNodeType().value());
        } else if (handle.isTerminatorMode() && !currentDfaState) {
            return new RecognizerResult(RECOGNIZER_ACTION_POP);
        } else if (!currentDfaState) {
            return new RecognizerResult(RECOGNIZER_ACTION_SHIFT);
        }
    }

    return new RecognizerResult(RECOGNIZER_ACTION_SHIFT);
}

DFA* SyntaxDfa::getDFA() {
    return _dfa;
}

void SyntaxDfa::init() {

    DFANode* varDeclaration = DFANodeFactory::Once::createWithTarget(AST_VARIABLE_DECLARATION_NODE, AST_VARIABLE_DECLARATION_NODE);
    DFANode* varInit = DFANodeFactory::Once::create(AST_VARIABLE_INIT_NODE);
    DFANode* varType = DFANodeFactory::Once::create(AST_VARIABLE_TYPE_NODE);
    DFANode* identifierExpression = DFANodeFactory::Once::create(AST_IDENTIFIER_EXPRESSION_NODE);
    DFANode* literalExpression = DFANodeFactory::Once::create(AST_LITERAL_EXPRESSION_NODE);
    DFANode* logicalOperator = DFANodeFactory::Once::create(AST_LOGICAL_OPERATOR_NODE);
    DFANode* binaryExpression = DFANodeFactory::Once::create(AST_BINARY_EXPRESSION_NODE);
    DFANode* logicalExpression = DFANodeFactory::Once::create(AST_LOGICAL_EXPRESSION_NODE);
    DFANode* unaryExpression = DFANodeFactory::Once::create(AST_UNARY_EXPRESSION_NODE);
    DFANode* binaryOperator = DFANodeFactory::Once::create(AST_BINARY_OPERATOR_NODE);
    DFANode* unaryOperator = DFANodeFactory::Once::create(AST_UNARY_OPERATOR_NODE);


    this->initVarType(varType);
    this->initVarInit(varInit);

    logicalOperator
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)));

    binaryOperator
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)));

    unaryOperator
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)));

    identifierExpression
            ->addTransition(DFATransitionFactory::create(logicalOperator))
            ->addTransition(DFATransitionFactory::create(binaryOperator));

    literalExpression
            ->addTransition(DFATransitionFactory::create(logicalOperator))
            ->addTransition(DFATransitionFactory::create(binaryOperator));

    binaryExpression
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator));

    logicalExpression
    ->addTransition(DFATransitionFactory::create(logicalOperator));

    unaryExpression
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator));

    _dfa
    ->insertStartNode(varDeclaration->getNodeType(), varDeclaration)
    ->insertStartNode(varType->getNodeType(), varType)
    ->insertStartNode(varInit->getNodeType(), varInit)
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(identifierExpression)
    ->insertStartNode(literalExpression)
    ->insertStartNode(binaryExpression)
    ->insertStartNode(logicalExpression)
    ->insertStartNode(unaryExpression)
    ->insertStartNode(unaryOperator)
    ->insertStartNode(DFANodeFactory::Once::create(AST_BINARY_OPERATOR_NODE)
                      ->markAlwaysReduceSelf()
                      ->backtrackWhenLastReducedNodeIsOneOf({
                          AST_BINARY_EXPRESSION_NODE,
                          AST_UNARY_EXPRESSION_NODE,
                          AST_LITERAL_EXPRESSION_NODE,
                          AST_IDENTIFIER_EXPRESSION_NODE
                      }))
    ->insertStartNode(DFANodeFactory::Once::create(logicalOperator->getNodeType())
                      ->markAlwaysReduceSelf()
                      ->backtrackWhenLastReducedNodeIsOneOf({
                          AST_BINARY_EXPRESSION_NODE,
                          AST_UNARY_EXPRESSION_NODE,
                          AST_LITERAL_EXPRESSION_NODE,
                          AST_IDENTIFIER_EXPRESSION_NODE
                      }));
}

void SyntaxDfa::initVarType(DFANode* varTypeNode) {
    varTypeNode
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_IDENTIFIER_NODE)
                    ->addTransition(
                            DFATransitionFactory::create(
                                DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_VARIABLE_INIT_NODE)))
            )
    );
}

void SyntaxDfa::initVarInit(DFANode* varInitNode) {

    varInitNode
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)));

}