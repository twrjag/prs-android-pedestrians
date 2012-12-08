#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

using namespace std;
using namespace cv;

extern "C" {
JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial4_Sample4Mixed_FindFeatures(JNIEnv*, jobject, jlong addrGray, jlong addrRgba)
{
    Mat* pMatGr=(Mat*)addrGray;
    Mat* pMatRgb=(Mat*)addrRgba;
    vector<KeyPoint> v;

    FastFeatureDetector detector(50);
    detector.detect(*pMatGr, v);
    for( size_t i = 0; i < v.size(); i++ )
        circle(*pMatRgb, Point(v[i].pt.x, v[i].pt.y), 10, Scalar(255,0,0,255));
}

JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial4_Sample4Mixed_DetectMatch(JNIEnv*, jobject, jlong addrSource, jlong addrTempl, jlong addrDst, jdouble imax, jdouble jmax)
{
	int delta = 3;

	Mat* pMatSrc=(Mat*)addrSource;
	Mat* pMatTempl=(Mat*)addrTempl;
	Mat* pMatDst=(Mat *)addrDst;

	Mat resultCanny;
	Mat resultDt;
	Mat resultDilate;

	cv::Canny(*pMatSrc,resultCanny,70,100);
	//cv::bitwise_not(resultCanny,resultCanny);

	resultCanny.convertTo(resultCanny,CV_8UC1);

	Mat element = cv::getStructuringElement(cv::MORPH_CROSS,cv::Size(5,5),cv::Point(2,2));

	distanceTransform(resultCanny,resultDt,CV_DIST_L2,5);

//	cv::dilate(resultDt,resultDilate,element,cv::Point(-1,-1),delta,BORDER_DEFAULT,morphologyDefaultBorderValue());

/*	Mat result;

	pMatTempl->convertTo(*pMatTempl,CV_32F);

	int cols = resultDt.cols - pMatTempl->cols + 1;
	int rows = resultDt.rows - pMatTempl->rows + 1;

	result.create(cols,rows,CV_32F);

	//cv::matchTemplate(resultDt,*pMatTempl,result,CV_TM_CCOEFF_NORMED);

	double min;
	double max;
	Point minLoc;
	Point maxLoc;

	cv::minMaxLoc(result,&min,&max,&minLoc,&maxLoc,cv::Mat());

	imax = minLoc.x;
	jmax = minLoc.y;
*/
	// todo make comparisons here
	vector<vector<Point> > results;
	vector<float> costs;

	resultCanny.convertTo(resultCanny,CV_GRAY2BGR);
	pMatTempl->convertTo(*pMatTempl,CV_GRAY2BGR);

	int best = CV_EXPORTS_W::chamerMatching(resultCanny,*pMatTempl,results, costs);

	imax = best;

	resultCanny.copyTo(*pMatDst);
	//pMatTempl->copyTo(pMatDst->colRange(0,pMatTempl->cols).rowRange(0,pMatTempl->rows));
}

}
