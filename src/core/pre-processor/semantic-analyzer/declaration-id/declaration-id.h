//
// Created by Johny Georges on 2024-05-01.
//

#ifndef JETLANG_DECLARATION_ID_H
#define JETLANG_DECLARATION_ID_H

#include <string>

class DeclarationId {
private:
    std::string _id;
public:
    DeclarationId(std::string id);
    std::string getId();
};

#endif //JETLANG_DECLARATION_ID_H
