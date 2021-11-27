#include "primary.h"
using namespace cv;
#include <vector>
#include <string>
void show_images(const std :: vector<Mat> &srcImages );
void images_show_in_single_window()
{
	std::vector<std::string> imageNames;
	std ::string suffix = ".jpg";
	for (size_t i = 0; i < 15; i++)
	{
		std::cout << std::to_string(i) + suffix << std::endl;
		imageNames.push_back(imgAddr+std ::to_string(i) +suffix);
	}

	std::vector<Mat> images(imageNames.size());
	for (size_t i = 0; i < 15; i++)
	{
		std::cout << imageNames[i] << std::endl;
		images[i] = imread(imageNames[i]);
		//std::cout << images[i].size() << std ::endl;
		if (images[i].empty())
		{
			std::cout << "failed to read image..." << std::endl;
			system("pause");
			return ;
		}
	}
	
	std::cout << imageNames.size() << std::endl;
	std::cout << images.size() << std::endl;
	show_images(images);
	system("pause");
}
void show_images(const std::vector<Mat>& srcImages)
{
	int  n_images = srcImages.size(); // ͼ������
	if (n_images > 15)
	{
		std::cout << "num of images should be < 12"<< std ::endl;
		return;
	}
	int n_horizontal = 0;
	int n_vertical = 0;
	switch (n_images) 
	{
	case 1: n_horizontal = 1; n_vertical = 1; break;
	case 2: n_horizontal = 2; n_vertical = 1; break;
	case 3: n_horizontal = 3; n_vertical = 2; break;
	case 4: n_horizontal = 2; n_vertical = 2; break;
	case 5: n_horizontal = 3; n_vertical = 3; break;
	case 6: n_horizontal = 3; n_vertical = 2; break;
	case 7: n_horizontal = 3; n_vertical = 3; break;
	case 8: n_horizontal = 3; n_vertical = 3; break;
	case 9: n_horizontal = 3; n_vertical = 3; break;
	case 10:
	case 11: 
	case 12: 
	case 13: n_horizontal = 5; n_vertical = 3; break;
	case 14: n_horizontal = 5; n_vertical = 3; break;
	case 15: n_horizontal = 5; n_vertical = 3; break;
	default: n_horizontal = 4; n_vertical = 3; break;
	}

	int edge_distance = 30; // ����Ե�ľ���30
	int imageGap_distance = 20; // Сͼ����20
	int imageResize = 250; // Сͼ����250��250��
	
	const int dstHeight = imageResize * n_vertical 
		                            + ( n_vertical - 1 ) * imageGap_distance
		                             + edge_distance * 2; // 250*3+2*20+60 =850
	const int dstWidth = imageResize * n_horizontal
									+ ( n_horizontal - 1) * imageGap_distance
									+ edge_distance * 2;// 250*5+4*20+60=1390
	Mat dst(dstHeight, dstWidth, CV_8UC3, Scalar(0, 0, 0)); // (rows,cols,type)
	std::cout << " dst.size() = " << dst.size() <<"    dst.rows = "<<dst.rows<< std ::endl; 
	//  dst.size() = [1390 x 850]    dst.rows = 850

	int x = edge_distance;
	int y = edge_distance;
	std::cout << "(x,y) = " << "(" << x << "," << y << ")" << std::endl;

	int temp_x = x;
	int temp_y = y;
	Mat temp_image;
	int current_row=0, current_col=0;
	for (int i = 0; i < n_images; i++)
	{
		current_col = i % n_horizontal; // 0,1,2,3,4��
		if (current_col == 0 && (temp_x != x)) 
		{
			// �����������ֹ��1��0�ͻ��� (0,0)�������������,(1,0)(2,0)(3,0)(4,0)�ֲ�����ǰ������
			// ֱ����һ��(0,0)��ʱtemp_x���¹�,���Ա�Ϊ(0,1)->(1,1)->(2,1)->(3,1)->(4,1)
			current_row++;
			temp_x = x; // ���о͸���λ��
			temp_y += (imageResize + imageGap_distance);//�ۼ�270
		}
		
		
		const std::vector<std::string> text = { "H","o","n","e","y","I","L","o","v","e","!","Y","o","u","!" };
		// ���������ָ��dst���������,�ı�temp_image�����Զ��ı�dst
		temp_image = dst(Rect(temp_x, temp_y, imageResize, imageResize));
		resize(srcImages[i], temp_image, Size(imageResize, imageResize));
		putText(temp_image, text[i],Point(80,150),FONT_HERSHEY_COMPLEX,4,Scalar(0,0,255),3,8);
		temp_x += (imageResize + imageGap_distance);//�ۼ�215,Ҫ����ǰ�����ĺ���
		std::cout << "current_row = " << current_row
			<< "    current_col = " << current_col;
		std::cout << "    (x,y) = " << "(" << temp_x << "," << temp_y << ")" << std::endl;
		//imshow(std::to_string(i), temp_image);


	}
	namedWindow("MyBaby", WINDOW_FREERATIO);
	imshow("MyBaby",dst);
	waitKey(0);
	destroyAllWindows();
}