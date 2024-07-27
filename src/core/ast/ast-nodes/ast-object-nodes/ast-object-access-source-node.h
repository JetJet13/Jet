//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_SOURCE_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_SOURCE_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-expression-nodes/ast-aggregate-expression-node.h"
#include "../../../type-signature/aggregate-type-signature.h"

class ASTObjectAccessSourceNode : public ASTNode {
private:
    ASTExpressionNode* _source;
public:
    explicit ASTObjectAccessSourceNode(ASTExpressionNode* source);
    ASTExpressionNode* getSource();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_SOURCE_NODE_H
