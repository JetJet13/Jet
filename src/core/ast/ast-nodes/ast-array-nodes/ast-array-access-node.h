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
    ASTLeftBracketNode* _leftBracket;
    ASTRightBracketNode* _rightBracket;
    ASTExpressionNode* _index;
public:
    explicit ASTArrayAccessNode(ASTLeftBracketNode* leftBracket, ASTExpressionNode* index, ASTRightBracketNode* rightBracket);
    ASTExpressionNode* getIndex();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_ARRAY_ACCESS_NODE_H
