#ifndef CVSUPPORT_H
#define CVSUPPORT_H

#include <opencv2/opencv.hpp>

//!  CV Support
/*!
  Support class for using openCV
*/
class CVSupport
{
public:
    //! Wrapper around cv::imwrite for saving in parallel
    /*!
    * Saves an image, can also be called sequentially.
    *
    * @param[in] fname Output filename
    * @param[in] src Image matrix
    *
    * @return True/false if the write was successful
    */
    static bool write_parallel(std::string fname, cv::Mat src)
    {
        std::vector<int> params;
        int compression_level = 9;
        params.push_back(cv::IMWRITE_PNG_COMPRESSION);
        params.push_back(compression_level);

        return cv::imwrite(fname, src, params);
    }
};

#endif // CVSUPPORT_H
