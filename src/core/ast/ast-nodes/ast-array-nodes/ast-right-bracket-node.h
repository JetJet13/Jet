//
// Created by Johny Georges on 2024-03-09.
//

#ifndef JETLANG_AST_RIGHT_BRACKET_NODE_H
#define JETLANG_AST_RIGHT_BRACKET_NODE_H

#include <optional>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"
#include "../ast-symbol-node.h"

class ASTRightBracketNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    explicit ASTRightBracketNode(Lexeme* lexeme);
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_RIGHT_BRACKET_NODE_H

/*
 * const arr = [1,2,3];
 * arr[0];
 * arr[0] + arr[1];
 * arr[1 + 2];
 * arr[one];
 * arr[one] + arr[two];
 * arr[one + two];
 * hello()[1];
 * (arr[0] + arr[1]);
 */