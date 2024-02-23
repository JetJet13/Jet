//
// Created by Johny Georges on 2024-02-15.
//

#include "dfa-node-factory.h"

namespace DFANodeFactory {

    DFANode* createVarDeclarationDFANode() {
        return new DFANode(AST_VARIABLE_DECLARATION_NODE, true, true, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createVarInitDFANode() {
        return new DFANode(AST_VARIABLE_INIT_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createVarTypeDFANode() {
        return new DFANode(AST_VARIABLE_TYPE_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createVarIdentifierDFANode() {
        return new DFANode(AST_IDENTIFIER_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createEndAssignmentOperatorDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_ASSIGNMENT_OPERATOR_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStartIdentifierDFANode() {
        return new DFANode(AST_IDENTIFIER_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createIdentifierDFANode() {
        return new DFANode(AST_IDENTIFIER_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndIdentifierDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_IDENTIFIER_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStartIntLiteralDFANode() {
        return new DFANode(AST_INT_LITERAL_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createIntLiteralDFANode() {
        return new DFANode(AST_INT_LITERAL_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createEndIntLiteralDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_INT_LITERAL_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStartFloatLiteralDFANode() {
        return new DFANode(AST_FLOAT_LITERAL_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createFloatLiteralDFANode() {
        return new DFANode(AST_FLOAT_LITERAL_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createEndFloatLiteralDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_FLOAT_LITERAL_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStartStringLiteralDFANode() {
        return new DFANode(AST_STRING_LITERAL_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createStringLiteralDFANode() {
        return new DFANode(AST_STRING_LITERAL_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createEndStringLiteralDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_STRING_LITERAL_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStartCharLiteralDFANode() {
        return new DFANode(AST_CHAR_LITERAL_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createCharLiteralDFANode() {
        return new DFANode(AST_CHAR_LITERAL_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createEndCharLiteralDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_CHAR_LITERAL_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStartBooleanLiteralDFANode() {
        return new DFANode(AST_BOOLEAN_LITERAL_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createBooleanLiteralDFANode() {
        return new DFANode(AST_BOOLEAN_LITERAL_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createEndBooleanLiteralDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_BOOLEAN_LITERAL_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createTerminatorDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_TERMINATOR_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStarOperatorDFANode() {
        return new DFANode(AST_STAR_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createSlashOperatorDFANode() {
        return new DFANode(AST_SLASH_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createModuloOperatorDFANode() {
        return new DFANode(AST_MODULO_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createGreaterThanOperatorDFANode() {
        return new DFANode(AST_GREATER_THAN_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createGreaterThanOrEqualOperatorDFANode() {
        return new DFANode(AST_GREATER_THAN_OR_EQUAL_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createLessThanOperatorDFANode() {
        return new DFANode(AST_LESS_THAN_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createLessThanOrEqualOperatorDFANode() {
        return new DFANode(AST_LESS_THAN_OR_EQUAL_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createLogicalOperatorDFANode() {
        return new DFANode(AST_LOGICAL_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createEqualityOperatorDFANode() {
        return new DFANode(AST_EQUALITY_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createInequalityOperatorDFANode() {
        return new DFANode(AST_INEQUALITY_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createStartBangOperatorDFANode() {
        return new DFANode(AST_BANG_OPERATOR_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createBangOperatorDFANode() {
        return new DFANode(AST_BANG_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createStartPlusOperatorDFANode() {
        return new DFANode(AST_PLUS_OPERATOR_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createPlusOperatorDFANode() {
        return new DFANode(AST_PLUS_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createStartMinusOperatorDFANode() {
        return new DFANode(AST_MINUS_OPERATOR_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createMinusOperatorDFANode() {
        return new DFANode(AST_MINUS_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createGroupStartDFANode() {
        return new DFANode(AST_GROUP_START_NODE, true, true, DFA_OCCURRENCE_ONCE_OR_MORE, AST_GROUP_START_NODE);
    }
    DFANode* createGroupEndDFANode() {
        return new DFANode(AST_GROUP_END_NODE, true, true, DFA_OCCURRENCE_ONCE_OR_MORE, AST_GROUP_END_NODE);
    }
    DFANode* createStartExpressionDFANode() {
        return new DFANode(AST_EXPRESSION_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createExpressionDFANode() {
        return new DFANode(AST_EXPRESSION_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndExpressionDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_EXPRESSION_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStartLiteralExpressionDFANode() {
        return new DFANode(AST_LITERAL_EXPRESSION_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createLiteralExpressionDFANode() {
        return new DFANode(AST_LITERAL_EXPRESSION_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndLiteralExpressionDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_LITERAL_EXPRESSION_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStartIdentifierExpressionDFANode() {
        return new DFANode(AST_IDENTIFIER_EXPRESSION_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createIdentifierExpressionDFANode() {
        return new DFANode(AST_IDENTIFIER_EXPRESSION_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndIdentifierExpressionDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_IDENTIFIER_EXPRESSION_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStartBinaryExpressionDFANode() {
        return new DFANode(AST_BINARY_EXPRESSION_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createBinaryExpressionDFANode() {
        return new DFANode(AST_BINARY_EXPRESSION_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndBinaryExpressionDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_BINARY_EXPRESSION_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStartLogicalExpressionDFANode() {
        return new DFANode(AST_LOGICAL_EXPRESSION_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createLogicalExpressionDFANode() {
        return new DFANode(AST_LOGICAL_EXPRESSION_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndLogicalExpressionDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_LOGICAL_EXPRESSION_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }
    DFANode* createStartUnaryExpressionDFANode() {
        return new DFANode(AST_UNARY_EXPRESSION_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createUnaryExpressionDFANode() {
        return new DFANode(AST_UNARY_EXPRESSION_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndUnaryExpressionDFANode(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_UNARY_EXPRESSION_NODE, false, true, DFA_OCCURRENCE_ONCE, targetAstNodeType);
    }

}