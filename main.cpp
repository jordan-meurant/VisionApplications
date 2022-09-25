#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"
#define IMAGE_PATH(filename) std::string("D:\\Users\\mb624\\Documents\\GitHub\\VisionApplications\\ImagesEtape5\\") + filename

#define WINDOW_NAME	"CVUI Test"

using namespace cv;
using namespace cvui;
void tools() {

    Mat tools = cv::imread(IMAGE_PATH("tools.png"));
    Mat frame, out, opening, th;

    cvtColor(tools, frame, COLOR_BGR2GRAY);
    cv::imshow("Image tools", tools);

    morphologyEx(frame, opening, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(21, 21)));
    subtract(frame, opening, frame);
    cv::imshow("Image after opening", frame);

    threshold(frame, th, 0, 255, THRESH_BINARY + THRESH_OTSU);
    cv::imshow("Result", th);
    waitKey();

}

Mat imreconstruct(Mat& image, Mat& mask, int radius = 3)
{
    int counter = 0;
    while (1)
    {
        Mat mat;
        morphologyEx(image, mat, MORPH_DILATE, getStructuringElement(MORPH_RECT, Size(radius, radius)));
        bitwise_and(mat, mask, mat);
        if (countNonZero(image) == countNonZero(mat))
            return mat;
        image = mat;
    }
}

void balanes()
{
    Mat frame, seuillage, erosion;
    Mat balanes = cv::imread(IMAGE_PATH("balanes.png"));
    cvtColor(balanes, frame, COLOR_BGR2GRAY);
    cvtColor(balanes, balanes, COLOR_BGR2GRAY);
    threshold(frame, seuillage, 0, 255, THRESH_BINARY + THRESH_OTSU);
    morphologyEx(seuillage, erosion, MORPH_ERODE, getStructuringElement(MORPH_RECT, Size(11, 11)));
    cv::imshow("erosion", erosion);
    cv::imshow("seuillage", seuillage);
    const Mat& rec = imreconstruct(erosion, seuillage);
    Mat origin;
    bitwise_and(rec, balanes, origin);
    cv::imshow("GRANDE", origin);
    Mat petitesBalanes;
    subtract(seuillage, rec, petitesBalanes);
    morphologyEx(petitesBalanes, petitesBalanes, MORPH_ERODE, getStructuringElement(MORPH_RECT, Size(5, 5)));
    Mat rec2 = imreconstruct(petitesBalanes, seuillage);
    bitwise_and(rec2, balanes, origin);
    cv::imshow("PETITES", origin);
    waitKey();
}

void pois()
{
    Mat pois = cv::imread(IMAGE_PATH("petitsPois.png"));
    Mat *caneaux = new Mat[3];
    Mat red, blue, redNeg, blueNeg;
    cv::imshow("poids", pois);

    split(pois, caneaux);
    red = caneaux[0];
    blue = caneaux[2];
    delete[] caneaux;

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

int main(int argc, const char* argv[])
{
    pois();
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