#include "Modelisation.h"

void Modelisation::cloud_cb_(const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud) {
    static unsigned count = 0;
    static double last = getTime ();
    if (++count == 30)
    {
        double now = getTime ();
        cout << "distance of center pixel :" << cloud->points [(cloud->width >> 1) * (cloud->height + 1)].z << " mm. Average framerate: " << double(count)/double(now - last) << " Hz" << endl;
        count = 0;
        last = now;
    }

    if (save)
    {
        stringstream ss;
        ss << "pointsclouddata.pcd";
        PCDWriter w;
        w.writeBinaryCompressed (ss.str (), *cloud);
        cout << "wrote point clouds to file " << ss.str () << endl;
        save=!save;
    }
}

void Modelisation::imageDepthImageCallback(const shared_ptr<openni_wrapper::Image> &, const shared_ptr<openni_wrapper::DepthImage> &d_img, float constant) {
    static unsigned count = 0;
    static double last = getTime ();
    if (++count == 30)
    {
        double now = getTime ();
        cout << "got synchronized image x depth-image with constant factor: " << constant << ". Average framerate: " << double(count)/double(now - last) << " Hz" << endl;
        cout << "Depth baseline: " << d_img->getBaseline () << " and focal length: " << d_img->getFocalLength () << endl;
        count = 0;
        last = now;
    }
}


void Modelisation::run() {
    save = false;

    // create a new grabber for OpenNI devices
    OpenNIGrabber interface;

    // Set the depth output format
    interface.getDevice ()->setDepthOutputFormat (mode);

    // make callback function from member function
    function<void (const PointCloud<PointXYZRGBA>::ConstPtr&)> f =
            bind (&Modelisation::cloud_cb_, this, _1);

    // connect callback function for desired signal. In this case its a point cloud with color values
    signals2::connection c = interface.registerCallback (f);

    // make callback function from member function
    function<void (const shared_ptr<openni_wrapper::Image>&, const shared_ptr<openni_wrapper::DepthImage>&, float constant)> f2 =
            bind (&Modelisation::imageDepthImageCallback, this, _1, _2, _3);

    // connect callback function for desired signal. In this case its a point cloud with color values
    signals2::connection c2 = interface.registerCallback (f2);

    // start receiving point clouds
    interface.start ();

    cout << "<Esc>, \'q\', \'Q\': quit the program" << endl;
    cout << "\' \': pause" << endl;
    cout << "\'s\': save" << endl;
    char key;
    do
    {
        key = static_cast<char> (getchar ());
        switch (key)
        {
        case ' ':
            if (interface.isRunning ())
                interface.stop ();
            else
                interface.start ();
        case 's':  save = !save;
        }
    } while (key != 27 && key != 'q' && key != 'Q');

    // stop the grabber
    interface.stop ();
}
