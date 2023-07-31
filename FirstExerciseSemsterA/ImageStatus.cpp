#include "ImageStatus.h"
#include <sstream>
#include <string>
#include "Exceptions.h"

using namespace std;
ImageStatus::ImageStatus(const string& text, const string& path, long int time) :Status(text, time)
{
	//This is a c'tor for image status
	setImageStatus(text, path);
}
ImageStatus::ImageStatus(const string& text, const string& path) :Status(text)
{
	//this is a c'tor for image status
	setImageStatus(text, path);
}
void ImageStatus::setImageStatus(const string& text, const string& path)throw(PathException)
{
	//this is a setter function for image status
	setStatus(text);
	if (path.find(".jpg") != string::npos)
		m_FilePath = path;
	else
		throw PathException("The image file extention is not \".jpg\", please try again");
}
void ImageStatus::displayAdditionalStatus()const
{
	//this is a function to display to display the image
	stringstream sstream;
	sstream << "start " << m_FilePath;
	system(sstream.str().c_str());
}
void ImageStatus::saveAddionalData(ofstream& file)const 
{
	//this is a function to save the image status datas
	//Write the image path
	file << "1" << endl;
	size_t pathSize = m_FilePath.size();
	file.write(m_FilePath.data(), pathSize);
	file << endl;
}