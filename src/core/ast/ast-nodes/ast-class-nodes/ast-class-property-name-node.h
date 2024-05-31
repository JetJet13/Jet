//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_NAME_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_NAME_NODE_H

#include "../ast-symbol-node.h"

class ASTClassPropertyNameNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_NAME_NODE_H
