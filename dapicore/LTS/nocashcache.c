#include "dectalkf.h"
#include "FileSystemDict.h"

#include "nocashcache.h"

// Rough description.

//Purpose: When matching partial strings in a word against several small
//dictionaries that contain lemata, suffixes, prefixes and other word
//morphological elements, we often find that the same thing needs to be found
//over and over. This is in particular the case if the matching occurs during a
//parsing process in which the word is parsed according to a grammar tree. 

//The information that needs to be stored is the combination of a string and a rule number.
//The string is not directly stored, but rather by a reference number which usually corresponds to 

//We are using two types of structures and one header structure to hold the
//information. 

//Conventions: The meaning of the value of foundinfoindex is as follows:
 
//A positive value represents an offset into a table of strings
//zero means that there was no information found
//-1  means that the information was found but there is no associated string and no rule
//In the case of zero and -1 there is no associated finfo.


void add_entry_to_free_list(ltrcache *trc, short ent);
void recycle_finfo(ltrcache *trc, short ninfo);

void init_foundinfo(ltrcache *trc, int finfo_length, int ltinfo_length)
{
    /* To do: Initialize the foundinfo space which is a forward linked list */
    
    int k;
    
    for (k=0; k < finfo_length; k++)
    {
	trc->finfo[k].next = k+1;
    }
    trc->finfo[finfo_length-1].next= CACHENULLPTR;

    trc->firstfree=0;
    trc->lastfree=finfo_length-1;
    trc->nfree = finfo_length;
	
    for (k=0; k < ltinfo_length; k++)
    {
	trc->ltinfo[k].next=k+1;
	trc->ltinfo[k].prev=k-1;

	trc->ltinfo[k].foundinfoindex = -1;
	trc->ltinfo[k].ltrienumber=0;
	trc->ltinfo[k].position=0;
    }
    trc->ltinfo[ltinfo_length-1].next=CACHENULLPTR;
    trc->ltinfo[0].prev = CACHENULLPTR;

    trc->ltfirst=CACHENULLPTR;
    trc->ltfirstfree=0;
    trc->ltlast=CACHENULLPTR;
    trc->sizefinfo = finfo_length;
    trc->sizeltinfo = ltinfo_length;
}


void delete_last_ltinfo(ltrcache *trc)
{
    short prevp,lastp;
    short found;
  
    if (trc->ltlast==CACHENULLPTR)
	return;

    
    lastp = trc->ltlast;
    prevp = trc->ltinfo[lastp].prev;
    if (prevp==CACHENULLPTR)
    {
	trc->ltfirst=CACHENULLPTR;
	trc->ltlast=CACHENULLPTR;
    }
    else
    {
    
	trc->ltinfo[prevp].next = CACHENULLPTR;
	trc->ltlast = prevp;
    }
    trc->ltinfo[lastp].prev = CACHENULLPTR;

   found = trc->ltinfo[lastp].foundinfoindex;
   if (found >= 0)  recycle_finfo(trc,found);

    add_entry_to_free_list(trc,lastp);
}

void delete_ltinfo(ltrcache *trc, short N)
{
    short prevp, nextp;
    short found;

    if (N == CACHENULLPTR) return;

    prevp = trc->ltinfo[N].prev;
    nextp = trc->ltinfo[N].next;

    if (prevp == CACHENULLPTR)
    {
	if (nextp == CACHENULLPTR)
	{
	    trc->ltfirst = trc->ltlast =  CACHENULLPTR;
	}
	else
	{
	    trc->ltinfo[nextp].prev = CACHENULLPTR;
	    trc->ltfirst = nextp;
	}
    }
    else  // not the first
    {
	if (nextp  == CACHENULLPTR) // but the last
	{
	    trc->ltinfo[prevp].next = CACHENULLPTR;
	    trc->ltlast = prevp;
	}
	else  // not the last either
	{
	    trc->ltinfo[prevp].next = nextp;
	    trc->ltinfo[nextp].prev = prevp;
	}
    }

    found = trc->ltinfo[N].foundinfoindex;
    if (found !=CACHENULLPTR)  recycle_finfo(trc,found);

    add_entry_to_free_list(trc,N);
    return;
}


void add_entry_to_free_list(ltrcache *trc, short ent)
{
    trc->ltinfo[ent].next=trc->ltfirstfree;
    trc->ltfirstfree=ent;
}

int get_entry_from_free_ltlist(ltrcache *trc)
{
    short ent;

    ent=trc->ltfirstfree;
    if (ent==CACHENULLPTR)
	return ent;
    trc->ltfirstfree=trc->ltinfo[ent].next;
    trc->ltinfo[ent].next=CACHENULLPTR;    
    trc->ltinfo[ent].prev=CACHENULLPTR;
    if (trc->ltfirstfree!=CACHENULLPTR)
    {
	trc->ltinfo[trc->ltfirstfree].prev=CACHENULLPTR;
    }
    return(ent);
}

void add_entry_to_ltinfo(ltrcache *trc,short ent)
{
    short old_first;

    if (trc->ltfirst==CACHENULLPTR)
    {
	trc->ltfirst=ent;
	trc->ltlast=ent;
    }
    else
    {
	old_first=trc->ltfirst;
	trc->ltfirst=ent;
	trc->ltinfo[old_first].prev=ent;
	trc->ltinfo[ent].next=old_first;
    }
}


/* If an ltinfo was accessed, it will be sent to the top of the list so it's
 * found first, the next time we ask. */

void move_to_top_of_ltinfo(ltrcache *trc,short ent)
{
    short prev, next;

    if (trc->ltfirst==CACHENULLPTR)
	return;

    if (trc->ltfirst==ent)     // If already first, leave it.
	return;

    /* Unlink ent: connect previous with next */
    prev = trc->ltinfo[ent].prev;
    next = trc->ltinfo[ent].next;
    trc->ltinfo[prev].next = next;
    if (next==CACHENULLPTR) 
    {
	trc->ltlast = prev;
    }
    trc->ltinfo[next].prev = prev;
    
    /* Relink ent as first in list */
    trc->ltinfo[ent].next = trc->ltfirst;
    trc->ltinfo[trc->ltfirst].prev = ent;
    trc->ltfirst = ent;
    trc->ltinfo[ent].prev = CACHENULLPTR;
}

void fill_ltinfo_entry(ltrcache *trc, short ent, unsigned char ltr, unsigned char pos, short found)
{
    trc->ltinfo[ent].ltrienumber = ltr;
    trc->ltinfo[ent].position = pos;                
    trc->ltinfo[ent].foundinfoindex = found;  // negative: no finfo associated.
}

#if 0
void traverse_finfo(ltrcache *trc,int fptr)
{
    int i;
    i=fptr;
    for (i=fptr;i<MAXFOUNDINFO && i!=CACHENULLPTR; i=trc->finfo[i].next)
    {
	printf("\tfinfo %3i next=%3i [%d,0x%x,%3i]\n",
	       i,trc->finfo[i].next, trc->finfo[i].string_handle,
	       trc->finfo[i].ruleno, trc->finfo[i].end_pos);
    }
}

void print_ltinfo(ltrcache *trc)
{
    int i;

    printf("ltfirst = %4i ltlast=%4i ltfirstfree=%4i\n",
	   trc->ltfirst, trc->ltlast, trc->ltfirstfree);

    for (i=0;i<MAXTESTINFO; i++)
    {
	printf("%3i next=%3i prev=%3i [%2i,%2i] found=%4i\n",
	       i,trc->ltinfo[i].next, trc->ltinfo[i].prev,
	       trc->ltinfo[i].ltrienumber, trc->ltinfo[i].position,
	       trc->ltinfo[i].foundinfoindex);
    }
}


void traverse_ltinfo(ltrcache *trc)
{
    int i;

    i=trc->ltfirst;
    printf("trav ltfirst = %4i ltlast=%4i ltfirstfree=%4i\n",
	   trc->ltfirst, trc->ltlast, trc->ltfirstfree);

    while (i>=0 && i<trc->sizeltinfo)
    {
	printf("%3i next=%3i prev=%3i [%2i,%2i] found=%4i\n",
	       i,trc->ltinfo[i].next, trc->ltinfo[i].prev,
	       trc->ltinfo[i].ltrienumber, trc->ltinfo[i].position,
	       trc->ltinfo[i].foundinfoindex);
	traverse_finfo(trc,trc->ltinfo[i].foundinfoindex);
	i=trc->ltinfo[i].next;
    }

    i = trc->ltfirstfree;
    printf("freelist %4i\n",trc->ltfirstfree);
    while (i>=0 && i<trc->sizeltinfo)
    {
	printf("%3i next=%3i prev=%3i [%2i,%2i] found=%4i\n",
	       i,trc->ltinfo[i].next, trc->ltinfo[i].prev,
	       trc->ltinfo[i].ltrienumber, trc->ltinfo[i].position,
	       trc->ltinfo[i].foundinfoindex);
	i=trc->ltinfo[i].next;
    }

}

void print_finfo(ltrcache *trc)
{
    int i;

    printf("finfo firstfree = %4i lastfree=%4i nfree=%4i\n",
	   trc->firstfree, trc->lastfree, trc->nfree);

    for (i=0;i<MAXFOUNDINFO; i++)
    {
	printf("%3i next=%3i [%d,%3i,%3i]\n",
	       i,trc->finfo[i].next, trc->finfo[i].string_handle,
	       trc->finfo[i].ruleno, trc->finfo[i].end_pos);
    }
}
#endif


void recycle_finfo(ltrcache *trc, short ninfo)
{
/* what is does:
   attaches the free cell or sequence of cells to the last
   entry in the free list and update the lastfree entry 
*/
    short nextf;

    if (trc->lastfree == CACHENULLPTR)
    {
	trc->firstfree = ninfo;
	trc->lastfree = ninfo;
	trc->nfree = 1;
    }
    else
    {
	trc->finfo[trc->lastfree].next = ninfo;
	trc->lastfree = ninfo;
	trc->nfree += 1;
    }
    nextf = trc->finfo[ninfo].next;
    while (nextf != CACHENULLPTR)
    {
	trc->lastfree = nextf;
	nextf = trc->finfo[nextf].next;
	trc->nfree += 1;
    }
}


short get_free_finfo(ltrcache *trc, short num)
{
/* 
   Gets a list of num elements from the free finfo list:

   returns an index number to first free finfo and -1 if there is not enough
   space.  This version returns the index of the first in a list of num
   elements. The record last in the list is terminated with -1. firstfree is
   updated accordingly.

   To find out if there is enough space, we traverse the free list using ffree
   as index. To be able to access the last element of the list we need to keep
   a copy of the previous ffree which is in ffreeprev. While traversing the
   list, we count down from the number num to zero. If zero can be reached, we
   terminate the to-be-returned list, modify the firstfree field and return
   the list. If zero can't be reached, -1 is returned and no changes take place

*/
    short ffree, freereturn, ffreeprev;
    short count;

    ffree = trc->firstfree;
    if (ffree == CACHENULLPTR) return (ffree);
    

    count = num;    
    freereturn = trc->firstfree;   // return this if there is enough space
    ffreeprev = ffree;

    while ((count>0) && (ffree != CACHENULLPTR))
    {
	ffreeprev = ffree;
	ffree = trc->finfo[ffree].next;
	count--;
    }
    if (count > 0)
    {
	return CACHENULLPTR;
    }
    else
    {
	trc->finfo[ffreeprev].next = CACHENULLPTR;
	trc->firstfree = ffree;  // (can be -1 if free storage exhausted)
	if (ffree==CACHENULLPTR) trc->lastfree = CACHENULLPTR;
	trc->nfree -= num;
	return (freereturn);
    }
}

short delete_oldest_ltelement(ltrcache *trc, short how)
{
/* if how is 0 we remove the very last element in the list and
   if how is 1, we start at the end, and find the first (oldest) element
   whose removal results in creating free space in the finfo space. 
*/
    short oldest,todelete;

    if (how == 0) 
    {
	delete_last_ltinfo(trc);
	return(1);
    }
    else
    {
	oldest = trc->ltlast;
	while (oldest != CACHENULLPTR)

	{
	    if (trc->ltinfo[oldest].foundinfoindex!=CACHENULLPTR)
	    {
		todelete=oldest;
		break;
	    }
	    else
	    {
		oldest = trc->ltinfo[oldest].prev;
	    }
	}
	if (todelete != CACHENULLPTR)
	{
	    delete_ltinfo(trc, todelete);
	    return 0;
	}
	else
	{
	    return 1;
	}   
    }
}

/* 
   what needs to be written?

Situation: We need an finfo list of length N to fill in new information. Let's
say N is greater than zero (see below if not). First, we check if there is space in
the ltlist info.  If yes, we next figure out if there is space in the finfo
list. If yes, we take the last element of the ltlist info, move it too first
position and replace whatever is stored on it, then we request the space from
the finfo list and fill the list.

All these nice things we have to do anyways, but first we may end up with a
situation where there isn't any space in finfo. So what we do is to remove one
ltinfo entry which has as a consequence also freeing up space in the finfo
structure and then ask again. Modify this as follows: Under these
circumstances, an element from the ltlist is only removed if it frees up space
in the finfo list: Some ltlist entries have nothing stored in the finfo and so
their removal does not give us any advantage. 

*/

short create_ltinfo_space(ltrcache *trc, short N)
{
/* 
   N is the number of associated finfo elements are needed.
*/

    short ltfree;
    short storage_expired;
    /* 
       First, let's say N is zero: we don't need to care about the finfo issue
       since that table changed.
    */


    if (trc->nfree >= N)
    {
	    ltfree = get_entry_from_free_ltlist(trc);
		if (ltfree!=CACHENULLPTR)
			return (ltfree);
    }
    if (N == 0)
    {
	if (trc->ltfirstfree != CACHENULLPTR)
	{
	    ltfree = get_entry_from_free_ltlist(trc);
	    return (ltfree);
	}
	else
	{
	    storage_expired = delete_oldest_ltelement(trc,0); /* 0: simply delete last one */
	    ltfree = get_entry_from_free_ltlist(trc);
	    return (ltfree);
	}
    }
    else   /* N>0: need to find ltinfo space and finfo space */
    {
	storage_expired = 0;
	while (trc->nfree < N && !storage_expired)
	{
	    storage_expired = delete_oldest_ltelement(trc,1);  /* delete oldest that creates space */
	}
	if (storage_expired)
	{
	    return (CACHENULLPTR);
	}
	else
	{
	    ltfree = get_entry_from_free_ltlist(trc);
		if (ltfree==CACHENULLPTR)
		{
		    storage_expired = delete_oldest_ltelement(trc,0); /* 0: simply delete last one */
		    ltfree = get_entry_from_free_ltlist(trc);
		}
		
	    return (ltfree);
	}
    }
}
    

int  num_finfo_records(short nlist, WORD_SEG_LIST *list)
{
/* precomputes how many finfo records are needed to represent the list */

    int    n;
    int    i,len;

    n = 0;

    for (i=0;i<nlist;i++)
    {
	if (list[i].iPronOffset !=CACHENULLPTR)
		n++;
    }
    return (n);
}

/*
  fill_finfo_records Parameters:
  ltrcache *trc:        Pointer to cache structure
  int nlist:            Number of records from file search
  WORD_SEG_LIST *list:  The list generated from file search 
  short first:          index of the first finfo element
*/

void fill_finfo_records(ltrcache *trc, int nlist, WORD_SEG_LIST *list, short first)
{
    int    n;
    int    i,k,kk,len,rem;
    short  finfo_indx;
    unsigned char   rule, mask;

    finfo_indx =first;
    
    for (i=0;i<nlist;i++)
    {
		trc->finfo[finfo_indx].ruleno = list[i].iRule;
		trc->finfo[finfo_indx].end_pos = list[i].iLettersUsed;
		trc->finfo[finfo_indx].string_handle=list[i].iPronOffset;
		finfo_indx = trc->finfo[finfo_indx].next;
    }
}

short search_cache_entry(ltrcache *trc, short npos, short ntree)
{
/* 
   finds whether or not at position npos the ltree number ntree was consulted 
   returns -1 if not found, otherwise the ltinfo index
*/
    short lptr;

    lptr=trc->ltfirst;

    while(lptr!=CACHENULLPTR)
    {
	if (trc->ltinfo[lptr].ltrienumber==ntree && 
	    trc->ltinfo[lptr].position==npos)
	{
	    // HELPME this is broken.....
	    move_to_top_of_ltinfo(trc,lptr);
	    return(lptr);
	}
	lptr=trc->ltinfo[lptr].next;
    }
    return(CACHENULLPTR);
}

int retrieve_cache_entry(ltrcache *trc, int ltinfo, int max_nseg, WORD_SEG_LIST* list)
{

/* returns number of entries in list.  If there are more than max_nseg entries, it returns -(the number needed)*/
    short fptr;
    
    int needed_word_segs=0;
    int cur_word_seg=0;
    int cur_string_pos=0;
    fptr=trc->ltinfo[ltinfo].foundinfoindex;
    
    //count the number or word segs needed 
    while(fptr!=CACHENULLPTR)
    {
	if ((trc->finfo[fptr].ruleno) & 0x80)
	{
	    fptr=trc->finfo[fptr].next;
	    continue;
	}
	needed_word_segs++;
	fptr=trc->finfo[fptr].next;
    }
    if (needed_word_segs>max_nseg)
	return(-needed_word_segs);

    
    fptr=trc->ltinfo[ltinfo].foundinfoindex;
    //actually copy the data 
    while(fptr!=CACHENULLPTR)
    {
	list[cur_word_seg].iLettersUsed=trc->finfo[fptr].end_pos;
	list[cur_word_seg].iRule=(trc->finfo[fptr].ruleno & 0x7F);// mask the high bit;
	cur_string_pos=0;
	list[cur_word_seg].iPronOffset=trc->finfo[fptr].string_handle;

	fptr=trc->finfo[fptr].next;
	cur_word_seg++;
    }
    return(cur_word_seg);
}


short add_cache_entry(ltrcache *trc, short npos, short ntree, int nseg, WORD_SEG_LIST* list)
{
/* 
   This function is called if for a position npos in a word, we have consulted the letter tree ntree
   and found an info with nseg parts, in list 

   If nseg is zero, only a ltinfo entry has to be generated with foundinfoindex set -1.
   
*/
    short num_records_needed;
    short ltinfo_ptr=CACHENULLPTR;
    short finfo_ptr=CACHENULLPTR;
    // count the number of records needed
    num_records_needed=num_finfo_records(nseg, list);

    // be sure there is space in ltinfo;
    ltinfo_ptr=create_ltinfo_space(trc,num_records_needed );

    if (ltinfo_ptr==CACHENULLPTR)
	return(CACHENULLPTR);
    
    if (num_records_needed>0)
    {
    //get the finfo records
    finfo_ptr= get_free_finfo(trc, num_records_needed);
    if (finfo_ptr==CACHENULLPTR)
    {
		add_entry_to_free_list(trc,ltinfo_ptr);
	//free ltinfo_ptr
	return(CACHENULLPTR);
    }
    // fill the finfo records
    fill_finfo_records(trc,nseg , list, finfo_ptr);
    // put the data into the ltinfo
    fill_ltinfo_entry(trc,ltinfo_ptr,ntree, npos, finfo_ptr);
    }
    else
    {
    // put the data into the ltinfo
    fill_ltinfo_entry(trc,ltinfo_ptr,ntree, npos, CACHENULLPTR);
    }
    add_entry_to_ltinfo(trc,ltinfo_ptr);
    return(0);
}

#if 0
WORD_SEG_LIST list1[1]={
    { 1,1,"foo4"}};
WORD_SEG_LIST list2[3]={
    { 2,2,"bar1"},
    { 4,3,"baz2"},
    { 6,4,"bla3"}};
WORD_SEG_LIST list3[1]={
    { 3,3,"speedy"}};
WORD_SEG_LIST list4[3]={
    { 4,3,"oopsie"},
    { 6,6,"mice"},
    { 8,8,"gonzales"}};


WORD_SEG_LIST junklist[5];
#endif
/*short search_cache_entry(ltrcache *trc, short npos, short ntree)
int retrieve_cache_entry(ltrcache *trc, int ltinfo, int max_nseg, WORD_SEG_LIST* list)
short add_cache_entry(ltrcache *trc, short npos, short ntree, int nseg, WORD_SEG_LIST* list)
*/
//int FindAllWordSegments(char *sWord, WORD_SEG_LIST *pWordSegList, int nMaxWordSegs, FILE *fp, int iDictOffset)

#ifdef _BIGENDIAN_
int lt_cache_search(ltrcache *trc,void *dict_file, unsigned char *sWord,short npos, short ntree, int dict_offset, int max_nseg,WORD_SEG_LIST *list,unsigned short cacheit)
#else
int lt_cache_search(ltrcache *trc,FILE *dict_file, unsigned char *sWord,short npos, short ntree, int dict_offset, int max_nseg,WORD_SEG_LIST *list,unsigned short cacheit)
#endif
{
// num_seg is only needed in this function because we dont have a real search function 
// num_seg will come from the actual searched data

    int res;
	int num_seg;
	int i;

    
    res=search_cache_entry(trc,npos,ntree);
    if (res==CACHENULLPTR)
    {

		num_seg=FindAllWordSegments(sWord+npos,list,max_nseg,dict_file,dict_offset);
		for (i=0;i<num_seg;i++)
		{
			list[i].iLettersUsed-=1;
		}
		if (cacheit)
		{
			res=add_cache_entry(trc,npos,ntree,num_seg,list);
			if (res!=CACHENULLPTR)
			{
				res=num_seg;
			}
		}
		else
		{
			res=num_seg;
		}
    }
    else
    {
	// we got data
		res=retrieve_cache_entry(trc,res,max_nseg,list);
    }
	if (res==CACHENULLPTR)
	{
		res=0;
	}
    return(res);
}

#if 0
int main(int argc, char *argv[])
{
    ltrcache trc;
    short ent;
    int i;
    int res=0;
    

    init_foundinfo(&trc,MAXFOUNDINFO,MAXTESTINFO);
    print_ltinfo(&trc);

    memcpy(junklist,list1,sizeof(list1));
    res=lt_cache_search(&trc,1,10,1,5,junklist);
    traverse_ltinfo(&trc);

    memcpy(junklist,list2,sizeof(list2));
    res=lt_cache_search(&trc,2,5,3,5,junklist);
    traverse_ltinfo(&trc);
    print_finfo(&trc);

    
    memcpy(junklist,list1,sizeof(list1));
    res=lt_cache_search(&trc,1,10,1,5,junklist);
    traverse_ltinfo(&trc);
    for (i=0;i<res;i++) {
	printf("result [%3i,%3i,%s]\n",junklist[i].iLettersUsed,junklist[i].iRule,junklist[i].sPron); }

    memcpy(junklist,list3,sizeof(list3));
    res=lt_cache_search(&trc,4,12,1,5,junklist);
    traverse_ltinfo(&trc);
    for (i=0;i<res;i++) {
	printf("result [%3i,%3i,%s]\n",junklist[i].iLettersUsed,junklist[i].iRule,junklist[i].sPron); }

    memcpy(junklist,list2,sizeof(list2));
    res=lt_cache_search(&trc,3,7,0,5,junklist);
    traverse_ltinfo(&trc);
    for (i=0;i<res;i++) {
	printf("result [%3i,%3i,%s]\n",junklist[i].iLettersUsed,junklist[i].iRule,junklist[i].sPron); }

    memcpy(junklist,list4,sizeof(list4));
    res=lt_cache_search(&trc,5,15,3,5,junklist);
    traverse_ltinfo(&trc);
    for (i=0;i<res;i++) {
	printf("result [%3i,%3i,%s]\n",junklist[i].iLettersUsed,junklist[i].iRule,junklist[i].sPron); }
        
    print_finfo(&trc);

    memcpy(junklist,list2,sizeof(list2));
    res=lt_cache_search(&trc,5,15,3,5,junklist);
    traverse_ltinfo(&trc);
    for (i=0;i<res;i++) {
	printf("result [%3i,%3i,%s]\n",junklist[i].iLettersUsed,junklist[i].iRule,junklist[i].sPron); }

    memcpy(junklist,list2,sizeof(list2));
    res=lt_cache_search(&trc,3,7,0,5,junklist);
    traverse_ltinfo(&trc);
    for (i=0;i<res;i++) {
	printf("result [%3i,%3i,%s]\n",junklist[i].iLettersUsed,junklist[i].iRule,junklist[i].sPron); }
        
    


//    ent = get_entry_from_free_ltlist(&trc);
//    fill_ltinfo_entry(&trc,ent, 1,1,11);
//    print_ltinfo(&trc); 
//    add_entry_to_ltinfo(&trc, ent);
//    print_ltinfo(&trc);

//    ent = get_entry_from_free_ltlist(&trc);
//    fill_ltinfo_entry(&trc,ent, 2,2,22);
//    add_entry_to_ltinfo(&trc, ent);
//    print_ltinfo(&trc);
 
//    ent = get_entry_from_free_ltlist(&trc);
//    fill_ltinfo_entry(&trc,ent, 3,3,33);
//    add_entry_to_ltinfo(&trc, ent);
//    print_ltinfo(&trc);

//    traverse_ltinfo(&trc);
//    move_to_top_of_ltinfo(&trc,1);
    
//    traverse_ltinfo(&trc);

//    ent = get_entry_from_free_ltlist(&trc);
//    fill_ltinfo_entry(&trc,ent, 4,4,44);
//    add_entry_to_ltinfo(&trc, ent);
//    traverse_ltinfo(&trc);

//    delete_last_ltinfo(&trc);


//    traverse_ltinfo(&trc);
    
//    delete_last_ltinfo(&trc);
//    traverse_ltinfo(&trc);

//    ent = get_entry_from_free_ltlist(&trc);
//    fill_ltinfo_entry(&trc,ent, 5,5,55);
//    add_entry_to_ltinfo(&trc, ent);
//    traverse_ltinfo(&trc);

}
#endif