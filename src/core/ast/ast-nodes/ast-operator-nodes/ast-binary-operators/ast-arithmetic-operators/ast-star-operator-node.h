//
// Created by Johny Georges on 2024-02-22.
//

#ifndef JETLANG_AST_STAR_OPERATOR_NODE_H
#define JETLANG_AST_STAR_OPERATOR_NODE_H

#include "../../../../../lexeme/lexeme.h"
#include "../../../ast-node.h"
#include "../ast-binary-operator-node.h"

class ASTStarOperatorNode : public ASTBinaryOperatorNode {
private:
    Lexeme* _starOperator;
public:
    ASTStarOperatorNode(Lexeme* starOperator);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;
};


#endif //JETLANG_AST_STAR_OPERATOR_NODE_H
