//
// Created by Johny Georges on 2024-06-12.
//

#ifndef JETLANG_IR_LOOKUP_TABLE_H
#define JETLANG_IR_LOOKUP_TABLE_H

#include <unordered_map>
#include <optional>
#include "../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../ir-nodes/ir-instruction-node.h"

class IRLookupTable : public std::enable_shared_from_this<IRLookupTable> {
private:
    std::string _moduleId;
    std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> _globalScope;
    std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> _scope;
    std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> _arcScope;
    std::optional<std::shared_ptr<IRLookupTable>> _outerScope;
    std::unordered_map<std::string, std::shared_ptr<IRType>> _typeScope;
    std::unordered_map<std::string, std::shared_ptr<IRType>> _globalTypeScope;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<IRLookupTable>>> _linkedScopes;
public:
    explicit IRLookupTable(std::optional<std::shared_ptr<IRLookupTable>> outerScope = {});
    explicit IRLookupTable(std::string moduleId, std::optional<std::shared_ptr<IRLookupTable>> outerScope = {});
    std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> getGlobalScope();
    std::unordered_map<std::string, std::shared_ptr<IRType>> getTypeScope();
    std::unordered_map<std::string, std::shared_ptr<IRType>> getGlobalTypeScope();
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<IRLookupTable>>> getLinkedScopes();
    std::string getModuleId();
    void inherit(std::shared_ptr<IRLookupTable> otherScope);
    void link(std::shared_ptr<IRLookupTable> otherScope);
    std::shared_ptr<IRLookupTable> insert(std::string key, std::shared_ptr<IRInstructionNode> value);
    std::shared_ptr<IRLookupTable> insertArc(std::string key, std::shared_ptr<IRInstructionNode> value);
    std::shared_ptr<IRLookupTable> insert(std::string key, std::shared_ptr<IRType> value);
    std::shared_ptr<IRLookupTable> insertGlobalType(std::string key, std::shared_ptr<IRType> value);
    std::optional<std::shared_ptr<IRInstructionNode>> find(std::string key);
    std::optional<std::shared_ptr<IRInstructionNode>> findArc(std::string key);
    std::optional<std::shared_ptr<IRInstructionNode>> findAcrossScopes(std::string key);
    std::optional<std::shared_ptr<IRInstructionNode>> findAcrossScopes(std::string moduleId, std::string key);
    std::optional<std::shared_ptr<IRType>> findType(std::string key);
    std::optional<std::shared_ptr<IRType>> findType(std::string moduleId, std::string key);
    std::optional<std::shared_ptr<IRType>> findGlobalType(std::string key);
    std::optional<std::shared_ptr<IRType>> findGlobalType(std::string moduleId, std::string key);
    std::shared_ptr<IRLookupTable> insertGlobalVariable(std::string key, std::shared_ptr<IRInstructionNode> value);
    std::optional<std::shared_ptr<IRInstructionNode>> findGlobalVariable(std::string key);
    std::optional<std::shared_ptr<IRInstructionNode>> findGlobalVariable(std::string moduleId, std::string key);
    std::optional<std::shared_ptr<IRInstructionNode>> getClassScope();
    void dump();
};

#endif //JETLANG_IR_LOOKUP_TABLE_H
