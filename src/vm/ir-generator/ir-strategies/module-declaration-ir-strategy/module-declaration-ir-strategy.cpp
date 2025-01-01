//
// Created by Johny Georges on 2024-10-29.
//

#include "module-declaration-ir-strategy.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRModuleDeclarationNode* ModuleDeclarationIRStrategy::generate(ASTModuleDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto exports = std::vector<IRDeclarationNode*>();
    auto moduleIrType = irGenerator->generateTypeFor(node->getTypeSignature(), scope);
    for (auto exportedNode : *node->getExports()) {
        auto irNode = scope->findAcrossScopes(exportedNode->getId());
        if (irNode) {
            exports.push_back((IRDeclarationNode*)irNode.value());
        } else {
            throw std::logic_error("failed to find ir-node for exported node");
        }
    }
    auto allocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(moduleIrType));
    return new IRModuleDeclarationNode(node, allocation, moduleIrType, exports);
}