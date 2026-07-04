//
// Created by Johny Georges on 2024-03-11.
//

#ifndef JETLANG_AST_ARRAY_NODE_H
#define JETLANG_AST_ARRAY_NODE_H

#include <optional>
#include <string>
#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-left-bracket-node.h"
#include "ast-right-bracket-node.h"
#include "../ast-comma-node.h"

class ASTArrayNode : public ASTNode {
private:
    std::shared_ptr<ASTLeftBracketNode> _leftBracket;
    std::shared_ptr<ASTRightBracketNode> _rightBracket;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTExpressionNode>>* _elements;
public:
    explicit ASTArrayNode(std::shared_ptr<ASTLeftBracketNode> leftBracket, std::shared_ptr<ASTRightBracketNode> rightBracket);
    explicit ASTArrayNode(std::shared_ptr<ASTLeftBracketNode> leftBracket, std::vector<std::shared_ptr<ASTExpressionNode>> elements, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTRightBracketNode> rightBracket);
    std::shared_ptr<ASTArrayNode> addElement(std::shared_ptr<ASTExpressionNode> element);
    std::shared_ptr<ASTArrayNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    void markElementsAsReferenced();
    std::shared_ptr<ASTLeftBracketNode> getLeftBracket();
    std::shared_ptr<ASTRightBracketNode> getRightBracket();
    std::optional<std::shared_ptr<ASTExpressionNode>> getFirstElement();
    std::vector<std::shared_ptr<ASTExpressionNode>>* getElements();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_NODE_H
