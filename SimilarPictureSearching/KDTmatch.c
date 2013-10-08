#include "..\sift\sift.h"
#include "..\sift\imgfeatures.h"
#include "..\sift\utils.h"
#include "..\sift\xform.h"
#include "..\sift\kdtree.h"

#include "KDTmatch.h"





int KDTmatch( IplImage* SourceImage, IplImage* TargetImage, int sourceNum, int targetNum, 
				struct feature* sourceFeat, struct feature* targetFeat, int PopUp, int MatchNum  )
{
	IplImage* stacked;
	struct feature* feat;
	struct feature** nbrs;
	struct kd_node* kd_root;
	CvPoint pt1, pt2;
	double d0, d1;
	int k, i, m = 0;
	/*
	sourceimg = cvLoadImage( img1_file, 1 );
	if( ! SourceImage )
		fatal_error( "unable to load image from %s", img1_file );
	targetimg = cvLoadImage( img2_file, 1 );
	if( ! TargetImage )
		fatal_error( "unable to load image from %s", img2_file );
	*/
	stacked = stack_imgs( SourceImage, TargetImage );

	/*
	fprintf( stderr, "Finding features in %s...\n", img1_file );
	sourceN = sift_features( Sourceimage, &sourceFeat );
	fprintf( stderr, "Finding features in %s...\n", img2_file );
	targetN = sift_features( TargetImage, &targetFeat );
	*/
	kd_root = kdtree_build( targetFeat, targetNum );

	#pragma omp for
	for( i = 0; i < sourceNum; i++ )
	{
		feat = sourceFeat + i;

		k = kdtree_bbf_knn( kd_root, feat, 2, &nbrs, KDTREE_BBF_MAX_NN_CHKS );
		if( k == 2 )
		{
			d0 = descr_dist_sq( feat, nbrs[0] );
			d1 = descr_dist_sq( feat, nbrs[1] );
			if( d0 < d1 * NN_SQ_DIST_RATIO_THR )
			{
				pt1 = cvPoint( cvRound( feat->x ), cvRound( feat->y ) );
				pt2 = cvPoint( cvRound( nbrs[0]->x ), cvRound( nbrs[0]->y ) );
				pt2.y += SourceImage->height;
				cvLine( stacked, pt1, pt2, CV_RGB(255,0,255), 1, 8, 0 );
				m++;

				sourceFeat[i].fwd_match = nbrs[0];
			}
		}
		free( nbrs );
	}

	if (PopUp == 1)
	{
		//fprintf( stderr, "Found %d total matches\n", m );
		cvNamedWindow( "Matches", 1 );
		cvShowImage( "Matches", stacked );
		cvWaitKey( 0 );
		cvDestroyWindow("Matches");
	}
	

	/* 
	UNCOMMENT BELOW TO SEE HOW RANSAC FUNCTION WORKS

	Note that this line above:

	sourceFeat[i].fwd_match = nbrs[0];

	is important for the RANSAC function to work.
	*/
	/*
	{
		CvMat* H;
		H = ransac_xform( sourceFeat, sourceN, FEATURE_FWD_MATCH, lsq_homog, 4, 0.01,
			homog_xfer_err, 3.0, NULL, NULL );
		if( H )
		{
			IplImage* xformed;
			xformed = cvCreateImage( cvGetSize( targetPicture ), IPL_DEPTH_8U, 3 );
			cvWarpPerspective( sourcePicture, xformed, H, 
				CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS,
				cvScalarAll( 0 ) );
			cvNamedWindow( "Xformed", 1 );
			cvShowImage( "Xformed", xformed );
			cvWaitKey( 0 );
			cvReleaseImage( &xformed );
			cvReleaseMat( &H );
		}
	}
	*/

	cvReleaseImage( &stacked );
	//cvReleaseImage( &sourcePicture );
	cvReleaseImage( &TargetImage );
	kdtree_release( kd_root );
	//free( sourceFeat );
	free( targetFeat );

	if ( m >= MatchNum )
	{
		return 1;
	}
	else
		return 0;

}
