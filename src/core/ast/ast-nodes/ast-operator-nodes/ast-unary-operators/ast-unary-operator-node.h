//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_AST_UNARY_OPERATOR_NODE_H
#define JETLANG_AST_UNARY_OPERATOR_NODE_H

#include "../../ast-node.h"

class ASTUnaryOperatorNode : public ASTNode {
protected:
    Lexeme* _lexemeOperator;
public:
    ASTUnaryOperatorNode(Lexeme* lexemeOperator);
    Lexeme* getOperator();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;
};

#endif //JETLANG_AST_UNARY_OPERATOR_NODE_H
