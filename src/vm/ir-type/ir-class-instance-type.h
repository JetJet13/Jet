//
// Created by Johny Georges on 2025-12-27.
//

#ifndef JETLANG_IR_CLASS_INSTANCE_TYPE_H
#define JETLANG_IR_CLASS_INSTANCE_TYPE_H

#include "ir-type.h"
#include "ir-class-type.h"
#include "ir-struct-ref-type.h"

class IRClassInstanceType : public IRType {
private:
    IRStructRefType* _irClassInstancePropertiesType;
    IRClassType* _irClassType;
public:
    IRClassInstanceType(IRClassType* irClassType, IRStructRefType* irClassInstancePropertiesType);
    IRStructRefType* getIRClassPropertiesType();
    IRClassType* getIRClassType();
    IRFunctionType* getIRConstructorType();
    std::string getIRMethodName(std::string methodName);
    std::string getIRPropertyName(std::string propertyName);
    unsigned long getIndexForProperty(std::string propertyName);
    IRType* getIRTypeForProperty(std::string propertyName);
    std::optional<IRFunctionType*> getIRTypeForMethod(std::string methodName);
    uint64_t getSizeInBytes() override;
    llvm::StructType* getType() override;
    bool containsTypeThatRequiresFreeing() override;
    bool isClassInstanceType() override;
    llvm::Align getAlignment() override;
    IRClassInstanceType* clone() override;
    void print() override;
};

#endif //JETLANG_IR_CLASS_INSTANCE_TYPE_H
