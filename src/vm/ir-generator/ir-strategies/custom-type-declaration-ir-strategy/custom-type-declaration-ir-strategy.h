//
// Created by Johny Georges on 2025-07-07.
//

#ifndef JETLANG_CUSTOM_TYPE_DECLARATION_IR_STRATEGY_H
#define JETLANG_CUSTOM_TYPE_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-type-declaration-nodes/ir-custom-type-declaration-node.h"

class CustomTypeDeclarationIRStrategy {
public:
    std::shared_ptr<IRCustomTypeDeclarationNode> generate(std::shared_ptr<ASTCustomTypeDeclarationNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_CUSTOM_TYPE_DECLARATION_IR_STRATEGY_H
