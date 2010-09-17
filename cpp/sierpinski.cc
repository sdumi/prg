#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const unsigned DIM = 2;

/*

Triangle point numbering:

         p1
        /  \
       /    \
      /      \
     p0------p2

The s0, s1 and s2 functions below are contraction maps, i.e.
they pull the specified point towards the fixed point of the
map, by an amount corresponding to the distance between the
point and the fixed point scaled by the contraction mapping
constant k.  The fixed point of s0 is p0, and the fixed point
of s1 is p1, etc.

For example, the following call to s0:

s0(2, 0.5, p0, p1, p2)

returns a new point exactly halfway between p0 and p2 in the
above triangle diagram.

*/

vector<double> s0(const int point,
      const double k,
      const vector<double> &p0,
      const vector<double> &p1,
      const vector<double> &p2){
  vector<double> p(DIM, 0.0);

  switch(point){
  case 0:
    return(p0); // fixed point of the map
  case 1:
    p[0] = p0[0] + k*(p1[0] - p0[0]);
    p[1] = p0[1] + k*(p1[1] - p0[1]);
    break;
  case 2:
    p[0] = p0[0] + k*(p2[0] - p0[0]);
    p[1] = p0[1] + k*(p2[1] - p0[1]);
    break;
  }

  return(p);
}

vector<double> s1(const int point,
      const double k,
      const vector<double> &p0,
      const vector<double> &p1,
      const vector<double> &p2){
  vector<double> p(DIM, 0.0);

  switch(point){
  case 0:
    p[0] = p1[0] + k*(p0[0] - p1[0]);
    p[1] = p1[1] + k*(p0[1] - p1[1]);
    break;
  case 1:
    return(p1); // fixed point of the map
  case 2:
    p[0] = p1[0] + k*(p2[0] - p1[0]);
    p[1] = p1[1] + k*(p2[1] - p1[1]);
    break;
  }

  return(p);
}

vector<double> s2(const int point,
      const double k,
      const vector<double> &p0,
      const vector<double> &p1,
      const vector<double> &p2){
  vector<double> p(DIM, 0.0);

  switch(point){
  case 0:
    p[0] = p2[0] + k*(p0[0] - p2[0]);
    p[1] = p2[1] + k*(p0[1] - p2[1]);
    break;
  case 1:
    p[0] = p2[0] + k*(p1[0] - p2[0]);
    p[1] = p2[1] + k*(p1[1] - p2[1]);
    break;
  case 2:
    return(p2); // fixed point of the map
  }

  return(p);
}

// Sierpinski gasket function
//
// Does the following:
// 1. Applies a contraction map to each of three input points.
// 2. Saves the newly computed points in a vector.
// 3. Recursively calls itself on the resulting three inner triangles.
//
void sg(const int d, // depth (how many more times do we recurse)
  const double k, // contraction mapping constant
  const vector<double> &p0,
  const vector<double> &p1,
  const vector<double> &p2,
  vector< vector<double> > &points){

  if(d == 0) return;

  vector<double> p01, p12, p20;
  p01 = s0(1,k,p0,p1,p2);
  p12 = s1(2,k,p0,p1,p2);
  p20 = s2(0,k,p0,p1,p2);

  points.push_back(p01);
  points.push_back(p12);
  points.push_back(p20);

  sg(d-1, k, p0, p01, s0(2,k,p0,p1,p2), points);
  sg(d-1, k, s1(0,k,p0,p1,p2), p1, p12, points);
  sg(d-1, k, p20, s2(1,k,p0,p1,p2), p2, points);
}

int main(){

  vector<double> p0(DIM), p1(DIM), p2(DIM);

  // Initialize the three corners of the starting triangle
  p0[0] = 0.0;     p0[1] = 0.0;
  p1[0] = 1.0/2.0; p1[1] = sqrt(3.0)/2.0;
  p2[0] = 1.0;     p2[1] = 0.0;

  int depth = 0;
  double k = 0.5;
  cerr << "Enter depth (integer > 0, usually 10 is good): ";
  cin >> depth;
  cerr << "Enter contraction mapping constant (for example 0.5):  ";
  cin >> k;

  // This vector holds all data points generated
  // via recursive calls to sg()
  vector< vector<double> > points;

  points.push_back(p0);
  points.push_back(p1);
  points.push_back(p2);

  // Recursively generate Sierpinski's gasket
  sg(depth-1, k, p0, p1, p2, points);

  for(vector< vector<double> >::size_type i=0; i < points.size(); ++i){
    cout << points[i][0] << ' ' << points[i][1] << endl;
  }

  return 0;
}
