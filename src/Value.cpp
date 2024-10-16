#include "C:\Users\nicky\OneDrive\Desktop\Network\Network\include\Value.h"
#include <cmath>
#include <cassert>
#include <memory>

// Constructor
Value::Value(double data, std::vector<Value*> children, std::string op)
    : data(data), grad(0.0), _op(std::move(op)), _backward([]() {}), _prev(children.begin(), children.end()) {}

// Addition
Value Value::operator+(const Value& other) const {
    auto out = std::make_shared<Value>(this->data + other.data, std::vector<Value*>{this, &other}, "+");
    out->_backward = [this, &other, out]() {
        this->grad += 1.0 * out->grad;
        const_cast<Value&>(other).grad += 1.0 * out->grad;
    };
    return *out;
}

// Subtraction
Value Value::operator-(const Value& other) const {
    return *this + (-other);
}

// Multiplication
Value Value::operator*(const Value& other) const {
    auto out = std::make_shared<Value>(this->data * other.data, std::vector<Value*>{this, &other}, "*");
    out->_backward = [this, &other, out]() {
        this->grad += other.data * out->grad;
        const_cast<Value&>(other).grad += this->data * out->grad;
    };
    return *out;
}

// Tanh function
Value Value::tanh() const {
    double t = std::tanh(this->data);
    auto out = std::make_shared<Value>(t, std::vector<Value*>{this}, "tanh");
    out->_backward = [this, t, out]() {
        this->grad += (1 - t * t) * out->grad;
    };
    return *out;
}

// Exponential function
Value Value::exp() const {
    auto out = std::make_shared<Value>(std::exp(this->data), std::vector<Value*>{this}, "exp");
    out->_backward = [this, out]() {
        this->grad += out->data * out->grad;
    };
    return *out;
}

// Backpropagation function
void Value::backward() {
    std::vector<Value*> topo;
    std::set<Value*> visited;
    std::function<void(Value*)> buildTopo = [&](Value* v) {
        if (visited.find(v) == visited.end()) {
            visited.insert(v);
            for (Value* child : v->_prev) {
                buildTopo(child);
            }
            topo.push_back(v);
        }
    };
    buildTopo(this);

    this->grad = 1.0;
    for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
        (*it)->_backward();
    }
}

// Stream output
std::ostream& operator<<(std::ostream& os, const Value& val) {
    os << "Value(data=" << val.data << ", grad=" << val.grad << ")";
    return os;
}
