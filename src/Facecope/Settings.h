#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>

class Settings {
public:
  Settings();

private:
  QString recognizer_samples_dir;
  QString output_dir;
  bool separate;
  double threahold;
  bool skip_recognized;
  bool cut_files;
  unsigned int steps_of_detection;
  unsigned int loader_buffer_size = 3;
};

#endif // SETTINGS_H
