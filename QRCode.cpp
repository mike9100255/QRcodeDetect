#include "QRCode.h"
#include <zbar.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

QRCode::QRCode()
{
	std::vector<decodedObject> decodedObjects;
}

QRCode::~QRCode()
{
}

void QRCode::decode(cv::Mat &im, std::vector<decodedObject>&decodedObjects) {
	// Create zbar scanner
	zbar::ImageScanner scanner;
	
	// Configure scanner
	scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

	// Convert image to grayscale
	cv::Mat imGray;
	cv::cvtColor(im, imGray, CV_BGR2GRAY);

	// Wrap image data in a zbar image
	zbar::Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

	// Scan the image for barcodes and QRCodes
	int n = scanner.scan(image);

	// Print results
	for (zbar::Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
	{
		decodedObject obj;
		
		obj.type = symbol->get_type_name();
		obj.data = symbol->get_data();
		QRnum = obj.data;
		// Print type and data
		std::cout << "Type : " << obj.type << std::endl;
		std::cout << "Data : " << obj.data << std::endl << std::endl;

		// Obtain location
		for (int i = 0; i< symbol->get_location_size(); i++)
		{
			obj.location.push_back(cv::Point(symbol->get_location_x(i), symbol->get_location_y(i)));
		}
		obj.rotate = cv::minAreaRect(obj.location);
		QRlocation = obj.location;
		std::cout << "Angle: " << obj.rotate.angle << std::endl;
		std::cout << "Position : " << GetQRPosition() << std::endl;
		decodedObjects.push_back(obj);
	}
}
void QRCode::display(cv::Mat & im, std::vector<decodedObject>& decodedObjects){
	// Loop over all decoded objects
	for (int i = 0; i < decodedObjects.size(); i++)
	{
		std::vector<cv::Point> points = decodedObjects[i].location;
		std::vector<cv::Point> hull;

		// If the points do not form a quad, find convex hull
		if (points.size() > 4)
			convexHull(points, hull);
		else
			hull = points;

		// Number of points in the convex hull
		int n = hull.size();

		for (int j = 0; j < n; j++)
		{
			line(im, hull[j], hull[(j + 1) % n], cv::Scalar(255, 0, 0), 3);
		}

	}
	im.copyTo(image);
	// Display results 
	imshow("Results", im);
}

std::string QRCode::GetQRNumber()
{
	return QRnum;
	
}

cv::Point QRCode::GetQRPosition()
{
	cv::Moments moments = cv::moments(QRlocation);
	int QRPositionX = moments.m10 / moments.m00;
	int QRPositionY = moments.m01 / moments.m00;

	return cv::Point(QRPositionX, QRPositionY);
}

cv::Mat QRCode::GetImage(){
	return image;
}
