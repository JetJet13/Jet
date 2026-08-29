//
// Created by Johny Georges on 2026-08-29.
//

#ifndef JETLANG_IR_CLASS_METHOD_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_CLASS_METHOD_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "ir-expression-node.h"
#include "../../ir-type/ir-struct-ref-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"
#include "../../ir-type/ir-invocable-type.h"

class IRClassMethodAccessExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTClassPropertyAccessExpressionNode> _node;
    std::shared_ptr<IRInstructionNode> _irMethod;
    std::shared_ptr<IRInvocableType> _irType;
public:
    IRClassMethodAccessExpressionNode(std::shared_ptr<ASTClassPropertyAccessExpressionNode> node, std::shared_ptr<IRInstructionNode> irMethod, std::shared_ptr<IRInvocableType> irType);
    std::shared_ptr<ASTClassPropertyAccessExpressionNode> getNode();
    std::shared_ptr<IRInstructionNode> getIRMethod();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CLASS_METHOD_ACCESS_EXPRESSION_NODE_H
