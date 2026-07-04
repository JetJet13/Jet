//
// Created by Johny Georges on 2026-03-27.
//

#ifndef JETLANG_IR_MODULE_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_MODULE_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "ir-expression-node.h"
#include "../../ir-type/ir-struct-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-module-access-expression-node.h"

class IRModuleAccessExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTModuleAccessExpressionNode> _node;
    llvm::Value* _irValue;
    IRType* _irType;
    std::optional<IRInstructionNode*> _sourceAllocation;
public:
    IRModuleAccessExpressionNode(std::shared_ptr<ASTModuleAccessExpressionNode> node, llvm::Value* irValue, IRType* irType);
    void markAsGlobal() override;
    std::shared_ptr<ASTModuleAccessExpressionNode> getNode();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_MODULE_ACCESS_EXPRESSION_NODE_H
