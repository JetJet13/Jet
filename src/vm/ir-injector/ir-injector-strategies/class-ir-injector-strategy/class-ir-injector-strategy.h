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
    void injectPreConstructor(std::shared_ptr<IRClassPreConstructorNode> irClassPreConstructorNode, std::shared_ptr<IRClassType> irClassType, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    void injectConstructor(std::shared_ptr<IRClassConstructorNode> irClassConstructorNode, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    void injectMethod(std::shared_ptr<IRClassMethodNode> irClassMethodNode, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    void injectStaticProperty(std::shared_ptr<IRClassStaticPropertyNode> irClassStaticPropertyNode, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
public:
    void inject(std::shared_ptr<IRClassDeclarationNode> irClassDeclarationNode, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_CLASS_IR_INJECTOR_STRATEGY_H
