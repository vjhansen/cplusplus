//  Travelling salesman problem
//  Victor


// - 1. definer hvor mange byer vi skal besøke
// - 2. angi posisjon (x,y,z) for hver by.


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
using namespace std;

int main(int argc, const char * argv[]) {
    
    // define vector of size 3 for holding xyz-coordinates
    std::vector<int> v(3);
    v.clear();
    std::cout << "Enter numbers: ('Q' to quit)"<< std::endl;
    
int num;
while (cin) {
    std::cin >> num;
    if (!cin) {
        break;
    }
    v.push_back(num);
    
    if (v.size() > 3){
        v.pop_back();  // use pop.back() to remove last item of vector
    }
}
    
    std::cout << "you entered " << v.size() << endl;
    
    for (int i =0; i<v.size(); i++) {
        cout << v[i] << endl;
    }
    
    return 0;
}
