#ifndef VALUE_H
#define VALUE_H

#include <vector>
#include <set>
#include <string>
#include <functional>

class Value {
public:
    // Constructors
    Value(double data, std::vector<Value*> children = {}, std::string op = "");

    // Operator overloads
    Value operator+(const Value& other);
    Value operator*(const Value& other);
    Value operator-() const;
    Value operator-(const Value& other) const;
    Value operator/(const Value& other) const;

    // Power, tanh, exp, log, sqrt, sin, cos, abs, ReLU
    Value pow(double exp) const;
    Value tanh() const;
    Value exp() const;
    Value log() const;
    Value sqrt() const;
    Value sin() const;
    Value cos() const;
    Value abs() const;
    Value relu() const;
    Value max(const Value& other) const;
    Value min(const Value& other) const;

    // Backpropagation
    void backward();

    // Data and gradient
    double data;
    double grad;

    // Debugging representation
    friend std::ostream& operator<<(std::ostream& os, const Value& val);

private:
    std::function<void()> _backward;
    std::set<Value*> _prev;
    std::string _op;
};

#endif // VALUE_H
