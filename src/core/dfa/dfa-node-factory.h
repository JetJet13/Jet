//
// Created by Johny Georges on 2024-02-15.
//

#ifndef JETLANG_DFA_NODE_FACTORY_H
#define JETLANG_DFA_NODE_FACTORY_H

#include "dfa-node.h"

namespace DFANodeFactory {
    static std::shared_ptr<DFANode> createAny(ASTNodeType targetAstNodeType) {
        return std::make_shared<DFANode>(AST_ANY_NODE, DFA_OCCURRENCE_NIL_OR_ONCE, targetAstNodeType);
    }
    namespace Once {
        static std::shared_ptr<DFANode> create(ASTNodeType astNodeType) {
            return std::make_shared<DFANode>(astNodeType, DFA_OCCURRENCE_ONCE);
        }
        static std::shared_ptr<DFANode> createWithTarget(ASTNodeType astNodeType, ASTNodeType targetAstNodeType) {
            return std::make_shared<DFANode>(astNodeType, DFA_OCCURRENCE_ONCE, targetAstNodeType);
        }

    }
    namespace OnceOrMore {
        static std::shared_ptr<DFANode> create(ASTNodeType astNodeType) {
            return std::make_shared<DFANode>(astNodeType, DFA_OCCURRENCE_ONCE_OR_MORE);
        }
        static std::shared_ptr<DFANode> createWithTarget(ASTNodeType astNodeType, ASTNodeType targetAstNodeType) {
            return std::make_shared<DFANode>(astNodeType, DFA_OCCURRENCE_ONCE_OR_MORE, targetAstNodeType);
        }
        static std::shared_ptr<DFANode> identifier = OnceOrMore::create(AST_IDENTIFIER_NODE);
        static std::shared_ptr<DFANode> groupStart = OnceOrMore::create(AST_GROUP_START_NODE);
        static std::shared_ptr<DFANode> groupEnd = OnceOrMore::create(AST_GROUP_END_NODE);
        static std::shared_ptr<DFANode> expression = OnceOrMore::create(AST_EXPRESSION_NODE);
        static std::shared_ptr<DFANode> literalExpression = OnceOrMore::create(AST_LITERAL_EXPRESSION_NODE);
        static std::shared_ptr<DFANode> identifierExpression = OnceOrMore::create(AST_IDENTIFIER_EXPRESSION_NODE);
        static std::shared_ptr<DFANode> binaryExpression = OnceOrMore::create(AST_BINARY_ARITHMETIC_EXPRESSION_NODE);
        static std::shared_ptr<DFANode> logicalExpression = OnceOrMore::create(AST_LOGICAL_EXPRESSION_NODE);
        static std::shared_ptr<DFANode> unaryExpression = OnceOrMore::create(AST_UNARY_EXPRESSION_NODE);
    }
    namespace NilOrMore {
        static std::shared_ptr<DFANode> create(ASTNodeType astNodeType) {
            return std::make_shared<DFANode>(astNodeType, DFA_OCCURRENCE_NIL_OR_MORE);
        }
        static std::shared_ptr<DFANode> createWithTarget(ASTNodeType astNodeType, ASTNodeType targetAstNodeType) {
            return std::make_shared<DFANode>(astNodeType, DFA_OCCURRENCE_NIL_OR_MORE, targetAstNodeType);
        }
    }
    namespace NilOrOnce {
        static std::shared_ptr<DFANode> create(ASTNodeType astNodeType) {
            return std::make_shared<DFANode>(astNodeType, DFA_OCCURRENCE_NIL_OR_ONCE);
        }
        static std::shared_ptr<DFANode> createWithTarget(ASTNodeType astNodeType, ASTNodeType targetAstNodeType) {
            return std::make_shared<DFANode>(astNodeType, DFA_OCCURRENCE_NIL_OR_ONCE, targetAstNodeType);
        }
    }
}

#endif //JETLANG_DFA_NODE_FACTORY_H
