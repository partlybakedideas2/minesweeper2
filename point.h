#ifndef POINT_H
#define POINT_H

struct Point
{
public:
    Point();
    Point(int r, int c);
    bool operator==(const Point& other) const;

    int row, col;
};

#endif // POINT_H
