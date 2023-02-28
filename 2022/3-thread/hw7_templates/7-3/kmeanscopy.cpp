#include "kmeans.hpp"

double Point::Distance(Point& other)
{
    // YOUR CODE HERE
    return sqrt((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y));
}

std::istream& operator>>(std::istream& is, Point& pt)
{
    // YOUR CODE HERE
    is >> pt.x >> pt.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, Point& pt)
{
    // YOUR CODE HERE
    os << pt.x << " " << pt.y;
    return os;
}


Kmeans::Kmeans(const std::vector<Point>& points, const std::vector<Point>& initialCenters)
{
    // YOUR CODE HERE
    m_points = points;
    m_centers = initialCenters;
    m_numCenters = initialCenters.size();
    m_numPoints = points.size();
}

std::vector<index_t> Kmeans::Run(int maxIterations)
{
    // DO NOT MODIFY THESE CODE
    std::vector<index_t> assignment(m_numPoints, 0); // the return vector
    int currIteration = 0;
    std::cout << "Running kmeans with num points = " << m_numPoints 
            << ", num centers = " << m_numCenters 
            << ", max iterations = " << maxIterations << "...\n";

    // YOUR CODE HERE
    while(currIteration < maxIterations)
    {
        currIteration++;

        //Assign the nearest points to centers
        index_t index = 0;
        for(std::vector<Point>::iterator it = m_points.begin(); it != m_points.end(); ++it)
        {

            double min_dis = it->Distance(m_centers[0]);
            assignment[index] = 0;
            index_t index1 = 0;
            for(std::vector<Point>::iterator center = m_centers.begin(); center != m_centers.end(); ++center)
            {
                if(it->Distance(*center) < min_dis)
                {
                    min_dis = it->Distance(*center);
                    assignment[index] = index1;
                }
                index1++;
            }
            index++;
        }

        //Recalculate center points and check changed
        index = 0;
        std::vector<Point> new_centers(m_numCenters, Point(0,0));
        std::vector<int> cnt_centers(m_numCenters, 0);
        for(std::vector<Point>::iterator it = m_points.begin(); it != m_points.end(); ++it)
        {  
            new_centers[assignment[index]].x += it->x;
            new_centers[assignment[index]].y += it->y;
            cnt_centers[assignment[index]]++;

            index++;
        }
        
        index=0;
        bool flag = true;
        for(std::vector<Point>::iterator it = new_centers.begin(); it != new_centers.end(); ++it)
        {
            it->x = it->x / double(cnt_centers[index]);
            it->y = it->y / double(cnt_centers[index]);

            if (it->x != m_centers[index].x || it->y != m_centers[index].y) flag = false;

            index++;
        }


        if(flag)
        {
            break;
        }else
        {
            m_centers = new_centers;
        }

    }

    // YOUR CODE ENDS HERE
    std::cout << "Finished in " << currIteration << " iterations." << std::endl;
    return assignment;
}