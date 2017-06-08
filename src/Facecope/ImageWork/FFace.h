#ifndef FPERSON_H
#define FPERSON_H
#include <FacecopeTypes.h>
#include <opencv2/imgproc.hpp>

class FFace {
  int rotation;
  int original_rotation;
  cv::Rect face_frame;
  cv::Rect original_frame;

  long face_area_id;
  Eye eye_left;
  Eye eye_rigth;

  Human info;

  bool is_normalized;

private:
  void set_face_frame(const cv::Rect &frame);
  void normalize();

public:
  FFace(int angle, const cv::Rect &face_area_frame, const cv::Rect &eye_1,
        const cv::Rect &eye_2, long ID = -1);
  ~FFace();

  int get_rotation();
  cv::Rect &get_face_frame();
  cv::Rect &get_original_frame();
  long get_ID();
  Human &get_info();
  Eye &get_left_eye(bool normalized);
  Eye &get_rigth_eye(bool normalized);
  int get_rotation_original();

  void set_rotation(int angle);
  void set_original_frame(const cv::Rect &frame);
  void set_ID(long ID);
  void set_left_eye(const cv::Rect &frame_eye);
  void set_rigth_eye(const cv::Rect &frame_eye);
  void set_info(const Human &human);
};

#endif // FPERSON_H
