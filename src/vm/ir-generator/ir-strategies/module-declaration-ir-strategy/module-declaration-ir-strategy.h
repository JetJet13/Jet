//
// Created by Johny Georges on 2024-10-29.
//

#ifndef JETLANG_MODULE_DECLARATION_IR_STRATEGY_H
#define JETLANG_MODULE_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-module-declaration-node.h"

class ModuleDeclarationIRStrategy {
public:
    std::shared_ptr<IRModuleDeclarationNode> generate(std::shared_ptr<ASTModuleDeclarationNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
};

#endif //JETLANG_MODULE_DECLARATION_IR_STRATEGY_H
