/**
 *
 *
 */
#include "Tracking.h"
#include "../Calibration/Calibration.h"

UserGenerator user;

XnBool isNeedingPose = FALSE;
XnChar pose[20] = "";

#define MAX_USERS 1

/** Called when a new user is detected */
void XN_CALLBACK_TYPE userDetected(UserGenerator&, XnUserID id, void*)
{
    cout << "User " << id << " detected." << endl;
    if (isNeedingPose)
        user.GetPoseDetectionCap().StartPoseDetection(pose, id);
    else
        user.GetSkeletonCap().RequestCalibration(id, TRUE);
}

/** Called when a user is losted */
void XN_CALLBACK_TYPE userLosted(UserGenerator&, XnUserID id, void*)
{
    cout << "User " << id << " losted." << endl;
}

/** Called when a user calibration pose is detected */
void XN_CALLBACK_TYPE calibrationPoseDetected(PoseDetectionCapability&, const XnChar* strPose, XnUserID id, void*)
{
    cout << "Pose " << strPose << " detected for user " << id  << "." << endl;
    user.GetPoseDetectionCap().StopPoseDetection(id);
    user.GetSkeletonCap().RequestCalibration(id, TRUE);
}

/** Called when a user is going to be calibrated */
void XN_CALLBACK_TYPE userCalibrationStarted(SkeletonCapability&, XnUserID id, void*)
{
    cout << "Calibration started for user " << id  << ". Don't move !" << endl;
}

/** Called to confirm that a user is tracked */
void XN_CALLBACK_TYPE userCalibrationFinished(SkeletonCapability&, XnUserID id, XnCalibrationStatus eStatus, void*)
{
    if (eStatus == XN_CALIBRATION_STATUS_OK)
    {
        cout << "Calibration finished, start tracking user "<< id << "." << endl;
        user.GetSkeletonCap().StartTracking(id);
    }
    else
    {
        cout << "Calibration failed for user "<< id << "." << endl;
        if (isNeedingPose)
            user.GetPoseDetectionCap().StartPoseDetection(pose, id);
        else
            user.GetSkeletonCap().RequestCalibration(id, TRUE);
    }
}

Tracking::Tracking() {}

void Tracking::setupTracking()
{
    Calibration c;
    c.launchCalibration();
    c.context.FindExistingNode(XN_NODE_TYPE_USER, user);
    user.Create(c.context);

    // Used for calling different functions depending of the user action.
    XnCallbackHandle userDetection, calibrationStart, calibrationComplete, poseDetected;
    user.RegisterUserCallbacks(userDetected, userLosted, NULL, userDetection);
    user.GetSkeletonCap().RegisterToCalibrationStart(userCalibrationStarted, NULL, calibrationStart);
    user.GetSkeletonCap().RegisterToCalibrationComplete(userCalibrationFinished, NULL, calibrationComplete);
    user.GetPoseDetectionCap().RegisterToPoseDetected(calibrationPoseDetected, NULL, poseDetected);
    user.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

    c.context.StartGeneratingAll();

    XnUserID users[MAX_USERS];
    XnUInt16 nUsers;
    XnSkeletonJointTransformation head;

    cout << "Waiting for user." << endl;


    // Main loop for users detection, calibration and tracking.
    while (!xnOSWasKeyboardHit())
    {
        // TODO : Send the user pixels to the display function.
        c.calibrationDisplay();
        c.context.WaitOneUpdateAll(user);
        nUsers=MAX_USERS;
        user.GetUsers(users, nUsers);
        if(user.GetSkeletonCap().IsTracking(users[0])==FALSE)
            continue;

        user.GetSkeletonCap().GetSkeletonJoint(users[0],XN_SKEL_HEAD,head);

        /*cout << "User head at (" << -head.position.position.X << ","
             << head.position.position.Y+1350 << ","
             << head.position.position.Z << ")" << endl;*/

        X = -head.position.position.X;
        Y = head.position.position.Y+1350;
        Z = -(5700-head.position.position.Z);
    }
}
