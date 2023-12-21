//
// Created by 沈嘉瑞 on 2023.12.21.
//

#ifndef NEAREST_SHAPE_MANAGEMENT_H
#define NEAREST_SHAPE_MANAGEMENT_H

#include "../Point/PointManagement.h"
#include "../LineSegment/LineSegementManagement.h"
#include "../Triangle/TriangleManagement.h"

class Management {
    PointManagement pointManagement;
    LineSegementManagement lineSegementManagement;
    TriangleManagement triangleManagement;

};

#endif //NEAREST_SHAPE_MANAGEMENT_H