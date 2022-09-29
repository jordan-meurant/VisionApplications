#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

using namespace std;

#define WINDOW_NAME    "CVUI Test"
#define IMAGE_PATH(filename) std::string("D:\\Users\\mb624\\Documents\\GitHub\\VisionApplications\\ImagesEtape5\\") + filename
#define delta_time(start, end) std::to_string(std::chrono::duration<double, std::milli>(end - start).count()) + std::string("ms")
#define delta_time_db(start, end) std::chrono::duration<double, std::milli>(end - start).count()
#define imshow(title, frame) if(show_native)cv::imshow(title, frame)


using namespace cv;
using namespace cvui;

bool show_native = true;


void save_delta_time(double dt)
{
    ofstream out("performances.txt", ios::out);
    if (out.is_open())
    {
        out << dt << endl;
    }
    out.close();
}



Mat imreconstruct(Mat &image, Mat &mask, int radius = 3) {
    while (1) {
        Mat mat;
        morphologyEx(image, mat, MORPH_DILATE, getStructuringElement(MORPH_ELLIPSE, Size(radius, radius)));
        bitwise_and(mat, mask, mat);
        if (countNonZero(image) == countNonZero(mat))
            return mat;
        image = mat;
    }
}

double tools() {

    Mat tools = cv::imread(IMAGE_PATH("tools.png"));
    Mat frame, out, opening, th;

    cvtColor(tools, frame, COLOR_BGR2GRAY);

    auto t_start = std::chrono::high_resolution_clock::now();

    morphologyEx(frame, opening, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(21, 21)));
    subtract(frame, opening, frame);

    threshold(frame, th, 0, 255, THRESH_BINARY + THRESH_OTSU);

    auto t_end = std::chrono::high_resolution_clock::now();

    save_delta_time(delta_time_db(t_start, t_end));
    imwrite("tools-result.png", th);

    imshow("Tools d'origine: temps => " + delta_time(t_start, t_end), tools);
    imshow("Result", th);
    //waitKey();
    return delta_time_db(t_start, t_end);
}

double balanes() {
    Mat frame, seuillage, erosion;
    Mat balanes = cv::imread(IMAGE_PATH("balanes.png"));
    Mat origin = balanes.clone();
    cvtColor(balanes, frame, COLOR_BGR2GRAY);
    cvtColor(balanes, balanes, COLOR_BGR2GRAY);

    auto t_start = std::chrono::high_resolution_clock::now();

    threshold(frame, seuillage, 0, 255, THRESH_BINARY + THRESH_OTSU);
    morphologyEx(seuillage, erosion, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));
    const Mat &rec = imreconstruct(erosion, seuillage);

    Mat grandesBalanes;
    bitwise_and(rec, balanes, grandesBalanes);

    Mat petitesBalanes;
    subtract(seuillage, rec, petitesBalanes);
    morphologyEx(petitesBalanes, petitesBalanes, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    Mat reconstructionPetitesBalanes = imreconstruct(petitesBalanes, seuillage);
    bitwise_and(reconstructionPetitesBalanes, balanes, petitesBalanes);

    auto t_end = std::chrono::high_resolution_clock::now();

    save_delta_time(delta_time_db(t_start, t_end));
    imwrite("petites-balanes-result.png", petitesBalanes);
    imwrite("grandes-balanes-result.png", grandesBalanes);
    imshow("balanes d'origine: temps => " + delta_time(t_start, t_end), origin);
    imshow("GRAND Balanes", grandesBalanes);
    imshow("PETITES Balanes", petitesBalanes);
    //waitKey();
    return delta_time_db(t_start, t_end);
}

double pois()
{
    Mat pois = cv::imread(IMAGE_PATH("petitsPois.png"));
    Mat red, blue, redNeg, blueNeg;
    Mat channels[3];

    auto t_start = std::chrono::high_resolution_clock::now();
    
    split(pois, channels);
    red = channels[0];
    blue = channels[2];


    threshold(red, redNeg, 0, 255, THRESH_BINARY_INV);
    threshold(blue, blueNeg, 0, 255, THRESH_BINARY_INV);

    morphologyEx(redNeg, red, MORPH_ERODE, getStructuringElement(MORPH_RECT, Size(11, 11)));
    morphologyEx(blueNeg, blue, MORPH_ERODE, getStructuringElement(MORPH_RECT, Size(11, 11)));

    red = imreconstruct(red, redNeg);
    blue = imreconstruct(blue, blueNeg);

    auto t_end = std::chrono::high_resolution_clock::now();

    save_delta_time(delta_time_db(t_start, t_end));
    imwrite("poids-rouges-result.png", red);
    imwrite("poids-bleus-result.png", blue);
    imshow("poids: temps => " + delta_time(t_start, t_end), pois);
    imshow("red", red);
    imshow("blue", blue);
    
    //waitKey();
    return delta_time_db(t_start, t_end);
}

void perf_data_set_generation(int n)
{
    ofstream out("D:\\Users\\mb624\\Documents\\GitHub\\VisionApplications\\perf-image-processing.csv", ios::out | ios::app);
    if (out.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            if (i % 50 == 0)
                std::cout << "Iteration: " << i << std::endl;
            auto&& dt1 = tools();
            auto&& dt2 = balanes();
            auto&& dt3 = pois();
            out << "tools;" << (int)dt1 << ";c++" << endl
                << "balanes;" << (int)dt2 << ";c++" << endl
                << "pois;" << (int)dt3 << ";c++" << endl;

        }
    }
    out.close();
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        if (argc == 3)
            show_native = false;
        if (strcmp(argv[1], "poids") == 0)
        {
            pois();
        }
        else if (strcmp(argv[1], "tools") == 0)
        {
            tools();
        }
        else if (strcmp(argv[1], "balanes") == 0)
        {
            balanes();
        }
        
    }
    else
    {
        show_native = false;
        perf_data_set_generation(300);
    }

    return 0;
}
