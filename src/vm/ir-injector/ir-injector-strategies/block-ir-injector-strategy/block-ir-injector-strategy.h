//
// Created by Johny Georges on 2025-05-19.
//

#ifndef JETLANG_BLOCK_IR_INJECTOR_STRATEGY_H
#define JETLANG_BLOCK_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"

class BlockIRInjectorStrategy {
public:
    void inject(IRBlockNode* irBlockNode, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
};

#endif //JETLANG_BLOCK_IR_INJECTOR_STRATEGY_H
