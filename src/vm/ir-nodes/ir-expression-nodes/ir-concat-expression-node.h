//
// Created by Johny Georges on 2025-06-09.
//

#ifndef JETLANG_IR_CONCAT_EXPRESSION_NODE_H
#define JETLANG_IR_CONCAT_EXPRESSION_NODE_H

#include <llvm/IR/InstrTypes.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-concat-expression-node.h"
#include "ir-expression-node.h"
#include "../../ir-type/ir-array-pointer-type.h"

class IRConcatExpressionNode : public IRExpressionNode {
private:
    ASTConcatExpressionNode* _node;
    IRInstructionNode* _irValue;
    IRExpressionNode* _irLeftNode;
    IRExpressionNode* _irRightNode;
    IRArrayPointerType* _type;
public:
    IRConcatExpressionNode(ASTConcatExpressionNode* astNode, IRInstructionNode* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRArrayPointerType* type);
    void markAsGlobal() override;
    bool isReferenced() override;
    llvm::Value* getValue() override;
    IRExpressionNode* getLeftNode();
    IRExpressionNode* getRightNode();
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    IRArrayPointerType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CONCAT_EXPRESSION_NODE_H
