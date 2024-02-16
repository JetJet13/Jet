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
    DFANode* createAssignmentOperatorDFANode() {
        return new DFANode(AST_ASSIGNMENT_OPERATOR_NODE, false, true, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createStartIdentifierDFANode() {
        return new DFANode(AST_IDENTIFIER_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createIdentifierDFANode() {
        return new DFANode(AST_IDENTIFIER_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndIdentifierDFANode() {
        return new DFANode(AST_IDENTIFIER_NODE, false, true, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createIntLiteralDFANode() {
        return new DFANode(AST_INT_LITERAL_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createFloatLiteralDFANode() {
        return new DFANode(AST_FLOAT_LITERAL_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createStringLiteralDFANode() {
        return new DFANode(AST_STRING_LITERAL_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createCharLiteralDFANode() {
        return new DFANode(AST_CHAR_LITERAL_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createBooleanLiteralDFANode() {
        return new DFANode(AST_BOOLEAN_LITERAL_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createTerminatorDFANode() {
        return new DFANode(AST_TERMINATOR_NODE, false, true, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createBinaryOperatorDFANode() {
        return new DFANode(AST_BINARY_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createLogicalOperatorDFANode() {
        return new DFANode(AST_LOGICAL_OPERATOR_NODE, false, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createUnaryOperatorDFANode() {
        return new DFANode(AST_UNARY_OPERATOR_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createGroupStartDFANode() {
        return new DFANode(AST_GROUP_START_NODE, true, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createGroupEndDFANode() {
        return new DFANode(AST_GROUP_END_NODE, false, true, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createStartExpressionDFANode() {
        return new DFANode(AST_EXPRESSION_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createExpressionDFANode() {
        return new DFANode(AST_EXPRESSION_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndExpressionDFANode() {
        return new DFANode(AST_EXPRESSION_NODE, false, true, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createStartBinaryExpressionDFANode() {
        return new DFANode(AST_BINARY_EXPRESSION_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createBinaryExpressionDFANode() {
        return new DFANode(AST_BINARY_EXPRESSION_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndBinaryExpressionDFANode() {
        return new DFANode(AST_BINARY_EXPRESSION_NODE, false, true, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createStartLogicalExpressionDFANode() {
        return new DFANode(AST_LOGICAL_EXPRESSION_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createLogicalExpressionDFANode() {
        return new DFANode(AST_LOGICAL_EXPRESSION_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndLogicalExpressionDFANode() {
        return new DFANode(AST_LOGICAL_EXPRESSION_NODE, false, true, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createStartUnaryExpressionDFANode() {
        return new DFANode(AST_UNARY_EXPRESSION_NODE, true, false, DFA_OCCURRENCE_ONCE);
    }
    DFANode* createUnaryExpressionDFANode() {
        return new DFANode(AST_UNARY_EXPRESSION_NODE, false, false, DFA_OCCURRENCE_ONCE_OR_MORE);
    }
    DFANode* createEndUnaryExpressionDFANode() {
        return new DFANode(AST_UNARY_EXPRESSION_NODE, false, true, DFA_OCCURRENCE_ONCE);
    }

}