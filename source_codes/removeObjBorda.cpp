#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int nobjects,nobjectsborder,nobjectsholes;
  
  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;

	//busca por objetos nas bordas superior e inferior	
	nobjectsborder=0;
	for (int i=0;i<height;i=i+height-1){
		for(int j=0;j<width;j++){
			if (image.at<uchar>(i,j) == 255){
				nobjectsborder++;
				p.x=j;
				p.y=i;
				floodFill(image,p,0);
			}
		}	
	}

	//busca por objetos nas bordas laterais
	for (int i=0;i<height;i++){
		for(int j=0;j<width;j=j + width -1){
			if (image.at<uchar>(i,j) == 255){
				nobjectsborder++;
				p.x=j;
				p.y=i;
				floodFill(image,p,0);
			}
		}	
	}
	

  imshow("image", image);
  imwrite("labeling.png", image);
  waitKey();
  return 0;
}
