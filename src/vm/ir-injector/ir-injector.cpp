//
// Created by Johny Georges on 2024-08-15.
//

#include "ir-injector.h"

IRInjector::IRInjector() {
    _irInjectorMap = IRInjectorMap();
}

void IRInjector::inject(IRBlockNode* irBlock, IRNode* irNode, IRModuleNode* irModule, IRLookupTable* scope) {
    this->inject(irBlock, (IRDeclarationNode*)irNode, irModule, scope);
    this->inject(irBlock, (IRStatementNode*)irNode, irModule, scope);
}

void IRInjector::inject(IRBlockNode* irBlock, IRDeclarationNode* irDeclaration, IRModuleNode* irModule, IRLookupTable* scope) {
    if (irDeclaration->is(IR_VARIABLE_DECLARATION_NODE)) {
        _irInjectorMap.getVariableInjector()->inject((IRVariableDeclarationNode*)irDeclaration, irBlock->getBuilder(), &_irInjectorMap, irModule, scope);
    } else if (irDeclaration->is(IR_FUNCTION_PARAMETER_DECLARATION_NODE)) {
        _irInjectorMap.getFunctionParameterInjector()->inject((IRFunctionParameterDeclarationNode*)irDeclaration, irBlock->getBuilder(), &_irInjectorMap, irModule);
    } else if (irDeclaration->is(IR_MODULE_DECLARATION_NODE)) {
        _irInjectorMap.getModuleInjector()->inject((IRModuleDeclarationNode*)irDeclaration, irBlock->getBuilder(), &_irInjectorMap, irModule, scope);
    }
}

void IRInjector::inject(IRBlockNode* irBlock, IRStatementNode* irStatement, IRModuleNode* irModule, IRLookupTable* scope) {
    if (irStatement->is(IR_FUNCTION_RETURN_EXPRESSION_NODE)) {
        _irInjectorMap.getFunctionReturnInjector()->inject((IRFunctionReturnExpressionNode *) irStatement, irBlock->getBuilder(), &_irInjectorMap, irModule, scope);
    } else if (irStatement->is(IR_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE)) {
        _irInjectorMap.getClassPropertyAssignmentIRInjectorStrategy()->inject((IRClassPropertyAssignmentStatementNode*)irStatement, irBlock->getBuilder(), &_irInjectorMap, irModule, scope);
    }
}

llvm::Value* IRInjector::inject(IRBlockNode* irBlock, IRExpressionNode* irExpression, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope) {
    return _irInjectorMap.getInjector(irExpression->getTypeSignature())->inject(irExpression, irBlock->getBuilder(), &_irInjectorMap, irOperationType, irModule, scope);
}

void IRInjector::injectVoidReturnType(IRBlockNode* irBlock) {
    irBlock->getBuilder()->get()->CreateRet(irBlock->getBuilder()->get()->getInt32(0));
}