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
    std::shared_ptr<ASTIdentifierExpressionNode> _node;
    IRInstructionNode* _irValue;
    std::optional<IRInstructionNode*> _irArc;
    IRPointerType* _irType;
public:
    IRIdentifierExpressionNode(std::shared_ptr<ASTIdentifierExpressionNode> node, IRInstructionNode* irValue, std::optional<IRInstructionNode*> irArc = {});
    IRInstructionNode* getIRValue();
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    std::optional<IRInstructionNode*> getArc() override;
    llvm::Value* getValue() override;
    IRPointerType* getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    llvm::Type* getTypeAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_IDENTIFIER_EXPRESSION_NODE_H
