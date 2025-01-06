//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_IR_INJECTOR_H
#define JETLANG_IR_INJECTOR_H

#include "../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../ir-nodes/ir-block-node.h"
#include "./ir-injector-map.h"
#include "../ir-lookup-table/ir-lookup-table.h"

class IRInjector {
private:
    IRInjectorMap _irInjectorMap;
public:
    IRInjector();
    void inject(IRBlockNode* irBlock, IRNode* irNode, IRModuleNode* irModule, IRLookupTable* scope);
    void inject(IRBlockNode* irBlock, IRDeclarationNode* irDeclaration, IRModuleNode* irModule, IRLookupTable* scope);
    void inject(IRBlockNode* irBlock, IRStatementNode* irStatement, IRModuleNode* irModule, IRLookupTable* scope);
    llvm::Value* inject(IRBlockNode* irBlock, IRExpressionNode* irExpression, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope);
    void injectVoidReturnType(IRBlockNode* irBlock);
};

#endif //JETLANG_IR_INJECTOR_H
