//
// Created by Johny Georges on 2024-08-15.
//

#include "ir-injector.h"

IRInjector::IRInjector() {
    _irInjectorMap = IRInjectorMap();
}

void IRInjector::inject(IRBlockNode* irBlock, IRDeclarationNode* irDeclaration) {
    if (irDeclaration->is(IR_VARIABLE_DECLARATION_NODE)) {
        _irInjectorMap.getVariableInjector()->inject((IRVariableDeclarationNode*)irDeclaration, irBlock->getBuilder());
    }
}

void IRInjector::inject(IRBlockNode* irBlock, IRStatementNode* irStatement) {
    if (irStatement->is(IR_FUNCTION_RETURN_EXPRESSION_NODE)) {
        _irInjectorMap.getFunctionReturnInjector()->inject((IRFunctionReturnExpressionNode*)irStatement, irBlock->getBuilder());
    }
}

void IRInjector::inject(IRBlockNode* irBlock, IRExpressionNode* irExpression) {
    _irInjectorMap.getInjector(irExpression->getTypeSignature())->inject(irExpression, irBlock->getBuilder());
}