//
// Created by Johny Georges on 2024-03-12.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_NODE_H

#include <string>
#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-left-bracket-node.h"
#include "ast-right-bracket-node.h"

class ASTArrayAccessNode : public ASTNode {
private:
    std::shared_ptr<ASTLeftBracketNode> _leftBracket;
    std::shared_ptr<ASTRightBracketNode> _rightBracket;
    std::shared_ptr<ASTExpressionNode> _index;
public:
    explicit ASTArrayAccessNode(std::shared_ptr<ASTLeftBracketNode> leftBracket, std::shared_ptr<ASTExpressionNode> index, std::shared_ptr<ASTRightBracketNode> rightBracket);
    std::shared_ptr<ASTExpressionNode> getIndex();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_ARRAY_ACCESS_NODE_H
