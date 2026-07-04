//
// Created by Johny Georges on 2024-08-05.
//

#ifndef JETLANG_IR_STRING_LITERAL_EXPRESSION_NODE_H
#define JETLANG_IR_STRING_LITERAL_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../ir-type/ir-pointer-type.h"
#include "../ir-literal-nodes/ir-string-literal-node.h"
#include "../../ir-type/ir-array-pointer-type.h"
#include "ir-expression-node.h"

class IRStringLiteralExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTLiteralExpressionNode> _node;
    IRStringLiteralNode* _irValue;
    IRArrayPointerType* _irArrayPointerType;
    IRInstructionNode* _sourceAllocation;
    IRInstructionNode* _arrayPointerSourceAllocation;
public:
    IRStringLiteralExpressionNode(std::shared_ptr<ASTLiteralExpressionNode> node, IRStringLiteralNode* irValue, IRArrayPointerType* irArrayPointerType, IRInstructionNode* sourceAllocation, IRInstructionNode* arrayPointerSourceAllocation);
    IRArrayPointerType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    llvm::Constant* getValue() override;
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    IRInstructionNode* getSourceAggregateAllocation();
    IRInstructionNode* getAggregatePointerAllocation();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRING_LITERAL_EXPRESSION_NODE_H
