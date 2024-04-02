#ifndef PARSER_H
#define PARSER_H

#include "detectSym.h"
#include "Stack.h"
#include <string>
#include <stdexcept>

namespace spiridonov
{
    class Parser
    {
    public:
        static int parseExpression(const std::string& expression);
    private:
        static void applyOperation(Stack<int>& operands, char op);
    };
}
#endif
