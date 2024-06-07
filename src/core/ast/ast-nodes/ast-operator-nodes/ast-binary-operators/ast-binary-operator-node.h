//
// Created by Johny Georges on 2024-02-07.
//

#ifndef JETLANG_AST_BINARY_OPERATOR_NODE_H
#define JETLANG_AST_BINARY_OPERATOR_NODE_H

#include "../../ast-node.h"
#include "../../../../lexeme/lexeme.h"

class ASTBinaryOperatorNode : public ASTNode {
private:
    Lexeme* _lexeme;
    unsigned int determinePriority(Lexeme* lexeme);
public:
    ASTBinaryOperatorNode(Lexeme* lexeme);
    Lexeme* getOperator();
    bool isPlus();
    bool isMinus();
    bool isMultiply();
    bool isDivide();
    bool isModulo();
    bool isEqual();
    bool isNotEqual();
    bool isGreaterThan();
    bool isLessThan();
    bool isGreaterThanOrEqual();
    bool isLessThanOrEqual();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BINARY_OPERATOR_NODE_H
