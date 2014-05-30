#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>



int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << " Usage: no image files were specified" << std::endl;
		return -1;
	}

	cv::Mat img;
	img = cv::imread(argv[1], CV_8UC1);

	if (!img.data) // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	//Apply blur to smooth edges and use adaptative thresholding  
	cv::Size size(3, 3);
	cv::GaussianBlur(img, img, size, 0);

	adaptiveThreshold(img, img, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 75, 10);
	cv::bitwise_not(img, img);


	//We trace the distinct lines

	std::vector<cv::Vec4i> lines;
	HoughLinesP(img, lines, 1, CV_PI / 180, 80, 100, 10);


	for (int i = 0, len = lines.size(); i < len; i++)
	{
		cv::Vec4i line = lines[i];
		cv::line(img, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0, 255, 0));
	}
	//cv::namedWindow("Image Display");
	cv::imshow("Image display", img);


	cv::waitKey(0); // Wait for a keystroke in the window
	return 0;
}

