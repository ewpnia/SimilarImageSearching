/*
Detects SIFT features in two images and finds matches between them.

Copyright (C) 2006  Rob Hess <hess@eecs.oregonstate.edu>

@version 1.1.1-20070913
*/


#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <stdio.h>

/* the maximum number of keypoint NN candidates to check during BBF search */
#define KDTREE_BBF_MAX_NN_CHKS 200

/* threshold on squared ratio of distances between NN and 2nd NN */
#define NN_SQ_DIST_RATIO_THR 0.49

#ifdef __cplusplus
extern "C"
{
#endif

	int KDTmatch( IplImage* SourceImage, IplImage* TargetImage, int sourceNum, int targetNum, 
	struct feature* sourceFeat, struct feature* targetFeat, int PopUp, int MatchNum );

#ifdef __cplusplus
}
#endif
