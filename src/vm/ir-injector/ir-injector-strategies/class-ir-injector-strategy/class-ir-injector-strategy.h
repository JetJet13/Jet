//
// Created by Johny Georges on 2025-12-27.
//

#ifndef JETLANG_CLASS_IR_INJECTOR_STRATEGY_H
#define JETLANG_CLASS_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-class-declaration-node.h"


class ClassIRInjectorStrategy {
private:
    void injectPreConstructor(IRClassPreConstructorNode* irClassPreConstructorNode, IRClassType* irClassType, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope);
    void injectConstructor(IRClassConstructorNode* irClassConstructorNode, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope);
    void injectMethod(IRClassMethodNode* irClassMethodNode, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope);
public:
    void inject(IRClassDeclarationNode* irClassDeclarationNode, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope);
};

#endif //JETLANG_CLASS_IR_INJECTOR_STRATEGY_H
