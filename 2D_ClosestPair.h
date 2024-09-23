//
// Created by Adrian Hwang on 2024-09-14.
//

#ifndef INC_2D_CLOSESTPAIR_H
#define INC_2D_CLOSESTPAIR_H
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <float.h>

struct Point {
    int x, y;
};

// A utility function to find the distance between two points
double distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// A brute force method to return the smallest distance between points in P[]
double bruteForce(std::vector<Point>& P, int left, int right) {
    double minDist = DBL_MAX;
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j < right; ++j) {
            if (distance(P[i], P[j]) < minDist) {
                minDist = distance(P[i], P[j]);
            }
        }
    }
    return minDist;
}

// divide and conquer

// A function to find the smallest distance in a strip of points
// The strip contains points within distance `d` from the dividing line
double stripClosest(std::vector<Point>& strip, double d) {
    double minDist = d;
    //ascending order by y
    std::sort(strip.begin(), strip.end(), [](const Point& p1, const Point& p2) {
        return p1.y < p2.y;
    });

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            if (distance(strip[i], strip[j]) < minDist) {
                minDist = distance(strip[i], strip[j]);
            }
        }
    }
    return minDist;
}

// A recursive function to find the closest pair of points in P[]
// within the range of indices [left, right) (left close, right open)
double closestUtil(std::vector<Point>& P, int left, int right) {
		//if small pool, using bruteforce
    if (right - left <= 3) {
        return bruteForce(P, left, right);
    }

    int mid = left + (right - left) / 2;
    Point midPoint = P[mid];

		// Recursively find the smallest distance in the left and right halves
    double dl = closestUtil(P, left, mid);
    double dr = closestUtil(P, mid, right);

		//start merge
		// Find the smaller of the two distances
    double d = std::min(dl, dr);

		// Create a strip of points that are within distance `d` from the midpoint
		std::vector<Point> strip;
		//distance in [left,mid] -- dl, and that in [mid,right] -- dr, >= min(they) -- d, >= distance in [left,right] >= two
    for (int i = left; i < right; ++i) {
        if (std::abs(P[i].x - midPoint.x) < d) {
            strip.push_back(P[i]);
        }
    }

    return std::min(d, stripClosest(strip, d));
}

// The main function to find the smallest distance
double closestPair(std::vector<Point>& P) {
    std::sort(P.begin(), P.end(), [](const Point& p1, const Point& p2) {
        return p1.x < p2.x;
    });

    return closestUtil(P, 0, P.size());
}

#endif //INC_2D_CLOSESTPAIR_H
