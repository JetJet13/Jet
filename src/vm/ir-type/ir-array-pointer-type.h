//
// Created by Johny Georges on 2024-08-08.
//

#ifndef JETLANG_IR_ARRAY_POINTER_TYPE_H
#define JETLANG_IR_ARRAY_POINTER_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"

class IRArrayPointerType : public IRType {
private:
    llvm::StructType* _type;
    unsigned int _numElementsIndex;
    unsigned int _depthIndex;
    unsigned int _allocIndex;
    IRType* _arrayElementType;
public:
    explicit IRArrayPointerType(llvm::StructType* type, IRType* arrayElementType);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getNumElementsIndex() const;
    [[nodiscard]] unsigned int getDepthIndex() const;
    [[nodiscard]] unsigned int getAllocIndex() const;
    llvm::Type* getNumElementsType();
    llvm::PointerType* getAllocType();
    IRType* getElementIRType();
    llvm::Type* getElementType();
    unsigned long getDepth();
    uint64_t getSizeInBytes() override;
    uint64_t get8BitAlignedSizeInBytes() override;
    bool containsTypeThatRequiresFreeing() override;
    bool isArrayPointerType() override;
};

#endif //JETLANG_IR_ARRAY_POINTER_TYPE_H
