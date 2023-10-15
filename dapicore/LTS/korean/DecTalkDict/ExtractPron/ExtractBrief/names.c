/*C_HEADER_FILE****************************************************************
FILE        :  names.c
DESC        :  Functions to get or manipulate category names
TABS        :  3
OWNER       :  Fonix
DATE CREATED:  

(C) Copyright 1999,2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/06/03 4:28p $
  $Revision: 4 $

*END_HEADER*******************************************************************/

#include "FnxPlatform.h"
#include "FnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxNames.h"
#include "FnxMisc.h" /* for GrabField() */
#include "FnxHash.h"

/*FUNCTION_HEADER*******************
 * NAME:    ;BasePhoneIndex
 * DESC:    Find the index of a base phoneme.
 * IN:      pDesc - a Description structure that has at least the base phone list sorted.
 * OUT:     n/a
 * RETURN:  Index of the base phoneme, if found; -1 if not found.
 * NOTES:   
 *END_HEADER***************************/
SWORD BasePhoneIndex(DescPtr pDesc, char *sPhone)
{
   H_HashEntry *pHashEntry;

   if (!pDesc || !sPhone)
      return -1;
   pHashEntry = H_FindHashEntry(&(pDesc->PhoneHash), sPhone);
   if(pHashEntry)
      return (SWORD) ((SDWORD) H_GetHashValue(pHashEntry));
   return -1;
}  /* BasePhoneIndex */

/*FUNCTION_HEADER*******************
 * NAME:    ;defineCenter
 * DESC:    Find a category corresponding to a center phone, and build a diphone structure for it.
 * IN:      pDesc   - Description structure containing all categories.
            sCenter - Name of the center phone to find.
 * OUT:     a diphoneT structure is allocated and filled with category information for "<center>".
 * RETURN:  Pointer to the newly-allocated diphoneT structure, or NULL if no category was found.
 * NOTES:
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
diphoneTPtr defineCenter(DescPtr pDesc, char *sCenter)
{
   diphoneTPtr  d;
   SWORD       iBasephone, iCategory;
   CategoryPtr  pCategory;
   
   /* Look up the base phone in the base phone hash table */
   iBasephone = BasePhoneIndex(pDesc, sCenter);
   
   if (iBasephone>=0)
   {
      /* Get the index of the category that has iBasephone as the center context */
      iCategory = pDesc->pBasephones[iBasephone].iCenter;
      if (iCategory >= 0)
      {
         pCategory = &(pDesc->pCategories[iCategory]);
         
         d = (diphoneTPtr)FNX_MALLOC(SIZE_DIPHONET);
         if(pCategory->iTie<0) 
            d->cat = iCategory;
         else 
            d->cat    = pCategory->iTie;
         d->mindur    = pCategory->iMinDur;
         d->maxdur    = pCategory->iMaxDur;
         d->modelname = pCategory->sName;
         return d;
      }  /* if category>=0 */
   }  /* if found basephone */
   return NULL; /* Couldn't find category */
}  /* defineCenter */
#endif

/*FUNCTION_HEADER*******************
 * NAME:    ;defineLeft
 * DESC:    Find a category that corresponds to a center phone with a given phone on the left,
               (or a context containing that phone) and build a diphone structure for it.
 * IN:      pDesc   - Description structure containing all categories.
            sCenter - Name of the center phone
            sLeft   - Name of the phone on the left
 * OUT:     a diphoneT structure is allocated and filled with category information for "<center>".
 * RETURN:  Pointer to the newly-allocated diphoneT structure, or NULL if no matching category was found.
 * NOTES:   Find a category that is either "sLeft<sCenter" or "$Context<sCenter", where
              $Context is a list of phones that includes sLeft.
 *END_HEADER***************************/
diphoneTPtr defineLeft(DescPtr pDesc, char *sCenter, char *sLeft)
{
   diphoneTPtr  d;
   SWORD       iBasephone, iLeftPhone, iCategory;
   CategoryPtr  pCategory;
   
   /* Look up the index of the base phone */
   iBasephone = BasePhoneIndex(pDesc, sCenter);
   
   if (iBasephone>=0 && pDesc->pBasephones[iBasephone].piLeft)
   {
      /* Get the index of the left phone */
      iLeftPhone = BasePhoneIndex(pDesc, sLeft);
      if (iLeftPhone >= 0)
      {
         /* Get the index of the base phoneme */
         iCategory = pDesc->pBasephones[iBasephone].piLeft[iLeftPhone];
         if (iCategory >= 0)
         {
            pCategory = &(pDesc->pCategories[iCategory]);
         
            d = (diphoneTPtr)FNX_MALLOC(SIZE_DIPHONET);
            if(pCategory->iTie<0) 
               d->cat = iCategory;
            else 
               d->cat    = pCategory->iTie;
            d->mindur    = pCategory->iMinDur;
            d->maxdur    = pCategory->iMaxDur;
            d->modelname = pCategory->sName;
            return d;
         }  /* if category>=0 */
      }  /* if found left phone */
   }  /* if found center phone */
   return NULL; /* Didn't find it .*/
}  /* defineLeft */

/*FUNCTION_HEADER*******************
 * NAME:    ;defineRight
 * DESC:    Find a category that corresponds to a center phone with a given phone on the right,
               (or a context containing that phone) and build a diphone structure for it.
 * IN:      pDesc   - Description structure containing all categories.
            sCenter - Name of the center phone
            sRight  - Name of the phone on the right.
 * OUT:     a diphoneT structure is allocated and filled with category information for "sCenter>sRight" (or sCenter>$Right).
 * RETURN:  Pointer to the newly-allocated diphoneT structure, or NULL if no matching category was found.
 * NOTES:   Find a category that is either "sCenter>sRight" or "sCenter>$Context", where
              $Context is a list of phones that includes sRight.
 *END_HEADER***************************/
diphoneTPtr defineRight(DescPtr pDesc, char *sCenter, char *sRight)
{
   diphoneTPtr  d;
   SWORD          iBasephone, iRightPhone, iCategory;
   CategoryPtr     pCategory;
   
   /* Get the index of the base phoneme */
   iBasephone = BasePhoneIndex(pDesc, sCenter);
   
   if (iBasephone >= 0 && pDesc->pBasephones[iBasephone].piRight)
   {
      /* Get the index of the right phone */
      iRightPhone = BasePhoneIndex(pDesc, sRight);
      
      if (iRightPhone>=0)
      {
         iCategory = pDesc->pBasephones[iBasephone].piRight[iRightPhone];
         if (iCategory >= 0)
         {
            pCategory = &(pDesc->pCategories[iCategory]); // Get a local pointer to the category.

            d = (diphoneTPtr)FNX_MALLOC(SIZE_DIPHONET);
            if(pCategory->iTie<0) 
               d->cat = iCategory;
            else 
               d->cat    = pCategory->iTie;
            d->mindur    = pCategory->iMinDur;
            d->maxdur    = pCategory->iMaxDur;
            d->modelname = pCategory->sName;
            return d;
         }  /* if category>=0 */
      }  /* if found left phone */
   }  /* if found center phone */
   return NULL; /* Didn't find it .*/
}  /* defineRight */

/*FUNCTION_HEADER*******************
 * NAME:    ;GetCenter
 * DESC:    Get the index of the category corresponding to a center base phoneme index.
 * IN:      pDesc   - Description structure containing all categories.
            iCenter - Index of the base phoneme for the center phoneme to find.
 * OUT:     
 * RETURN:  Index to the category "<iCenter>", or -1 if not found.
 * NOTES:   iCenter is an index into the list of basephones stored in the hashing
              table by SortProbNames() and may not be the same as that in basemodel[].
 *END_HEADER***************************/
SWORD GetCenter(DescPtr pDesc, SWORD iCenter)
{
   SWORD          iCategory=-1; /* => didn't find it */
   CategoryPtr     pCategory;
   
   if (iCenter>=0)
   {
      /* Get the index of the category that has iCenter as the center context */
      iCategory = pDesc->pBasephones[iCenter].iCenter;
      if (iCategory >= 0)
      {
         pCategory = &(pDesc->pCategories[iCategory]);
         if(pCategory->iTie>=0) 
            iCategory = pCategory->iTie;
      }  /* if category>=0 */
   }  /* if valid basephone */
   return iCategory;
}  /* GetCenter */

/*FUNCTION_HEADER*******************
 * NAME:    ;GetLeft
 * DESC:    Get the index of a category that corresponds to a center phone 
              with a given phone on the left (or a context containing that phone).
 * IN:      pDesc      - Description structure containing all categories.
            iLeftPhone - Index of the base phone on the left
            iCenter    - Index of the center base phone
 * OUT:     
 * RETURN:  Index of category, or -1 if not found.
 * NOTES:   Finds a category that is either "iLeft<sCenter" or "$Context<iCenter", where
              $Context is contains base phoneme iLeft.
 *END_HEADER***************************/
SWORD GetLeft(DescPtr pDesc, SWORD iLeftPhone, SWORD iCenter)
{
   SWORD   iCategory = -1; /* => didn't find it */
   CategoryPtr pCategory;
   
   if (iCenter>=0 && iLeftPhone >= 0 && pDesc->pBasephones[iCenter].piLeft)
   {
      /* Get the index of the base phoneme */
      iCategory = pDesc->pBasephones[iCenter].piLeft[iLeftPhone];
      if (iCategory >= 0)
      {
         pCategory = &(pDesc->pCategories[iCategory]);
      
         if(pCategory->iTie>=0) 
            iCategory = pCategory->iTie;
      }  /* if category>=0 */
   }  /* if found left phone */
   return iCategory;
}  /* GetLeft */

/*FUNCTION_HEADER*******************
 * NAME:    ;GetRight
 * DESC:    Find the index of the category that corresponds to a center phone 
              with a given phone on the right (or a context containing that phone).
 * IN:      pDesc       - Description structure containing all categories.
            iCenter     - Index of the center phone
            iRightPhone - Index of the phone on the right.
 * OUT:     
 * RETURN:  Index of the category, or -1 if not found.
 * NOTES:   Finds a category that is either "iCenter>iRight" or "iCenter>$Context", where
              $Context contains iRight.
 *END_HEADER***************************/
SWORD GetRight(DescPtr pDesc, SWORD iCenter, SWORD iRightPhone)
{
   SWORD   iCategory=-1;/* => didn't find it yet */
   CategoryPtr pCategory;
   
   if (iCenter >= 0 && iRightPhone>=0 && pDesc->pBasephones[iCenter].piRight)
   {
      iCategory = pDesc->pBasephones[iCenter].piRight[iRightPhone];
      if (iCategory >= 0)
      {
         pCategory = &(pDesc->pCategories[iCategory]); // Get a local pointer to the category.
         
         if(pCategory->iTie>=0) 
            iCategory = pCategory->iTie;
      }  /* if category>=0 */
   }  /* if both phones exist */
   return iCategory; /* Didn't find it .*/
}  /* GetRight */

/*FUNCTION_HEADER*******************
 * NAME:    ;NumInList
 * DESC:    Decide whether a number is in a list of integers that is terminated by a -1.
 * IN:      iNum - Number to look for.
            piList - List of integers, terminated with -1. (or NULL if empty).
 * OUT:     n/a
 * RETURN:  TRUE if iNum is in the list; FALSE if iNum is not in the list, or the list is NULL.
 * NOTES:   
 *END_HEADER***************************/
BOOL NumInList(SWORD iNum, SWORDPTR piList)
{
   SDWORD i;
   if (piList)
   {
      for (i=0; piList[i]>=0; i++)
      {
         if (piList[i]==iNum)
            return TRUE; /* Found it. */
      }
   }
   return FALSE; /* Didn't find iNum in piList (or piList was NULL) */
}  /* NumInList */

/*FUNCTION_HEADER*******************
 * NAME:    ;GetTriphone
 * DESC:    Find a category that corresponds to a center phone with given phones
               (or contexts containing those phones) on the left and right,
               and build a diphone structure for it.
 * IN:      pDesc   - Description structure containing all categories.
            iLeft   - Index of the phone on the left.
            sCenter - Name of the center phone
            iRight  - Index of the phone on the right.
 * OUT:     
 * RETURN:  Index of the category for the specified triphone, or -1 if it does not exist.
 * NOTES:   Find a category that is $Left<sCenter>$Right, where $Left and $Right can each
              be sLeft or sRight (respectively), OR a context containing those phones.
 *END_HEADER***************************/
SWORD GetTriphone(DescPtr pDesc, SWORD iLeft, SWORD iCenter, SWORD iRight)
{
   SWORD iTriphone, iCategory;
   SDWORD iNumTriphones; /* Number of triphones that have 'iCenter' as the center basephone. */
   BasephonePtr pBasephone;

   if (iCenter >= 0 && pDesc->ppiLeftContext && pDesc->ppiRightContext)
   {
      pBasephone = &(pDesc->pBasephones[iCenter]);
      iNumTriphones = pBasephone->iNumTriphones;
      /* Search through the list of triphones that have 'iCenter' as their basephone,
         and see if each one has a match for the left AND right context. */
      for (iTriphone = 0; iTriphone < iNumTriphones; iTriphone++)
      {
         /* Get a pointer to a triphone in the list of triphones for this basephone */
         iCategory = pBasephone->piTriphones[iTriphone];
         FNX_ASSERT(iCategory>=0);
         /* Skip over this loop if either context fails to match */
         if (NumInList((SWORD)iLeft, pDesc->ppiLeftContext[iCategory]) &&
             NumInList((SWORD)iRight, pDesc->ppiRightContext[iCategory]))
         {
            /* Found a triphone category that matches iLeft<iCenter>iRight, so return its index. */
            return iCategory;
         }
      }  /* for iTriphone */
   }  /* if found center phone */
   return -1; /* Didn't find it .*/
}  /* GetTriphone */
