/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Amy Yee                                                   */
/* Date: 12/08/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
	int x = 0;
	char *fin = NULL;
	char *fout = NULL;

	unsigned int width = 480;
	unsigned int height = 270;

  /**************/
  /* Parameters */
  /**************/
  IENTRY *frame;
  IMAGE *rgbframe;
  MOVIE *movie = NULL;
  int fin_len, fout_len;
  int frames_count;
  int start, end;
  int factor; /* ZOOM parameter */

  /*********/
  /* Flags */
  /*********/
  int load=0, save=0; // Load and save files
  int aging=0, hflip=0, edge=0, crop=0, fast=0,
      reverse=0, watermark=0, spotlight=0, zoom=0; // DIPs

	/* the while loop to check options in the command line */
	while (x < argc) {
    /* the help option */
    if (strcmp(argv[x], "-h") == 0) {
      PrintUsage();
      free(fin);
      free(fout);
      return 5;
    } /*fi*/

		/* the input file name */
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
        fin_len = strlen(argv[x+1]);
				fin = (char *)malloc(fin_len * sizeof(char) + 1);

        if (fin == NULL) {
          printf("Error allocating memory for file!");
          free(fin);
          free(fout);
          return 5;
        }

        strcpy(fin, argv[x+1]);
        printf("%s", fin);

			} /*fi*/
			else {
				printf("Missing argument for the input file name!\n");
        free(fin);
        free(fout);
				return 5;
			} /*esle*/
      load = 1;
			x += 2;
			continue;
		} /*fi*/

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				fout_len = strlen(argv[x + 1]);
        fout = (char *)malloc(fout_len * sizeof(char) + 1);
        if (fout == NULL) {
          printf("Error with allocating memory to save movie!");
          free(fout);
          free(fin);
        }
        strcpy(fout, argv[x+1]);
			} /*fi*/
			else {
				printf("Missing argument for the output file name!\n");
				return 5;
			} /*esle*/

      save = 1;
			x += 2;
			continue;
		} /*fi*/

    /* Number of frames */
    if(strcmp(argv[x], "-f") == 0) {
      if(x < argc-1) {
        sscanf(argv[x+1], "%d", &frames_count);
      }  else {
        printf("Missing parameter for number of frames!");
        free(fin);
        free(fout);
        return 0;
      }

      x += 2;
      continue;
    }

    /* Size of frames */
    if(strcmp(argv[x], "-s") == 0) {
      if (x < argc-1) {
        sscanf(argv[x+1], "%dx%d", &width, &height);
      } else {
        printf("Missing a WIDTHxHEIGHT parameter!");
        free(fin);
        free(fout);
        return 0;
      }
      x += 2;
      continue;
    }

    /* DIP Operations */

    /* AGING */
    if(strcmp(argv[x], "-aging") == 0) {
      aging = 1;
      x++;
      continue;
    }

    /* HORIZONTAL FLIP */
    if(strcmp(argv[x], "-hflip") == 0) {
      // YUV2RGBMovie(movie);
      //
      // frame = movie->Frames->First;
      // while(frame != NULL) {
      //         frame->RGBImage = HFlip(frame->RGBImage);
      //         frame = frame->Next;
      // }
      //
      // RGB2YUVMovie(movie);
      // printf("HFlip operation is done!\n");
      x++;
      continue;
    }

    /* EDGE */
    if(strcmp(argv[x], "-edge") == 0) {
      // YUV2RGBMovie(movie);
      //
      // frame = movie->Frames->First;
      // while(frame != NULL) {
      //         frame->RGBImage = Edge(frame->RGBImage);
      //         frame = frame->Next;
      // }
      //
      // RGB2YUVMovie(movie);
      // printf("Edge operation is done!\n");
      x++;
      continue;
    }

    /* CROP */
    if(strcmp(argv[x], "-crop") == 0) {
      // if (x < argc-1) {
      //   sscanf(argv[x+1], "%u-%u", &start, &end);
      //   CropImageList(movie->Frames, start, end);
      //   printf("Crop operation is done! The new number of frames is %d.\n", movie->Frames->Length);
      // } else {
      //   printf("Missing crop start and end parameter!\n");
      //   free(fin);
      //   free(fout);
      //   return 0;
      // }

      x += 2;
      continue;
    }

    if(strcmp(argv[x], "-fast") == 0) {
      // if (x < argc-1) {
      //   sscanf(argv[x+1], "%u", &factor);
      //   FastImageList(movie->Frames, factor);
    	// 	printf("FastImageList is done! New number of frames is %d\n", movie->Frames->Length);
      // } else {
      //   printf("Missing parameter for Fast operation!\n");
      //   free(fin);
      //   free(fout);
      //   return 0;
      // }

      x += 2;
      continue;
    }

    if(strcmp(argv[x], "-reverse") == 0) {
      // /* do something */
      // if (x < argc-1) {
      //   ReverseImageList(movie->Frames);
      //   printf("ReverseImageList operation is done!\n");
      // }
      x++;
      continue;
    }

    if(strcmp(argv[x], "-watermark") == 0) {
      /* do something */
      /* check next argument for watermark */
    }

    if(strcmp(argv[x], "-spotlight") == 0) {
      /* do something */
    }

    if(strcmp(argv[x], "-zoom") == 0) {
      /* do something */
    }
		x++;
	} /*elihw*/

  /******************/
  /* ERROR HANDLING */
  /******************/

	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		return 5;
	}

  /**************/
  /* OPERATIONS */
  /**************/

  if (load == 1) {
    movie = LoadMovie(fin, frames_count, width, height);
  }
  if (save == 1) {
    SaveMovie(fout, movie);
  }
  if (aging == 1) {
    YUV2RGBMovie(movie);

    frame = movie->Frames->First;

    while(frame != NULL) {
	frame->RGBImage = Aging(frame->RGBImage);
	frame = frame->Next;
    }

    RGB2YUVMovie(movie);
    printf("Aging operation is done!");

  }
  if(hflip == 1) {
    /* DIP here */
  }
  if(edge == 1) {
    /* DIP here */
  }
  if(crop == 1) {
    /* DIP here */
  }
  if(fast == 1) {
    /* DIP here */
  }
  if(reverse == 1) {
    /* DIP here */
  }
  if(watermark == 1) {
    /* DIP here */
  }
  if(spotlight == 1) {
    /* DIP here */
  }
  if(zoom == 1) {
    /* DIP here */
  }


	/* to be implemented */
  SaveMovie(fout, movie);
  free(fin);
  free(fout);
	fin = NULL;
	fout = NULL;

	return 0;
}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
	       "Options:\n"
	       "-aging                Activate the aging filter on every movie frame\n"
	       "-hflip                Activate horizontal flip on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-reverse              Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight            Spotlight the fade in and fade out\n"
	       "-zoom                 Zoom in and out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVIMAGE* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height)
{
  assert(fname);
  MOVIE *m = CreateMovie();

  for(int i=0; i<frameNum; i++) {
    AppendYUVImage(m->Frames,LoadOneFrame(fname, i, width, height));
  }

  printf("Movie is successfully loaded! \n");
  return m;

}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	/* to be implemented */
  int count; // counts number of frames
  int x, y;
  IENTRY *curr;
  FILE *file;

  file = fopen(fname, "w");
  if (file == NULL) {
    printf("File could not be read!");
    return 0;
  }

  count = 0;
  curr = movie->Frames->First;
  while (curr != NULL) {
    for(y = 0; y < curr->YUVImage->H; y++) {
      for(x = 0; x < curr->YUVImage->W; x++) {
        fputc(GetPixelY(curr->YUVImage,x,y),file);
      }
    }
    for(y = 0; y < curr->YUVImage->H; y += 2) {
      for(x = 0; x < curr->YUVImage->W; x += 2) {
        fputc(GetPixelU(curr->YUVImage,x,y),file);
      }
    }
    for(y = 0; y < curr->YUVImage->H; y += 2) {
      for(x = 0; x < curr->YUVImage->W; x += 2) {
        fputc(GetPixelV(curr->YUVImage,x,y),file);
      }
    }
    curr = curr->Next;
    count++;
  }

  fclose(file);
  file = NULL;

  printf("%d frames from the movie %s were written successfully! \n", count, fname);
  return 0;

}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file)
{
	int x, y;
	for (y = 0; y < image->H; y++) {
		for (x = 0; x < image->W; x++) {
			fputc(GetPixelY(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelU(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelV(image, x, y), file);
		}
	}
}

/* EOF */
