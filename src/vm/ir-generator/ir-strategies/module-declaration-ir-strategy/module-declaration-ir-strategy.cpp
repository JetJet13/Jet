//
// Created by Johny Georges on 2024-10-29.
//

#include "module-declaration-ir-strategy.h"

IRModuleDeclarationNode* ModuleDeclarationIRStrategy::generate(ASTModuleDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto exports = std::vector<IRNode*>();
    for (auto exportedNode : *node->getExports()) {
        auto irNode = scope->findAcrossScopes(exportedNode->getId());
        if (irNode) {
            exports.push_back(irNode.value());
        } else {
            throw std::logic_error("failed to find ir-node for exported node");
        }
    }
    return new IRModuleDeclarationNode(node, exports);
}