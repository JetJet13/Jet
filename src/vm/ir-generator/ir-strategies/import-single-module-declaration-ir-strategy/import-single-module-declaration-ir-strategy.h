//
// Created by Johny Georges on 2024-10-30.
//

#ifndef JETLANG_IMPORT_SINGLE_MODULE_DECLARATION_IR_STRATEGY_H
#define JETLANG_IMPORT_SINGLE_MODULE_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-declaration-nodes/ast-import-single-module-declaration-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-import-single-module-declaration-node.h"

class ImportSingleModuleDeclarationIRStrategy {
public:
    std::shared_ptr<IRImportSingleModuleDeclarationNode> generate(std::shared_ptr<ASTImportSingleModuleDeclarationNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_IMPORT_SINGLE_MODULE_DECLARATION_IR_STRATEGY_H
