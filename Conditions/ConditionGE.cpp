/**
 * class for greater then or equal condition.
 *
 * @author Jhonny
 * @date 12.23.19
 */

#include "ConditionGE.h"

/**
 * using Condition inherited class to evaluate the sides of the condition.
 *
 * @return 1 if left is greater or equal right, else 0
 */
int ConditionGE::isTrue() {
    this -> calculateSides();

    return (this -> left_value) >= (this -> right_value);
}
