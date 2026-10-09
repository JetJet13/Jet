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
// Created by Johny Georges on 2024-12-31.
//

#ifndef JETLANG_IR_NEW_CLASS_INSTANCE_TYPE_H
#define JETLANG_IR_NEW_CLASS_INSTANCE_TYPE_H

#include "ir-type.h"
#include "ir-class-type.h"
#include "ir-struct-ref-type.h"

class IRNewClassInstanceType : public IRType {
private:
    std::shared_ptr<IRStructRefType> _irClassInstancePropertiesType;
    std::shared_ptr<IRClassType> _irClassType;
    std::string _constructorId;
public:
    IRNewClassInstanceType(std::shared_ptr<IRClassType> irClassType, std::string constructorId, std::shared_ptr<IRStructRefType> irClassInstancePropertiesType);
    std::shared_ptr<IRStructRefType> getIRClassPropertiesType();
    std::shared_ptr<IRClassType> getIRClassType();
    std::shared_ptr<IRFunctionType> getIRConstructorType();
    std::string getIRMethodName(std::string methodName);
    std::string getIRPropertyName(std::string propertyName);
    uint64_t getIndexForProperty(std::string propertyName);
    std::shared_ptr<IRType> getIRTypeForProperty(std::string propertyName);
    std::optional<std::shared_ptr<IRFunctionType>> getIRTypeForMethod(std::string methodName);
    uint64_t getSizeInBytes() override;
    llvm::StructType* getType() override;
    bool containsTypeThatRequiresFreeing() override;
    bool isNewClassInstanceType() override;
    llvm::Align getAlignment() override;
    std::shared_ptr<IRType> clone() override;
    void print() override;
};

#endif //JETLANG_IR_NEW_CLASS_INSTANCE_TYPE_H
