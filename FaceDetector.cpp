// This is the OpenCV file we need to run this code
#include <opencv2/opencv.hpp>
#include <vector>

/*
"cv" so that we don't have to write it whenever 
we use a function related to OpenCV.
*/
using namespace cv;
using namespace std;

int main() {
    /*
    Will help us scale down the image/frame we're working 
    on to make the work more efficient.
    */
    double scale = 5.0;

    // This object will detect faces
    CascadeClassifier faceCascade;

    // We load the XML file that will help the faceCascade object to detect faces
    faceCascade.load("C:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");

    /*
    This object represents the use of the system's webcam. 
    The "0" means "use the 0 webcam on this system", so 
    just the one webcam we have for now.
    */
    VideoCapture cap(0);

    // If the camera isn't opened, just return a -1
    if (!cap.isOpened()) { 
        return -1;
    }//Close if 

    // Open a infinite for loop 
    for (;;) {
        /*
        This is a Matrix object, and it stores the frames
        from the webcam video feed.
        */
        Mat frame;
        cap >> frame; // This sends frames from the video feed to "frame"

        // This object will store images/frames but in grayscale
        Mat grayscale;

        /*
        This method does the actual converting to grayscale, using the "frame" 
        array as input and the "grayscale" array as output.
        */
        cvtColor(frame, grayscale, COLOR_BGR2GRAY);

        // Resizes the image/frame based on "scale", which was declared and initialized earlier
        resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

        // Vector of triangles
        vector<Rect> faces;

        // This method detects objects of different sizes in the image
        faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

        // Iterate through every "rect" 
        for (Rect area : faces) {
            // The color of the rectangle drawed around a face
            Scalar drawColor = Scalar(255, 0, 0);

            /*
            This method draws the rectangle around the face, calculating the top left 
            corner/point and the bottom right corner/point of the rectangle.
            */
            rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)), 
                Point(cvRound(((double)area.x + (double)area.width - 1) * scale), 
                    cvRound(((double)area.y + (double)area.height - 1) * scale)), drawColor);
        }//Close for

        // Opens up a window, and in this case, the webcam window
        imshow("Webcam", frame);
        char c = (char)waitKey(10);

        // If a capital/lowercase "Q" is entered, it stops the video input
        if (c == 27 || c == 'q' || c == 'Q') {
            break;
        }//Close if
    }//Close for 

    return 0;
}//Close main 