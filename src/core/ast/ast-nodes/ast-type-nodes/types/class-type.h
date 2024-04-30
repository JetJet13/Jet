//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_CLASS_TYPE_H
#define JETLANG_CLASS_TYPE_H

#include "base-type.h"
#include "type.h"
#include "../../../../lexeme/lexeme.h"

class ClassType : public BaseType {
private:
    Lexeme* _className;
public:
    ClassType(Lexeme* className);
    Lexeme* getName();
    TypeSource getTypeSource() override;
    bool isEqualTo(BaseType *otherType) override;
};

#endif //JETLANG_CLASS_TYPE_H
