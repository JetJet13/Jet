//
// Created by Johny Georges on 2025-05-24.
//

#ifndef JETLANG_FOR_IN_STATEMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_FOR_IN_STATEMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-for-in-statement-node/ir-for-in-statement-node.h"
#include "../../ir-injector.h"
#include "../../../ir-type/ir-array-pointer-type.h"

class ForInStatementIRInjectorStrategy {
private:
    llvm::Value* getSourceValue(std::shared_ptr<IRForInStatementNode> irForInStatement, std::shared_ptr<IRArrayPointerType> arrayPointerType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    void finalize(std::shared_ptr<IRForInStatementNode> irForInStatement, std::shared_ptr<IRBlockNode> irBlock);
public:
    void inject(std::shared_ptr<IRForInStatementNode> irForInStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_FOR_IN_STATEMENT_IR_INJECTOR_STRATEGY_H
