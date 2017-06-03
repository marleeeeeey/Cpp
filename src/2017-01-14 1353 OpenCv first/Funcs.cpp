#include "Funcs.h"

void recogniseStickersByThreshold(cv::Mat image, std::vector<cv::Mat> &stickers)
{
    enum
    {
        key_light = 100,
        key_sat = 100,
        key_hue = 100,
    };

    cv::Mat image_hsv;
    std::vector< std::vector<cv::Point> > contours;
    cv::cvtColor(image, image_hsv, cv::COLOR_BGR2HSV); // Преобразуем в hsv
    cv::Mat tmp_img(image.size(), CV_8U);
    // Выделение подходящих по цвету областей. Цвет задается константой :)
    cv::inRange(image_hsv, cv::Scalar(key_light - 2, key_sat - 20, key_hue - 35),
        cv::Scalar(key_light + 2, key_sat + 20, key_hue + 35), tmp_img);
    // "Замазать" огрехи в при выделении по цвету
    cv::dilate(tmp_img, tmp_img, cv::Mat(), cv::Point(-1, -1), 3);
    cv::erode(tmp_img, tmp_img, cv::Mat(), cv::Point(-1, -1), 1);
    //Выделение непрерывных областей
    cv::findContours(tmp_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (uint i = 0; i < contours.size(); i++) {
        cv::Mat sticker;
        //Для каждой области определяем ограничивающий прямоугольник
        cv::Rect rect = cv::boundingRect(contours[i]);
        image(rect).copyTo(sticker);
        stickers.push_back(sticker); //Добавить к массиву распознанных стикеров
    }
}

void transparenRect(cv::Mat image, int x, int y, int w, int h, cv::Scalar clr)
{
    cv::Mat roi = image(cv::Rect(x, y, w, h));
    cv::Mat color(roi.size(), CV_8UC3, clr);
    double alpha = 0.3;
    cv::addWeighted(color, alpha, roi, 1.0 - alpha, 0.0, roi);
}

int readVideoFromCamera()
{
    using namespace cv;

    VideoCapture cap(0); // Открываем камеру или файл
    if (!cap.isOpened()) // check if we succeeded
        return -1;
    Mat edges;
    namedWindow("edges", 1);
    while (1) 
    {
        Mat frame;
        cap >> frame;                                     // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);           // Перевод в градации серого
        GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5); // Размытие
        Canny(edges, edges, 0, 30, 3);                    // Выделение границ
        imshow("edges", edges);
        if (waitKey(30) >= 0) break;
    }

    return 0;
}

int readVideoFromFile()
{
    using namespace cv;

    VideoCapture & cap = ones().videoCapture();           

    //cap.set(CV_CAP_PROP_POS_MSEC, 300);       //start the video at 300ms

    double fps = cap.get(CV_CAP_PROP_FPS);      //get the frames per seconds of the video
    std::cout << "Frame per seconds : " 
        << fps << std::endl;
    namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
    while (true) 
    {
        Mat frame;
        bool bSuccess = cap.read(frame);        // read a new frame from video
        if (!bSuccess) 
        {
            std::cout 
                << "Cannot read the frame from video file" 
                << std::endl;
            break;
        }
        imshow("MyVideo", frame);               //show the frame in "MyVideo" window

        enum { escKey = 27 };
        if (waitKey(30) == escKey)
            break;
    }

    return 0;
}

int useFilterCanny()
{
    using namespace cv;

    double thresh = 1000; // try different values to see effect

    imshow("inp image", ones().inpImage());

    Mat imgContours;
    //Canny(ones().inpImage(), imgContours, 0.4*thresh, thresh);
    Canny(ones().inpImage(), imgContours, 10, 100, 3);
    imshow("countur image", ones().inpImage());

    Mat gray_image;
    Mat edge, draw;
    cvtColor(ones().inpImage(), gray_image, COLOR_BGR2GRAY);
    Canny(gray_image, edge, 50, 150, 3);
    //resize(edge, edge, cv::Size(800, 600));
    imshow("Canny", edge);

    return 0;
}

int useLSD()
{
    using namespace cv;
    
    VideoCapture & cap = ones().videoCapture();

    Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);
    while (1) 
    {
        Mat frame;
        std::vector<Vec4f> lines_std;
        bool bSuccess = cap.read(frame); // read a new frame from video
        if (!bSuccess) 
        {
            std::cout << "Cannot read the frame from video file" << std::endl;
            break;
        }

        Mat gray_image;
        cvtColor(frame, gray_image, COLOR_BGR2GRAY);
        ls->detect(gray_image, lines_std); // Detect the lines
        ls->drawSegments(frame, lines_std);
        cv::resize(frame, frame, cv::Size(800, 600));
        imshow("MyVideo", frame); //show the frame in "MyVideo" window

        enum { escKey = 27 };
        if (waitKey(30) == escKey)
            break;
    }
    

    return 0;
}

int useHistogramm()
{
    using namespace cv;

    Mat gray = imread("image.jpg", 0);
    namedWindow("Gray", 1); imshow("Gray", gray);
    int histSize = 256; // bin size
    float range[] = { 0, 255 };
    const float *ranges[] = { range };
    MatND hist;
    calcHist(&gray, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false); // Calculate histogram
    double total;
    total = gray.rows * gray.cols;

    for (int h = 0; h < histSize; h++) { // Show the calculated histogram in command window
        float binVal = hist.at<float>(h);
        cout << " " << binVal;
    }

    // Plot the histogram
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    for (int i = 1; i < histSize; i++) {
        line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
            Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
            Scalar(255, 0, 0), 2, 8, 0);
    }
    namedWindow("Result", 1); imshow("Result", histImage);
    waitKey(0);

    return 0;
}

int useSIFT()
{
//     using namespace cv;
// 
//     // Создать SIFT детектор
//     cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
//     //cv::Ptr<Feature2D> f2d = xfeatures2d::SURF::create();
//     //cv::Ptr<Feature2D> f2d = ORB::create();
//     // Сравниваем кадр из потока с образцом
//     
//     
//     //-- Step 1: Detect the keypoints:
//     std::vector<KeyPoint> keypoints_1, keypoints_2;
//     f2d->detect(frame, keypoints_1);          // Найдем характеристические точки для фрейма
//     f2d->detect(img_templete, keypoints_2);   // Найдем характеристические точки для фрейма
//                                               // (можно сделать заранее)
// 
// 
//     //-- Step 2: Вычислить описатели (feature vectors)
//         Mat descriptors_1, descriptors_2;
//     f2d->compute(img_1, keypoints_1, descriptors_1);
//     f2d->compute(img_2, keypoints_2, descriptors_2);
//     
//     
//     //-- Step 3: Сопоставить вектора описателей при помощи BFMatcher :
//     BFMatcher matcher;
//     std::vector< DMatch > matches;
//     matcher.match(descriptors_1, descriptors_2, matches);

    return 0;
}

int useSURF()
{
//     using namespace cv;
// 
//     vector<KeyPoint> keypoints_object, keypoints_scene; // keypoints
//     Mat descriptors_object, descriptors_scene; // descriptors (features)
//                                                //-- Steps 1 + 2, detect the keypoints and compute descriptors, both in one method
//     Ptr<SURF> surf = SURF::create(minHessian);
//     surf->detectAndCompute(img_object, noArray(), keypoints_object, descriptors_object);
//     surf->detectAndCompute(img_scene, noArray(), keypoints_scene, descriptors_scene);
//     //-- Step 3: Matching descriptor vectors using FLANN matcher
//     FlannBasedMatcher matcher; // FLANN - Fast Library for Approximate Nearest Neighbors
//     vector< vector< DMatch> > matches;
//     matcher.knnMatch(descriptors_object, descriptors_scene, matches, 2); // find the best 2 matches of each
//     descriptor
//         timer.Stop(); printf("Method processImage() ran in: %f msecs.\n", timer.Elapsed());
//     //-- Step 4: Select only goot matches
//     std::vector< DMatch > good_matches;
//     for (int k = 0; k < std::min(descriptors_scene.rows - 1, (int)matches.size()); k++) {
//         if ((matches[k][0].distance < 0.6*(matches[k][1].distance)) && ((int)matches[k].size() <= 2 &&
//             (int)matches[k].size()>0)) {
//             // take the first result only if its distance is smaller than 0.6*second_best_dist
//             // that means this descriptor is ignored if the second distance is bigger or of similar
//             good_matches.push_back(matches[k][0]);
//         }

    return 0;
}
