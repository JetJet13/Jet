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
    DFANode* createEndAssignmentOperatorDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStartIdentifierDFANode();
    DFANode* createIdentifierDFANode();
    DFANode* createEndIdentifierDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStartIntLiteralDFANode();
    DFANode* createIntLiteralDFANode();
    DFANode* createEndIntLiteralDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStartFloatLiteralDFANode();
    DFANode* createFloatLiteralDFANode();
    DFANode* createEndFloatLiteralDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStartStringLiteralDFANode();
    DFANode* createStringLiteralDFANode();
    DFANode* createEndStringLiteralDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStartCharLiteralDFANode();
    DFANode* createCharLiteralDFANode();
    DFANode* createEndCharLiteralDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStartBooleanLiteralDFANode();
    DFANode* createBooleanLiteralDFANode();
    DFANode* createEndBooleanLiteralDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStarOperatorDFANode();
    DFANode* createSlashOperatorDFANode();
    DFANode* createModuloOperatorDFANode();
    DFANode* createGreaterThanOperatorDFANode();
    DFANode* createGreaterThanOrEqualOperatorDFANode();
    DFANode* createLessThanOperatorDFANode();
    DFANode* createLessThanOrEqualOperatorDFANode();
    DFANode* createLogicalOperatorDFANode();
    DFANode* createEqualityOperatorDFANode();
    DFANode* createInequalityOperatorDFANode();
    DFANode* createStartBangOperatorDFANode();
    DFANode* createBangOperatorDFANode();
    DFANode* createStartPlusOperatorDFANode();
    DFANode* createPlusOperatorDFANode();
    DFANode* createMinusOperatorDFANode();
    DFANode* createStartMinusOperatorDFANode();
    DFANode* createGroupStartDFANode();
    DFANode* createGroupEndDFANode();
    DFANode* createStartExpressionDFANode();
    DFANode* createExpressionDFANode();
    DFANode* createEndExpressionDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStartLiteralExpressionDFANode();
    DFANode* createLiteralExpressionDFANode();
    DFANode* createEndLiteralExpressionDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStartIdentifierExpressionDFANode();
    DFANode* createIdentifierExpressionDFANode();
    DFANode* createEndIdentifierExpressionDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStartBinaryExpressionDFANode();
    DFANode* createBinaryExpressionDFANode();
    DFANode* createEndBinaryExpressionDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStartLogicalExpressionDFANode();
    DFANode* createLogicalExpressionDFANode();
    DFANode* createEndLogicalExpressionDFANode(ASTNodeType targetAstNodeType);
    DFANode* createStartUnaryExpressionDFANode();
    DFANode* createUnaryExpressionDFANode();
    DFANode* createEndUnaryExpressionDFANode(ASTNodeType targetAstNodeType);
}

#endif //JETLANG_DFA_NODE_FACTORY_H
