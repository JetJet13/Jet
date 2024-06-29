//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H
#define JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../ir-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

class IRIdentifierExpressionNode : public IRNode {
private:
    ASTIdentifierExpressionNode* _astNode;
    llvm::Value* _irValue;
public:
    IRIdentifierExpressionNode(ASTIdentifierExpressionNode* astIdentifierExpressionNode, llvm::Value* irValue);
    llvm::Value* getIRValue();
    IRNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H
