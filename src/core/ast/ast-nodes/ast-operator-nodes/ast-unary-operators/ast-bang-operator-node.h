//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_AST_BANG_OPERATOR_NODE_H
#define JETLANG_AST_BANG_OPERATOR_NODE_H

#include "../../../../lexeme/lexeme.h"
#include "../../../types/ast-node-type.h"
#include "../../ast-node.h"
#include "ast-unary-operator-node.h"

class ASTBangOperatorNode : public ASTUnaryOperatorNode {
private:
    Lexeme* _bangOperator;
public:
    ASTBangOperatorNode(Lexeme* bangOperator);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;
};


#endif //JETLANG_AST_BANG_OPERATOR_NODE_H
