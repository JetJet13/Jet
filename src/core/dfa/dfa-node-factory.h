//
// Created by Johny Georges on 2024-02-15.
//

#ifndef JETLANG_DFA_NODE_FACTORY_H
#define JETLANG_DFA_NODE_FACTORY_H

#include "dfa-node.h"

namespace DFANodeFactory {
    static DFANode* createAny(ASTNodeType targetAstNodeType) {
        return new DFANode(AST_ANY_NODE, DFA_OCCURRENCE_NIL_OR_ONCE, targetAstNodeType);
    }
    namespace Once {
        static DFANode* create(ASTNodeType astNodeType) {
            return new DFANode(astNodeType, DFA_OCCURRENCE_ONCE);
        }
        static DFANode* createWithTarget(ASTNodeType astNodeType, ASTNodeType targetAstNodeType) {
            return new DFANode(astNodeType, DFA_OCCURRENCE_ONCE, targetAstNodeType);
        }

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
