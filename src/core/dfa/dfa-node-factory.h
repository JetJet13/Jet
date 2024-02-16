//
// Created by Johny Georges on 2024-02-15.
//

#ifndef JETLANG_DFA_NODE_FACTORY_H
#define JETLANG_DFA_NODE_FACTORY_H

#include "dfa-node.h"

namespace DFANodeFactory {
    DFANode* createVarDeclarationDFANode();
    DFANode* createVarInitDFANode();
    DFANode* createVarTypeDFANode();
    DFANode* createVarIdentifierDFANode();
    DFANode* createAssignmentOperatorDFANode();
    DFANode* createStartIdentifierDFANode();
    DFANode* createIdentifierDFANode();
    DFANode* createEndIdentifierDFANode();
    DFANode* createIntLiteralDFANode();
    DFANode* createFloatLiteralDFANode();
    DFANode* createStringLiteralDFANode();
    DFANode* createCharLiteralDFANode();
    DFANode* createBooleanLiteralDFANode();
    DFANode* createTerminatorDFANode();
    DFANode* createBinaryOperatorDFANode();
    DFANode* createLogicalOperatorDFANode();
    DFANode* createUnaryOperatorDFANode();
    DFANode* createGroupStartDFANode();
    DFANode* createGroupEndDFANode();
    DFANode* createStartExpressionDFANode();
    DFANode* createExpressionDFANode();
    DFANode* createEndExpressionDFANode();
    DFANode* createStartBinaryExpressionDFANode();
    DFANode* createBinaryExpressionDFANode();
    DFANode* createEndBinaryExpressionDFANode();
    DFANode* createStartLogicalExpressionDFANode();
    DFANode* createLogicalExpressionDFANode();
    DFANode* createEndLogicalExpressionDFANode();
    DFANode* createStartUnaryExpressionDFANode();
    DFANode* createUnaryExpressionDFANode();
    DFANode* createEndUnaryExpressionDFANode();
}

#endif //JETLANG_DFA_NODE_FACTORY_H
