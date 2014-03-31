cv-pupil-cpp
============

Pupil detection and tracking based on OpenCV library.


OpenCV installation
-------------------

Run these commands to install OpenCV: 

    $ sudo apt-get update

    $ sudo apt-get install libopencv-*


Pupil installation
------------------

Clone repo:

    $ git clone https://github.com/nvellon/cv-pupil-cpp.git

Check /tests directory for usage examples.


Changelog
---------

v0.0.5-alpha
- Add cvp::Pupil camera stream tests.
- Remove old deprecated code and trk namespace.
- Strategy pattern implementation for detection and tracking, based on cvp::Strategy interface.
- Change test to support new detection strategy pattern.

v0.0.4-alpha
- Change cvp::Eye::track() method to call detect() method.
- Change tests for trk::Eye class for image files. 
- Add test for trk::Eye class for camera stream.
- Change cvp::Eye::detect() internal variables definition.
- Add cvp::Pupil class.
- Add cvp::Pupil class tests.

v0.0.3-alpha
- Change on directory structure.
- Add namespace cvp. 
- Add cvp::Tracker interface class. 
- Add cvp::Eye class -implements cvp::Tracker- for eye detection and tracking. 
- Add cvp::Pupil class -implements cvp::Tracker- for pupil detection and tracking.
- Remove old test scripts.
- Add new test scripts for cvp::Eye class.
- Fix coding style.

v0.0.2-alpha
- Add camera pupil detection.
- Change name of function trk::detect("...") to trk::detectFile("...").
- Change on ./run to run camera detection.
- Minor changes on code style and classifier source file paths.

v0.0.1-alpha
- Eye detection function based on haar classifier.
- Pupil detection based on round contour strategy, so pupil must be completely visible.
- Pupil tracking based on template matching.
- tkr namespace.
- Dummy function for testing with photos: tkr::detect("/path/to/image") with shrinking image support.
