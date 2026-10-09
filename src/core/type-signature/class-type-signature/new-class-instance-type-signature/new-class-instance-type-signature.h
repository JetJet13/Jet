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
// Created by Johny Georges on 2024-05-15.
//

#ifndef JETLANG_NEW_CLASS_INSTANCE_TYPE_SIGNATURE_H
#define JETLANG_NEW_CLASS_INSTANCE_TYPE_SIGNATURE_H

#include "../../type-signature.h"
#include "../class-type-signature.h"

class NewClassInstanceTypeSignature : public TypeSignature {
private:
    std::optional<std::shared_ptr<ClassTypeSignature>> _classTypeSignature;
    std::optional<std::pair<std::string, std::shared_ptr<ClassConstructorTypeSignature>>> _constructorInfo;
public:
    NewClassInstanceTypeSignature();
    NewClassInstanceTypeSignature(std::shared_ptr<ClassTypeSignature> classTypeSignature, std::optional<std::pair<std::string, std::shared_ptr<ClassConstructorTypeSignature>>> constructorInfo = {});
    std::shared_ptr<ClassTypeSignature> getClassTypeSignature();
    TypeSignatureMap<std::shared_ptr<TypeSignature>>* getClassInterface();
    std::shared_ptr<ClassConstructorTypeSignature> getConstructorTypeSignature();
    std::optional<std::shared_ptr<ClassMethodTypeSignature>> findMethod(std::string methodName);
    std::optional<std::shared_ptr<ClassPropertyTypeSignature>> findProperty(std::string propertyName);
    bool hasConstructorInfo();
    std::string getConstructorId();
    void setConstructorInfo(std::pair<std::string, std::shared_ptr<ClassConstructorTypeSignature>> constructorInfo);
    std::shared_ptr<TypeSignature> convertToVariableTypeSignature() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isInvalid() override;
    void print() override;
};


#endif //JETLANG_NEW_CLASS_INSTANCE_TYPE_SIGNATURE_H
