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
// Created by Johny Georges on 2024-06-19.
//

#ifndef JETLANG_IR_TYPE_H
#define JETLANG_IR_TYPE_H

#include <llvm/Support/Alignment.h>
#include <llvm/IR/DerivedTypes.h>
#include "../ir-nodes/ir-type-value-instruction-node.h"

// forward declaration
class IRInstructionNode;
class IRTypeValueInstructionNode;

class IRType : public std::enable_shared_from_this<IRType> {
protected:
    std::string _moduleId;
    std::string _id;
    llvm::Type* _type;
    std::optional<std::shared_ptr<IRTypeValueInstructionNode>> _value;
    std::optional<llvm::Align> _alignmentOverride;
    std::optional<uint64_t> _sizeInBytesOverride;
    void initClone(std::shared_ptr<IRType> irType);
public:
    explicit IRType(llvm::Type* type);
    virtual llvm::Type* getType();
    virtual std::shared_ptr<IRType> getUnderlyingType();
    virtual std::shared_ptr<IRType> getSourceType();
    virtual uint64_t getSizeInBytes();
    virtual llvm::Align getAlignment();
    virtual void setAlignmentOverride(llvm::Align alignmentOverride);
    std::string getId();
    std::string getModuleId();
    bool hasId();
    void setId(std::string id);
    void setModuleId(std::string id);
    void setValue(std::shared_ptr<IRTypeValueInstructionNode> value);
    virtual std::shared_ptr<IRTypeValueInstructionNode> getValue();
    void setSizeInBytesOverride(uint64_t sizeInBytes);
    bool hasValue();
    bool isCharType();
    bool isIntegerType();
    bool isInteger64Type();
    bool isFloatType();
    bool isBoolType();
    bool isLiteralType();
    virtual bool isArrayType();
    virtual bool isStructType();
    virtual bool isStructRefType();
    virtual bool isEnumType();
    virtual bool isModuleType();
    virtual bool isPointerType();
    virtual bool isArrayPointerType();
    virtual bool isInvocableType();
    virtual bool isLambdaType();
    virtual bool isFunctionType();
    virtual bool isClassType();
    virtual bool isClassInstanceType();
    virtual bool isNewClassInstanceType();
    virtual bool isTypeValueType();
    virtual bool isSharedType();
    virtual bool isVoidType();
    virtual bool isCapturedVariableType();
    virtual bool containsTypeThatRequiresFreeing();
    virtual bool requiresArc();
    bool isEqual(std::shared_ptr<IRType> otherValue);
    bool isNotEqual(std::shared_ptr<IRType> otherValue);
    bool isLessThan(std::shared_ptr<IRType> otherValue);
    bool isLessThanOrEqual(std::shared_ptr<IRType> otherValue);
    bool isGreaterThan(std::shared_ptr<IRType> otherValue);
    bool isGreaterThanOrEqual(std::shared_ptr<IRType> otherValue);
    virtual std::shared_ptr<IRType> clone();
    virtual void print();
};

#endif //JETLANG_IR_TYPE_H
