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
// Created by Johny Georges on 2024-07-02.
//

#ifndef JETLANG_IR_EXPRESSION_NODE_H
#define JETLANG_IR_EXPRESSION_NODE_H

#include "../ir-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-pointer-type.h"
#include "../../../core/type-signature/type-signature.h"
#include "../../../core/lexeme/types/position.h"

class IRExpressionNode : public IRNode {
protected:
    bool _isGlobal = false;
    bool _isAssigned = false;
    bool _isReturned = false;
    bool _isGrouped = false;
public:
    virtual void markAsGlobal();
    bool isGlobal();
    bool isAssigned();
    virtual void markAsAssigned();
    bool isReturned();
    virtual void markAsReturned();
    bool isGrouped();
    void markAsGrouped();
    bool needsToBeFreed();
    bool hasArc();
    std::shared_ptr<IRType> getUnderlyingIRType();
    virtual TypeSource getInjectorTypeSource();
    virtual std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation();
    virtual std::optional<std::shared_ptr<IRInstructionNode>> getArc();
    virtual llvm::Type* getType();
    virtual llvm::Type* getTypeAtIndex(uint64_t index);
    virtual llvm::Value* getValue() = 0;
    virtual std::shared_ptr<IRType> getIRType() = 0;
    virtual std::shared_ptr<TypeSignature> getTypeSignature() = 0;
    virtual std::shared_ptr<Position> getStartPosition() = 0;
    virtual std::shared_ptr<Position> getEndPosition() = 0;
    bool isExpression() override;
};

#endif //JETLANG_IR_EXPRESSION_NODE_H
