//
// Created by Johny Georges on 2026-03-14.
//

#ifndef JETLANG_IR_CLASS_STATIC_PROPERTY_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_CLASS_STATIC_PROPERTY_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "ir-expression-node.h"
#include "../../ir-type/ir-struct-ref-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"

class IRClassStaticPropertyAccessExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTObjectAccessExpressionNode> _node;
    IRInstructionNode* _irStaticProperty;
    std::shared_ptr<IRType> _irType;
public:
    IRClassStaticPropertyAccessExpressionNode(std::shared_ptr<ASTObjectAccessExpressionNode> node, IRInstructionNode* irStaticProperty, std::shared_ptr<IRType> irType);
    std::shared_ptr<ASTObjectAccessExpressionNode> getNode();
    std::shared_ptr<IRPointerType> getPointerIRType();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CLASS_STATIC_PROPERTY_ACCESS_EXPRESSION_NODE_H
