//
// Created by Johny Georges on 2024-08-15.
//

#include "ir-injector.h"

IRInjector::IRInjector() {
    _irInjectorMap = IRInjectorMap();
}

void IRInjector::inject(IRBlockNode* irBlock, IRDeclarationNode* irDeclaration, IRModuleNode* irModule) {
    if (irDeclaration->is(IR_VARIABLE_DECLARATION_NODE)) {
        _irInjectorMap.getVariableInjector()->inject((IRVariableDeclarationNode*)irDeclaration, irBlock->getBuilder(), &_irInjectorMap, irModule);
    } else if (irDeclaration->is(IR_FUNCTION_PARAMETER_DECLARATION_NODE)) {
        _irInjectorMap.getFunctionParameterInjector()->inject((IRFunctionParameterDeclarationNode*)irDeclaration, irBlock->getBuilder(), &_irInjectorMap, irModule);
    } else if (irDeclaration->is(IR_MODULE_DECLARATION_NODE)) {
        _irInjectorMap.getModuleInjector()->inject((IRModuleDeclarationNode*)irDeclaration, irBlock->getBuilder(), &_irInjectorMap, irModule);
    }
}

void IRInjector::inject(IRBlockNode* irBlock, IRStatementNode* irStatement, IRModuleNode* irModule) {
    if (irStatement->is(IR_FUNCTION_RETURN_EXPRESSION_NODE)) {
        _irInjectorMap.getFunctionReturnInjector()->inject((IRFunctionReturnExpressionNode*)irStatement, irBlock->getBuilder());
    }
}

void IRInjector::inject(IRBlockNode* irBlock, IRExpressionNode* irExpression, IROperationType irOperationType, IRModuleNode* irModule) {
    _irInjectorMap.getInjector(irExpression->getTypeSignature())->inject(irExpression, irBlock->getBuilder(), &_irInjectorMap, irOperationType, irModule);
}

llvm::Value* IRInjector::injectRawString(IRBlockNode* irBlock, std::string rawString, IRArrayPointerType* stringPointerType, IRModuleNode* irModule) {
    return _irInjectorMap.getStringInjector()->inject(rawString, stringPointerType, irBlock->getBuilder(), &_irInjectorMap, IR_OPERAND_OP, irModule);
}