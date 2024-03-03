//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_AST_ASSIGNMENT_NODE_H
#define JETLANG_AST_ASSIGNMENT_NODE_H


#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTAssignmentOperatorNode : public ASTNode {
private:
    Lexeme* _assignment;
public:
    ASTAssignmentOperatorNode(Lexeme* lexeme);
    Lexeme* getAssignmentOperator();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ASSIGNMENT_NODE_H
