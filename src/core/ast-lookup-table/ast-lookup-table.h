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

class ASTLookupTable {
private:
    std::unordered_map<std::string, std::shared_ptr<ASTDeclarationNode>> _globalScope;
    std::unordered_map<std::string, std::shared_ptr<ASTNode>> _scope;
    std::unordered_map<std::string, ASTLookupTable*> _childScopes;
    std::optional<ASTLookupTable*> _outerScope;
    std::optional<std::shared_ptr<ASTLambdaExpressionNode>> _lambda = {};
    std::optional<std::shared_ptr<ASTLambdaWithFatArrowExpressionNode>> _lambdaFatArrow = {};
public:
    explicit ASTLookupTable(std::optional<ASTLookupTable*> outerScope = {});
    std::unordered_map<std::string, std::shared_ptr<ASTDeclarationNode>> getGlobalScope();
    void inherit(ASTLookupTable* otherScope);
    ASTLookupTable* insert(std::string key, std::shared_ptr<ASTNode> value);
    ASTLookupTable* insertGlobalVariable(std::string key, std::shared_ptr<ASTDeclarationNode> value);
    ASTLookupTable* insertChildScope(std::string key, ASTLookupTable* value);
    ASTLookupTable* capture(std::shared_ptr<ASTNode> node);
    void bindLambda(std::shared_ptr<ASTLambdaExpressionNode> lambdaExpressionNode);
    bool isLambdaScope();
    void bindLambdaFatArrow(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> lambdaWithFatArrowExpressionNode);
    std::optional<std::shared_ptr<ASTNode>> find(std::string key);
    std::optional<std::shared_ptr<ASTNode>> findWithin(std::string key);
    std::optional<std::shared_ptr<ASTNode>> findInOuterScope(std::string key);
    std::optional<std::shared_ptr<ASTNode>> findAcrossScopes(std::string key);
    std::optional<std::shared_ptr<ASTNode>> findGlobalVariable(std::string key);
    std::optional<ASTLookupTable*> findChildScope(std::string key);
    std::optional<ASTLookupTable*> getOuterScope();
    void dumpFromRootScope();
    void dump(int indent = 0);
};

#endif //JETLANG_AST_LOOKUP_TABLE_H
