#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> getData(string strFileName)
{	
	//Object Instance
	string strUILine;
	ifstream fileIn;
	vector<string> vData(1);
	
	//Open File
	fileIn.open(strFileName.c_str());
		
	//Get data while looping through file
	while(!fileIn.eof())
	{
		getline(fileIn, strUILine);
		vData.push_back(strUILine);
	}
	
	//Close File
	fileIn.close();
	
	return vData;
}//End of getData
