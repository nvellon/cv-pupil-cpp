cv-pupil-cpp
============

Pupil detection and tracking based on OpenCV library.


OpenCV installation
-------------------

Run these commands to install OpenCV: 

    $ sudo apt-get update

    $ sudo apt-get install libopencv-*


Pupil installation and run
--------------------------

Clone repo:

    $ git clone https://github.com/nvellon/cv-pupil-cpp.git

Granting permissions:

    $ cd cv-pupil-cpp
    $ chmod +x run

Run (g++ compilation and execution):

    $ ./run

Changelog
---------

v0.0.1-alpha
- Eye detection function based on haar classifier.
- Pupil detection based on round contour strategy, so pupil must be completely visible.
- Pupil tracking based on template matching.
- tkr namespace.
- Dummy function for testing with photos: tkr::detect("/path/to/image") with shrinking image support.
