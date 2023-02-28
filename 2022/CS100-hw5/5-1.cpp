
// DO NOT MODIFY THE CODE BELOW
#include <cstddef>

class Array {
public:
    Array();
    explicit Array(std::size_t n);
    explicit Array(int *begin, int *end);
    Array(const Array &other);
    Array &operator=(const Array &other);
    ~Array();
    int &at(std::size_t n);
    const int &at(std::size_t n) const;
    std::size_t size() const;
    bool empty() const;
    void clear();
    Array slice(std::size_t l, std::size_t r, std::size_t s = 1) const;
private:
    std::size_t m_size;
    int *m_data;
};

// YOUR CODE STARTS HERE
Array::Array(std::size_t n){
    m_data=new int[n];
    m_size=n;
}
Array::Array(int *begin,int *end){
    m_size=int(end-begin);
    m_data=new int[m_size];
    int *p=begin;
    for(int i=0;i<m_size;++i){
        *(m_data+i)=*(p+i);
    }
}
const int &Array::at(std::size_t n) const{
    return *(m_data+n);
}
int &Array::at(std::size_t n){
    return *(m_data+n);
}
std::size_t Array::size() const{
    return m_size;
}
Array::Array(const Array &other){
    m_size=other.size();
    m_data=new int[m_size];
    for(int i=0;i<m_size;++i){
        *(m_data+i)=other.at(i);
    }
}
Array& Array::operator=(const Array &other){
    m_size=other.size();
    delete[] m_data;
    m_data=new int[m_size];
    for(int i=0;i<m_size;++i){
        at(i)=other.at(i);
    }
    return *this;
}
Array::~Array(){
    delete[] m_data;
}
void Array::clear(){
    m_size=0;
    delete[] m_data;
    m_data = nullptr;
}
bool Array::empty() const{
    if(size()==0) return true;
    return false;
}
Array Array::slice(std::size_t l, std::size_t r, std::size_t s) const{
    int *p=new int[(r-l-1)/s+1];
    for(int i=l;i<r;i+=s){
        *p=at(i);
        p++;
    }
    Array A=Array(p-(r-l-1)/s,p);
    delete[] (p-(r-l-1)/s);
    return A;
}
// YOUR CODE ENDS HERE

int main(){
    // You can test your implementation here, but we will replace themain function on OJ.
    return 0;
}