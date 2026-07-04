//
// Created by Johny Georges on 2025-03-22.
//

#include "ast-lookup-table.h"
#include <stack>
#include "../../shared/utils/logger/logger.h"

ASTLookupTable::ASTLookupTable(std::optional<ASTLookupTable*> outerScope) {
    _globalScope = std::unordered_map<std::string, std::shared_ptr<ASTDeclarationNode>>();
    _scope = std::unordered_map<std::string, std::shared_ptr<ASTNode>>();
    _childScopes = std::unordered_map<std::string, ASTLookupTable*>();
    _outerScope = outerScope;
}

std::unordered_map<std::string, std::shared_ptr<ASTDeclarationNode>> ASTLookupTable::getGlobalScope() {
    return _globalScope;
}

void ASTLookupTable::inherit(ASTLookupTable* otherScope) {
    _globalScope = otherScope->getGlobalScope();
}

ASTLookupTable* ASTLookupTable::insert(std::string key, std::shared_ptr<ASTNode> value) {
    _scope[key] = value;
    return this;
}

ASTLookupTable* ASTLookupTable::capture(std::shared_ptr<ASTNode> node) {
    if (_lambda) {
        _lambda.value()->addCapturedValueId(node->getId());
    }

    if (_lambdaFatArrow) {
        _lambdaFatArrow.value()->addCapturedValueId(node->getId());
    }

    if (_outerScope && _outerScope.value()->isLambdaScope() && !_outerScope.value()->findWithin(node->getId())) {
        _outerScope.value()->capture(node);
    }
    return this;
}

void ASTLookupTable::bindLambda(std::shared_ptr<ASTLambdaExpressionNode> lambdaExpressionNode) {
    _lambda = lambdaExpressionNode;
}

bool ASTLookupTable::isLambdaScope() {
    return _lambda.has_value() || _lambdaFatArrow.has_value();
}

void ASTLookupTable::bindLambdaFatArrow(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> lambdaWithFatArrowExpressionNode) {
    _lambdaFatArrow = lambdaWithFatArrowExpressionNode;
}

std::optional<std::shared_ptr<ASTNode>> ASTLookupTable::find(std::string key) {
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

std::optional<std::shared_ptr<ASTNode>> ASTLookupTable::findWithin(std::string key) {
    auto result = _scope.find(key);
    if (result == _scope.end()) {
        return {};
    } else {
        return result->second;
    }
}
std::optional<std::shared_ptr<ASTNode>> ASTLookupTable::findInOuterScope(std::string key) {
    if (!_outerScope) {
        return {};
    }
    return _outerScope.value()->find(key);
}

std::optional<std::shared_ptr<ASTNode>> ASTLookupTable::findAcrossScopes(std::string key) {
    auto result = this->find(key);
    if (result) {
        return result;
    }
    return this->findGlobalVariable(key);
}

ASTLookupTable* ASTLookupTable::insertGlobalVariable(std::string key, std::shared_ptr<ASTDeclarationNode> value) {
    _globalScope[key] = value;
    return this;
}

ASTLookupTable* ASTLookupTable::insertChildScope(std::string key, ASTLookupTable* value) {
    _childScopes[key] = value;
    return this;
}

std::optional<std::shared_ptr<ASTNode>> ASTLookupTable::findGlobalVariable(std::string key) {
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