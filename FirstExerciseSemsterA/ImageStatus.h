#ifndef IMAGE_STATUS_H
#define IMAGE_STATUS_H
#include "Status.h"
#include "Exceptions.h"

class ImageStatus : public Status
{
private:
	std::string m_FilePath;
public:
	ImageStatus(const std::string& text, const std::string& path, long int time);
	ImageStatus(const std::string& text, const std::string& path);
	virtual ~ImageStatus(){}
	void setImageStatus(const std::string& text, const std::string& path)throw(PathException);

protected:
	void displayAdditionalStatus()const override;
	void saveAddionalData(std::ofstream& file)const override;
};

#endif // !VEDIO_STATUS_H
