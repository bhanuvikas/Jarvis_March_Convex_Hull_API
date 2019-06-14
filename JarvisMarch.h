#ifndef JARVISMARCH_H
#define JARVISMARCH_H

#include <bits/stdc++.h>
#include "FileWriter.h"
#include "Utilities.h"
using namespace std;


//!  JarvisMarch Class 
/*!
  JarvisMarch Class provides the functionality to calculate the convex hull of a set of points
*/
class JarvisMarch
{
private:
	//! A Vector of points each of which is a pair of floats
	vector<pair<float, float> > points;
	//! indicates number of points in the file
	int numOfPoints;
	//! Name of the output file
	string fileName;

public:
	void ConvexHull();
	JarvisMarch(vector<pair<float, float> >, string);
	~JarvisMarch();
};


///Constructor
/*!
\param points The vector of pair of float and float
\param fileName The name of the output file
*/
JarvisMarch::JarvisMarch(vector<pair<float, float> > points, string fileName)
{
	this->points = points;
	this->numOfPoints = points.size();
	this->fileName = fileName;
}


///Clears the vector of pairs each of which is a pair of float and float
/*!
*/
JarvisMarch::~JarvisMarch()
{
	points.clear();
}

///Constructs the convex hull and writes the intermediate points into the output file
/*!
*/
void JarvisMarch::ConvexHull()
{
	FileWriter fileWriter(this->fileName);
	Utilities utilities(this->fileName);
	pair<float, float> p1;
	pair<float, float> p2;
	if(this->numOfPoints < 3)
	{
		p1 = make_pair(INT_MIN*1.0, INT_MIN*1.0);
		p2 = make_pair(INT_MIN*1.0, INT_MIN*1.0);
		fileWriter.WritePairs(p1, p2);
		return;
	}

	int left_most=0;
	for(int i=1;i<this->numOfPoints;i++)
	{
		if(this->points[i].first < this->points[left_most].first)
		{
			left_most = i;
		}
	}

	int curr_point, next_point, last_but_one;
	curr_point = left_most;

	do
	{
		p1 = make_pair(INT_MIN*1.0, INT_MIN*1.0);
		p2 = this->points[curr_point];
		fileWriter.WritePairs(p1, p2);

		next_point = (curr_point+1)%this->numOfPoints;
		int flag=0;
		for(int i=0;i<this->numOfPoints;i++)
		{
			if(utilities.Orientation(this->points[curr_point], this->points[i], this->points[next_point]) == 2)
			{
				flag=1;
				next_point = i;
				p1 = this->points[curr_point];
				p2 = this->points[next_point];
				fileWriter.WritePairs(p1, p2);
			}
		}
		if(!flag)
		{
			p1 = this->points[curr_point];
			p2 = this->points[next_point];
			fileWriter.WritePairs(p1, p2);
		}
		if(next_point == left_most)
		{
			last_but_one = curr_point;
		}
		curr_point = next_point;

	} while(curr_point != left_most);

	p1 = this->points[last_but_one];
	p2 = this->points[left_most];
	fileWriter.WritePairs(p1, p2);

	p1 = make_pair(INT_MIN*1.0, INT_MIN*1.0);
	p2 = this->points[left_most];
	fileWriter.WritePairs(p1, p2);
	return;

}


#endif