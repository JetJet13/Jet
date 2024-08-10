//
// Created by Johny Georges on 2024-08-05.
//

#ifndef JETLANG_IR_STRING_LITERAL_EXPRESSION_NODE_H
#define JETLANG_IR_STRING_LITERAL_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../ir-type/ir-pointer-type.h"
#include "../ir-literal-nodes/ir-string-literal-node.h"

class IRStringLiteralExpressionNode : public IRExpressionNode {
private:
    ASTLiteralExpressionNode* _node;
    IRStringLiteralNode* _irValue;
    IRArrayPointerType* _irArrayPointerType;
    IRInstructionNode* _sourceAllocation;
    IRInstructionNode* _arrayPointerSourceAllocation;
public:
    IRStringLiteralExpressionNode(ASTLiteralExpressionNode* node, IRStringLiteralNode* irValue, IRArrayPointerType* irArrayPointerType, IRInstructionNode* sourceAllocation, IRInstructionNode* arrayPointerSourceAllocation);
    llvm::Value* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    IRArrayPointerType* getIRType() override;
    llvm::Constant* getValue() override;
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRING_LITERAL_EXPRESSION_NODE_H
