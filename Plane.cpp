#include "Plane.h"

Plane::Plane()
{
	isSorted = false;
	fillVector();
}

void Plane::createPlane(long long int id, std::string plane, std::string type, long long int flights)
{
	isSorted = false;

	if (!validateData(id, plane, type, flights))
	{
		std::cout << "Invalid data\n";
		return;
	}

	PlaneDetails temp(id,plane, type, flights);
	planes.push_back(temp);

	createPlaneInFile(id, plane, type, flights);
}

void Plane::deletePlane(long long int id)
{
	isSorted = false;
	int index = searchPlaneByID(id);

	if (index == -1)
	{
		std::cout << "No such id\n";
		return;
	}

	planes.erase(planes.begin() + index);
	
	deletePlaneInFile(id);
}

void Plane::updatePlane(long long int id, std::string attribute, std::string newName)
{
	isSorted = false;
	int index = searchPlaneByID(id);

	if (index == -1)
	{
		std::cout << "There is no such id\n";
		return;
	}
	
	if (attribute == "id")
	planes[index].id = std::stoi(newName);
	if (attribute == "flights")
	planes[index].flights = std::stoi(newName);
	if (attribute == "plane")
	planes[index].plane = newName;
	if(attribute == "type")
	planes[index].type = newName;

	updatePlaneInFile(id,index);
}

bool Plane::validateData(long long int id, std::string plane, std::string type, long long int flights)
{
	long long int numLimit = pow(2, 50);
	int stringLimit = pow(2, 8);

	return id < numLimit && plane.size() < stringLimit && type.size() < stringLimit && flights < numLimit;
}

void Plane::createPlaneInFile(long long int id, std::string plane, std::string type,long long int flights)
{

	std::ofstream dataBasePlane("Planes.db.txt",std::ios::app);

	if (!dataBasePlane)
	{
		std::cout << "The file could not open" << std::endl;
	}

	dataBasePlane << id <<" " << plane<<" "<< type<<" "<< flights << "\n";

	dataBasePlane.close();
}

void Plane::deletePlaneInFile(long long int id)
{
	std::ifstream dataBasePlane("Planes.db.txt");

	if (!dataBasePlane)
	{
		std::cout << "The file could not open" << std::endl;
	}

	std::ofstream temp("temp.txt",std::ios::app);

	if (!temp)
	{
		std::cout << "The file could not open" << std::endl;
	}

	std::string line;
	while (std::getline(dataBasePlane,line))
	{
		long long int searchID = std::stoi(line);
		if (searchID != id)
		{
			temp << line << "\n";
		}
	}

	dataBasePlane.close();
	temp.close();

	std::remove("Planes.db.txt");
	int successful = std::rename("temp.txt","Planes.db.txt");

	if (successful != 0)
	{
		std::cout << "The file could not be renamed" << std::endl;
	}
	
}

void Plane::updatePlaneInFile(long long int id,int index)
{
	std::ifstream dataBasePlane("Planes.db.txt");

	if (!dataBasePlane)
	{
		std::cout << "The file could not open" << std::endl;
	}

	std::ofstream temp("temp.txt", std::ios::app);

	if (!temp)
	{
		std::cout << "The file could not open" << std::endl;
	}

	std::string line;
	while (std::getline(dataBasePlane, line))
	{
		long long int searchID = std::stoi(line);
		if (searchID != id)
		{
			temp << line << "\n";
		}
		else
		{
			temp << planes[index].id << " " << planes[index].plane << " " << planes[index].type << " " << planes[index].flights << "\n";
		}
	}

	dataBasePlane.close();
	temp.close();

	std::remove("Planes.db.txt");
	int successful = std::rename("temp.txt", "Planes.db.txt");

	if (successful != 0)
	{
		std::cout << "The file could not be renamed" << std::endl;
	}	
}

void Plane::showPlanes(long int limit, long int offset)
{
	int end = limit + offset;
	int size = planes.size();

	if (end > size)
	{
		end = size - 1;
	}

	for (int i = offset; i < end; ++i)
	{
		planes[i].print();
	}
}

void Plane::searchPlane(long long int id)
{
	int beggining = 0;
	int end = planes.size() - 1;
	int result = 0;

	if (isSorted)
	{
		result = binarySearch(beggining, end, id);
	}
	else
	{
		result = searchPlaneByID(id);
	}

	if (result == -1)
	{
		std::cout << "There is no such id\n";
		return;
	}

	planes[result].print();
}

void Plane::optimizePlane()
{	
	mergeSort(planes);
	isSorted = true;
}

int Plane::searchPlaneByID(long long int id)
{
	int size = planes.size();

	for (int i = 0; i < size; ++i)
	{
		if (planes[i].id == id)
			return i;
	}
	return -1;
}

void Plane::merge(std::vector<PlaneDetails>& left,std::vector<PlaneDetails>& right, std::vector<PlaneDetails>& planes)
{
	int sizeOfLeft = left.size();
	int sizeOfRight = right.size();
	
	int i = 0, j = 0, k = 0;

	while (i<sizeOfLeft && j<sizeOfRight)
	{
		if (left[i].id <= right[j].id)
		{
			planes[k] = left[i];
			++i;
		}
		else
		{
			planes[k] = right[j];
			++j;
		}
		k++;
	}

	while (i < sizeOfLeft)
	{
		planes[k] = left[i];
		i++;
		k++;
	}

	while (j < sizeOfRight)
	{
		planes[k] = right[j];
		j++;
		k++;
	}
}

void Plane::mergeSort(std::vector<PlaneDetails>& planes)
{
	int size = planes.size();

	if (size <= 1) 
		return;

		int middle = size / 2;
		std::vector<PlaneDetails> left;
		std::vector<PlaneDetails> right;

		for (int i = 0; i < middle; ++i)
		{
			left.push_back(planes[i]);
		}

		for (int j = middle; j < size; ++j)
		{
			right.push_back(planes[j]);
		}
		
		mergeSort(left);
		mergeSort(right);
		
		merge(left, right, planes);
}

int Plane::binarySearch(int left,int right,long long int id)
{
	if (left <= right)
	{
		int middle = (left + right) / 2;

		if (planes[middle].id == id)
		{
			return middle;
		}
		else if (planes[middle].id < id)
		{
			return binarySearch(middle + 1, right, id);
		}
		else
		{
			return binarySearch(left, middle - 1, id);
		}
	}	
	return -1;
}

void Plane::fillVector()
{
	std::ifstream dataBasePlane("Planes.db.txt");

	if (!dataBasePlane)
	{
		std::cout << "The file could not open\n";
	}

	dataBasePlane.seekg(0, std::ios::end);
	if (dataBasePlane.tellg() == 0) 
	{
		return;
	}

	dataBasePlane.seekg(0, std::ios::beg);
	std::string line, word;

	while (std::getline(dataBasePlane, line))
	{
		int counter = 0;
		PlaneDetails temp;
		std::istringstream SplitToSpaces(line);

		while (SplitToSpaces)
		{
			SplitToSpaces >> word;
			counter++;

			switch (counter)
			{
			case 1:temp.id = std::stoi(word); break;
			case 2:temp.plane = word; break;
			case 3:temp.type = word; break;
			case 4:temp.flights = std::stoi(word);
			}
		}
		planes.push_back(temp);
	}
}


