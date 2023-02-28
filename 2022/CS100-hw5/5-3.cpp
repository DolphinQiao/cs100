#include <iostream>
#include <string>

class Expr_node {
 public:
  Expr_node() = default;
  virtual double eval() const = 0;
  virtual std::string to_string() const = 0;
  virtual ~Expr_node() = default; 
  Expr_node(const Expr_node &) = delete;
  Expr_node &operator=(const Expr_node &) = delete;
};

//Number node
class Number_node : public Expr_node {
  friend Number_node *make_number(double);
  double value;
  Number_node(double val) : value(val) {}
  virtual double eval() const override;
  virtual std::string to_string() const override;
};
Number_node* make_number(double num)
{
  return new Number_node(num);
}
double Number_node::eval() const{
  return value;
}
std::string Number_node::to_string() const{
  return std::to_string(value);
}
// Number_node Number_node::*make_number(double num){
//   return &Number_node(num);
// }

//Negation node
class Negation_Node:public Expr_node
{
  friend Negation_Node *make_negation(Expr_node *);
  Expr_node *son;
  Negation_Node(Expr_node *node):son(node){}
  virtual double eval() const override;
  virtual std::string to_string() const override;
};

Negation_Node* make_negation(Expr_node* node)
{
  return new Negation_Node(node);
}
double Negation_Node::eval() const{
  return -(son->eval());
}
std::string Negation_Node::to_string() const{
  std::string s="-";
  return s+(son->to_string());
}


//Binary node
class Binary_node:public Expr_node{
  virtual double eval() const override =0;
  virtual std::string to_string() const override =0;
};

class  Plus_node:public Binary_node{
  public:
  Plus_node()=default;
  ~Plus_node()=default;
  private:
  Expr_node *lson,*rson;
  friend Plus_node *make_plus(Expr_node *,Expr_node *);
  Plus_node(Expr_node *l,Expr_node *r):lson(l),rson(r){}
  virtual double eval() const override;
  virtual std::string to_string() const override;
};
Plus_node *make_plus(Expr_node *l,Expr_node *r){
  return new Plus_node(l,r);
}
double Plus_node::eval() const{
  return lson->eval()+rson->eval();
}
std::string Plus_node::to_string() const{
  std::string s="+",s1="(",s2=")";
  return s1+lson->to_string()+s+rson->to_string()+s2;
}

class Minus_node:public Binary_node{
  Expr_node *lson,*rson;
  friend Minus_node *make_minus(Expr_node *,Expr_node *);
  Minus_node(Expr_node *l,Expr_node *r):lson(l),rson(r){}
  virtual double eval() const override;
  virtual std::string to_string() const override;
};
Minus_node *make_minus(Expr_node *l,Expr_node *r){
  return new Minus_node(l,r);
}
double Minus_node::eval() const{
  return lson->eval()-rson->eval();
}
std::string Minus_node::to_string() const{
  std::string s="-",s1="(",s2=")";
  return s1+lson->to_string()+s+rson->to_string()+s2;
}

class Multiply_node:public Binary_node{
  Expr_node *lson,*rson;
  friend Multiply_node *make_multiply(Expr_node *,Expr_node *);
  Multiply_node(Expr_node *l,Expr_node *r):lson(l),rson(r){}
  virtual double eval() const override;
  virtual std::string to_string() const override;
};
Multiply_node *make_multiply(Expr_node *l,Expr_node *r){
  return new Multiply_node(l,r);
}
double Multiply_node::eval() const{
  return lson->eval()*rson->eval();
}
std::string Multiply_node::to_string() const{
  std::string s="*",s1="(",s2=")";
  return s1+lson->to_string()+s+rson->to_string()+s2;
}

class Divide_node:public Binary_node{
  Expr_node *lson,*rson;
  friend Divide_node *make_divide(Expr_node *,Expr_node *);
  Divide_node(Expr_node *l,Expr_node *r):lson(l),rson(r){}
  virtual double eval() const override;
  virtual std::string to_string() const override;
};
Divide_node *make_divide(Expr_node *l,Expr_node *r){
  return new Divide_node(l,r);
}
double Divide_node::eval() const{
  return lson->eval()/rson->eval();
}
std::string Divide_node::to_string() const{
  std::string s="/",s1="(",s2=")";
  return s1+lson->to_string()+s+rson->to_string()+s2;
}

int main() {
  Expr_node *expr_tree = make_divide(
      make_plus(make_number(3), make_multiply(make_number(4), make_number(5))),
      make_number(6));
  //Expr_node *expr_tree = make_plus(make_number(4),make_number(5));
  std::cout << expr_tree->eval() << std::endl;
  std::cout << expr_tree->to_string() << std::endl;
  delete expr_tree;
  // Expr_node *bonus_tree =
  //     make_plus(make_exp(make_sin(make_number(3))), make_number(1));
  // std::cout << bonus_tree->eval() << std::endl;
  // std::cout << bonus_tree->to_string() << std::endl;
  // delete bonus_tree;
  return 0;
}