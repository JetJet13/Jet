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

class ASTArrayNode : public ASTNode {
private:
    ASTLeftBracketNode* _leftBracket;
    ASTRightBracketNode* _rightBracket;
    std::vector<ASTExpressionNode*>* _elements;
public:
    explicit ASTArrayNode(ASTLeftBracketNode* leftBracket, ASTRightBracketNode* rightBracket);
    explicit ASTArrayNode(ASTLeftBracketNode* leftBracket, std::vector<ASTExpressionNode*> elements, ASTRightBracketNode* rightBracket);
    ASTArrayNode* addElement(ASTExpressionNode* element);
    void markElementsAsReferenced();
    ASTLeftBracketNode* getLeftBracket();
    ASTRightBracketNode* getRightBracket();
    std::optional<ASTExpressionNode*> getFirstElement();
    std::vector<ASTExpressionNode*>* getElements();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_NODE_H
