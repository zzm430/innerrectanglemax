#include "innerRect.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace  std;
using namespace cv;
int main()
{
    std::stringstream  ss;
    for(int i = 10; i <= 25;i++) {
        string  temp_str;
        temp_str = "0" + to_string(i);
        std::cout << temp_str << std::endl;
        cv::Mat image;

        // 创建一个黑色背景的空白图像
        Mat img(1800, 1800, CV_8UC3, Scalar(0, 0, 0));

        // 定义多边形的顶点坐标

//    vector<Point> points = {Point(0, 140), Point(49, 351), Point(620, 314), Point(662, 0), Point(0, 140)};
        vector<Point> points;
        ifstream rec_file;
        string m;
        m  = "/home/zzm/Downloads/test_middle/" + temp_str  + ".txt";
        rec_file.open(m, std::ios::in);
        string line;
        std::vector<std::vector<double>> storage_number;
        while (getline(rec_file, line)) {
            istringstream iss(line);
            double num;
            std::vector<double> temp;
            while (iss >> num) {
                temp.push_back(num);
                std::cout << num << " ";
            }
            storage_number.push_back(temp);
            std::cout << std::endl;
        }
        rec_file.close();
        for (int i = 0; i < storage_number[0].size(); i++) {
            Point temp_point;
            temp_point.x = storage_number[0][i];
            temp_point.y = storage_number[1][i];
            points.push_back(temp_point);
        }


        polylines(img, points, true, Scalar(255, 255, 255), 2);


        // 填充多边形区域
        fillPoly(img, std::vector<std::vector<Point>>{points}, Scalar(255, 255, 255));

        // 显示结果图像
        imshow("Polygon", img);
        string f;
        f = "/home/zzm/Downloads/InnerRect-main/test_middle_result/" + temp_str + ".png";
        imwrite(f, img);

        img = cv::imread(f, IMREAD_GRAYSCALE);
        InnerRect test;
        std::vector<cv::Point2f> Rect_points;
        test.getInnerRect(img, Rect_points, 4);

        if (Rect_points.size() < 4) {
            std::cout << " get InnerRect failed.." << std::endl;
            return 0;
        }

        cv::Mat InnerRect_image = img.clone();
        cv::line(InnerRect_image, Rect_points[0], Rect_points[1], cv::Scalar(127));
        cv::line(InnerRect_image, Rect_points[1], Rect_points[2], cv::Scalar(127));
        cv::line(InnerRect_image, Rect_points[2], Rect_points[3], cv::Scalar(127));
        cv::line(InnerRect_image, Rect_points[3], Rect_points[0], cv::Scalar(127));

        ofstream rec_order;
        rec_order.open("./rec_order.txt", std::ios::out);
        for (int i = 0; i < Rect_points.size(); i++) {
            rec_order << " " << Rect_points[i].x;
        }
        rec_order << std::endl;
        for (int i = 0; i < Rect_points.size(); i++) {
            rec_order << " " << Rect_points[i].y;
        }
        rec_order << std::endl;
        rec_order.close();
        string g;
        g = "/home/zzm/Downloads/InnerRect-main/test_middle_result/" + temp_str + ".png";
        cv::imwrite(g, InnerRect_image);
    }
	return 0;
}