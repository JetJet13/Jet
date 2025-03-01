//
// Created by Johny Georges on 2025-03-01.
//

#ifndef JETLANG_IR_MALLOC_ARRAY_TYPE_H
#define JETLANG_IR_MALLOC_ARRAY_TYPE_H

#include <unordered_map>
#include <llvm/IR/Constants.h>
#include "ir-type.h"
#include "ir-pointer-type.h"

class IRMallocArrayType : public IRType {
private:
    llvm::StructType* _type;
public:
    explicit IRMallocArrayType(llvm::StructType* type);
    llvm::StructType* getType() override;
    unsigned long size();
    uint64_t getSizeInBytes() override;
    unsigned long getIndexForLevel();
    unsigned long getIndexForArray();
    virtual void print() override;
};

#endif //JETLANG_IR_MALLOC_ARRAY_TYPE_H
