#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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

    Mat tools = cv::imread(IMAGE_PATH("tools.png"));
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
void pois2(){
    Mat pois = cv::imread(IMAGE_PATH("petitsPois.png"));
    Mat channels[3], poidsBleus, poidsRouges;;
    split(pois, channels);
    cvtColor(pois, pois, COLOR_BGR2GRAY);

    bitwise_not(pois,pois);
    cv::imshow("poids", pois);

    threshold(channels[0], poidsBleus, 0, 255, THRESH_BINARY_INV);
    morphologyEx(poidsBleus, poidsBleus, MORPH_ERODE, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    threshold(channels[2], poidsRouges, 0, 255, THRESH_BINARY_INV);
    morphologyEx(poidsRouges, poidsRouges, MORPH_ERODE, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    cv::imshow("Poids bleus", poidsBleus);
    cv::imshow("Poids poidsRouges", poidsRouges);
    waitKey();
}

void pois()
{
    Mat pois = cv::imread(IMAGE_PATH("petitsPois.png"));
    Mat red, blue, redNeg, blueNeg;
    cv::imshow("poids", pois);

    Mat channels[3];
    split(pois, channels);
    red = channels[0];
    blue = channels[2];


    threshold(red, redNeg, 0, 255, THRESH_BINARY_INV);
    threshold(blue, blueNeg, 0, 255, THRESH_BINARY_INV);

    morphologyEx(redNeg, red, MORPH_ERODE, getStructuringElement(MORPH_RECT, Size(11, 11)));
    morphologyEx(blueNeg, blue, MORPH_ERODE, getStructuringElement(MORPH_RECT, Size(11, 11)));

    red = imreconstruct(red, redNeg);
    blue = imreconstruct(blue, blueNeg);


    cv::imshow("red", red);
    cv::imshow("blue", blue);
    waitKey();
}

int main(int argc, const char *argv[]) {
    //tools();
   // balanes();
    pois2();
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