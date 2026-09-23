//
// Created by Johny Georges on 2024-07-16.
//

#ifndef JETLANG_IR_STRUCT_TYPE_H
#define JETLANG_IR_STRUCT_TYPE_H

#include <unordered_map>
#include <llvm/IR/Constants.h>
#include "ir-type.h"
#include "ir-pointer-type.h"

class IRStructType : public IRType {
protected:
    llvm::StructType* _type;
    std::unordered_map<uint64_t, std::string> _keyIdMap;
    std::unordered_map<std::string, uint64_t> _keyIndexMap;
    std::unordered_map<std::string, std::shared_ptr<IRType>> _keyTypeMap;
public:
    IRStructType();
    IRStructType(llvm::StructType* type, std::unordered_map<std::string, uint64_t> keyIndexMap, std::unordered_map<uint64_t, std::string> keyIdMap, std::unordered_map<std::string, std::shared_ptr<IRType>> keyTypeMap);
    llvm::StructType* getType() override;
    void makeGlobal(std::string id, std::unique_ptr<llvm::LLVMContext>* context);
    void setAlignmentAndSizeForIRTypes();
    uint64_t size();
    uint64_t getSizeInBytes() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    llvm::Align getAlignment() override;
    std::string getKeyForIndex(uint64_t index);
    std::string getKeyIdForIndex(uint64_t index);
    uint64_t getIndexForKey(std::string key);
    uint64_t getIndexForKey(uint64_t key);
    std::shared_ptr<IRType> getIRTypeForKey(std::string key);
    std::shared_ptr<IRType> getIRTypeByIndex(uint64_t index);
    bool containsTypeThatRequiresFreeing() override;
    bool isStructType() override;
    std::shared_ptr<IRType> clone() override;
    virtual void print() override;
};

#endif //JETLANG_IR_STRUCT_TYPE_H
