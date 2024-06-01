//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_END_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_END_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"
#include "../ast-symbol-node.h"

class ASTImportModuleListEndNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};


#endif //JETLANG_AST_IMPORT_MODULE_LIST_END_NODE_H
