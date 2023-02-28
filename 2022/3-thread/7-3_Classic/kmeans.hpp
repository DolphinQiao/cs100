#ifndef __KMEANS_HPP_
#define __KMEANS_HPP_

#include <iostream>
#include <vector>
#include <thread>
#include <stdlib.h>
#include <time.h>

#define Thread_Num 20 
#define max_eps 1e-1
#define pass_eps 5e-2

using index_t = int;

struct Point
{
    double x, y;

    Point() : x(0), y(0) {};
    Point(double x_, double y_) : x(x_), y(y_) {}
    Point(const Point& other) : x(other.x), y(other.y) {}

    double Distance(Point& other);
};

struct threadvarhelper
{
    double centerx[1000], centery[1000], centers[1000];
    int startid,endid,changed;
    bool flag;
};

class Kmeans
{
public:
    Kmeans(const std::vector<Point>& points, const std::vector<Point>& initialCenters);
    std::vector<index_t> Run(int maxIterations=1000);
    void calcdist (threadvarhelper& info);
    void bakecenters (void);

private:
    std::vector<Point> m_points;
    std::vector<Point> m_centers;
    std::vector<std::vector<double> > m_dists;
    std::vector<index_t> assignment;
    int m_numPoints;
    int m_numCenters;
};

std::istream& operator>>(std::istream& is, Point& pt);
std::ostream& operator<<(std::ostream& os, Point& pt);

#endif // __KMEANS_HPP_
