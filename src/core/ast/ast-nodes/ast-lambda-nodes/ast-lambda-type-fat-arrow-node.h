//
// Created by Johny Georges on 2024-04-05.
//

#ifndef JETLANG_AST_LAMBDA_TYPE_FAT_ARROW_NODE_H
#define JETLANG_AST_LAMBDA_TYPE_FAT_ARROW_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"

class ASTLambdaTypeFatArrowNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTLambdaTypeFatArrowNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_FAT_ARROW_NODE_H
