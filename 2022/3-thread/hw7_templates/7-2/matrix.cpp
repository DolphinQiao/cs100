#include <algorithm>
#include "rational.hpp"
template<typename T> 
class Matrix {
public:
    Matrix();
    Matrix(unsigned int rows, unsigned int cols, const T& value = T());

    T& operator()(unsigned int r, unsigned int c);

    void Print();

    void GaussJordan();

private:
    std::vector<std::vector<T> > m_mat;
};

template <typename T> Matrix<T>::Matrix(){}

template <typename T> Matrix<T>::Matrix(unsigned int rows, unsigned int cols, const T& value = T())
{
  std::vector<T> tmp;
  for(int i=1;i<=rows;++i)
  {
    tmp.clear();
    for(int j=1;j<=cols;++j)
    {
      tmp.push_back(value);
    }
    m_mat.push_back(tmp);
  }
}

template <typename T> T& Matrix<T>::operator()(unsigned int r, unsigned int c)
{
  return m_mat[r][c];
}

template <typename T> void Matrix<T>::Print()
{
  for (int i=0;i<m_mat.size();++i)
  {
    for(int j=0;j<m_mat.size();++j)
    {
      std::cout<<m_mat[i][j]<<" ";
    }
    std::cout<<std::endl;
  }
}

template <typename T> void Matrix<T>::GaussJordan()
{
  int n = m_mat.size(), m = m_mat[0].size();
  for(int i=0;i<n;i++){
        int r=i;
        for(int j=i+1;j<n;j++)
            if(std::fabs(m_mat[r][i])<std::fabs(m_mat[j][i]))
                r=j;//find_the_biggest_number_of_the_first_column（at present) 
        if(i!=r)swap(m_mat[i],m_mat[r]);//对换一行或一列,属于找最大当前系数的其中一步。（这样就可以只处理当前行的系数啦！） 
        T div=m_mat[i][i];
        for(int j=i;j<m;j++)
            m_mat[i][j]/=div;
        for(int j=i+1;j<n;j++){
            div=m_mat[j][i];
            for(int k=i;k<m;k++)
                m_mat[j][k]-=m_mat[i][k]*div;
        }
    }
}
