#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#define CVUI_IMPLEMENTATION

#include "cvui.h"

using namespace std;

#define WINDOW_NAME    "CVUI Test"
#define IMAGE_PATH(filename) std::string("/Users/jordanmeurant/CLionProjects/Vision1/ImagesEtape5/") + filename

using namespace cv;
using namespace cvui;

Mat imreconstruct(Mat &image, Mat &mask, int radius = 3) {
    int counter = 0;
    while (1) {
        Mat mat;
        morphologyEx(image, mat, MORPH_DILATE, getStructuringElement(MORPH_ELLIPSE, Size(radius, radius)));
        bitwise_and(mat, mask, mat);
        if (countNonZero(image) == countNonZero(mat))
            return mat;
        image = mat;
    }
}

void tools() {

    Mat tools = cv::imread("/Users/jordanmeurant/CLionProjects/Vision1/ImagesEtape5/tools.png");
    Mat frame, out, opening, th;

    cvtColor(tools, frame, COLOR_BGR2GRAY);
    cv::imshow("Image tools", tools);

    morphologyEx(frame, opening, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(21, 21)));
    subtract(frame, opening, frame);
    cv::imshow("Image after opening", frame);

    threshold(frame, th, 0, 255, THRESH_BINARY + THRESH_OTSU);
    cv::imshow("Result", th);
    waitKey();
}

void balanes() {
    Mat frame, seuillage, erosion;
    Mat balanes = cv::imread(IMAGE_PATH("balanes.png"));
    cvtColor(balanes, frame, COLOR_BGR2GRAY);
    cvtColor(balanes, balanes, COLOR_BGR2GRAY);

    threshold(frame, seuillage, 0, 255, THRESH_BINARY + THRESH_OTSU);
    cv::imshow("GRAND ", seuillage);
    morphologyEx(seuillage, erosion, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));
    const Mat &rec = imreconstruct(erosion, seuillage);


    Mat grandesBalanes;
    bitwise_and(rec, balanes, grandesBalanes);
    cv::imshow("GRAND Balanes", grandesBalanes);

    Mat petitesBalanes;
    subtract(seuillage, rec, petitesBalanes);
    morphologyEx(petitesBalanes, petitesBalanes, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    Mat reconstructionPetitesBalanes = imreconstruct(petitesBalanes, seuillage);
    bitwise_and(reconstructionPetitesBalanes, balanes, petitesBalanes);
    cv::imshow("PETITES Balanes", petitesBalanes);
    waitKey();
}


int main(int argc, const char *argv[]) {
    //tools();
    balanes();
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