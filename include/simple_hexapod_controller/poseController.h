//Controller that handles changes in body pose
#pragma once
#include "model.h"
#include "debugOutput.h"
#include "walkController.h"

//stepToPosition modes
#define NO_STEP_MODE 0
#define SIMULTANEOUS_MODE 1
#define TRIPOD_MODE 2
#define SEQUENTIAL_MODE 3

struct PoseController
{
  Model *model;
  
  Parameters params;
  
  double timeDelta;
  bool firstIteration = true;
  
  double moveToPoseTime;
  Vector3d originTipPositions[3][2];
  Vector3d midTipPositions[3][2];
  
  //Used in startup and shutdown sequences
  int sequenceStep = 1;
  Vector3d phase1TipPositions[3][2];
  Vector3d phase2TipPositions[3][2];
  Vector3d phase3TipPositions[3][2];
  Vector3d phase4TipPositions[3][2];
  Vector3d phase5TipPositions[3][2];
  Vector3d phase6TipPositions[3][2];
  Vector3d phase7TipPositions[3][2];
  Vector3d phase8TipPositions[3][2];  
  
  Pose currentPose;
  Pose targetPose;  
  
  PoseController(Model *model, Parameters params);
  bool updateStance(Vector3d targetTipPositions[3][2], 
                    Pose targetPose, 
                    double timeToPose, 
                    bool moveLegsSequentially=false);
  bool stepToPosition(Vector3d (&targetTipPositions)[3][2], 
                      int mode=NO_STEP_MODE, 
                      double stepHeight = 0.0, 
                      double stepSpeed=1.0); //USE stepSpeed = 0.5 or 1.0
  bool startUpSequence(double startHeightRatio, double stepHeight, bool forceSequentialMode);
  bool shutDownSequence(double startHeightRatio, double stepHeight, bool forceSequentialMode);
  double createSequence(WalkController walker); 
  void resetSequence(void);
  double getPitchCompensation(double phase);
  double getRollCompensation(double phase);
};