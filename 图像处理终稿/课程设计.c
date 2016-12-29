#include <stdio.h>
#include <cv.h>
#include <highgui.h>

IplImage *img = 0;  //����ͼ��
int height,width,step,channels,depth;
int i,j,k;
uchar *data;
//���庯��
void loadimg();//����ͼ������ʾͼ����Ϣ
void slco();//ѡ��ͼ�����
void saveimg();//����ͼ��
void toGrayimg();//ת���Ҷ�ͼ��
void roGimg();//��ת�Ҷ�ͼ��
void roRGBimg();//��ת��ɫͼ��
void rollGimg();//��ת�Ҷ�ͼ��
void rollRGBimg();//��ת��ɫͼ��
void seltype();//ѡ��Ҷ�ͼƬ��������
void seltype1();//ѡ���ɫͼƬ��������
void rollkd1(IplImage *src);//ˮƽ����
void rollkd2(IplImage *src);//��ֱ����
int main()
{
	printf("  ����ͼ����\n   ���α任 1\nBy ��Ժ152 ��쿳�\n\n");
	loadimg();
	return 0;
}
void loadimg()//����ͼ������ʾͼ����Ϣ,�ṩ����ѡ��
{
	img=cvLoadImage("input.png");
	if(!img)
		{
		    printf("�޷����ر�Ŀ¼����ͼƬ: %s\n��"
             "���ͼƬ����Ϊ\"input.png\"���ڱ�Ŀ¼��","input.png");
            getchar();
		}
    else
    {
        height    = img->height;//ͼƬ����
        width     = img->width;
        step      = img->widthStep;
        channels  = img->nChannels;
        depth     = img->depth;
        data      = (uchar *)img->imageData;
        printf("�������ڴ���һ���ߴ�Ϊ%dx%d��%dͨ��%dλͼ��\n",height,width,depth,channels);
        cvNamedWindow("ԭͼ",CV_WINDOW_AUTOSIZE);//��������
        cvShowImage("ԭͼ",img);
        cvWaitKey(0);
        cvDestroyWindow("ԭͼ");
        slco();
    }
}
void slco()
{
    int n;
    printf("��ѡ����Ҫ���еĲ���\n"
		"0------�˳�����\n"
		"1------��ͼ��ת���ɻҶ�ͼ��\n"
		"2------�ѻҶ�ͼ����ת����Ƕ�\n"
		"3------�Ѳ�ɫͼ����ת����Ƕ�\n"
		"4------����任�Ҷ�ͼƬ\n"
		"5------����任��ɫͼƬ\n");

    scanf("%d",&n);
    switch(n)
    {

        case 0:
            break;

        case 1:
            toGrayimg();
            break;

        case 2:
            roGimg();
            break;

        case 3:
            roRGBimg();
            break;

        case 4:
            seltype();
            break;

        case 5:
            seltype1();
            break;
    }
}

void saveimg(IplImage *src)//����ͼ��
{
    cvSaveImage("out.bmp",src);
	if(!cvSaveImage("out.bmp",src))
		printf("Could not save: %s\n","output.bmp");
	else
		printf("ͼ���Ѿ�����Ϊ%s��\n","output.bmp");
    cvNamedWindow("ת����",CV_WINDOW_AUTOSIZE);//��������
    cvShowImage("ת����",src);
    cvWaitKey(0);
    cvDestroyWindow("ת����");
    slco();
}

void toGrayimg()//ת���Ҷ�ͼ��
{
    IplImage *result=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);//ʹ�ÿ�ת��ͼ��ռ�
    cvCvtColor(img,result,CV_RGB2GRAY);
    saveimg(result);
}

void roGimg()
{
    IplImage *result=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
    IplImage *res=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
    cvCvtColor(img,result,CV_RGB2GRAY);
    double angle;
    printf("������Ҫ��ת�ĽǶ�: ");
    scanf("%lf", &angle);
    float m[6];
    CvMat rotMat = cvMat(2, 3, CV_32F, m);
    CvPoint2D32f center;
    center.x = (float) (result->width / 2.0 + 0.5);
    center.y = (float) (result->height / 2.0 + 0.5);
    cv2DRotationMatrix(center, -angle, 1, &rotMat);
    cvWarpAffine(result,res, &rotMat, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
    //ͼ�����任����
    saveimg(res);
}

void roRGBimg()
{
    double angle;
    printf("������Ҫ��ת�ĽǶ�: ");
    scanf("%lf", &angle);
    float m[6];
    CvMat rotMat = cvMat(2, 3, CV_32F, m);
    CvPoint2D32f center;
    center.x = (float) (img->width / 2.0 + 0.5);
    center.y = (float) (img->height / 2.0 + 0.5);//�����ά��ת�ķ���任����
    cv2DRotationMatrix(center, -angle, 1, &rotMat);
    IplImage *result = cvCreateImage(cvGetSize(img),8,3);
    cvWarpAffine(img, result, &rotMat, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
    //ͼ�����任����
    saveimg(result);
}

void seltype()
{
    IplImage *result=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
    cvCvtColor(img,result,CV_RGB2GRAY);
    int q;
    printf("��ѡ��������"
		"0------ˮƽ����\n"
		"1------��ֱ����\n");
    scanf("%d",&q);
    switch(q)
    {
        case 0:
            rollkd1(result);

        case 1:
            rollkd2(result);
    }
}

void seltype1()
{
    IplImage *result=img;
    int q;
    printf("��ѡ��������"
		"0------ˮƽ����\n"
		"1------��ֱ����\n");
    scanf("%d",&q);
    switch(q)
    {
        case 0:
            rollkd1(result);

        case 1:
            rollkd2(result);
    }
}

void rollkd1(IplImage *src)//ˮƽ����
{
    float m[6] = {-1.0f, 0, (float) src->width,
                  0, 10f, 0};//�����任����
    CvMat fliper = cvMat(2, 3, CV_32F, m);//����Mat
    IplImage *result = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);//�ֳ��ж�λ���ͨ���������
    cvWarpAffine(src, result, &fliper, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
    saveimg(result);
}

void rollkd2(IplImage *src)//��ֱ����
{
    float m[6] = {1.0f, 0, 0,
                  0, -1.0f, (float) src->height};
    CvMat fliper = cvMat(2, 3, CV_32F, m);
    IplImage *result = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    cvWarpAffine(src, result, &fliper, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
    saveimg(result);
}


