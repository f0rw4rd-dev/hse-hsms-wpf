#ifndef REGULAREXPRESSIONS_H
#define REGULAREXPRESSIONS_H

#include <QRegularExpression>

class RegularExpressions
{
public:
    static QRegularExpression address;
    static QRegularExpression componentName;
    static QRegularExpression id;
    static QRegularExpression password;
    static QRegularExpression digit;
};

#endif // REGULAREXPRESSIONS_H