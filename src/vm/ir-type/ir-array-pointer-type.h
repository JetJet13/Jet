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
    std::shared_ptr<IRType> _arrayElementType;
public:
    explicit IRArrayPointerType(llvm::StructType* type, std::shared_ptr<IRType> arrayElementType);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getNumElementsIndex() const;
    [[nodiscard]] unsigned int getDepthIndex() const;
    [[nodiscard]] unsigned int getAllocIndex() const;
    llvm::Type* getNumElementsType();
    llvm::PointerType* getAllocType();
    std::shared_ptr<IRType> getElementIRType();
    llvm::Type* getElementType();
    uint64_t getDepth();
    uint64_t getSizeInBytes() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    bool containsTypeThatRequiresFreeing() override;
    bool isArrayPointerType() override;
    std::shared_ptr<IRType> clone() override;
    void print() override;
};

#endif //JETLANG_IR_ARRAY_POINTER_TYPE_H
