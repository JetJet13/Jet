//
// Created by Johny Georges on 2024-02-07.
//

#ifndef JETLANG_AST_BINARY_OPERATOR_NODE_H
#define JETLANG_AST_BINARY_OPERATOR_NODE_H

#include "../../ast-node.h"

class ASTBinaryOperatorNode : public ASTNode {
protected:
    Lexeme* _lexemeOperator;
public:
    ASTBinaryOperatorNode(Lexeme* lexemeOperator);
    Lexeme* getOperator();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;
};

#endif //JETLANG_AST_BINARY_OPERATOR_NODE_H
