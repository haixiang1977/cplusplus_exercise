#include <iostream>
#include <map>
#include <vector>
#include <algorithm> // for sort

bool sort_by_time(const std::pair<int, int>& p1, std::pair<int, int>& p2)
{
	return p1.second > p2.second;
}

int main()
{
	std::map<int, int> mymap;
	mymap[1] = 10;
	mymap[2] = 100;
	mymap[3] = 1;
	mymap[4] = 10;
	mymap[5] = 100;

	std::vector<std::pair<int, int> > vec;
	std::map<int, int>::iterator it;
	for (it = mymap.begin(); it != mymap.end(); it++)
	{
		vec.push_back(std::make_pair(it->first, it->second));
	}

	std::sort(vec.begin(), vec.end(), sort_by_time);

	for (int i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i].first << ":" << vec[i].second << std::endl;
	}

	return 0;
}

