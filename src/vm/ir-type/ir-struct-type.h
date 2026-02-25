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
    std::unordered_map<std::string, unsigned long> _keyIndexMap;
    std::unordered_map<std::string, IRType*> _keyTypeMap;
public:
    IRStructType();
    IRStructType(llvm::StructType* type, std::unordered_map<std::string, unsigned long> keyIndexMap, std::unordered_map<std::string, IRType*> keyTypeMap);
    llvm::StructType* getType() override;
    void makeGlobal(std::string id, std::unique_ptr<llvm::LLVMContext>* context);
    void setAlignmentAndSizeForIRTypes();
    unsigned long size();
    uint64_t getSizeInBytes() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    llvm::Align getAlignment() override;
    std::string getKeyForIndex(unsigned long index);
    unsigned long getIndexForKey(std::string key);
    unsigned long getIndexForKey(unsigned long key);
    IRType* getIRTypeForKey(std::string key);
    IRType* getIRTypeByIndex(unsigned long index);
    bool containsTypeThatRequiresFreeing() override;
    bool isStructType() override;
    IRStructType* clone() override;
    virtual void print() override;
};

#endif //JETLANG_IR_STRUCT_TYPE_H
