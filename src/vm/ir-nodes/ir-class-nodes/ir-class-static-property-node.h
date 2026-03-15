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
    ASTClassPropertyDeclarationNode* _node;
    llvm::GlobalVariable* _irValue;
    IRExpressionNode* _initialIRValue;
    IRType* _irType;
public:
    IRClassStaticPropertyNode(ASTClassPropertyDeclarationNode* node, llvm::GlobalVariable* irValue, IRExpressionNode* initialIRValue, IRType* irType);
    llvm::GlobalVariable* getGlobalVariable();
    IRExpressionNode* getInitialIRValue();
    IRType* getIRType();
};

#endif //JETLANG_IR_CLASS_STATIC_PROPERTY_NODE_H
