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

std::optional<ReduceNode*> SyntaxDfa::recognize(Handle handle) {
    if (handle.isEmpty()) {
        return {};
    }
    for (int i = 0; i < handle.size(); i++) {
        auto nodeType = handle.at(i).value()->getNodeType();
        if (i == 0) {
            _dfa->init(nodeType);
        } else {
            _dfa->determine(handle.at(i).value()->getNodeType());
        }

        auto currentDfaState = _dfa->getCurrentState();
        if (currentDfaState && currentDfaState.value()->isEnd()) {
            return new ReduceNode(i + 1);
        } else if (!currentDfaState) {
            return {};
        }
    }

}

DFA* SyntaxDfa::getDFA() {
    return _dfa;
}


void SyntaxDfa::init() {
    auto varDeclarationDFANode = DFANodeFactory::createVarDeclarationDFANode();
    auto varInitDFANode = DFANodeFactory::createVarInitDFANode();
    auto varTypeDFANode = DFANodeFactory::createVarTypeDFANode();
    auto varIdentifierDFANode = DFANodeFactory::createVarIdentifierDFANode();
    auto assignmentOperatorDFANode = DFANodeFactory::createAssignmentOperatorDFANode();
    auto startIdentifierDFANode = DFANodeFactory::createStartIdentifierDFANode();
    auto identifierDFANode = DFANodeFactory::createIdentifierDFANode();
    auto endIdentifierDFANode = DFANodeFactory::createEndIdentifierDFANode();
    auto intLiteralDFANode = DFANodeFactory::createIntLiteralDFANode();
    auto floatLiteralDFANode = DFANodeFactory::createFloatLiteralDFANode();
    auto stringLiteralDFANode = DFANodeFactory::createStringLiteralDFANode();
    auto charLiteralDFANode = DFANodeFactory::createCharLiteralDFANode();
    auto booleanLiteralDFANode = DFANodeFactory::createBooleanLiteralDFANode();
    auto terminatorDFANode = DFANodeFactory::createTerminatorDFANode();
    auto binaryOperatorDFANode = DFANodeFactory::createBinaryOperatorDFANode();
    auto logicalOperatorDFANode = DFANodeFactory::createLogicalOperatorDFANode();
    auto unaryOperatorDFANode = DFANodeFactory::createUnaryOperatorDFANode();
    auto groupStartDFANode = DFANodeFactory::createGroupStartDFANode();
    auto groupEndDFANode = DFANodeFactory::createGroupEndDFANode();
    auto startExpressionDFANode = DFANodeFactory::createStartExpressionDFANode();
    auto expressionDFANode = DFANodeFactory::createExpressionDFANode();
    auto endExpressionDFANode = DFANodeFactory::createEndExpressionDFANode();
    auto startBinaryExpressionDFANode = DFANodeFactory::createStartBinaryExpressionDFANode();
    auto binaryExpressionDFANode = DFANodeFactory::createBinaryExpressionDFANode();
    auto endBinaryExpressionDFANode = DFANodeFactory::createEndBinaryExpressionDFANode();
    auto startLogicalExpressionDFANode = DFANodeFactory::createStartLogicalExpressionDFANode();
    auto logicalExpressionDFANode = DFANodeFactory::createLogicalExpressionDFANode();
    auto endLogicalExpressionDFANode = DFANodeFactory::createEndLogicalExpressionDFANode();
    auto startUnaryExpressionDFANode = DFANodeFactory::createStartUnaryExpressionDFANode();
    auto unaryExpressionDFANode = DFANodeFactory::createUnaryExpressionDFANode();
    auto endUnaryExpressionDFANode = DFANodeFactory::createEndUnaryExpressionDFANode();

    // setup transitions
    varTypeDFANode
    ->addTransition(DFATransitionFactory::create(varIdentifierDFANode));

    varIdentifierDFANode
    ->addTransition(DFATransitionFactory::create(assignmentOperatorDFANode));

    varInitDFANode
    ->addTransition(DFATransitionFactory::create(endIdentifierDFANode))
    ->addTransition(DFATransitionFactory::create(endExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endBinaryExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endLogicalExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endUnaryExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(intLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(floatLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(charLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(stringLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(booleanLiteralDFANode));

    startIdentifierDFANode
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(binaryOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(terminatorDFANode));

    intLiteralDFANode
    ->addTransition(DFATransitionFactory::create(binaryOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(groupEndDFANode))
    ->addTransition(DFATransitionFactory::create(terminatorDFANode));

    floatLiteralDFANode
    ->addTransition(DFATransitionFactory::create(binaryOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(groupEndDFANode))
    ->addTransition(DFATransitionFactory::create(terminatorDFANode));

    charLiteralDFANode
    ->addTransition(DFATransitionFactory::create(binaryOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(groupEndDFANode))
    ->addTransition(DFATransitionFactory::create(terminatorDFANode));

    stringLiteralDFANode
    ->addTransition(DFATransitionFactory::create(terminatorDFANode))
    ->addTransition(DFATransitionFactory::create(binaryOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(groupEndDFANode))
    ->addTransition(DFATransitionFactory::create(terminatorDFANode));

    booleanLiteralDFANode
    ->addTransition(DFATransitionFactory::create(binaryOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(logicalOperatorDFANode))
    ->addTransition(DFATransitionFactory::create(groupEndDFANode))
    ->addTransition(DFATransitionFactory::create(terminatorDFANode));

    binaryOperatorDFANode
    ->addTransition(DFATransitionFactory::create(groupStartDFANode))
    ->addTransition(DFATransitionFactory::create(endIdentifierDFANode))
    ->addTransition(DFATransitionFactory::create(endExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endBinaryExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endLogicalExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endUnaryExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(intLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(floatLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(stringLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(charLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(booleanLiteralDFANode));

    logicalOperatorDFANode
    ->addTransition(DFATransitionFactory::create(groupStartDFANode))
    ->addTransition(DFATransitionFactory::create(endIdentifierDFANode))
    ->addTransition(DFATransitionFactory::create(endExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endBinaryExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endLogicalExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endUnaryExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(intLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(floatLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(stringLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(charLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(booleanLiteralDFANode));

    unaryOperatorDFANode
    ->addTransition(DFATransitionFactory::create(groupStartDFANode))
    ->addTransition(DFATransitionFactory::create(endIdentifierDFANode))
    ->addTransition(DFATransitionFactory::create(endExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endBinaryExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endLogicalExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(endUnaryExpressionDFANode))
    ->addTransition(DFATransitionFactory::create(intLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(floatLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(stringLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(charLiteralDFANode))
    ->addTransition(DFATransitionFactory::create(booleanLiteralDFANode));


    _dfa
    ->insertStartNode(varDeclarationDFANode->getNodeType(), varDeclarationDFANode)
    ->insertStartNode(varTypeDFANode->getNodeType(), varTypeDFANode)
    ->insertStartNode(varInitDFANode->getNodeType(), varInitDFANode)
    ->insertStartNode(startIdentifierDFANode->getNodeType(), startIdentifierDFANode)
    ->insertStartNode(unaryOperatorDFANode->getNodeType(), unaryOperatorDFANode)
    ->insertStartNode(groupStartDFANode->getNodeType(), groupStartDFANode)
    ->insertStartNode(startExpressionDFANode->getNodeType(), startExpressionDFANode)
    ->insertStartNode(startBinaryExpressionDFANode->getNodeType(), startBinaryExpressionDFANode)
    ->insertStartNode(startLogicalExpressionDFANode->getNodeType(), startLogicalExpressionDFANode)
    ->insertStartNode(startUnaryExpressionDFANode->getNodeType(), startUnaryExpressionDFANode);

}