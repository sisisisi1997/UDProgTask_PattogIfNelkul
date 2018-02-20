#include <iostream>
#include <vector>

using std::cout;

int main()
{
	double matrix[4][4];
	std::vector<bool> linkek = std::vector<bool>[4];
	for(int i = 0; i < 4; ++ i)
	{
		
	}
	
	// [0]: M
	// [1]: J
	// [2]: JP
	// [3]: JPL
	linkek[0].push_back(2); // az M hivatkozik a JP-re
	linkek[1].push_back(2); // a J hivatkozik a JP-re
	linkek[2].push_back(2); // a JP magára hivatkozik
	linkek[2].push_back(3); // a JP a JPL-re is hivatkozik
	linkek[3].push_back(0); // a JPL mindenre hivatkozik
	linkek[3].push_back(1);
	linkek[3].push_back(2);

	
}
