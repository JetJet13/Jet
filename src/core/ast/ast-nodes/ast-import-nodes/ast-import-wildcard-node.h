//
// Created by Johny Georges on 2024-04-15.
//

#ifndef JETLANG_AST_IMPORT_WILDCARD_NODE_H
#define JETLANG_AST_IMPORT_WILDCARD_NODE_H

#include <string>
#include "../ast-node.h"
#include "../ast-symbol-node.h"

class ASTImportWildcardNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};


#endif //JETLANG_AST_IMPORT_WILDCARD_NODE_H
