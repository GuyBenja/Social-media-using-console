#include "Status.h"
#include "VideoStatus.h"
#include <sstream>
#include <string>

using namespace std;

VideoStatus::VideoStatus(const string& text, const string& path) :Status(text)
	{
		//this is a c'tor for video status
		setVideoStatus(text, path);
	}
VideoStatus::VideoStatus(const std::string& text, const std::string& path, long int time) :Status(text, time)
	{
	//this is a c'tor for video status
		setVideoStatus(text, path);
	}
	void VideoStatus::setVideoStatus(const string& text, const string& path)throw(PathException)
	{//this is a setter for video status
		setStatus(text);
		if (path.find(".mov") != string::npos)
			m_FilePath = path;
		else
			throw (PathException("The video file extention is not \".mov\", please try again"));
	}
	void VideoStatus::displayAdditionalStatus() const 
	{
		//this is a function to display the movie
		stringstream sstream;
		sstream << "start " << m_FilePath;
		system(sstream.str().c_str());
	}
	void VideoStatus::saveAddionalData(ofstream& file)const 
	{
		//this a function to save the video datas
		//Write the video path
		file << "2" << endl;
		size_t pathSize = m_FilePath.size();
		file.write(m_FilePath.data(), pathSize);
		file << endl;
	}