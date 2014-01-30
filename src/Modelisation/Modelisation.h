/**
 *
 *
 */
#include "../Main.h"

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/common/time.h>
#include <pcl/console/parse.h>

using namespace pcl;
using namespace boost;

class Modelisation {
public :
    bool save;
    openni_wrapper::OpenNIDevice::DepthMode mode;
    Modelisation(openni_wrapper::OpenNIDevice::DepthMode depth_mode = openni_wrapper::OpenNIDevice::OpenNI_12_bit_depth) : mode (depth_mode) {}
    void cloud_cb_ (const PointCloud<PointXYZRGBA>::ConstPtr &cloud);
    void imageDepthImageCallback (const shared_ptr<openni_wrapper::Image>&, const shared_ptr<openni_wrapper::DepthImage>& d_img, float constant);
    void run ();
};
