//
// пример работы оператора Лапласа - cvLaplace()
//
// robocraft.ru
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* dst = 0;
IplImage* dst2 = 0;

int main(int argc, char* argv[])
{
    // имя картинки задаётся первым параметром
    char* filename =(char*) (argc >= 2 ? argv[1] : "Image0.jpg");
    // получаем картинку
    image = cvLoadImage(filename, 1);
    // создаём картинки
    dst = cvCreateImage( cvGetSize(image), IPL_DEPTH_16S, image->nChannels);
    dst2 = cvCreateImage( cvGetSize(image), image->depth, image->nChannels);

    printf("[i] image: %s\n", filename);
    assert( image != 0 );

    // окно для отображения картинки
    cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("cvLaplace", CV_WINDOW_AUTOSIZE);

    int aperture = argc == 3 ? atoi(argv[2]) : 3;

    // применяем оператор Лапласа
    cvLaplace(image, dst, aperture);

    // преобразуем изображение к 8-битному
    cvConvertScale(dst, dst2);

    // показываем картинку
    cvShowImage("original", image);
    cvShowImage("cvLaplace", dst2);

    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseImage(& image);
    cvReleaseImage(&dst);
    cvReleaseImage(&dst2);
    // удаляем окна
    cvDestroyAllWindows();
    return 0;
}