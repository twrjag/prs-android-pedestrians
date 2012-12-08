package org.opencv.samples.tutorial4;

import java.util.ArrayList;

import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.highgui.Highgui;
import org.opencv.imgproc.Imgproc;

import android.util.Log;

public class ImageLoader {

	public static final int NR_OF_IMAGES = 16;
	
	private ArrayList<Mat> imageMatrices;
	
	public ImageLoader() {
		imageMatrices = new ArrayList<Mat>();
		for (int i=1;i<=NR_OF_IMAGES;i++)
		{
			String imgPath = "/storage/sdcard0/prs-images/" + i + ".bmp";
			Mat m = Highgui.imread(imgPath);
			Log.d("ImageLoader","Image size for index " + i + " is (" + m.height() + "|"
					+ m.width() + ")");
			Imgproc.Canny(m, m, 70, 100);
			//Core.bitwise_not(m,m);
			m.convertTo(m, CvType.CV_32F);
			imageMatrices.add(m);
		}
	}
	
	// CALL WITH 1-BASED INDEX!!!!
	public Mat GetImageWithIndex(int index) {
		return imageMatrices.get(index-1);
	}

}
