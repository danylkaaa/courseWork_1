//
// Created by zulus on 20.04.17.
//

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
int main(int argc, char **argv) {
    // задаём высоту и ширину картинки
    int height = 620;
    int width = 440;
    // задаём точку для вывода текста
    CvPoint pt = cvPoint(height / 4, width / 2);
    // Создаёи 8-битную, 3-канальную картинку
    IplImage *hw = cvCreateImage(cvSize(height, width), 8, 3);
    // заливаем картинку чёрным цветом
    cvSet(hw, cvScalar(0, 0, 0));
    // инициализация шрифта
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1.0, 1.0, 0, 1, CV_AA);
    // используя шрифт выводим на картинку текст
    cvPutText(hw, "Hello world", pt, &font, CV_RGB(0, 0, 150));

    // создаём окошко
    cvNamedWindow("Hello World", 0);
    // показываем картинку в созданном окне
    cvShowImage("Hello World", hw);
    // ждём нажатия клавиши
    while (true) {
        char c = cvWaitKey(33);
        if (c == 27) { // если нажата ESC - выходим
            break;
        } else {
            cvPutText(hw, "Hello world", pt, &font, CV_RGB(rand()%c, rand()%c, rand()%c));
            cvShowImage("Hello World", hw);
        }
    }
    // освобождаем ресурсы
    cvReleaseImage(&hw);
    cvDestroyWindow("Hello World");
    return 0;
}