#include "kmeans.hpp"

using namespace std::chrono;

const int Numthread = 4;
std::mutex mtx;
bool flag=true;

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

void assign(int st, int en, std::vector<index_t>& assignme, std::vector<Point> m_points, std::vector<Point> m_centers)
{
    //Assign the nearest points to centers
    //std::cout << st << "  " << en << std::endl;
    mtx.lock();
    std::vector<index_t> temp; temp.clear();
    for(int i = st; i <= en; ++i)
    {
        double min_dis = m_points[i].Distance(m_centers[0]);
        
        index_t index1 = 0;
        index_t min_index = 0;
        for(std::vector<Point>::iterator center = m_centers.begin(); center != m_centers.end(); ++center)
        {
            if(m_points[i].Distance(*center) < min_dis)
            {
                min_dis = m_points[i].Distance(*center);
                //std::cout<<m_points[i].Distance(*center)<<std::endl;
                min_index = index1;
            }
            index1++;
        }
        temp.push_back(min_index);
    }
    assignme = temp;
    mtx.unlock();
    return;
}

void calc(int st, int en, std::vector<index_t>* assignme, std::vector<Point> m_points, std::vector<Point> m_centers, std::vector<Point>& new_centers, std::vector<int>& cnt_centers)
{
    //std::cout << st << "  " << en << std::endl;
    for(int i = st; i <= en; ++i)
    {  
        new_centers[(*assignme)[i]].x += m_points[i].x;
        new_centers[(*assignme)[i]].y += m_points[i].y;
        cnt_centers[(*assignme)[i]]++;
    }
    return;
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
    std::vector<std::thread> threads;
    while(currIteration < maxIterations)
    {
        currIteration++;
            
        time_point<steady_clock> start = steady_clock::now();
        std::vector<std::vector<index_t> > assignment_sec(Numthread);
        for (int i = 0; i < Numthread; ++i) assignment_sec[i].clear();
        for(int i = 0; i < Numthread; ++i)
        {
            int section = m_points.size() / Numthread + 1;
            threads.push_back(std::thread(assign, std::min(int(m_points.size()) - 1, section * i), std::min(int(m_points.size()) - 1, section * (i + 1) - 1), ref(assignment_sec[i]), m_points, m_centers));
        }
        
        for(int i = 0; i < Numthread; ++i)
        {
            if(threads[i].joinable()) threads[i].join();
        }
        
        threads.clear();

        assignment = assignment_sec[0];
        for(int i = 1; i < Numthread; ++i)
        {
            assignment.insert(assignment.end(), assignment_sec[i].begin(), assignment_sec[i].end());
        }

        time_point<steady_clock> end = steady_clock::now();
        duration<double> elapsed = end - start;
        std::cout<< "1 " <<elapsed.count() <<std::endl;
        //Recalculate center points and check changed

        std::vector<Point> new_centers_all(m_centers.size(), Point(0,0));
        std::vector<int> cnt_centers_all(m_centers.size(), 0);
        std::vector<std::vector<int> > cnt_centers (Numthread, std::vector<int>(m_centers.size(), 0));
        std::vector<std::vector<Point> > new_centers (Numthread, std::vector<Point>(m_centers.size(), Point(0,0)));

        for(int i = 0; i < Numthread; ++i)
        {
            int section = m_points.size() / Numthread + 1;
            threads.push_back(std::thread(calc, std::min(int(m_points.size()) - 1, section * i), std::min(int(m_points.size()) - 1, section * (i + 1) - 1), &assignment, m_points, m_centers, ref(new_centers[i]), ref(cnt_centers[i])));
        }
        for(int i = 0; i < Numthread; ++i)
        {
            if(threads[i].joinable()) threads[i].join();
        }
        threads.clear();

        for(int i = 0; i < Numthread; ++i)
        {
            for(int j = 0; j < new_centers_all.size(); ++j)
            {
                new_centers_all[j].x += new_centers[i][j].x;
                new_centers_all[j].y += new_centers[i][j].y;
                cnt_centers_all[j] += cnt_centers[i][j];
            }
        }

        flag = true;
        for(int i = 0; i < new_centers_all.size(); ++i)
        {
            new_centers_all[i].x = new_centers_all[i].x / double(cnt_centers_all[i]);
            new_centers_all[i].y = new_centers_all[i].y / double(cnt_centers_all[i]);
            
        
            if (new_centers_all[i].x != m_centers[i].x || new_centers_all[i].y != m_centers[i].y) flag = false;
        }
        
        if(flag)
        {
            break;
        }else
        {
            m_centers = new_centers_all;
        }


    }

    // YOUR CODE ENDS HERE
    std::cout << "Finished in " << currIteration << " iterations." << std::endl;
    return assignment;
}