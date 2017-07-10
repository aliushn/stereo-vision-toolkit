/*
* Copyright I3D Robotics Ltd, 2017
* Author: Josh Veitch-Michaelis
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtAwesome.h>
#include <QDebug>
#include <QDir>
#include <QDomDocument>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QSpacerItem>
#include <QTimer>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

// Visualization Toolkit (VTK)
#include <QVTKWidget.h>
#include <vtkRenderWindow.h>

#include "matcherwidgetopencvblock.h"
#include "matcherwidgetopencvsgbm.h"
#include "stereocameradeimos.h"
#include "stereocamerafromvideo.h"
#include "stereocameraopencv.h"

#include <disparityviewer.h>
#include "calibratefromimagesdialog.h"
#include "calibrationdialog.h"
#include "stereocalibrate.h"

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

 private:
  Ui::MainWindow* ui;

  QPixmap pmap_left;
  QFile* paramFile;
  QPixmap pmap_right;
  QPixmap pmap_disparity;
  QTimer* statusBarTimer;

  QLabel* frame_counter;
  QLabel* fps_counter;
  QSpacerItem* status_bar_spacer;
  QWidget* status_widget;
  QVariantMap icon_options;
  QtAwesome* awesome;
  DisparityViewer* disparityView;

  bool cameras_connected = false;

  AbstractStereoCamera* stereo_cam;
  StereoCalibrate* calibrator;

  QList<MatcherWidget*> matcher_list;

  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;

  CalibrationDialog* calDialog;
  CalibrateFromImagesDialog* calImDialog;

  QString calibrationDir = "";
  QString saveDir = "";

  unsigned int red;
  unsigned int green;
  unsigned int blue;
  QVTKWidget* vtk_widget;

  void setupMatchers();
  void statusBarInit();
  void controlsInit();
  void pointCloudInit();

  void stereoCameraRelease(void);
  void stereoCameraInit(void);

  void stereoCameraInitConnections(void);

 public slots:
  void updateDisplay(void);
  void updateFPS(qint64);
  void updateFrameCount(qint64);
  void toggleAcquire(void);
  void singleShotClicked(void);
  void saveSingle(void);
  void displaySaved(QString fname);
  void statusMessageTimeout(void);
  void setMatcher(int matcher);

  void stereoCameraLoad(void);
  void autoloadCameraTriggered();
  void videoStreamLoad(void);

  void setSaveDirectory(void);
  void setCalibrationFolder(void);

  void startCalibration(void);
  void doneCalibration(bool);

  void startCalibrationFromImages(void);

  void checkParamFile(void);
  void loadParamFile(void);
  void updateParamFile(QString tag, QString value);
  QString getParamFromFile(QString tagName);
  void updatePreviousDirectory(QString dir);

  void startVideoCapture(void);
  void stopVideoCapture(void);

  void updateCloud(void);
  void enable3DViz(int);
  void resetPointCloudView(void);
};

#endif  // MAINWINDOW_H