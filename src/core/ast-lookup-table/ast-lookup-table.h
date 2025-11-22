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
    std::unordered_map<std::string, ASTDeclarationNode*> _globalScope;
    std::unordered_map<std::string, ASTNode*> _scope;
    std::unordered_map<std::string, ASTLookupTable*> _childScopes;
    std::optional<ASTLookupTable*> _outerScope;
    std::optional<ASTLambdaExpressionNode*> _lambda = {};
    std::optional<ASTLambdaWithFatArrowExpressionNode*> _lambdaFatArrow = {};
public:
    explicit ASTLookupTable(std::optional<ASTLookupTable*> outerScope = {});
    std::unordered_map<std::string, ASTDeclarationNode*> getGlobalScope();
    void inherit(ASTLookupTable* otherScope);
    ASTLookupTable* insert(std::string key, ASTNode* value);
    ASTLookupTable* insertGlobalVariable(std::string key, ASTDeclarationNode* value);
    ASTLookupTable* insertChildScope(std::string key, ASTLookupTable* value);
    ASTLookupTable* capture(ASTNode* node);
    void bindLambda(ASTLambdaExpressionNode* lambdaExpressionNode);
    bool isLambdaScope();
    void bindLambdaFatArrow(ASTLambdaWithFatArrowExpressionNode* lambdaWithFatArrowExpressionNode);
    std::optional<ASTNode*> find(std::string key);
    std::optional<ASTNode*> findWithin(std::string key);
    std::optional<ASTNode*> findInOuterScope(std::string key);
    std::optional<ASTNode*> findAcrossScopes(std::string key);
    std::optional<ASTNode*> findGlobalVariable(std::string key);
    std::optional<ASTLookupTable*> findChildScope(std::string key);
    std::optional<ASTLookupTable*> getOuterScope();
    void dumpFromRootScope();
    void dump(int indent = 0);
};

#endif //JETLANG_AST_LOOKUP_TABLE_H
