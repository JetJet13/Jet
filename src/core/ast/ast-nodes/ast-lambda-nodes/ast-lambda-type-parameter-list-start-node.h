//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_START_NODE_H
#define JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_START_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTLambdaTypeParameterListStartNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTLambdaTypeParameterListStartNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_START_NODE_H
