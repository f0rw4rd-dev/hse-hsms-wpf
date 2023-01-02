#include "regularexpressions.h"

QRegularExpression RegularExpressions::address = QRegularExpression("[a-zA-Zа-яА-Я0-9.;, ]+");
QRegularExpression RegularExpressions::componentName = QRegularExpression("[a-zA-Zа-яА-Я0-9(), ]+");
QRegularExpression RegularExpressions::id = QRegularExpression("[0-9]+");
QRegularExpression RegularExpressions::password = QRegularExpression("[a-zA-Z0-9]+");
QRegularExpression RegularExpressions::integer = QRegularExpression("[0-9]+");
