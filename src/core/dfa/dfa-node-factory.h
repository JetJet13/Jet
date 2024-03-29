//
// Created by Johny Georges on 2024-02-15.
//

#ifndef JETLANG_DFA_NODE_FACTORY_H
#define JETLANG_DFA_NODE_FACTORY_H

#include "dfa-node.h"

namespace DFANodeFactory {
    namespace Once {
        static DFANode* create(ASTNodeType astNodeType) {
            return new DFANode(astNodeType, DFA_OCCURRENCE_ONCE);
        }
        static DFANode* createWithTarget(ASTNodeType astNodeType, ASTNodeType targetAstNodeType) {
            return new DFANode(astNodeType, DFA_OCCURRENCE_ONCE, targetAstNodeType);
        }
        static DFANode* varDeclaration = Once::create(AST_VARIABLE_DECLARATION_NODE);
        static DFANode* varInit = Once::create(AST_VARIABLE_INIT_NODE);
        static DFANode* varType = Once::create(AST_VARIABLE_TYPE_NODE);
        static DFANode* identifier = Once::create(AST_IDENTIFIER_NODE);
        static DFANode* intLiteral = Once::create(AST_INT_LITERAL_NODE);
        static DFANode* floatLiteral = Once::create(AST_FLOAT_LITERAL_NODE);
        static DFANode* stringLiteral = Once::create(AST_STRING_LITERAL_NODE);
        static DFANode* charLiteral = Once::create(AST_CHAR_LITERAL_NODE);
        static DFANode* booleanLiteral = Once::create(AST_BOOLEAN_LITERAL_NODE);
        static DFANode* plusOperator = Once::create(AST_PLUS_OPERATOR_NODE);
        static DFANode* minusOperator = Once::create(AST_MINUS_OPERATOR_NODE);
        static DFANode* starOperator = Once::create(AST_STAR_OPERATOR_NODE);
        static DFANode* slashOperator = Once::create(AST_SLASH_OPERATOR_NODE);
        static DFANode* moduloOperator = Once::create(AST_MODULO_OPERATOR_NODE);
        static DFANode* greaterThanOperator = Once::create(AST_GREATER_THAN_OPERATOR_NODE);
        static DFANode* greaterThanOrEqualOperator = Once::create(AST_GREATER_THAN_OR_EQUAL_OPERATOR_NODE);
        static DFANode* lessThanOperator = Once::create(AST_LESS_THAN_OPERATOR_NODE);
        static DFANode* lessThanOrEqualOperator = Once::create(AST_LESS_THAN_OR_EQUAL_OPERATOR_NODE);
        static DFANode* logicalOperator = Once::create(AST_LOGICAL_OPERATOR_NODE);
        static DFANode* equalityOperator = Once::create(AST_EQUALITY_OPERATOR_NODE);
        static DFANode* inequalityOperator = Once::create(AST_INEQUALITY_OPERATOR_NODE);
        static DFANode* bangOperator = Once::create(AST_BANG_OPERATOR_NODE);
        static DFANode* assignmentOperator = Once::create(AST_ASSIGNMENT_OPERATOR_NODE);
    }
    namespace OnceOrMore {
        static DFANode* create(ASTNodeType astNodeType) {
            return new DFANode(astNodeType, DFA_OCCURRENCE_ONCE_OR_MORE);
        }
        static DFANode* createWithTarget(ASTNodeType astNodeType, ASTNodeType targetAstNodeType) {
            return new DFANode(astNodeType, DFA_OCCURRENCE_ONCE_OR_MORE, targetAstNodeType);
        }
        static DFANode* identifier = OnceOrMore::create(AST_IDENTIFIER_NODE);
        static DFANode* groupStart = OnceOrMore::create(AST_GROUP_START_NODE);
        static DFANode* groupEnd = OnceOrMore::create(AST_GROUP_END_NODE);
        static DFANode* expression = OnceOrMore::create(AST_EXPRESSION_NODE);
        static DFANode* literalExpression = OnceOrMore::create(AST_LITERAL_EXPRESSION_NODE);
        static DFANode* identifierExpression = OnceOrMore::create(AST_IDENTIFIER_EXPRESSION_NODE);
        static DFANode* binaryExpression = OnceOrMore::create(AST_BINARY_EXPRESSION_NODE);
        static DFANode* logicalExpression = OnceOrMore::create(AST_LOGICAL_EXPRESSION_NODE);
        static DFANode* unaryExpression = OnceOrMore::create(AST_UNARY_EXPRESSION_NODE);
    }
    namespace NilOrMore {
        static DFANode* create(ASTNodeType astNodeType) {
            return new DFANode(astNodeType, DFA_OCCURRENCE_NIL_OR_MORE);
        }
        static DFANode* createWithTarget(ASTNodeType astNodeType, ASTNodeType targetAstNodeType) {
            return new DFANode(astNodeType, DFA_OCCURRENCE_NIL_OR_MORE, targetAstNodeType);
        }
    }
    namespace NilOrOnce {
        static DFANode* create(ASTNodeType astNodeType) {
            return new DFANode(astNodeType, DFA_OCCURRENCE_NIL_OR_ONCE);
        }
        static DFANode* createWithTarget(ASTNodeType astNodeType, ASTNodeType targetAstNodeType) {
            return new DFANode(astNodeType, DFA_OCCURRENCE_NIL_OR_ONCE, targetAstNodeType);
        }
    }
}

#endif //JETLANG_DFA_NODE_FACTORY_H
