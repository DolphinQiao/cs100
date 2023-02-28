#include <cstddef>

class Matrix {
public:
    typedef double Scalar;
    typedef std::size_t Index;

    explicit Matrix(Index rows, Index cols);
    Matrix(const Matrix &other);
    Matrix& operator=(const Matrix &other);
    ~Matrix();
    Index rows() const;
    Index cols() const;
    Scalar& at(Index r, Index c);
    const Scalar& at(Index r, Index c) const;
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix transpose() const;
    Matrix block(Index r, Index c, Index p, Index q) const; // Block of size p x q, starting at (r,c)
    Scalar trace() const; // For square matrix
    Scalar determinant() const; // For square matrix

private:
    Scalar **m_p;
    Index m_rows,m_cols;
    // Define your private member variables and functions here
};
Matrix::Index Matrix::rows() const{
    return m_rows;
}
Matrix::Index Matrix::cols() const{
    return m_cols;
}
Matrix::Matrix(Matrix::Index rows,Matrix::Index cols){
    m_p = new Matrix::Scalar*[rows];
    for(int i=0;i<rows;++i)
    {
        *(m_p+i)=new Matrix::Scalar[cols];
    }
    m_cols=cols;
    m_rows=rows;
}
Matrix::~Matrix()
{
    for(int i=0;i<m_rows;++i)
    {
        delete[] *(m_p+i);
    }
    delete[] m_p;
}
Matrix::Matrix(const Matrix &other){
    m_cols=other.cols();
    m_rows=other.rows();
    m_p = new Matrix::Scalar*[m_rows];
    for(int i=0;i<m_rows;++i)
    {
        *(m_p+i)=new Matrix::Scalar[m_cols];
        for(int j=0;j<m_cols;++j)
        {
            *(*(m_p+i)+j)=*(*(other.m_p+i)+j);
        }
    }
}
Matrix& Matrix::operator=(const Matrix &other){
    m_cols=other.cols();
    m_rows=other.rows();
    for(int i=0;i<m_rows;++i)
    {
        for(int j=0;j<m_cols;++j)
        {
            *(*(m_p+i)+j)=*(*(other.m_p+i)+j);
        }
    }
    return *this;
}
Matrix::Scalar& Matrix::at(Matrix::Index r,Matrix::Index c){
    return *(*(m_p+c)+r);
}
const Matrix::Scalar& Matrix::at(Matrix::Index r,Matrix::Index c)const{
    return *(*(m_p+c)+r);
}
Matrix Matrix::operator+(const Matrix &other) const{
    Matrix A=Matrix(m_rows,m_cols);
    for(int i=0;i<m_rows;++i)
    {
        for(int j=0;j<m_cols;++j)
        {
            A.at(i,j)=at(i,j)+other.at(i,j);
        }
    }
    return A;
}
Matrix Matrix::operator-(const Matrix &other) const{
    Matrix A=Matrix(m_rows,m_cols);
    for(int i=0;i<m_rows;++i)
    {
        for(int j=0;j<m_cols;++j)
        {
            A.at(i,j)=at(i,j)-other.at(i,j);
        }
    }
    return A;
}
Matrix Matrix::operator*(const Matrix &other) const{
    Matrix A=Matrix(m_rows,m_cols);
    for(int i=0;i<m_rows;++i)
    {
        for(int j=0;j<m_cols;++j)
        {
            A.at(i,j)=at(i,j)*other.at(i,j);
        }
    }
    return A;
}
Matrix Matrix::transpose() const{
    Matrix A=Matrix(m_rows,m_cols);
    for(int i=0;i<m_rows;++i)
    {
        for(int j=0;j<m_cols;++j)
        {
            A.at(j,i)=at(i,j);
        }
    }
    return A;
}
Matrix Matrix::block(Matrix::Index r,Matrix::Index c,Matrix::Index p,Matrix::Index q) const{
    Matrix A=Matrix(p,q);
    for(int i=r;i<r+p;++i)
    {
        for(int j=c;j<c+q;++j)
        {
            A.at(i-p,j-q)=at(i,j);
        }
    }
    return A;
}
Matrix::Scalar Matrix::trace() const{
    Matrix::Scalar t=0;
    for(int i=0;i<m_cols;++i)
    {
        t+=at(i,i);
    }
    return t;
}
Matrix::Scalar Matrix::determinant() const{
    if(m_cols==1)return **m_p;
    Matrix::Scalar sum=0;
    for(int i=0;i<m_cols;++i)
    {
        Matrix A=block(Matrix::Index(2),Matrix::Index(2),m_cols-1,m_cols-1);
        sum+=A.determinant();
    }
    return sum;
}
int main()
{
    
    return 0;
}