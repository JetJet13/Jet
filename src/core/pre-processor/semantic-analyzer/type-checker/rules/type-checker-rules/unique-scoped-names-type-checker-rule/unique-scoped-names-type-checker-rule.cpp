//
// Created by Johny Georges on 2024-05-28.
//

#include "unique-scoped-names-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

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
    auto classStaticPropertyNames = std::set<std::string>();
    for (auto classStaticProperty : *classDeclaration->getBlock()->getStaticProperties()) {
        auto name = classStaticProperty->getPropertyName()->getId();
        classStaticPropertyNames.insert(name);
    }
    auto classStaticMethodNames = std::set<std::string>();
    for (auto classStaticMethod : *classDeclaration->getBlock()->getStaticMethods()) {
        auto name = classStaticMethod->getClassMethodDefinition()->getMethodName()->getId();
        classStaticMethodNames.insert(name);
    }

    // check for conflicts
    for (auto classProperty : *classDeclaration->getBlock()->getInstanceProperties()) {
        auto name = classProperty->getPropertyName()->getId();
        if (classMethodNames.find(name) != classMethodNames.end()) {
            auto propertyNameConflictsWithMethodMessage = TypeCheckerErrorMessageTable::ClassPropertyNameConflictsWithMethodName(classProperty);
            typeCheckerResult->addError(propertyNameConflictsWithMethodMessage());
        }
        if (classStaticPropertyNames.find(name) != classStaticPropertyNames.end()) {
            auto propertyNameConflictsWithStaticPropertyMessage = TypeCheckerErrorMessageTable::ClassPropertyNameConflictsWithStaticPropertyName(classProperty);
            typeCheckerResult->addError(propertyNameConflictsWithStaticPropertyMessage());
        }
        if (classStaticMethodNames.find(name) != classStaticMethodNames.end()) {
            auto propertyNameConflictsWithStaticMethodMessage = TypeCheckerErrorMessageTable::ClassPropertyNameConflictsWithStaticMethodName(classProperty);
            typeCheckerResult->addError(propertyNameConflictsWithStaticMethodMessage());
        }
    }
    for (auto classMethod : *classDeclaration->getBlock()->getInstanceMethods()) {
        auto name = classMethod->getClassMethodDefinition()->getMethodName()->getId();
        if (classStaticPropertyNames.find(name) != classStaticPropertyNames.end()) {
            auto methodNameConflictsWithStaticPropertyMessage = TypeCheckerErrorMessageTable::ClassMethodNameConflictsWithStaticPropertyName(classMethod);
            typeCheckerResult->addError(methodNameConflictsWithStaticPropertyMessage());
        }
        if (classStaticMethodNames.find(name) != classStaticMethodNames.end()) {
            auto methodNameConflictsWithStaticMethodMessage = TypeCheckerErrorMessageTable::ClassMethodNameConflictsWithStaticMethodName(classMethod);
            typeCheckerResult->addError(methodNameConflictsWithStaticMethodMessage());
        }
    }
    for (auto classStaticProperty : *classDeclaration->getBlock()->getStaticProperties()) {
        auto name = classStaticProperty->getPropertyName()->getId();
        if (classStaticMethodNames.find(name) != classStaticMethodNames.end()) {
            auto staticPropertyNameConflictsWithStaticMethodMessage = TypeCheckerErrorMessageTable::ClassStaticPropertyNameConflictsWithStaticMethodName(classStaticProperty);
            typeCheckerResult->addError(staticPropertyNameConflictsWithStaticMethodMessage());
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