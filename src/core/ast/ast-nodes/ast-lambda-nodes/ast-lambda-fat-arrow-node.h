//
// Created by Johny Georges on 2024-04-05.
//

#ifndef JETLANG_AST_LAMBDA_FAT_ARROW_NODE_H
#define JETLANG_AST_LAMBDA_FAT_ARROW_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"
#include "../ast-symbol-node.h"

class ASTLambdaFatArrowNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_LAMBDA_FAT_ARROW_NODE_H
