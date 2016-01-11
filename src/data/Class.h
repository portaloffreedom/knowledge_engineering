//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_CLASS_H
#define KNOWLEDGE_ENGINEERING_CLASS_H


class Class {
public:
    enum Type {
        NORMAL,
        ABSOLUTE_DIFFERENCE,
        RELATIVE_DIFFERENCE,
    };

    enum Value {
        GOOD,
        BAD,
    };

    Type type;
    Value value;
};


#endif //KNOWLEDGE_ENGINEERING_CLASS_H
