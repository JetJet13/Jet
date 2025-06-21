//
// Created by Johny Georges on 2025-06-21.
//

#ifndef JETLANG_IR_REF_ARRAY_ACCESS_TYPE_H
#define JETLANG_IR_REF_ARRAY_ACCESS_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"

class IRRefArrayAccessType : public IRType {
private:
    llvm::StructType* _type;
    unsigned int _accessIndex;
    unsigned int _arrayIndex;
    IRType* _arrayElementType;
public:
    explicit IRRefArrayAccessType(llvm::StructType* type, IRType* arrayElementType);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getAccessIndex() const;
    [[nodiscard]] unsigned int getArrayIndex() const;
    llvm::Type* getAccessType();
    llvm::PointerType* getArrayType();
    IRType* getElementIRType();
    llvm::Type* getElementType();
    IRType* getSourceType() override;
    uint64_t getSizeInBytes() override;
    bool containsTypeThatRequiresFreeing() override;
};

#endif //JETLANG_IR_REF_ARRAY_ACCESS_TYPE_H
