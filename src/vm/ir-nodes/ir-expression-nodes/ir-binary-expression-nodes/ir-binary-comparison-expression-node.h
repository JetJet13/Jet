//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_BINARY_COMPARISON_EXPRESSION_NODE_H
#define JETLANG_IR_BINARY_COMPARISON_EXPRESSION_NODE_H

#include <llvm/IR/InstrTypes.h>
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "ir-binary-expression-node.h"

class IRBinaryComparisonExpressionNode : public IRBinaryExpressionNode {
private:
    ASTBinaryExpressionNode* _astNode;
    llvm::CmpInst* _irValue;
    IRExpressionNode* _irLeftNode;
    IRExpressionNode* _irRightNode;
    IRType* _type;
    IRInstructionNode* _sourceAllocation;
public:
    IRBinaryComparisonExpressionNode(ASTBinaryExpressionNode* astNode, llvm::CmpInst* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRType* type, IRInstructionNode* sourceAllocation);
    llvm::Value* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::CmpInst* getValue() override;
    IRInstructionNode* getSourceAllocation() override;
    IRType* getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_BINARY_COMPARISON_EXPRESSION_NODE_H
