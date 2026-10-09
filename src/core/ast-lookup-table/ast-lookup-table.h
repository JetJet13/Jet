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
// Created by Johny Georges on 2025-03-22.
//

#ifndef JETLANG_AST_LOOKUP_TABLE_H
#define JETLANG_AST_LOOKUP_TABLE_H

#include <unordered_map>
#include <optional>
#include "../ast/ast-nodes/ast-declaration-nodes/ast-declaration-node.h"
#include "../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"
#include "../ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"

class ASTLookupTable : public std::enable_shared_from_this<ASTLookupTable> {
private:
    std::unordered_map<std::string, std::shared_ptr<ASTDeclarationNode>> _globalScope;
    std::unordered_map<std::string, std::shared_ptr<ASTNode>> _scope;
    std::unordered_map<std::string, std::shared_ptr<ASTLookupTable>> _childScopes;
    std::optional<std::shared_ptr<ASTLookupTable>> _outerScope;
    std::optional<std::shared_ptr<ASTLambdaExpressionNode>> _lambda = {};
    std::optional<std::shared_ptr<ASTLambdaWithFatArrowExpressionNode>> _lambdaFatArrow = {};
public:
    explicit ASTLookupTable(std::optional<std::shared_ptr<ASTLookupTable>> outerScope = {});
    std::unordered_map<std::string, std::shared_ptr<ASTDeclarationNode>> getGlobalScope();
    void inherit(std::shared_ptr<ASTLookupTable> otherScope);
    std::shared_ptr<ASTLookupTable> insert(std::string key, std::shared_ptr<ASTNode> value);
    std::shared_ptr<ASTLookupTable> insertGlobalVariable(std::string key, std::shared_ptr<ASTDeclarationNode> value);
    std::shared_ptr<ASTLookupTable> insertChildScope(std::string key, std::shared_ptr<ASTLookupTable> value);
    std::shared_ptr<ASTLookupTable> capture(std::shared_ptr<ASTNode> node);
    void bindLambda(std::shared_ptr<ASTLambdaExpressionNode> lambdaExpressionNode);
    bool isLambdaScope();
    void bindLambdaFatArrow(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> lambdaWithFatArrowExpressionNode);
    std::optional<std::shared_ptr<ASTNode>> find(std::string key);
    std::optional<std::shared_ptr<ASTNode>> findWithin(std::string key);
    std::optional<std::shared_ptr<ASTNode>> findInOuterScope(std::string key);
    std::optional<std::shared_ptr<ASTNode>> findAcrossScopes(std::string key);
    std::optional<std::shared_ptr<ASTNode>> findGlobalVariable(std::string key);
    std::optional<std::shared_ptr<ASTLookupTable>> findChildScope(std::string key);
    std::optional<std::shared_ptr<ASTLookupTable>> getOuterScope();
    void dumpFromRootScope();
    void dump(int indent = 0);
};

#endif //JETLANG_AST_LOOKUP_TABLE_H
