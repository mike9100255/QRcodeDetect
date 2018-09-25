#include "QRCode.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <Windows.h>
#include <iostream>

int main() {
	QRCode QRcode;
	cv::VideoCapture cap(1);
	cv::Mat image;
	while (1) {
		cap >> image;

		std::vector<decodedObject> decodedObjects;

		// Find and decode barcodes and QR codes
		QRcode.decode(image, decodedObjects);

		// Display location 
		QRcode.display(image, decodedObjects);
		cv::Mat image = QRcode.GetImage();

		int key = cvWaitKey(1);
		if (key == VK_ESCAPE) break;


		switch (key)
		{
		case 'r':
			cv::imwrite("QRtest.png", image);
			std::cout << "SAVE!" << std::endl;
			break;
		default:
			break;
		}
	}
	return 0;
}