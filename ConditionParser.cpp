#include "ConditionParser.h"
#include "Calculator.h"

bool ConditionParser::isConditionTrue(vector<string>::iterator it) {
    string leftExpression = this->nextExpression(it);
    string conditionSign = *it;
    it++; // Go past condition sign
    Calculator* leftCalculator = new Calculator(leftExpression);
    double leftValue = leftCalculator->calculate();

    string rightExpression = this->nextExpression(it);
    it++; // Go past "{"
    Calculator* rightCalculator = new Calculator(rightExpression);
    double rightValue = rightCalculator->calculate();

    return checkCondition(leftValue, rightValue, conditionSign);
}

bool ConditionParser::checkCondition(double leftValue, double rightValue, string conditionSign) {
    if (conditionSign == "==") {
        return leftValue == rightValue;
    } else if (conditionSign == "!=") {
        return leftValue != rightValue;
    } else if (conditionSign == "<") {
        return leftValue < rightValue;
    } else if (conditionSign == ">") {
        return leftValue > rightValue;
    } else if (conditionSign == "<=") {
        return leftValue <= rightValue;
    } else if (conditionSign == ">=") {
        return leftValue >= rightValue;
    }
    return false;
}