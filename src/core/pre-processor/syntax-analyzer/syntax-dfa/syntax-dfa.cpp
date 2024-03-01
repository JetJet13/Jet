//
// Created by Johny Georges on 2024-02-14.
//

#include "syntax-dfa.h"
#include "../../../dfa/dfa-node-factory.h"
#include "../../../dfa/dfa-transition-factory.h"

SyntaxDfa::SyntaxDfa() {
    _dfa = new DFA();
    this->init();
}

RecognizerResult* SyntaxDfa::recognize(Handle handle) {
    if (handle.isTerminatorOnlyNode()) {
        return new RecognizerResult(RECOGNIZER_ACTION_POP);
    } else if (handle.isEmpty()) {
        return new RecognizerResult(RECOGNIZER_ACTION_SHIFT);
    }

    auto suffix = handle.getPeekNode();
    if (suffix && _dfa->isValidSuffixForNode(handle.first().value()->getNodeType(), suffix.value()->getNodeType())) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, handle.first().value()->getNodeType());
    }

    auto prefix = handle.getLastReducedNode();
    if (prefix && _dfa->isValidPrefixForNode(handle.first().value()->getNodeType(), prefix.value()->getNodeType())) {
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
        if (currentDfaState && currentDfaState.value()->isEnd() && currentDfaState.value()->getTargetAstNodeType()) {
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
    auto varDeclarationDFANode = DFANodeFactory::createVarDeclarationDFANode();
    auto varInitDFANode = DFANodeFactory::createVarInitDFANode();
    auto varTypeDFANode = DFANodeFactory::createVarTypeDFANode();
    auto varIdentifierDFANode = DFANodeFactory::createVarIdentifierDFANode();
    auto startIdentifierDFANode = DFANodeFactory::createStartIdentifierDFANode();
    auto identifierDFANode = DFANodeFactory::createIdentifierDFANode();
    auto intLiteralDFANode = DFANodeFactory::createIntLiteralDFANode();
    auto floatLiteralDFANode = DFANodeFactory::createFloatLiteralDFANode();
    auto stringLiteralDFANode = DFANodeFactory::createStringLiteralDFANode();
    auto charLiteralDFANode = DFANodeFactory::createCharLiteralDFANode();
    auto booleanLiteralDFANode = DFANodeFactory::createBooleanLiteralDFANode();
    auto starOperatorDFANode = DFANodeFactory::createStarOperatorDFANode();
    auto slashOperatorDFANode = DFANodeFactory::createSlashOperatorDFANode();
    auto moduloOperatorDFANode = DFANodeFactory::createModuloOperatorDFANode();
    auto greaterThanOperatorDFANode = DFANodeFactory::createGreaterThanOperatorDFANode();
    auto greaterThanOrEqualOperatorDFANode = DFANodeFactory::createGreaterThanOrEqualOperatorDFANode();
    auto lessThanOperatorDFANode = DFANodeFactory::createLessThanOperatorDFANode();
    auto lessThanOrEqualOperatorDFANode = DFANodeFactory::createLessThanOrEqualOperatorDFANode();
    auto logicalOperatorDFANode = DFANodeFactory::createLogicalOperatorDFANode();
    auto equalityOperatorDFANode = DFANodeFactory::createEqualityOperatorDFANode();
    auto inequalityOperatorDFANode = DFANodeFactory::createInequalityOperatorDFANode();
    auto startBangOperatorDFANode = DFANodeFactory::createStartBangOperatorDFANode();
    auto bangOperatorDFANode = DFANodeFactory::createBangOperatorDFANode();
    auto startPlusOperatorDFANode = DFANodeFactory::createStartPlusOperatorDFANode();
    auto plusOperatorDFANode = DFANodeFactory::createPlusOperatorDFANode();
    auto startMinusOperatorDFANode = DFANodeFactory::createStartMinusOperatorDFANode();
    auto minusOperatorDFANode = DFANodeFactory::createMinusOperatorDFANode();
    auto groupStartDFANode = DFANodeFactory::createGroupStartDFANode();
    auto groupEndDFANode = DFANodeFactory::createGroupEndDFANode();
    auto startExpressionDFANode = DFANodeFactory::createStartExpressionDFANode();
    auto expressionDFANode = DFANodeFactory::createExpressionDFANode();
    auto endExpressionDFANode = DFANodeFactory::createEndExpressionDFANode(AST_VARIABLE_DECLARATION_NODE);
    auto startLiteralExpressionDFANode = DFANodeFactory::createStartLiteralExpressionDFANode();
    auto literalExpressionDFANode = DFANodeFactory::createLiteralExpressionDFANode();
    auto startBinaryExpressionDFANode = DFANodeFactory::createStartBinaryExpressionDFANode();
    auto binaryExpressionDFANode = DFANodeFactory::createBinaryExpressionDFANode();
    auto startLogicalExpressionDFANode = DFANodeFactory::createStartLogicalExpressionDFANode();
    auto logicalExpressionDFANode = DFANodeFactory::createLogicalExpressionDFANode();
    auto startUnaryExpressionDFANode = DFANodeFactory::createStartUnaryExpressionDFANode();
    auto unaryExpressionDFANode = DFANodeFactory::createUnaryExpressionDFANode();

    // setup transitions
    varTypeDFANode
    ->addTransition(DFATransitionFactory::create(varIdentifierDFANode));

    varIdentifierDFANode
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndAssignmentOperatorDFANode(AST_VARIABLE_INIT_NODE)));

    varInitDFANode
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndExpressionDFANode(AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierExpressionDFANode(AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLogicalExpressionDFANode(AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndStringLiteralDFANode(AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndCharLiteralDFANode(AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBooleanLiteralDFANode(AST_VARIABLE_DECLARATION_NODE)));

    startIdentifierDFANode
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(plusOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(minusOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(starOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(slashOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(moduloOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(greaterThanOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(greaterThanOrEqualOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(lessThanOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(lessThanOrEqualOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(equalityOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(inequalityOperatorDFANode));

    intLiteralDFANode
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(plusOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(minusOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(starOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(slashOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(moduloOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(greaterThanOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(greaterThanOrEqualOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(lessThanOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(lessThanOrEqualOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(equalityOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(inequalityOperatorDFANode));

    floatLiteralDFANode
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(plusOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(minusOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(starOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(slashOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(moduloOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(greaterThanOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(greaterThanOrEqualOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(lessThanOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(lessThanOrEqualOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(equalityOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(inequalityOperatorDFANode));

    charLiteralDFANode
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(equalityOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(inequalityOperatorDFANode));

    stringLiteralDFANode
    ->addTransition(DFATransitionFactory::create(plusOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(equalityOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(inequalityOperatorDFANode));

    booleanLiteralDFANode
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(equalityOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(inequalityOperatorDFANode));

    startBinaryExpressionDFANode
    ->addTransition(DFATransitionFactory::create(plusOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(minusOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(starOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(slashOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(moduloOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(slashOperatorDFANode));

    startLogicalExpressionDFANode
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode));

    startUnaryExpressionDFANode
    ->addTransition(DFATransitionFactory::create(plusOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(minusOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(starOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(slashOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(moduloOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode));


    logicalOperatorDFANode
    ->addPrefix(AST_BINARY_EXPRESSION_NODE)
    ->addPrefix(AST_UNARY_EXPRESSION_NODE)
    ->addPrefix(AST_LOGICAL_EXPRESSION_NODE)
    ->addTransition(DFATransitionFactory::create(bangOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndExpressionDFANode(AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLogicalExpressionDFANode(AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndStringLiteralDFANode(AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndCharLiteralDFANode(AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBooleanLiteralDFANode(AST_LOGICAL_EXPRESSION_NODE)));

    equalityOperatorDFANode
    ->addTransition(DFATransitionFactory::create(bangOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLogicalExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndStringLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndCharLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBooleanLiteralDFANode(AST_BINARY_EXPRESSION_NODE)));

    inequalityOperatorDFANode
    ->addTransition(DFATransitionFactory::create(bangOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLogicalExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndStringLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndCharLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBooleanLiteralDFANode(AST_BINARY_EXPRESSION_NODE)));

    greaterThanOperatorDFANode
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLogicalExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_BINARY_EXPRESSION_NODE)));

    greaterThanOrEqualOperatorDFANode
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLogicalExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_BINARY_EXPRESSION_NODE)));

    lessThanOperatorDFANode
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLogicalExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_BINARY_EXPRESSION_NODE)));

    lessThanOrEqualOperatorDFANode
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLogicalExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_BINARY_EXPRESSION_NODE)));

    plusOperatorDFANode
    ->addSuffix(AST_PLUS_OPERATOR_NODE)
    ->addSuffix(AST_MINUS_OPERATOR_NODE)
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndStringLiteralDFANode(AST_BINARY_EXPRESSION_NODE)));

    minusOperatorDFANode
    ->addSuffix(AST_PLUS_OPERATOR_NODE)
    ->addSuffix(AST_MINUS_OPERATOR_NODE)
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndStringLiteralDFANode(AST_BINARY_EXPRESSION_NODE)));

    starOperatorDFANode
    ->addPrefix(AST_BINARY_EXPRESSION_NODE)
    ->addPrefix(AST_UNARY_EXPRESSION_NODE)
    ->addSuffix(AST_PLUS_OPERATOR_NODE)
    ->addSuffix(AST_MINUS_OPERATOR_NODE)
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndStringLiteralDFANode(AST_BINARY_EXPRESSION_NODE)));

    slashOperatorDFANode
    ->addPrefix(AST_BINARY_EXPRESSION_NODE)
    ->addPrefix(AST_UNARY_EXPRESSION_NODE)
    ->addSuffix(AST_PLUS_OPERATOR_NODE)
    ->addSuffix(AST_MINUS_OPERATOR_NODE)
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndStringLiteralDFANode(AST_BINARY_EXPRESSION_NODE)));

    moduloOperatorDFANode
    ->addPrefix(AST_BINARY_EXPRESSION_NODE)
    ->addPrefix(AST_UNARY_EXPRESSION_NODE)
    ->addSuffix(AST_PLUS_OPERATOR_NODE)
    ->addSuffix(AST_MINUS_OPERATOR_NODE)
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndStringLiteralDFANode(AST_BINARY_EXPRESSION_NODE)));

    startBangOperatorDFANode
    ->addPrefix(AST_BINARY_EXPRESSION_NODE)
    ->addPrefix(AST_UNARY_EXPRESSION_NODE)
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndExpressionDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBinaryExpressionDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLogicalExpressionDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndUnaryExpressionDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndStringLiteralDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndCharLiteralDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndBooleanLiteralDFANode(AST_UNARY_EXPRESSION_NODE)));

    startPlusOperatorDFANode
    ->addPrefix(AST_BINARY_EXPRESSION_NODE)
    ->addPrefix(AST_UNARY_EXPRESSION_NODE)
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndExpressionDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierExpressionDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_UNARY_EXPRESSION_NODE)));

    startMinusOperatorDFANode
    ->addPrefix(AST_BINARY_EXPRESSION_NODE)
    ->addPrefix(AST_UNARY_EXPRESSION_NODE)
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndExpressionDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndLiteralExpressionDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierExpressionDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIdentifierDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndIntLiteralDFANode(AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createEndFloatLiteralDFANode(AST_UNARY_EXPRESSION_NODE)));

    _dfa
    ->insertStartNode(varDeclarationDFANode->getNodeType(), varDeclarationDFANode)
    ->insertStartNode(varTypeDFANode->getNodeType(), varTypeDFANode)
    ->insertStartNode(varInitDFANode->getNodeType(), varInitDFANode)
    ->insertStartNode(groupEndDFANode->getNodeType(), groupEndDFANode)
    ->insertStartNode(startIdentifierDFANode->getNodeType(), startIdentifierDFANode)
    ->insertStartNode(intLiteralDFANode->getNodeType(), intLiteralDFANode)
    ->insertStartNode(floatLiteralDFANode->getNodeType(), floatLiteralDFANode)
    ->insertStartNode(stringLiteralDFANode->getNodeType(), stringLiteralDFANode)
    ->insertStartNode(charLiteralDFANode->getNodeType(), charLiteralDFANode)
    ->insertStartNode(booleanLiteralDFANode->getNodeType(), booleanLiteralDFANode)
    ->insertStartNode(groupStartDFANode->getNodeType(), groupStartDFANode)
    ->insertStartNode(startExpressionDFANode->getNodeType(), startExpressionDFANode)
    ->insertStartNode(startLiteralExpressionDFANode->getNodeType(), startLiteralExpressionDFANode)
    ->insertStartNode(startBinaryExpressionDFANode->getNodeType(), startBinaryExpressionDFANode)
    ->insertStartNode(startLogicalExpressionDFANode->getNodeType(), startLogicalExpressionDFANode)
    ->insertStartNode(startUnaryExpressionDFANode->getNodeType(), startUnaryExpressionDFANode)
    ->insertStartNode(startBangOperatorDFANode->getNodeType(), startBangOperatorDFANode)
    ->insertStartNode(startPlusOperatorDFANode->getNodeType(), startPlusOperatorDFANode)
    ->insertStartNode(startMinusOperatorDFANode->getNodeType(), startMinusOperatorDFANode)
    ->insertStartNode(starOperatorDFANode->getNodeType(), starOperatorDFANode)
    ->insertStartNode(slashOperatorDFANode->getNodeType(), slashOperatorDFANode)
    ->insertStartNode(moduloOperatorDFANode->getNodeType(), moduloOperatorDFANode)
    ->insertStartNode(logicalOperatorDFANode->getNodeType(), logicalOperatorDFANode);
}