/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *l;
  l = malloc(sizeof(ILIST));

	if (!l) {
		printf("List not created due to memory error");
	}

	l->Length = 0;
	l->First = NULL;
	l->Last = NULL;

	return l;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	assert(list);
	IENTRY *curr, *next;
	YUVIMAGE *yuv;

	curr = list->First->Next->Prev;
	next = list->First->Next;
	yuv = curr->YUVImage;

	while(curr) {
		free(curr);
		curr->YUVImage = NULL;
		DeleteYUVImage(yuv);

		// curr->Next = NULL;
		// /* May not be necessary */
		// curr->Prev = NULL;

		// Assigns "next" element as the new first element
		curr = next;
		// Deletes old first pointer
		curr->Prev = NULL;

		list->Length--;
	}

	free(list);
	list = NULL;
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
	IENTRY *e = NULL;
	assert(list);
	assert(RGBimage);

	e = malloc(sizeof(IENTRY));

	e->List = NULL;
	e->Next = NULL;
	e->YUVImage = NULL;
	e->RGBImage = RGBimage;

	if (list->Last) {
		e->List = list;
		e->Next = NULL;
		e->Prev = list->Last;

		/* Ensures that "previous" last image's next pointer points to the new entry */
		list->Last->Next = e;
		/* Sets the new entry as the last element in the list */
		list->Last = e;
	}
	else {
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;

		list->First = e;
		list->Last = e;
	}

	list->Length++;


}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
	IENTRY *e = NULL;
	assert(list);
	assert(YUVimage);
	e = malloc(sizeof(IENTRY));

	e->List = NULL;
	e->Next = NULL;
	e->YUVImage = YUVimage;

	if (list->Last) {
		e->List = list;
		e->Next = NULL;
		e->Prev = list->Last;

		/* Ensures that "previous" last image's next pointer points to the new entry */
		list->Last->Next = e;
		/* Sets the new entry as the last element in the list */
		list->Last = e;
	}
	else {
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;

		list->First = e;
		list->Last = e;
	}

	list->Length++;

}

/* Crop an image list (deletes elements at the end of clip) */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
	assert(list);

	IENTRY *e;
	int x, y;
	unsigned int movielen;
	movielen = list->Length;

	/* Makes the starting image at the index *start */
	for(x = 1; x < start; x++) {
		if(list->First) {
			e = list->First;
			list->First = e->Next;

			/* makes the former first image NULL */
			if(list->First) {
				list->First->Prev = NULL;
			}
			/* iteration reaches the end of the image list */
			else {
				assert(list->Last == e);
				list->Last = NULL;
			}

			list->Length--;
			DeleteYUVImage(e->YUVImage);
			free(e);
			e = NULL;
		}
	}

	for(y=end; y < movielen; y++) {
		if (list->Last) {
			e = list->Last;
			list->Last = e->Prev;

			if(list->Last) {
				list->Last->Next = NULL;
			}
			else {
				list->First = NULL;
			}

			list-> Length--;
			DeleteYUVImage(e->YUVImage);
			free(e);
			e = NULL;
		}
	}
}

/* Fast forward an image list (deletes elements in the middle of the clip) */
void FastImageList(ILIST *list, unsigned int factor)
{
	assert(list);
	assert(factor);

	int x;
	unsigned int length = list->Length;
	IENTRY *e, *next_e, *curr_e;

	e = list->First;

	for(x=0; x<length; x++) {
		/* When the index % factor is 0, then the index is saved, for it is "fast forwarded" by that factor */
		if(x % factor == 0 ) {
			next_e = e->Next;
			e = next_e;
			list->Last = e; /* "appends" this image at end of list */
		}
		/* if cannot be divided by this factor, the image is deleted and the memory is freed */
		else {
			curr_e = e;
			DeleteYUVImage(e->YUVImage);
			free(e);
			e = NULL;

			if (curr_e->Next) {
				curr_e->Prev->Next = curr_e->Next;
				curr_e->Next->Prev = curr_e->Prev;

				e = curr_e->Next;
			}
			else {
				curr_e->Prev->Next = NULL;
			}

			list->Length--;
		}
	}
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	/* to be implemented */
}

/* EOF */
