#include "kmeans.hpp"
#include "math.h"
#include "algorithm"
#include <functional>
#include <cstring>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
bool main_finished = false;
std::condition_variable cv;
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
    while(1)
    {
        //check if main_thread is finished
        mtx.lock();
        info.finish = false;
        mtx.unlock();
        if(main_finished){
            //std::cout<<info.startid<<" finished\n";
            return ;
        }
        
        mtx.lock();
        info.flag = true;
        mtx.unlock();
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
                if (mindist * 4 > m_dists[minj][j]){

                    thisdist = m_points[i].Distance(m_centers[j]);
                    if (thisdist < mindist)
                    {
                        minj = j;
                        mindist = thisdist;
                    }
                }
            }
            if (info.flag && assignment[i] != minj)
            {
                mtx.lock();
                info.flag = false;
                mtx.unlock();
            }
            assignment[i] = minj;
            info.centerx[minj] += m_points[i].x;
            info.centers[minj]++;
            info.centery[minj] += m_points[i].y;
        }

        //notify
        mtx.lock();
        info.finish = true;
        mtx.unlock();
        //wait main_thread finished
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck);
    }

}

void Kmeans::main_thread(int maxIterations)
{
    int currIteration = 0;
    for (currIteration = 0; currIteration < maxIterations; ++currIteration)
    {
        //std::cout<<currIteration<<std::endl;
        bool flag = true;
        bakecenters();
        //wait calc_thread finished
        while(1)
        {
            bool finish = true;
            //mtx.lock();
            for(int i = 0; i < Thread_Num; ++i)
            {
                finish = finish && threadinfo[i].finish;
            }
            //mtx.unlock();
            if(finish) break;
        }

        //check whether assignment changed  --> info.flag
        //mtx.lock();
        for(int i = 0; i < Thread_Num; ++i)
        {
            flag = flag && threadinfo[i].flag;
            //std::cout<<threadinfo[i].flag<<" ";
        }
        //std::cout<<"\n";
        if(flag)
        {
            //mtx.unlock();
            main_finished = true;
            std::unique_lock<std::mutex> lck(mtx);
            cv.notify_all();
            break;
        }
        //mtx.unlock();

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

        //wake up calc_thread
        std::unique_lock<std::mutex> lck(mtx);
        cv.notify_all();
    }
    main_finished = true;
    std::unique_lock<std::mutex> lck(mtx);
    cv.notify_all();
    std::cout << "Finished in " << currIteration << " iterations." << std::endl;
}

std::vector<index_t> Kmeans::Run(int maxIterations)
{
    // DO NOT MODIFY THESE CODE
    int currIteration = 0;
    std::cout << "Running kmeans with num points = " << m_numPoints
              << ", num centers = " << m_numCenters
              << ", max iterations = " << maxIterations << "...\n";
    // YOUR CODE HERE
    static std::thread threads[Thread_Num];
    static std::thread main_thread;
    for (int i = 0; i < Thread_Num; ++i)
    {
        threadinfo[i].startid = m_numPoints * i / Thread_Num;
        threadinfo[i].endid = m_numPoints * (i + 1) / Thread_Num;
    }
    for (int i = 0; i < Thread_Num; ++i)
        threads[i] = std::thread(&Kmeans::calcdist, this, std::ref(threadinfo[i]));

    main_thread = std::thread(&Kmeans::main_thread, this, maxIterations);
    
    for (int i = 0; i < Thread_Num; ++i) threads[i].join();
    main_thread.join();
    return assignment;
}
