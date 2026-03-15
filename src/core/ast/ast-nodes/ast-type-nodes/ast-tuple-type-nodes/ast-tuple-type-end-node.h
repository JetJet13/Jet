//
// Created by Johny Georges on 2026-03-14.
//

#ifndef JETLANG_AST_TUPLE_TYPE_END_NODE_H
#define JETLANG_AST_TUPLE_TYPE_END_NODE_H

#include <string>
#include "../../ast-node.h"
#include "../../../../lexeme/lexeme.h"
#include "../../ast-symbol-node.h"

class ASTTupleTypeEndNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_TUPLE_TYPE_END_NODE_H
