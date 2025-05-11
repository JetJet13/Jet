//
// Created by Johny Georges on 2024-06-12.
//

#ifndef JETLANG_IR_LOOKUP_TABLE_H
#define JETLANG_IR_LOOKUP_TABLE_H

#include <unordered_map>
#include <optional>
#include "../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../ir-nodes/ir-instruction-node.h"
#include "../ir-nodes/ir-load-instruction-node.h"

class IRLookupTable {
private:
    std::unordered_map<std::string, IRInstructionNode*> _globalScope;
    std::unordered_map<std::string, IRInstructionNode*> _scope;
    std::unordered_map<std::string, IRLoadInstructionNode*> _loadedScope;
    std::optional<IRLookupTable*> _outerScope;
    std::unordered_map<std::string, IRType*> _typeScope;
public:
    explicit IRLookupTable(std::optional<IRLookupTable*> outerScope = {});
    std::unordered_map<std::string, IRInstructionNode*> getGlobalScope();
    std::unordered_map<std::string, IRType*> getTypeScope();
    void inherit(IRLookupTable* otherScope);
    IRLookupTable* insert(std::string key, IRInstructionNode* value);
    IRLookupTable* insert(std::string key, IRLoadInstructionNode* value);
    IRLookupTable* insert(std::string key, IRType* value);
    std::optional<IRInstructionNode*> find(std::string key);
    std::optional<IRLoadInstructionNode*> findLoaded(std::string key);
    std::optional<IRInstructionNode*> findAcrossScopes(std::string key);
    std::optional<IRType*> findType(std::string key);
    IRLookupTable* insertGlobalVariable(std::string key, IRInstructionNode* value);
    std::optional<IRInstructionNode*> findGlobalVariable(std::string key);
    std::optional<IRInstructionNode*> getClassScope();
    std::vector<IRInstructionNode*> getAllInstructionsToFree();
    std::vector<IRInstructionNode*> getInstructionsToFree();
    void dump();
};

#endif //JETLANG_IR_LOOKUP_TABLE_H
