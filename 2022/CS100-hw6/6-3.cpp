#include <string>

// REMOVE THIS CLASS WHEN SUBMITTING!!!
class Point {
  double x{0}, y{0};
  std::string label;

 public:
  Point(double x0, double y0, const std::string &l = "")
      : x(x0), y(y0), label(l) {}
  Point() = default;
  double get_x() const {
    return x;
  }
  double get_y() const {
    return y;
  }
  std::string get_label() const {
    return label;
  }
  Point &set_x(double x0) {
    x = x0;
    return *this;
  }
  Point &set_y(double y0) {
    y = y0;
    return *this;
  }
  Point &set_label(const std::string &l) {
    label = l;
    return *this;
  }
};

class Point_counted {
  friend class Point_handle;

  // All the members are private.
  
  Point p;
  unsigned cnt;
  
  // Define some helper member functions if you need.
};

class Point_handle {
  Point_counted *ptr;
  // Your code here.
  Point_handle(double x0,double y0,const std::string &l="");
  ~Point_handle();
  Point_handle()=default;
  double get_x()const;
  double get_y()const;
  std::string get_label()const;
  Point &set_x(double x0);
  Point &set_y(double y0);
  Point &set_label(const std::string &l);
};
double Point_handle::get_x()const{
  return ptr->p.get_x();
}
double Point_handle::get_y()const{
  return ptr->p.get_y();
}
std::string Point_handle::get_label()const{
  return ptr->p.get_label();
}
Point_handle::Point_handle(double x0,double y0,const std::string &l)
{

  ptr=new Point_counted;
  ptr->p.set_x(x0);
  ptr->p.set_y(y0);
  ptr->p.set_label(l);
  ptr->cnt++;
}
Point_handle::~Point_handle()
{
  ptr->cnt--;
  delete ptr;
}
Point& Point_handle::set_x(double x0)
{
  ptr->p.set_x(x0);
  return ptr->p;
}
Point& Point_handle::set_y(double y0)
{
  ptr->p.set_y(y0);
  return ptr->p;
}
Point& Point_handle::set_label(const std::string &l)
{
  ptr->p.set_label(l);
  return ptr->p;
}
int main()
{
  return 0;
}