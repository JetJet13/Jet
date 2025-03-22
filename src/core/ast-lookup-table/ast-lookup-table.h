//
// Created by Johny Georges on 2025-03-22.
//

#ifndef JETLANG_AST_LOOKUP_TABLE_H
#define JETLANG_AST_LOOKUP_TABLE_H

#include <unordered_map>
#include <optional>
#include "../ast/ast-nodes/ast-declaration-nodes/ast-declaration-node.h"

class ASTLookupTable {
private:
    std::unordered_map<std::string, ASTDeclarationNode*> _globalScope;
    std::unordered_map<std::string, ASTDeclarationNode*> _scope;
    std::unordered_map<std::string, ASTLookupTable*> _childScopes;
    std::optional<ASTLookupTable*> _outerScope;
public:
    explicit ASTLookupTable(std::optional<ASTLookupTable*> outerScope = {});
    std::unordered_map<std::string, ASTDeclarationNode*> getGlobalScope();
    void inherit(ASTLookupTable* otherScope);
    ASTLookupTable* insert(std::string key, ASTDeclarationNode* value);
    ASTLookupTable* insertGlobalVariable(std::string key, ASTDeclarationNode* value);
    ASTLookupTable* insertChildScope(std::string key, ASTLookupTable* value);
    std::optional<ASTDeclarationNode*> find(std::string key);
    std::optional<ASTDeclarationNode*> findAcrossScopes(std::string key);
    std::optional<ASTDeclarationNode*> findGlobalVariable(std::string key);
    std::optional<ASTLookupTable*> findChildScope(std::string key);
    void dump();
};

#endif //JETLANG_AST_LOOKUP_TABLE_H
