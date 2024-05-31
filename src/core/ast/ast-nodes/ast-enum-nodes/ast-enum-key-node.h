//
// Created by Johny Georges on 2024-03-23.
//

#ifndef JETLANG_AST_ENUM_KEY_NODE_H
#define JETLANG_AST_ENUM_KEY_NODE_H

#include "../ast-symbol-node.h"

class ASTEnumKeyNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ENUM_KEY_NODE_H
