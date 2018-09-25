#include <opencv2/core.hpp>

typedef struct
{
	std::string type;
	std::string data;
	std::vector <cv::Point> location;
	cv::RotatedRect rotate;
} decodedObject;

class QRCode
{
public:
	QRCode();
	~QRCode();

	void decode(cv::Mat &im, std::vector<decodedObject>&decodedObjects);
	void display(cv::Mat &im, std::vector<decodedObject>&decodedObjects);

	std::string GetQRNumber();
	cv::Point GetQRPosition();
	cv::Mat GetImage();
private:
	cv::Mat image;
	std::string QRnum;
	std::vector <cv::Point> QRlocation;
};