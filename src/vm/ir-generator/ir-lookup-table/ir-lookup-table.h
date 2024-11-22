//
// Created by Johny Georges on 2024-06-12.
//

#ifndef JETLANG_IR_LOOKUP_TABLE_H
#define JETLANG_IR_LOOKUP_TABLE_H

#include <unordered_map>
#include <optional>
#include "../../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../../ir-nodes/ir-instruction-node.h"
#include "../../ir-nodes/ir-global-variable-node.h"

class IRLookupTable {
private:
    std::unordered_map<std::string, IRGlobalVariableNode*> _globalScope;
    std::unordered_map<std::string, IRInstructionNode*> _scope;
    std::optional<IRLookupTable*> _outerScope;
public:
    explicit IRLookupTable(std::optional<IRLookupTable*> outerScope = {});
    std::unordered_map<std::string, IRGlobalVariableNode*> getGlobalScope();
    void inheritGlobalScope(IRLookupTable* otherScope);
    IRLookupTable* insert(std::string key, IRInstructionNode* value);
    std::optional<IRInstructionNode*> find(std::string key);
    std::optional<IRNode*> findAcrossScopes(std::string key);
    IRLookupTable* insertGlobalVariable(std::string key, IRGlobalVariableNode* value);
    std::optional<IRGlobalVariableNode*> findGlobalVariable(std::string key);
    void dump();
};

#endif //JETLANG_IR_LOOKUP_TABLE_H
