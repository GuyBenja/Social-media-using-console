#ifndef STATE_SAVER_READER_H
#define STATE_SAVER_READER_H
#include <iostream>
#include <fstream>
#include "User.h"
#include "FanPage.h"
#include "Exceptions.h"

class StateSaverReader
{
private:
	const std::string m_usersPath;
	const std::string m_pagesPath;

	inline void EnsureValidation(const std::string& path)throw(PathException)
	{
		if (path.empty())
			throw(PathException("Invalid path"));
	}

	inline void DeleteFileContent(const std::string& path)const throw(PathException)
	{
		if (path.empty())
			throw(PathException("Invalid path"));

		std::ofstream outfstream(path, std::ios::trunc | std::ios::binary);
		outfstream.close();
	}

	template<typename Data>
	void SaveData(const Data& data, const std::string& path)const;

	template<typename Data>
	void ReadData(std::vector<Data*>& data, const std::string& path)const;

public:
	StateSaverReader()
		: m_usersPath("usersStates.b")
		, m_pagesPath("pagesStates.b")
	{}

	StateSaverReader(const std::string& usersPath, const std::string& pagesPath);

	void Save(const User& user)const;

	void Save(const FanPage& page)const;

	void Read(std::vector<User*>& users);

	void Read(std::vector<FanPage*>& pages);
};
#endif //!STATE_SAVER_READER_H

