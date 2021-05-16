#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace std;
using namespace cv;


// img: input 3 channels image
// roi : polygon represents by points
// color: transparent base color
// alpha1: transparent ratio image1
// alpha2: transparent ratio image2
// out:   out image with transparent area
Mat SetTransparentColor(cv::Mat &img, vector<vector<cv::Point> > &roi, cv::Scalar color, double alpha1, double alpha2) {
  Mat out;
  cv::Mat layer = cv::Mat::zeros(img.size(), CV_8UC3);
  cv::fillPoly(layer, roi, color);
  cv::addWeighted(img, alpha1, layer, alpha2, 0, out);
  return out;
}

Mat SetTransparentColor(cv::Mat &img, vector<vector<cv::Point> > &roi, vector<cv::Scalar> color, double alpha1, double alpha2) {
  Mat out;
  cv::Mat layer = cv::Mat::zeros(img.size(), CV_8UC3);
  for (unsigned int i=0; i<roi.size(); i++){
    cv::fillPoly(layer, roi[i], color[i]);
  }
  cv::addWeighted(img, alpha1, layer, alpha2, 0, out);
  return out;
}


vector<int> ComputeScaledDef(vector<float> vf, int scalerange){
    float vfmin = 0.0;
    float vfmax = 0.0;

    for (unsigned int i=0; i<vf.size(); i++){
        if (i==0){
            vfmin = vf[i];
            vfmax = vf[i];
        }
        else{
            if (vf[i]<vfmin)
                vfmin = vf[i];
            else if (vf[i]>vfmax)
                vfmax = vf[i];
        }
    }

    if (vfmin < 0){
        for (unsigned int i=0; i<vf.size(); i++)
            vf[i] -= vfmin;
        vfmax -= vfmin;
        vfmin = 0.0;
    }

    float vfrange = vfmax - vfmin;
    vector<int> vsf;
    for (unsigned int i=0;i<vf.size(); i++){
        int vsfi = scalerange*vf[i]/vfrange;
        vsf.push_back(vsfi);
    }

    return vsf;
}


cv::Scalar SetColor(float floatValue){

    int cRed = floatValue * 255;
    int cBlue = 255 - floatValue * 255;
    int cGreen = 0;

    if (floatValue>0 && floatValue<= 0.5)
       cGreen = floatValue * 512; // Since I guess you want it to be maxed out at 128.
    else if (floatValue > 0.5 && floatValue <= 1)
       cGreen = 255 - (floatValue - 0.5)*512;
    else {
       cout << "floatValue has a value smaller than 0 or bigger than 1!";
       return -1;
    }

    cv::Scalar output = cv::Scalar(cBlue,cGreen,cRed);
    return output;
}



int main()
{
    cout << "Hello world!" << endl;


    vector<float> vf;

    vf.push_back(1.0);
    vf.push_back(2.0);
    vf.push_back(0.5);
    vf.push_back(0.1);
    vf.push_back(5.0);
    vf.push_back(5.9);
    vf.push_back(2.6);
    vf.push_back(2.1);
    vf.push_back(-0.1);



    vector<int> otp = ComputeScaledDef(vf,256);
    for (unsigned int i=0; i<otp.size(); i++){
        cout << vf[i] << "\t" << otp[i] << endl;
    }

    float vfi2 = 0.0;
    for (unsigned int i=0; i<3; i++)
        vfi2 += i*i;
    float vf2 = sqrt(vfi2);
    cout << "sqrt " << vf2 << endl;


    string img_path = "1.png";
    Mat img = imread(img_path,IMREAD_COLOR);
    resize(img,img,Size(),0.5,0.5);

    vector<vector<Point> > roi;
    vector<Point> roii;

    roii.push_back(Point(0,0));
    roii.push_back(Point(100,0));
    roii.push_back(Point(100,100));
    roi.push_back(roii);
    roii.clear();
    roii.push_back(Point(100,0));
    roii.push_back(Point(200,0));
    roii.push_back(Point(200,100));
    roi.push_back(roii);
    roii.clear();
    roii.push_back(Point(200,0));
    roii.push_back(Point(300,0));
    roii.push_back(Point(300,100));
    roi.push_back(roii);
    roii.clear();
    roii.push_back(Point(300,0));
    roii.push_back(Point(400,0));
    roii.push_back(Point(400,100));
    roi.push_back(roii);
    roii.clear();
    roii.push_back(Point(400,0));
    roii.push_back(Point(500,0));
    roii.push_back(Point(500,100));
    roi.push_back(roii);
    roii.clear();
    roii.push_back(Point(500,0));
    roii.push_back(Point(600,0));
    roii.push_back(Point(600,100));
    roi.push_back(roii);
    roii.clear();
    roii.push_back(Point(600,0));
    roii.push_back(Point(700,0));
    roii.push_back(Point(700,100));
    roi.push_back(roii);
    roii.clear();
    roii.push_back(Point(700,0));
    roii.push_back(Point(800,0));
    roii.push_back(Point(800,100));
    roi.push_back(roii);
    roii.clear();
    roii.push_back(Point(800,0));
    roii.push_back(Point(900,0));
    roii.push_back(Point(900,100));
    roi.push_back(roii);
    roii.clear();
    roii.push_back(Point(900,0));
    roii.push_back(Point(1000,0));
    roii.push_back(Point(1000,100));
    roi.push_back(roii);
    roii.clear();
    roii.push_back(Point(1000,0));
    roii.push_back(Point(1100,0));
    roii.push_back(Point(1100,100));
    roi.push_back(roii);
    roii.clear();

    vector<cv::Scalar> colors;
    colors.push_back(SetColor(0.0));
    colors.push_back(SetColor(0.1));
    colors.push_back(SetColor(0.2));
    colors.push_back(SetColor(0.3));
    colors.push_back(SetColor(0.4));
    colors.push_back(SetColor(0.5));
    colors.push_back(SetColor(0.6));
    colors.push_back(SetColor(0.7));
    colors.push_back(SetColor(0.8));
    colors.push_back(SetColor(0.9));
    colors.push_back(SetColor(1.0));


    //Mat out = SetTransparentColor(img, roi, Scalar(0,255,0,50), 1.0, 0.2);
    Mat out = SetTransparentColor(img, roi, colors, 1.0, 0.5);

    imshow("Window1",out);


    waitKey(0);
    return 0;
}


