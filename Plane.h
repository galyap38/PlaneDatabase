#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include<math.h>
#include <vector>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <string>

struct PlaneDetails
{
	long long int id;
	std::string plane;
	std::string type;
	long long int flights;

	PlaneDetails() :id(0), plane("uknown"), type("uknown"), flights(0)
	{ }
	PlaneDetails(long long int i,std::string p,std::string t, long long int f):id(i),plane(p),type(t),flights(f)
	{ }
	void print() const
	{
		std::cout << id << " " << plane << " " << type << " " << flights << std::endl;
	}
};

class Plane
{
private:
	bool isSorted;
	std::vector<PlaneDetails> planes;

public:
	Plane();
	void createPlane(long long int, std::string, std::string, long long int);
	void deletePlane(long long int);
	void updatePlane(long long int, std::string, std::string);
	void showPlanes(long int, long int);
	void searchPlane(long long int);
	void optimizePlane();

private:
	bool validateData(long long int, std::string, std::string, long long int);
	void createPlaneInFile(long long int, std::string, std::string,long long int);
	void deletePlaneInFile(long long int);
	void updatePlaneInFile(long long int,int);
	int searchPlaneByID(long long int);
	void merge(std::vector<PlaneDetails>&, std::vector<PlaneDetails>&, std::vector<PlaneDetails>&);
	void mergeSort(std::vector<PlaneDetails>&);
	int binarySearch(int,int,long long int);
	void fillVector();
};
#endif
