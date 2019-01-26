/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Amy Yee                                                   */
/* Date: 12/08/2017                                                  */
/*                                                                   */
/* Constants.h: header file for macros                               */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	MOVIE *m;
  m = (MOVIE *)malloc(sizeof(MOVIE));
	m->Frames = CreateImageList();
  return m;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);
	DeleteImageList(movie->Frames);
	free(movie);
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
	assert(movie);
	IENTRY *frame;
	int x, y;
	unsigned int W, H;
	unsigned char R, G, B;
	unsigned char Y, U, V, C, D, E;

	frame = movie->Frames->First;
	// Creates RGB image based on height of YUV image
	W = frame->YUVImage->W;
	H = frame->YUVImage->H;

	while (frame) {
		IMAGE *rgb = CreateImage(W, H);
		for (x=0; x<W; x++) {
			for (y=0; y<H; y++) {
				Y = frame->YUVImage->Y[x + y*W];
				U = frame->YUVImage->U[x + y*W];
				V = frame->YUVImage->V[x + y*W];
				C = Y - 16;
				D = U - 128;
				E = V - 128;

				R = clip(((298*C) + (409*E) + 128)>>8);
				G = clip(((298*C) - (100*D) - (208*E) + 128)>>8);
				B = clip(((298*C) + (516*D) + 128)>>8);

				// Assigning RGB values into rgb image pointer
				rgb->R[x + y*W] = R;
				rgb->G[x + y*W] = G;
				rgb->B[x + y*W] = B;
			}
		}
		frame->RGBImage = rgb;

		/* YUV is NULL when RGB is active */
		DeleteYUVImage(frame->YUVImage);

		frame=frame->Next;
	}
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
	assert(movie);
	IENTRY *frame;
	int x, y;
	unsigned int W, H;
	unsigned char R, G, B;
	unsigned char Y, U, V;

	frame = movie->Frames->First;
	// Creates RGB image based on height of YUV image
	W = frame->RGBImage->W;
	H = frame->RGBImage->H;

	while (frame) {
		/* Must create new image for each FRAME */
		YUVIMAGE *yuv = CreateYUVImage(W,H);
		for (x=0; x<W; x++) {
			for (y=0; y<H; y++) {
				R = frame->RGBImage->R[x + y*W];
				G = frame->RGBImage->G[x + y*W];
				B = frame->RGBImage->B[x + y*W];

				Y = clip((((66*R) + (129*G) + (25*B) + 128)>>8) + 16);
				U = clip((((-38*R) - (74*G) + (112*B) + 128)>>8) + 128);
				V = clip((((112*R) - (94*G) - (18*B) + 128)>>8) + 128);

				// Assigning RGB values into rgb image pointer
				yuv->Y[x + y*W] = Y;
				yuv->U[x + y*W] = U;
				yuv->V[x + y*W] = V;


			}
		}
		DeleteImage(frame->RGBImage);
		frame->YUVImage = yuv;
		frame=frame->Next;
	}

}

int clip(int x) {
	int adj_x;
	if (x>255) {
		adj_x = 255;
	}
	else if(x<0) {
		adj_x = 0;
	} else {
		adj_x = x;
	}
	return adj_x;
}
/* EOF */
