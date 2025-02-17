//
// Created by Johny Georges on 2024-07-17.
//

#ifndef JETLANG_IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE_H
#define JETLANG_IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-global-variable-node.h"

class IRGlobalIdentifierExpressionNode : public IRExpressionNode {
private:
    ASTIdentifierExpressionNode* _node;
    IRInstructionNode* _irValue;
public:
    IRGlobalIdentifierExpressionNode(ASTIdentifierExpressionNode* node, IRInstructionNode* irValue);
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    llvm::GlobalVariable* getValue() override;
    IRPointerType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    llvm::Type* getType() override;
    llvm::Type* getTypeAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE_H
