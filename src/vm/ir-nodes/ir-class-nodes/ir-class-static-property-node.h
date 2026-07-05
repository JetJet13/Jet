//
// Created by Johny Georges on 2026-03-14.
//

#ifndef JETLANG_IR_CLASS_STATIC_PROPERTY_NODE_H
#define JETLANG_IR_CLASS_STATIC_PROPERTY_NODE_H

#include <llvm/IR/GlobalVariable.h>
#include "../ir-expression-nodes/ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"

class IRClassStaticPropertyNode {
private:
    std::shared_ptr<ASTClassPropertyDeclarationNode> _node;
    llvm::GlobalVariable* _irValue;
    IRExpressionNode* _initialIRValue;
    std::shared_ptr<IRType> _irType;
public:
    IRClassStaticPropertyNode(std::shared_ptr<ASTClassPropertyDeclarationNode> node, llvm::GlobalVariable* irValue, IRExpressionNode* initialIRValue, std::shared_ptr<IRType> irType);
    llvm::GlobalVariable* getGlobalVariable();
    IRExpressionNode* getInitialIRValue();
    std::shared_ptr<IRType> getIRType();
};

#endif //JETLANG_IR_CLASS_STATIC_PROPERTY_NODE_H
