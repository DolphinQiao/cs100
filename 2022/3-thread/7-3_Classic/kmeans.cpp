#include "kmeans.hpp"
#include "math.h"
#include "algorithm"
#include <functional>
#include <cstring>

double Point::Distance(Point &other)
{
    // YOUR CODE HERE
    return ((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

std::istream &operator>>(std::istream &is, Point &pt)
{
    // YOUR CODE HERE
    is >> pt.x >> pt.y;
    return is;
}

std::ostream &operator<<(std::ostream &os, Point &pt)
{
    // YOUR CODE HERE
    os << pt.x << ' ' << pt.y;
    return os;
}

Kmeans::Kmeans(const std::vector<Point> &points, const std::vector<Point> &initialCenters)
{
    // YOUR CODE HERE
    m_points = points;
    m_centers = initialCenters;
    m_numPoints = m_points.size();
    m_numCenters = m_centers.size();
    m_dists.assign(m_numCenters, std::vector<double>(m_numCenters));
    assignment.assign(m_numPoints, 0);
}

void Kmeans::bakecenters(void)
{
    // Calculate distance from center to center
    for (int i = 0; i < m_numCenters; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            m_dists[i][j] = m_dists[j][i] = m_centers[i].Distance(m_centers[j]);
        }
    }
}

void Kmeans::calcdist(threadvarhelper &info)
{
    info.flag = true;
    memset(info.centerx, 0, sizeof(info.centerx));
    memset(info.centery, 0, sizeof(info.centery));
    memset(info.centers, 0, sizeof(info.centers));
    int minj;
    double mindist, thisdist;
    for (int i = info.startid; i < info.endid; ++i)
    {
        minj = assignment[i];
        mindist = m_points[i].Distance(m_centers[minj]);
        for (int j = 0; j < m_numCenters; ++j)
        {
            if (mindist * 4 <= m_dists[minj][j])
                continue;
            thisdist = m_points[i].Distance(m_centers[j]);
            if (thisdist < mindist)
            {
                minj = j;
                mindist = thisdist;
            }
        }
        if (info.flag && assignment[i] != minj)
        {
            info.flag = false;
        }
        assignment[i] = minj;
        info.centerx[minj] += m_points[i].x;
        info.centers[minj]++;
        info.centery[minj] += m_points[i].y;
    }
}

std::vector<index_t> Kmeans::Run(int maxIterations)
{
    // DO NOT MODIFY THESE CODE
    int currIteration = 0;
    std::cout << "Running kmeans with num points = " << m_numPoints
              << ", num centers = " << m_numCenters
              << ", max iterations = " << maxIterations << "...\n";
    // YOUR CODE HERE
    static threadvarhelper threadinfo[Thread_Num];
    static std::thread threads[Thread_Num];
    for (int i = 0; i < Thread_Num; ++i)
    {
        threadinfo[i].startid = m_numPoints * i / Thread_Num;
        threadinfo[i].endid = m_numPoints * (i + 1) / Thread_Num;
    }
    for (currIteration = 0; currIteration < maxIterations; ++currIteration)
    {
        bool flag = true;
        bakecenters();
        for (int i = 0; i < Thread_Num; ++i)
            threads[i] = std::thread(&Kmeans::calcdist, this, std::ref(threadinfo[i]));
        for (int i = 0; i < Thread_Num; ++i)
        {
            threads[i].join();
            flag = flag && threadinfo[i].flag;
        }
        if (flag)
            break;
        static double x_sum, y_sum;
        static int p_cnt;
        for (int j = 0; j < m_numCenters; ++j)
        {
            x_sum = y_sum = p_cnt = 0;
            for (int i = 0; i < Thread_Num; ++i)
            {
                x_sum += threadinfo[i].centerx[j];
                y_sum += threadinfo[i].centery[j];
                p_cnt += threadinfo[i].centers[j];
            }
            if (p_cnt)
            {
                m_centers[j].x += (x_sum / p_cnt - m_centers[j].x);
                m_centers[j].y += (y_sum / p_cnt - m_centers[j].y);
            }
        }
    }
    // YOUR CODE ENDS HERE
    std::cout << "Finished in " << currIteration << " iterations." << std::endl;
    return assignment;
}
