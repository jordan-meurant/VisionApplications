#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"CVUI Test"

using namespace cv;
using namespace cvui;
void tools(){
    Mat frame;
    Mat tools = cv::imread("/Users/jordanmeurant/CLionProjects/Vision1/ImagesEtape5/tools.png");
    cvtColor(tools,frame, COLOR_BGR2GRAY);
    equalizeHist(frame,frame);

    cv::imshow("tools", tools);
    cv::imshow("tools_gray", frame);
    morphologyEx(frame,frame, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(21,21)));
    cv::imshow("opening", frame);
    waitKey();



}


int main(int argc, const char *argv[])
{
    tools();
//    Mat lena = cv::imread("/Users/jordanmeurant/CLionProjects/Vision1/ImagesEtape5/vaisseaux.jpg");
//    Mat frame = lena.clone();
//
//
//    int scale_percent = 100;
//    int width = int(frame.rows * scale_percent / 100);
//    int height = int(frame.cols * scale_percent / 100);
//    Size dim = Size(width, height);
//
//    // resize image
//    Mat resizedImage;
//    resize(frame, resizedImage, dim, INTER_LINEAR);
//
//
//    int low_threshold = 50, high_threshold = 150;
//    bool use_canny = false;
//
//    namedWindow(WINDOW_NAME);
//    init(WINDOW_NAME);
//
//    while (true) {
//        if (use_canny) {
//            cvtColor(resizedImage, frame, COLOR_BGR2GRAY);
//            Canny(frame, frame, low_threshold, high_threshold, 3);
//        } else {
//            resizedImage.copyTo(frame);
//        }
//
//        window(frame, 10, 50, 180 , 180 , "Settings");
//        checkbox(frame, 15, 80, "Use Canny Edge", &use_canny);
//        cvui::trackbar(frame, 15, 110, 165, &low_threshold, 5, 150);
//        cvui::trackbar(frame, 15, 180, 165, &high_threshold, 80, 300);
//
//        update();
//        cv::imshow(WINDOW_NAME, frame);
//
//        if (cv::waitKey(30) == 27) {
//            break;
//        }
//    }
//    return 0;
}