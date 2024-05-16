#include <iostream>
#include <fstream>
#include <vector>

struct Point {
    double x, y;
};

bool arePointsOnLine(int A, int B, int C, Point p1, Point p2) {
    return A * p1.x + B * p1.y + C == 0 && A * p2.x + B * p2.y + C == 0;
}

void checkIntersection(Point p1, Point p2, Point& p, double A, double B, double C){
    double x1, y1, x2, y2, x, y;
    double znamX, znamY;
    double chislX, chislY;

    x1 = p1.x;
    x2 = p2.x;

    y1 = p1.y;
    y2 = p2.y;


    znamX = p2.x- p1.x;
    znamY = p2.y - p1.y;

    if (znamX == 0)
    {
        x = p1.x;
        y = (-C - A * x) / B;
    }
    else if (znamY == 0)
    {
        y = p1.y;
        x = (-B * y - C) / A;
    }
    else {
        double c =  - p1.y * znamX + p1.x * znamY;
        double a = znamY;
        double b = - znamX;

        double det = a * B - b * A;
        if (det != 0)
        {
            x = (c * B - b * -C) / det;
            y = (a * -C - c * A) / det;
        }
    }
    p.x = x;
    p.y = y;
}

bool checkEquals(std::vector <Point> arr, Point p)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i].x == p.x && arr[i].y == p.y)
            return true;
    }
    return false;
}

bool inSegment(const Point& p, const Point& a, const Point& b) {
    double crossproduct = (p.y - a.y) * (b.x - a.x) - (p.x - a.x) * (b.y - a.y);
    if (crossproduct != 0) {
        return false;
    }

    double dotproduct = (p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y);
    if (dotproduct < 0) {
        return false;
    }

    double squaredlengthba = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    if (dotproduct > squaredlengthba) {
        return false;
    }

    return true;
    /*double k, c;
    if (a.x == b.x) {
        return (p.x == a.x && p.y >= std::min(a.y, b.y) && a.x <= std::max(a.y, b.y));
    }
    k = (b.y - a.y) / (b.x - a.x);
    c = a.y - k * a.x;
    return p.y == p.x * k + c;*/
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    double A, B, C;
    Point p1, p2, p3, p4, p5;
    std::vector <Point> p;
    std::vector<Point> intersections;

    input >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;
    input >> A >> B >> C;

    p.push_back(p1);
    p.push_back(p2);
    p.push_back(p3);
    p.push_back(p4);


    int i = p.size();
    while (i > -1)
    {
        if (i < 3)
        {
            checkIntersection(p[i], p[i + 1], p5, A, B, C);
            if(inSegment(p5, p[i], p[i + 1]) && !checkEquals(intersections, p5))
                intersections.push_back(p5);
        }    
        else if (i == 3)
        {
            checkIntersection(p[i], p[0], p5, A, B, C);
            if (inSegment(p5, p[i], p[0]) && !checkEquals(intersections, p5))
                intersections.push_back(p5);
        }   
        i--;
    }
    int n = p.size();
    int s = intersections.size();

    std::vector<Point> inter;

    int j = 0;
    while (j < n - 1)
    {
        
        for (int k = 0; k < s - 1; k++)
        {
            if (intersections.size() > 1) {
                if (k < 3)
                {
                    if (inSegment(intersections[j], p[k], p[k + 1]) && inSegment(intersections[j + 1], p[k], p[k + 1]) && arePointsOnLine(A, B, C, p[j], p[j + 1]))
                    {
                        intersections.erase(intersections.begin() + j);
                        intersections.erase(intersections.begin() + j);
                        j++;
                    }
                }
                else if (k == 3)
                {
                    if (inSegment(intersections[j], p[k], p[0]) && inSegment(intersections[j + 1], p[k], p[0]) && arePointsOnLine(A, B, C, p[j], p[j + 1]))
                    {
                        intersections.erase(intersections.begin() + j);
                        intersections.erase(intersections.begin() + j);
                        j++;
                    }
                }
            }
            
        }
        j++;
    }

    //2 2 2 6 8 6 8 2
    // 0.5 -1 5
    

    if (intersections.empty()) {
        output << "-1\n";
    }
    else {
        output << intersections.size() << "\n";
        for (int i = 0; i < intersections.size(); i++)
        {
            output << intersections[i].x << " " << intersections[i].y << std::endl;
        }
    }

    return 0;
}
