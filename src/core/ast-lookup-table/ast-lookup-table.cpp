//
// Created by Johny Georges on 2025-03-22.
//

#include "ast-lookup-table.h"
#include <stack>
#include "../../shared/utils/logger/logger.h"

ASTLookupTable::ASTLookupTable(std::optional<ASTLookupTable*> outerScope) {
    _globalScope = std::unordered_map<std::string, ASTDeclarationNode*>();
    _scope = std::unordered_map<std::string, ASTNode*>();
    _childScopes = std::unordered_map<std::string, ASTLookupTable*>();
    _outerScope = outerScope;
}

std::unordered_map<std::string, ASTDeclarationNode*> ASTLookupTable::getGlobalScope() {
    return _globalScope;
}

void ASTLookupTable::inherit(ASTLookupTable* otherScope) {
    _globalScope = otherScope->getGlobalScope();
}

ASTLookupTable* ASTLookupTable::insert(std::string key, ASTNode* value) {
    _scope[key] = value;
    return this;
}

ASTLookupTable* ASTLookupTable::insertCapturedVariable(ASTNode* node) {
    if (_lambda) {
        _lambda.value()->addCapturedVariableId(node->getId());
    }

    if (_lambdaFatArrow) {
        _lambdaFatArrow.value()->addCapturedVariableId(node->getId());
    }
    return this;
}

void ASTLookupTable::markAsLambdaScope(ASTLambdaExpressionNode* lambdaExpressionNode) {
    _lambda = lambdaExpressionNode;
}

bool ASTLookupTable::isLambdaScope() {
    return _lambda.has_value() || _lambdaFatArrow.has_value();
}

void ASTLookupTable::markAsLambdaFatArrowScope(ASTLambdaWithFatArrowExpressionNode* lambdaWithFatArrowExpressionNode) {
    _lambdaFatArrow = lambdaWithFatArrowExpressionNode;
}

bool ASTLookupTable::isLambdaFatArrowScope() {
    return _lambdaFatArrow.has_value();
}

std::optional<ASTLambdaWithFatArrowExpressionNode*> ASTLookupTable::getLambdaFatArrowExpression() {
    return _lambdaFatArrow;
}

std::optional<ASTNode*> ASTLookupTable::find(std::string key) {
    auto result = _scope.find(key);
    if (result == _scope.end()) {
        if (_outerScope) {
            return _outerScope.value()->find(key);
        }
        return {};
    } else {
        return result->second;
    }
}

std::optional<ASTNode*> ASTLookupTable::findWithin(std::string key) {
    auto result = _scope.find(key);
    if (result == _scope.end()) {
        return {};
    } else {
        return result->second;
    }
}
std::optional<ASTNode*> ASTLookupTable::findInOuterScope(std::string key) {
    if (!_outerScope) {
        return {};
    }
    return _outerScope.value()->find(key);
}

std::optional<ASTNode*> ASTLookupTable::findAcrossScopes(std::string key) {
    auto result = this->find(key);
    if (result) {
        return result;
    }
    return this->findGlobalVariable(key);
}

ASTLookupTable* ASTLookupTable::insertGlobalVariable(std::string key, ASTDeclarationNode* value) {
    _globalScope[key] = value;
    return this;
}

ASTLookupTable* ASTLookupTable::insertChildScope(std::string key, ASTLookupTable* value) {
    _childScopes[key] = value;
    return this;
}

std::optional<ASTNode*> ASTLookupTable::findGlobalVariable(std::string key) {
    auto result = _globalScope.find(key);
    if (result == _globalScope.end()) {
        if (_outerScope) {
            return _outerScope.value()->findGlobalVariable(key);
        }
        return {};
    } else {
        return result->second;
    }
}

std::optional<ASTLookupTable*> ASTLookupTable::findChildScope(std::string key) {
    auto result = _childScopes.find(key);
    if (result == _childScopes.end()) {
        return {};
    } else {
        return result->second;
    }
}

std::optional<ASTLookupTable*> ASTLookupTable::getOuterScope() {
    return _outerScope;
}

void ASTLookupTable::dumpFromRootScope() {
    auto stack = std::stack<ASTLookupTable*>();
    stack.push(this);
    auto outerScope = _outerScope;
    while (outerScope.has_value()) {
        stack.push(outerScope.value());
        outerScope = outerScope.value()->getOuterScope();
    }

    Logger::log("=========== ASTLookupTable DUMP ===========");
    auto indent = 0;
    while (!stack.empty()) {
        stack.top()->dump(indent);
        stack.pop();
        indent += 2;
    }
    Logger::log("============================================");
}

void ASTLookupTable::dump(int indent) {
    std::string indentSpace;
    for (int i = 0; i < indent; ++i) {
        indentSpace += " ";
    }
    for (const auto& keyValue : _globalScope) {
        Logger::log(indentSpace + "GLOBAL KEY - ", keyValue.first);
    }
    for (const auto& keyValue : _scope) {
        Logger::log(indentSpace + "KEY - ", keyValue.first);
    }
}