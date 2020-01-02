#include "Plane.h"

int main()
{
	Plane p;
	std::string plane;
	std::string type;
	long int id;
	long int flights;

	std::string command;
	std::cin >> command;

	while (command != "exit")
	{
		if (command == "create")
		{
			std::cin >> id >> plane >> type >> flights;
			p.createPlane(id, plane, type, flights);
		}
		if (command == "delete")
		{
			std::cin >> id;
			p.deletePlane(id);
		}
		if (command == "update")
		{
			std::string newName;
			std::string attribute;
		
			std::cin >> id;
			std::cin >> attribute;
			std::cin >> newName;

			p.updatePlane(id, attribute, newName);
		}
		if (command == "search")
		{
			std::cin >> id;
			p.searchPlane(id);
		}
		if (command == "show")
		{
			int offset, limit;
			std::cin >> offset >> limit;
			p.showPlanes(limit, offset);
		}
		if (command == "optimize")
		{
			p.optimizePlane();
		}
		std::cin >> command;
	}
	return 0;
}