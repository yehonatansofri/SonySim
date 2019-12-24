/**
 * @author Yehonatan Sofri
 * @date 23.12.19
 */

#include "CommandVar.h"

/**
 * reset all data of object
 */
void CommandVar::cleanData() {
    this -> var_info = {"", 0, NO_ONE};
    this->indexCounter = 0;
}

/**
 * inserting the new value in the scope's map
 * if updater is client - updating the simulator
 */
void CommandVar::updateData() {

    symbol_table.insert(this->var_name, this->var_info);

    if (this->var_info.updater == CLIENT) {
        cout <<"now i should update the simulator: ";
        cout << this ->var_name << this ->var_info.value<< endl;
        //updateSimulator(this -> var_info.reference, this -> var_info.value);
    }
}

/**
 * reset the object data, and set/ update a var in the map.
 *
 * @param index in vector of tokens
 * @return number of cells in tokens_array to go ahead
 */
int CommandVar::execute(int index) {
    this->cleanData();
    this->indexCounter++;

    if (tokens[index] == "var") {
        setVarCommand(++index);
    }
    else {
        setVarCommand(index);
    }

    this -> updateData();

    return this->indexCounter;
}

/**
 * handle a var creation/ update command, depending on the sequence of strings in vector.
 *
 * @param index in vector of tokens
 * @throw const char * in case of invalid input
 */
void CommandVar::setVarCommand(int index) {
    string token_after_name;

    this -> var_name = tokens[index];
    this -> indexCounter+=2;

    token_after_name = tokens[++index];

    if (token_after_name == "\n") {
        return;
    }
    else if (token_after_name == "=") {
        if (symbol_table.get(this -> var_name).updater == SIMULATOR) {
            throw "can't assign value to a var dependent on the simulator updates";
        }

        setValue(index+1);//index in the beginning of expression
    }
    else if(this -> isArrow(index)) {
        this -> setVarInfo(index);
    }
    else if (token_after_name == "{") {
        this -> indexCounter--;//so the next parser will see "{"
    }
    else {
        throw "Invalid input";
    }
}//end of setVarCommand()

/**
 * check if the string in the vector at the specific index is an arrow.
 * arrow is "->" or "<-"
 *
 * @param position of token in vector
 * @return boolean - 1 true / 0 false
 */
int CommandVar::isArrow(int index) {
    if ((tokens[index] == "<-")  || (tokens[index] == "->")) {
            return 1;
    }

    return 0;
}

/**
 * creating a Var - setting reference and updater by direction of arrow.
 *
 * @param index in vector
 */
void CommandVar::setVarInfo(int index) {

    //check binding direction - first char is "-" or "<"
    (tokens[index][0] == '-') ? this->var_info.updater = CLIENT : this->var_info.updater = SIMULATOR;

    //skipping "sim" in the vector
    indexCounter+=2;
    index+=2;

    this -> var_info.reference = tokens[index];

    //skipping "\n"
    indexCounter+=2;
}

/**
 * calculate the value in the string that index points to.
 * using Interpreter class.
 *
 * @param index in vector of tokens
 */
void CommandVar::setValue(int index) {
    FloatFromStringExpression floatFromStringExpression;
    this -> var_info.value = floatFromStringExpression.calculateExpression(tokens[index]);

    this->indexCounter+=2;//skipping expression and "\n"
}

/**
 * check if given string is a variable, by elimination.
 * if it is not a number nor an operator it is a variable.
 *
 * @param str token in an expression
 * @return boolean - true or false
 */
int CommandVar::isVar(string str) {
    if (strlen(str.c_str()) == strspn(str.c_str(), "0123456789.")) {
        return 0;
    }
    else if (strlen(str.c_str()) == strspn(str.c_str(), "*/-+()")) {
        return 0;
    }

    return 1;
}
