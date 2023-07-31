#include "StateSaverReader.h"
#include <iostream>
#include <fstream>
#include "User.h"
#include "FanPage.h"
#include "Exceptions.h"
	template<typename Data>
	void StateSaverReader::SaveData(const Data& data, const std::string& path)const throw(PathException)
	{
		//this is a template function to save data into the file
		std::ofstream outfstream(path, std::ios::binary | std::ios::out | std::ios::app);
		if (outfstream.is_open())
		{
			data.saveToFile(outfstream);
			outfstream.close();
			return;
		}
		//throw(PathException("The path is invalid,please try again"));
	}

	template<typename Data>
	void StateSaverReader::ReadData(std::vector<Data*>& data, const std::string& path)const throw(PathException)
		//this is a template function to read data from the file
	{
		std::ifstream infstream(path, std::ios::binary | std::ios::in);
		if (infstream.is_open())
		{
			while (infstream.peek() != std::ifstream::traits_type::eof())
			{
				Data* temp = new Data(infstream);
				data.push_back(temp);
			}

			infstream.close();
			DeleteFileContent(path);
			return;
		}
		//throw(PathException("The path is invalid,please try again"));
	}


	StateSaverReader::StateSaverReader(const std::string& usersPath, const std::string& pagesPath)
		: m_usersPath(usersPath)
		, m_pagesPath(pagesPath)
	{
		//this is a c'tor 
		EnsureValidation(usersPath);
		EnsureValidation(pagesPath);
	}

	void StateSaverReader::Save(const User& user)const
	{
		//this is a function to save user to file
		SaveData<User>(user, m_usersPath);
	}

	void StateSaverReader::Save(const FanPage& page)const
	{
		//this is a function to save fan page to file
		SaveData<FanPage>(page, m_pagesPath);
	}

	void StateSaverReader::Read(std::vector<User*>& users)
	{
		//this is a function to read user from file
		ReadData<User>(users, m_usersPath);
	}

	void StateSaverReader::Read(std::vector<FanPage*>& pages)
	{
		//this is a function to read fan page from file
		ReadData<FanPage>(pages, m_pagesPath);
	}