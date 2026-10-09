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
// Created by Johny Georges on 2025-07-07.
//

#ifndef JETLANG_IR_CUSTOM_TYPE_DECLARATION_NODE_H
#define JETLANG_IR_CUSTOM_TYPE_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "../ir-instruction-node.h"
#include "ir-type-declaration-node.h"
#include "../../ir-type/ir-struct-type.h"
#include "../../../core/ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"

class IRCustomTypeDeclarationNode : public IRTypeDeclarationNode {
private:
    std::shared_ptr<ASTCustomTypeDeclarationNode> _node;
    std::shared_ptr<IRType> _irType;
public:
    IRCustomTypeDeclarationNode(std::shared_ptr<ASTCustomTypeDeclarationNode> node, std::shared_ptr<IRType> irType);
    std::string getName();
    std::shared_ptr<IRType> getIRType();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CUSTOM_TYPE_DECLARATION_NODE_H
