/* 
 * File:   Box.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 14. August 2014, 16:59
 */

#include "Box.hpp"

std::pair<bool,Ray> Box::intersect(Ray const& ray) const {
    float tmin = (edge1.x - ray.origin.x) / ray.direction.x;
    float tmax = (edge2.x - ray.origin.x) / ray.direction.x;
    if(tmin > tmax) std::swap(tmin, tmax);

    float ty_min = (edge1.y - ray.origin.y) / ray.direction.y;
    float ty_max = (edge2.y - ray.origin.y) / ray.direction.y;
    if(ty_min > ty_max) std::swap(ty_min, ty_max);

    if((tmin > ty_max) || (ty_min > tmax))
        return std::make_pair(false,Ray());
    if(ty_min > tmin) tmin = ty_min;
    if(ty_max < tmax) tmax = ty_max;

    float tz_min = (edge1.z - ray.origin.z) / ray.direction.z;
    float tz_max = (edge2.z - ray.origin.z) / ray.direction.z;
    if(tz_min > tz_max) std::swap(tz_min, tz_max);

    if((tmin > tz_max) || (tz_min > tmax))
      return std::make_pair(false,Ray());
    if(tz_min > tmin) tmin = tz_min;
    if(tz_max < tmax) tmax = tz_max;

    ray.distance = tmin;
    glm::vec3 n = ray.origin + tmin * ray.direction;
    return std::make_pair(
            true,
            Ray(ray.origin + tmin * ray.direction, calcNormal(n.x, n.y, n.z))
    );
}

glm::vec3 Box::calcNormal(float const& x, float const& y, float const& z) const {
    glm::vec3 normal;
    if(fabs(x - edge1.x) < 0.01f){//normal from left
      normal.x = -1;
      normal.y = 0;
      normal.z = 0;
    }else if(fabs(x - edge2.x) < 0.01f){//normal from right
      normal.x = 1;
      normal.y = 0;
      normal.z = 0;
    }else if(fabs(y - edge1.y) < 0.01f){//normal from bottom
      normal.x = 0;
      normal.y = -1;
      normal.z = 0;
    }else if(fabs(y - edge2.y) < 0.01f){//normal from up
      normal.x = 0;
      normal.y = 1;
      normal.z = 0;
    }else if(fabs(z - edge1.z) < 0.01f){//normal from back
      normal.x = 0;
      normal.y = 0;
      normal.z = 1;
    }else if(fabs(z - edge2.z) < 0.01f){//normal from front
      normal.x = 0;
      normal.y = 0;
      normal.z = -1;
    }
    return normal;
}

