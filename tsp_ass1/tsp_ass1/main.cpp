//  Travelling salesman problem
//  Victor


/*
 - Use a Point class to represent the individual 3D points in the inputs.
 - pass const-references as arguments to the functions specified below; this will require you to update your Point class with const specifications where required.
 */

// - 1. definer hvor mange byer vi skal besøke
// - 2. angi posisjon for hver by.





#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace std;
struct Vertex {
    float x,y,z;
    Vertex(float x, float y, float z)
    : x(x), y(y), z(z) {}
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex) {
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
}

// find distance between two points (x,y,z)
float distance(int x1, int y1, int z1, int x2, int y2, int z2) {
    return sqrt( pow(x2-x1,2)+pow(y2-y1,2)+pow(z2-z1,2) );
}


int main(int argc, const char * argv[]) {
    
    
    
    std::vector<vector<int>> x;
    int n;
    cin >> n;
    vector<int> vec;
    
    cout << "how many cities? ";
    for (int i = 0; i < n; i++) {
        vec.push_back(i);
        x.push_back(vec);
    }
    std::cout << vec[0];
    
    std::vector<Vertex> vertices;
    vertices.reserve(3);
    vertices.clear();
    //p1.clear();
    
    std::cout << "Enter 3 integers: \n";
    std::istream_iterator<int> iit(cin);
    std::copy(iit, std::istream_iterator<int>(), vec.begin());
    vertices.emplace_back(vec[0],vec[1],vec[2]);
        
    
    
    // reference, we dont want to copy.
    for (const Vertex& v : vertices) {
        std::cout <<endl<< v << std::endl;
    }
    
    std::cin.get();
    
    
    /*
     std::vector<int> point1 = {2,3,1};
     std::vector<int> point2 = {8,-5,0};
     //--------------------------------------------
     
     */
    
    /*
     
     
     std::cout << "Here are the values you entered: ";
     for(i = 0; i < points.size(); i++) std::cout << points[ i ] << " ";
     //--------------------------------------------
     */
    
    
    // calc distance between point 1 and points 2,3,4,5
    // calc distance between point 2 and points 1,3,4,5 and so on...
    
    // std::cout << distance(point1[0],point1[1],point1[2],point2[0],point2[1],point2[2]) << std::endl;
    
    return 0;
}
