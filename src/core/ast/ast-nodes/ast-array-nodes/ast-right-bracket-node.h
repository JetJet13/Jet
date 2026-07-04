//
// Created by Johny Georges on 2024-03-09.
//

#ifndef JETLANG_AST_RIGHT_BRACKET_NODE_H
#define JETLANG_AST_RIGHT_BRACKET_NODE_H

#include <optional>
#include "../ast-symbol-node.h"
#include "../../../lexeme/lexeme.h"

class ASTRightBracketNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) override;
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