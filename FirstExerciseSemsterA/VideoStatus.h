#ifndef VIDEO_STATUS_H
#define VIDEO_STATUS_H
#include "Status.h"
#include "Exceptions.h"

class VideoStatus : public Status
{
private:
	std::string m_FilePath;
public:
	VideoStatus(const std::string& text, const std::string& path);
	VideoStatus(const std::string& text, const std::string& path, long int time);
	virtual ~VideoStatus() {}
	void setVideoStatus(const std::string& text, const std::string& path)throw(PathException);

protected:
	void displayAdditionalStatus() const override;
	void saveAddionalData(std::ofstream& file)const override;
};
#endif // !VIDEO_STATUS_H
