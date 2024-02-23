//
// Created by Johny Georges on 2024-02-22.
//

#ifndef JETLANG_AST_SLASH_OPERATOR_NODE_H
#define JETLANG_AST_SLASH_OPERATOR_NODE_H

#include "../../../ast-node.h"
#include "../ast-binary-operator-node.h"

class ASTSlashOperatorNode : public ASTBinaryOperatorNode {
private:
    Lexeme* _slashOperator;
public:
    ASTSlashOperatorNode(Lexeme* slashOperator);
    ASTNodeType getNodeType() override;
};

#endif //JETLANG_AST_SLASH_OPERATOR_NODE_H
