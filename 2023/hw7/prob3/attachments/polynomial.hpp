#ifndef EXPR_HPP
#define EXPR_HPP

#include <memory>
#include <string>

class NodeBase
{
public:
  // Make any of these functions virtual, or pure virtual, if necessary.
  NodeBase() = default;
  virtual double eval(double x) const = 0;
  virtual double derivative(double x) const = 0;
  virtual std::string rep() const = 0;
  ~NodeBase() = default;
};

class Expr
{
  std::shared_ptr<NodeBase> m_ptr;

  Expr(std::shared_ptr<NodeBase> ptr) : m_ptr{ptr} {}

 public:
  Expr(double value);

  // Add member functions if necessary.

  double eval(double x) const
  {
    return m_ptr->eval(x);
  }
  double derivative(double x) const
  {
    return m_ptr->derivative(x);
  }
  std::string rep() const
  {
    return m_ptr->rep();
  }

  static const Expr x;

  // Add friend declarations if necessary.
  
  friend Expr operator-(const Expr &operand);
  friend Expr operator+(const Expr &operand);
  friend Expr operator+(const Expr &left, const Expr &right);
  friend Expr operator-(const Expr &left, const Expr &right);
  friend Expr operator*(const Expr &left, const Expr &right);
  friend Expr operator/(const Expr &left, const Expr &right);

};

class Variable : public NodeBase
{
  // Add functions if necessary.
  double eval(double x) const override
  {
    return x;
  }
  double derivative(double x) const override
  {
    x = x + 1;
    return 1.0f;
  }
  std::string rep() const override
  {
    return std::string("x");
  }

public:
  Variable() = default;
  static const Expr x;
};

class Constant : public NodeBase
{
  double m_value;

  // Add functions if necessary.
  double eval(double x) const override
  {
    x = x + 1;
    return m_value;
  }
  double derivative(double x) const override
  {
    x = x + 1;
    return 0;
  }
  std::string rep() const override
  {
    return std::to_string(m_value);
  }

public:
  Constant(double value) : m_value{value} {}
  friend Expr::Expr(double value);
};

class UnaryOperator : public NodeBase
{
  char m_op;
  Expr m_operand;

  // Add functions if necessary.

public:
  UnaryOperator(char op, const Expr &operand) : m_op{op}, m_operand{operand} {}
  double eval(double x) const override
  {
    if (m_op == '+')
    {
      return m_operand.eval(x);
    }
    else
    {
      return -m_operand.eval(x);
    }
  }
  double derivative(double x) const override
  {
    if (m_op == '+')
    {
      return m_operand.derivative(x);
    }
    else
    {
      return -m_operand.derivative(x);
    }
  }
  std::string rep() const override
  {
    if (m_op == '+')
    {
      return m_operand.rep();
    }
    else
    {
      return "-(" + m_operand.rep() + ")";
    }
  }
};

class BinaryOperator : public NodeBase
{
protected:
  Expr m_left;
  Expr m_right;

public:
  BinaryOperator(const Expr &left, const Expr &right)
      : m_left{left}, m_right{right} {}
};

class PlusOp : public BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  char m_op;
  // Add functions if necessary.
public:
  PlusOp(char op, const Expr &left, const Expr &right) : BinaryOperator(left, right), m_op(op) {}
  double eval(double x) const override
  {
    return m_left.eval(x) + m_right.eval(x);
  }
  double derivative(double x) const override
  {
    return m_left.derivative(x) + m_right.derivative(x);
  }
  std::string rep() const override
  {
    return "(" + m_left.rep() + ") + (" + m_right.rep() + ")";
  }
};

class MinusOp : public BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  char m_op;
  // Add functions if necessary.
public:
  MinusOp(char op, const Expr &left, const Expr &right) : BinaryOperator(left, right), m_op(op) {}
  double eval(double x) const override
  {
    return m_left.eval(x) - m_right.eval(x);
  }
  double derivative(double x) const override
  {
    return m_left.derivative(x) - m_right.derivative(x);
  }
  std::string rep() const override
  {
    return "(" + m_left.rep() + ") - (" + m_right.rep() + ")";
  }
};

class MultiplyOp : public BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  char m_op;
  // Add functions if necessary.
public:
  MultiplyOp(char op, const Expr &left, const Expr &right) : BinaryOperator(left, right), m_op(op) {}
  double eval(double x) const override
  {
    return m_left.eval(x) * m_right.eval(x);
  }
  double derivative(double x) const override
  {
    return m_left.derivative(x) * m_right.eval(x) +
           m_left.eval(x) * m_right.derivative(x);
  }
  std::string rep() const override
  {
    return "(" + m_left.rep() + ") * (" + m_right.rep() + ")";
  }
};

class DivideOp : public BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  char m_op;
  // Add functions if necessary.
public:
  DivideOp(char op, const Expr &left, const Expr &right) : BinaryOperator(left, right), m_op(op) {}
  double eval(double x) const override
  {
    return m_left.eval(x) / m_right.eval(x);
  }
  double derivative(double x) const override
  {
    return (m_left.derivative(x) * m_right.eval(x) -
            m_left.eval(x) * m_right.derivative(x)) /
           (m_right.eval(x) * m_right.eval(x));
  }
  std::string rep() const override
  {
    return "(" + m_left.rep() + ") / (" + m_right.rep() + ")";
  }
};

const Expr Expr::x{std::make_shared<Variable>()};

Expr::Expr(double value) : m_ptr{std::make_shared<Constant>(value)} {}

Expr operator-(const Expr &operand)
{
  return {std::make_shared<UnaryOperator>('-', operand)};
}

Expr operator+(const Expr &operand)
{
  return {std::make_shared<UnaryOperator>('+', operand)};
}

Expr operator+(const Expr &left, const Expr &right)
{
  // Your code here.
  return {std::make_shared<PlusOp>('+', left, right)};
}

Expr operator-(const Expr &left, const Expr &right)
{
  // Your code here.
  return {std::make_shared<MinusOp>('-', left, right)};
}

Expr operator*(const Expr &left, const Expr &right)
{
  // Your code here.
  return {std::make_shared<MultiplyOp>('*', left, right)};
}

Expr operator/(const Expr &left, const Expr &right)
{
  // Your code here.
  return {std::make_shared<DivideOp>('/', left, right)};
}

#endif // EXPR_HPP