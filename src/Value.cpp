#include "Value.h"
#include <isostream>
#include <cmath>
#include <cassert>

Value::Value(double data, std::vector<Value*> children, std::string op)
    : data(data), grad(0.0), _op(op), _backward([](){}), _prev(children.begin(), children.end()) {}


Value Value::operator+(const Value& other){
    Value* other_ptr = new Value(other);
    Value* out = new Value(this->data + other_ptr->data, {this, other_ptr}, "+");

    return *out;
}

Value Value::operator-(const Value& other){
    Value* other_ptr = new Value(other);
    Value* out = new Value(this->data - other_ptr->data, {this, other_ptr}, "-");

    return *out;
}

Value Value::operator*(const Value& other){
    Value* other_ptr = new Value(other);
    Value* out = new Value(this->data * other_ptr->data, {this, other_ptr}, "*")

    return *out;
}

Value Value::operator/(const Value& other){
    Value* other_ptr = new Value(other);
    Value out = new Value(this-> data / other_ptr->data, {this, other_ptr}, "/")

    return *out;
}


