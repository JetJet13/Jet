//
// Created by Johny Georges on 2024-07-16.
//

#ifndef JETLANG_IR_STRUCT_TYPE_H
#define JETLANG_IR_STRUCT_TYPE_H

#include <unordered_map>
#include <llvm/IR/Constants.h>
#include "ir-type.h"

class IRStructType : public IRType {
private:
    llvm::StructType* _type;
    std::unordered_map<std::string, unsigned long> _keyIndexMap;
public:
    IRStructType(llvm::StructType *type, std::unordered_map<std::string, unsigned long> keyIndexMap);
    llvm::StructType* getType() override;
    unsigned long getIndexForKey(std::string key);
    void print();
};

#endif //JETLANG_IR_STRUCT_TYPE_H
