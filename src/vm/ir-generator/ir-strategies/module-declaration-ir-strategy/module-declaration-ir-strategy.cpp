//
// Created by Johny Georges on 2024-10-29.
//

#include "module-declaration-ir-strategy.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

std::shared_ptr<IRModuleDeclarationNode> ModuleDeclarationIRStrategy::generate(std::shared_ptr<ASTModuleDeclarationNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto exports = std::vector<std::shared_ptr<IRDeclarationNode>>();
    auto moduleIrType = irGenerator->generateTypeFor(node->getModuleTypeSignature(), scope, irContext);
    for (auto exportedNode : *node->getExports()) {
        auto irNode = scope->findAcrossScopes(exportedNode->getId());
        if (irNode) {
            exports.push_back(std::dynamic_pointer_cast<IRDeclarationNode>(irNode.value()));
        } else {
            throw std::logic_error("failed to find ir-node for exported node");
        }
    }
    auto allocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(moduleIrType));
    return std::make_shared<IRModuleDeclarationNode>(node, allocation, moduleIrType, exports);
}