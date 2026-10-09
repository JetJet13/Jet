// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-10-29.
//

#include "module-declaration-ir-strategy.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

std::shared_ptr<IRModuleDeclarationNode> ModuleDeclarationIRStrategy::generate(std::shared_ptr<ASTModuleDeclarationNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
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