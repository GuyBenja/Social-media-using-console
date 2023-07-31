#include <iostream>
#include <fstream>
#include "Status.h"
#include "Exceptions.h"


	void Status::setStatus(const std::string text) throw(StatusException)
	{
		//this is a setter for status
		if (text.size() != 0)
			m_text = text;
		else
			throw(StatusException("Status can not be empty ,please try again"));
	}
	void Status::displayStatus() const
	{
		//this is function to display status
		std::cout << m_text << std::endl;
		printPublishTime();
		displayAdditionalStatus();
	}
	void Status::printPublishTime()const
	{
		//this is a function to print the time the status published
		
		struct tm tm;
		gmtime_s(&tm, &m_time);

		struct tm local_tm;
		localtime_s(&local_tm, &m_time);

		char s[64];
		strftime(s, sizeof(s), "%c", &local_tm);

		std::cout << s << std::endl;
	}

	void Status::saveToFile(std::ofstream& file)const
	{
		//this is a function to save the status data to file
		// Write the text
		size_t textSize = m_text.size();
		file.write(m_text.data(), textSize);
		file << std::endl;

		//Wrtie Date
		file << m_time << std::endl;

		//Write Movie/Image
		saveAddionalData(file);
	}