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
// Created by Johny Georges on 2024-05-28.
//

#include "unique-scoped-names-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void UniqueScopedNamesTypeCheckerRule::enforce(std::shared_ptr<ASTClassDeclarationNode> classDeclaration, TypeCheckerResult* typeCheckerResult) {
    // populate sets of names
    auto classPropertyNames = std::set<std::string>();
    for (auto classProperty : *classDeclaration->getBlock()->getInstanceProperties()) {
        auto name = classProperty->getPropertyName()->getId();
        classPropertyNames.insert(name);
    }
    auto classMethodNames = std::set<std::string>();
    for (auto classMethod : *classDeclaration->getBlock()->getInstanceMethods()) {
        auto name = classMethod->getClassMethodDefinition()->getMethodName()->getId();
        classMethodNames.insert(name);
    }


    // check for conflicts
    for (auto classProperty : *classDeclaration->getBlock()->getInstanceProperties()) {
        auto name = classProperty->getPropertyName()->getId();
        if (classMethodNames.find(name) != classMethodNames.end()) {
            auto propertyNameConflictsWithMethodMessage = TypeCheckerErrorMessageTable::ClassPropertyNameConflictsWithMethodName(classProperty);
            typeCheckerResult->addError(propertyNameConflictsWithMethodMessage());
        }
    }

}

void UniqueScopedNamesTypeCheckerRule::enforce(std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>* classProperties, TypeCheckerResult* typeCheckerResult) {
    auto seenNames = std::set<std::string>();
    for (auto classProperty : *classProperties) {
        auto name = classProperty->getPropertyName()->getId();
        if (seenNames.find(name) != seenNames.end()) {
            auto variableNamesNotUniqueMessage = TypeCheckerErrorMessageTable::ClassPropertyNamesNotUnique(classProperty);
            typeCheckerResult->addError(variableNamesNotUniqueMessage());
        } else {
            seenNames.insert(name);
        }
    }
}

void UniqueScopedNamesTypeCheckerRule::enforce(std::vector<std::shared_ptr<ASTVariableDeclarationNode>>* names, TypeCheckerResult* typeCheckerResult) {
    auto seenNames = std::set<std::string>();
    for (auto identifier : *names) {
        if (seenNames.find(identifier->getId()) != seenNames.end()) {
            auto variableNamesNotUniqueMessage = TypeCheckerErrorMessageTable::VariableNamesNotUnique(identifier);
            typeCheckerResult->addError(variableNamesNotUniqueMessage());
            return;
        } else {
            seenNames.insert(identifier->getId());
        }
    }
}

void UniqueScopedNamesTypeCheckerRule::enforce(std::vector<std::shared_ptr<ASTClassDeclarationNode>>* classes, TypeCheckerResult* typeCheckerResult) {
    auto seenNames = std::set<std::string>();
    for (auto classDeclaration : *classes) {
        if (seenNames.find(classDeclaration->getId()) != seenNames.end()) {
            auto variableNamesNotUniqueMessage = TypeCheckerErrorMessageTable::ClassNameConflictsWithAnotherClass(classDeclaration);
            typeCheckerResult->addError(variableNamesNotUniqueMessage());
            return;
        } else {
            seenNames.insert(classDeclaration->getId());
        }
    }
}

void UniqueScopedNamesTypeCheckerRule::enforce(std::vector<std::shared_ptr<ASTEnumDeclarationNode>>* enums, TypeCheckerResult* typeCheckerResult) {
    auto seenNames = std::set<std::string>();
    for (auto enumDeclaration : *enums) {
        if (seenNames.find(enumDeclaration->getId()) != seenNames.end()) {
            auto variableNamesNotUniqueMessage = TypeCheckerErrorMessageTable::EnumNameConflictsWithAnotherEnum(enumDeclaration);
            typeCheckerResult->addError(variableNamesNotUniqueMessage());
            return;
        } else {
            seenNames.insert(enumDeclaration->getId());
        }
    }
}

void UniqueScopedNamesTypeCheckerRule::enforce(std::vector<std::shared_ptr<ASTCustomTypeDeclarationNode>>* customTypes, TypeCheckerResult* typeCheckerResult) {
    auto seenCustomTypes = std::set<std::string>();
    for (auto customType : *customTypes) {
        if (seenCustomTypes.find(customType->getId()) != seenCustomTypes.end()) {
            auto typeNameConflictsMessage = TypeCheckerErrorMessageTable::CustomTypeNameConflictsWithAnotherCustomType(customType);
            typeCheckerResult->addError(typeNameConflictsMessage());
            return;
        } else {
            seenCustomTypes.insert(customType->getId());
        }
    }
}

void UniqueScopedNamesTypeCheckerRule::enforce(std::vector<std::shared_ptr<ASTFunctionDeclarationNode>>* functions, TypeCheckerResult* typeCheckerResult) {
    auto seenFunctions = std::set<std::string>();
    for (auto function : *functions) {
        auto identifier = FunctionIdGenerator::generateFor(function);
        if (seenFunctions.find(identifier) != seenFunctions.end()) {
            auto functionConflictMessage = TypeCheckerErrorMessageTable::FunctionTypeSignatureConflictsWithAnotherFunction(function->getDefinition());
            typeCheckerResult->addError(functionConflictMessage());
            return;
        } else {
            seenFunctions.insert(identifier);
        }
    }
}

void UniqueScopedNamesTypeCheckerRule::enforce(std::vector<std::shared_ptr<ASTProcedureDeclarationNode>>* procedures, TypeCheckerResult* typeCheckerResult) {
    auto seenProcedures = std::set<std::string>();
    for (auto procedure : *procedures) {
        auto identifier = FunctionIdGenerator::generateFor(procedure);
        if (seenProcedures.find(identifier) != seenProcedures.end()) {
            auto procedureConflictMessage = TypeCheckerErrorMessageTable::ProcedureTypeSignatureConflictsWithAnotherProcedure(procedure->getDefinition());
            typeCheckerResult->addError(procedureConflictMessage());
            return;
        } else {
            seenProcedures.insert(identifier);
        }
    }
}


TypeCheckerRuleType UniqueScopedNamesTypeCheckerRule::getType() {
    return UNIQUE_SCOPED_NAMES_TCR;
}

std::string UniqueScopedNamesTypeCheckerRule::toString() {
    return "UNIQUE_SCOPED_NAMES";
}

bool UniqueScopedNamesTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void UniqueScopedNamesTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}