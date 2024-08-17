//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H
#define JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"

class IRIdentifierExpressionNode : public IRExpressionNode {
private:
    ASTIdentifierExpressionNode* _node;
    IRInstructionNode* _irValue;
public:
    IRIdentifierExpressionNode(ASTIdentifierExpressionNode* node, IRInstructionNode* irValue);
    IRInstructionNode* getIRValue();
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    llvm::Value* getValue() override;
    IRPointerType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    llvm::Type* getTypeAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H
