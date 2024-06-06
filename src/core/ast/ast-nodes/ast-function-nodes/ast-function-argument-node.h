//
// Created by Johny Georges on 2024-03-25.
//

#ifndef JETLANG_AST_FUNCTION_ARGUMENT_NODE_H
#define JETLANG_AST_FUNCTION_ARGUMENT_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-type-nodes/ast-type-node.h"

class ASTFunctionArgumentNode : public ASTNode {
private:
    ASTExpressionNode* _argument;
public:
    explicit ASTFunctionArgumentNode(ASTExpressionNode* identifier);
    ASTExpressionNode* getArgument();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_ARGUMENT_NODE_H
