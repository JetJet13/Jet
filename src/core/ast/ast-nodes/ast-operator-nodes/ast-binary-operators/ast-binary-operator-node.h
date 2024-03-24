//
// Created by Johny Georges on 2024-02-07.
//

#ifndef JETLANG_AST_BINARY_OPERATOR_NODE_H
#define JETLANG_AST_BINARY_OPERATOR_NODE_H

#include "../../ast-node.h"

class ASTBinaryOperatorNode : public ASTNode {
private:
    Lexeme* _lexemeOperator;
    unsigned int determinePriority(Lexeme* lexeme);
public:
    explicit ASTBinaryOperatorNode(Lexeme* lexemeOperator);
    ASTBinaryOperatorNode(Lexeme* lexemeOperator, int priority);
    Lexeme* getOperator();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
};

#endif //JETLANG_AST_BINARY_OPERATOR_NODE_H
