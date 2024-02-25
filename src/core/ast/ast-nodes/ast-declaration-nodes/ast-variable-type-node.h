//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_AST_VARIABLE_TYPE_NODE_H
#define JETLANG_AST_VARIABLE_TYPE_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"

class ASTVariableTypeNode : public ASTNode {
private:
    Lexeme* _varTypeQualifier;
public:
    ASTVariableTypeNode(Lexeme* varTypeQualifier);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;
};

#endif //JETLANG_AST_VARIABLE_TYPE_NODE_H
