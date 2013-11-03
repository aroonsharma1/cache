/*
 * 
 * cache.c
 * 
 * Donald Yeung
 */


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "cache.h"
#include "main.h"

/* cache configuration parameters */
static int cache_split = 0;
static int cache_usize = DEFAULT_CACHE_SIZE;
static int cache_isize = DEFAULT_CACHE_SIZE; 
static int cache_dsize = DEFAULT_CACHE_SIZE;
static int cache_block_size = DEFAULT_CACHE_BLOCK_SIZE;
static int words_per_block = DEFAULT_CACHE_BLOCK_SIZE / WORD_SIZE;
static int cache_assoc = DEFAULT_CACHE_ASSOC;
static int cache_writeback = DEFAULT_CACHE_WRITEBACK;
static int cache_writealloc = DEFAULT_CACHE_WRITEALLOC;

/* cache model data structures */
static Pcache icache;
static Pcache dcache;
static cache c1;
static cache c2;
static cache_stat cache_stat_inst;	//Icaches statistics
static cache_stat cache_stat_data;	//Dcache statistics

/************************************************************/
void set_cache_param(param, value)
  int param;
  int value;
{

  switch (param) {
  case CACHE_PARAM_BLOCK_SIZE:
    cache_block_size = value;
    words_per_block = value / WORD_SIZE;
    break;
  case CACHE_PARAM_USIZE:
    cache_split = FALSE;
    cache_usize = value;
    break;
  case CACHE_PARAM_ISIZE:
    cache_split = TRUE;
    cache_isize = value;
    break;
  case CACHE_PARAM_DSIZE:
    cache_split = TRUE;
    cache_dsize = value;
    break;
  case CACHE_PARAM_ASSOC:
    cache_assoc = value;
    break;
  case CACHE_PARAM_WRITEBACK:
    cache_writeback = TRUE;
    break;
  case CACHE_PARAM_WRITETHROUGH:
    cache_writeback = FALSE;
    break;
  case CACHE_PARAM_WRITEALLOC:
    cache_writealloc = TRUE;
    break;
  case CACHE_PARAM_NOWRITEALLOC:
    cache_writealloc = FALSE;
    break;
  default:
    printf("error set_cache_param: bad parameter value\n");
    exit(-1);
  }

}
/************************************************************/

/************************************************************/
void init_cache()
{	
  /* initialize the cache, and cache statistics data structures */
	//unified cache
	if(cache_split == 0) {
		c1.size = cache_usize/4;	
		c1.associativity = cache_assoc;
		c1.n_sets = cache_usize/cache_block_size/cache_assoc;
		c1.index_mask = (c1.n_sets-1) << LOG2(cache_block_size);
		c1.index_mask_offset = LOG2(cache_block_size);	
		
		//allocate the array of cache line pointers
		c1.LRU_head = (Pcache_line *)malloc(sizeof(Pcache_line)*c1.n_sets);
		c1.LRU_tail = (Pcache_line *)malloc(sizeof(Pcache_line)*c1.n_sets);
		c1.set_contents = (int *)malloc(sizeof(int)*c1.n_sets);
		int i;
		//allocate each cache line in the pointer array
		for(i = 0; i < c1.n_sets; i++) {
			c1.LRU_head[i] = NULL;
			c1.LRU_tail[i] = NULL;
			c1.set_contents[i] = 0;
		}
	}
	//split cache
	else {
		//I-cache initialization
		c1.size = cache_isize/4;
		c1.associativity = cache_assoc;
		c1.n_sets = cache_isize/cache_block_size/cache_assoc;
		c1.index_mask = (c1.n_sets-1) << LOG2(cache_block_size);
		c1.index_mask_offset = LOG2(cache_block_size);
		
		//allocate the array of cache line pointers
		c1.LRU_head = (Pcache_line *)malloc(sizeof(Pcache_line)*c1.n_sets);
		c1.LRU_tail = (Pcache_line *)malloc(sizeof(Pcache_line)*c1.n_sets);
		c1.set_contents = (int *)malloc(sizeof(int)*c1.n_sets);
		int i;
		//allocate each cache line in the pointer array
		for(i = 0; i < c1.n_sets; i++) {
			c1.LRU_head[i] = NULL;
			c1.LRU_tail[i] = NULL;
			c1.set_contents[i] = 0;
		}
		
		//D-cache initialization
		c2.size = cache_dsize/4;
		c2.associativity = cache_assoc;
		c2.n_sets = cache_dsize/cache_block_size/cache_assoc;
		c2.index_mask = (c2.n_sets-1) << LOG2(cache_block_size);
		c2.index_mask_offset = LOG2(cache_block_size);
		
		//allocate the array of cache line pointers
		c2.LRU_head = (Pcache_line *)malloc(sizeof(Pcache_line)*c2.n_sets);
		c2.LRU_tail = (Pcache_line *)malloc(sizeof(Pcache_line)*c2.n_sets);
		c2.set_contents = (int *)malloc(sizeof(int)*c2.n_sets);
		//allocate each cache line in the pointer array
		for(i = 0; i < c2.n_sets; i++) {
			c2.LRU_head[i] = NULL;
			c2.LRU_tail[i] = NULL;
			c2.set_contents[i] = 0;
		}
	}
}
/************************************************************/

/************************************************************/
void perform_access(addr, access_type)
  unsigned addr, access_type;
{
  /* handle an access to the cache */
	//unified cache
	if(cache_split == FALSE) {
		access_to_cache(c1, addr, access_type);
	}
	//split cache
	else {
		if(access_type == TRACE_DATA_LOAD || access_type == TRACE_DATA_STORE) {
			access_to_cache(c2, addr, access_type);
		}
		else if(access_type == TRACE_INST_LOAD) {
			access_to_cache(c1, addr, access_type);
		}
	}
}
/************************************************************/

/************************************************************/
void flush()
{
  /* flush the cache */
	int i;
	
	//flush I-cache
	for(i = 0; i < c1.n_sets; i++) {
		Pcache_line current_line;
		if(c1.LRU_head[i] != NULL) {
			for(current_line = c1.LRU_head[i]; current_line != c1.LRU_tail[i]->LRU_next; current_line = current_line->LRU_next) {
				if(current_line != NULL && current_line->dirty == TRUE) {
					cache_stat_inst.copies_back += cache_block_size/4;
				}
			}
		}
	}
	
	//flush D-cache
	for(i = 0; i < c2.n_sets; i++) {
		Pcache_line current_line;
		if(c2.LRU_head[i] != NULL) {
			for(current_line = c2.LRU_head[i]; current_line != c2.LRU_tail[i]->LRU_next; current_line = current_line->LRU_next) {
				if(current_line != NULL && current_line->dirty == TRUE) {
					cache_stat_inst.copies_back += cache_block_size/4;
				}
			}
		}
	}
}
/************************************************************/

/************************************************************/
void delete(head, tail, item)
  Pcache_line *head, *tail;
  Pcache_line item;
{
  if (item->LRU_prev) {
    item->LRU_prev->LRU_next = item->LRU_next;
  } else {
    /* item at head */
    *head = item->LRU_next;
  }

  if (item->LRU_next) {
    item->LRU_next->LRU_prev = item->LRU_prev;
  } else {
    /* item at tail */
    *tail = item->LRU_prev;
  }
}
/************************************************************/

/************************************************************/
/* inserts at the head of the list */
void insert(head, tail, item)
  Pcache_line *head, *tail;
  Pcache_line item;
{
  item->LRU_next = *head;
  item->LRU_prev = (Pcache_line)NULL;

  if (item->LRU_next)
    item->LRU_next->LRU_prev = item;
  else
    *tail = item;

  *head = item;
}
/************************************************************/

/************************************************************/
void dump_settings()
{
  printf("Cache Settings:\n");
  if (cache_split) {
    printf("\tSplit I- D-cache\n");
    printf("\tI-cache size: \t%d\n", cache_isize);
    printf("\tD-cache size: \t%d\n", cache_dsize);
  } else {
    printf("\tUnified I- D-cache\n");
    printf("\tSize: \t%d\n", cache_usize);
  }
  printf("\tAssociativity: \t%d\n", cache_assoc);
  printf("\tBlock size: \t%d\n", cache_block_size);
  printf("\tWrite policy: \t%s\n", 
	 cache_writeback ? "WRITE BACK" : "WRITE THROUGH");
  printf("\tAllocation policy: \t%s\n",
	 cache_writealloc ? "WRITE ALLOCATE" : "WRITE NO ALLOCATE");
}
/************************************************************/

/************************************************************/
void print_stats()
{
  printf("*** CACHE STATISTICS ***\n");
  printf("  INSTRUCTIONS\n");
  printf("  accesses:  %d\n", cache_stat_inst.accesses);
  printf("  misses:    %d\n", cache_stat_inst.misses);
  printf("  miss rate: %f\n", 
	 (float)cache_stat_inst.misses / (float)cache_stat_inst.accesses);
  printf("  replace:   %d\n", cache_stat_inst.replacements);

  printf("  DATA\n");
  printf("  accesses:  %d\n", cache_stat_data.accesses);
  printf("  misses:    %d\n", cache_stat_data.misses);
  printf("  miss rate: %f\n", 
	 (float)cache_stat_data.misses / (float)cache_stat_data.accesses);
  printf("  replace:   %d\n", cache_stat_data.replacements);

  printf("  TRAFFIC (in words)\n");
  printf("  demand fetch:  %d\n", cache_stat_inst.demand_fetches + 
	 cache_stat_data.demand_fetches);
  printf("  copies back:   %d\n", cache_stat_inst.copies_back +
	 cache_stat_data.copies_back);
}
/************************************************************/
void print_cache() {
	int i;
	Pcache_line line;
	for(i = 0; i < c1.n_sets; i++) {
		for(line = c1.LRU_head[i]; line != c1.LRU_tail[i]; line = line->LRU_next) {
			printf("%d ", line->tag);
		}
		printf("\n");
	}
	printf("num_sets = %d\n", i);
}
/************************************************************/
void print_set_contents() {
	int i;
	for(i = 0; i < c1.n_sets; i++) {
		printf("%d\n", c1.set_contents[i]);
	}
}
/************************************************************/
//helper function to be used in perform_access()
void access_to_cache(cache c, unsigned addr, unsigned access_type) {
	unsigned int index = (addr & c.index_mask) >> c.index_mask_offset;
	//printf("index = %d\n", index);
	unsigned tag = addr >> (LOG2(c.n_sets) + LOG2(cache_block_size)); 

	if(c.LRU_head[index] == NULL) {
		//compulsory miss (empty cache set)
		Pcache_line line = malloc(sizeof(cache_line));
		line->tag = tag;
		if(access_type == TRACE_DATA_LOAD || access_type == TRACE_DATA_STORE) {
			cache_stat_data.accesses++;
			cache_stat_data.misses++;
			if(cache_writealloc == TRUE || access_type != TRACE_DATA_STORE) {
				cache_stat_data.demand_fetches += cache_block_size/4;				
			}
			
			if(access_type == TRACE_DATA_STORE && cache_writealloc == TRUE) {
				if(cache_writeback == TRUE) {
					line->dirty = TRUE;					
				}
				else {
					//if write through, then copy back one word
					cache_stat_data.copies_back++;
				}
			}
			else if(access_type == TRACE_DATA_STORE && cache_writealloc == FALSE){
				cache_stat_data.copies_back++;				
			}
		}
		else if(access_type == TRACE_INST_LOAD) {
			cache_stat_inst.accesses++;
			cache_stat_inst.misses++;
			if(cache_writealloc == TRUE || access_type != TRACE_DATA_STORE) {
				cache_stat_inst.demand_fetches += cache_block_size/4;				
			}
		}
		if(cache_writealloc == TRUE || access_type != TRACE_DATA_STORE) {
			insert(&c.LRU_head[index], &c.LRU_tail[index], line);			
			c.set_contents[index]++;
		}
	}
	else {
		//check for cache hit
		Pcache_line current_line;
		for(current_line = c.LRU_head[index]; current_line != c.LRU_tail[index]->LRU_next; current_line = current_line->LRU_next) {
			if(current_line->tag == tag) {
		        if(access_type == TRACE_DATA_LOAD || access_type == TRACE_DATA_STORE) {
		        	cache_stat_data.accesses++;
		            if(access_type == TRACE_DATA_STORE) {
						if(cache_writeback == TRUE) {
			            	current_line->dirty = TRUE;							
						}
						else {
							//if write through, then copy back one word
							cache_stat_data.copies_back++;
						}
		            }
		        }
		        else if(access_type == TRACE_INST_LOAD) {
		            cache_stat_inst.accesses++;
		        }
				Pcache_line line = current_line;
				delete(&c.LRU_head[index], &c.LRU_tail[index], current_line);
				insert(&c.LRU_head[index], &c.LRU_tail[index], line);	
				return;
			}
		}
		//cache miss
		if(c.set_contents[index] < cache_assoc) {
			//non-full cache set
			Pcache_line line = malloc(sizeof(cache_line));
			line->tag = tag;
			if(access_type == TRACE_DATA_LOAD || access_type == TRACE_DATA_STORE) {
				cache_stat_data.accesses++;
				cache_stat_data.misses++;
				if(cache_writealloc == TRUE || access_type != TRACE_DATA_STORE) {
					cache_stat_data.demand_fetches += cache_block_size/4;									
				}
				
				if(access_type == TRACE_DATA_STORE && cache_writealloc == TRUE) {
					if(cache_writeback == TRUE) {
						line->dirty = TRUE;						
					}
					else {
						//if write through, then copy back one word
						cache_stat_data.copies_back++;
					}
				}
				else if(access_type == TRACE_DATA_STORE && cache_writealloc == FALSE){
					cache_stat_data.copies_back++;
				}
			}
			else if(access_type == TRACE_INST_LOAD) {
				cache_stat_inst.accesses++;
				cache_stat_inst.misses++;
				if(cache_writealloc == TRUE || access_type != TRACE_DATA_STORE) {
					cache_stat_inst.demand_fetches += cache_block_size/4;
				}				
			}
			
			if(cache_writealloc == TRUE || access_type != TRACE_DATA_STORE) {
				insert(&c.LRU_head[index], &c.LRU_tail[index], line);	
				c.set_contents[index]++;	
			}
		}
		else {
			//cache miss and eviction
			
			Pcache_line line = malloc(sizeof(cache_line));
			line->dirty = FALSE;
			line->tag = tag;
	
			if(access_type == TRACE_DATA_LOAD || access_type == TRACE_DATA_STORE) {
				cache_stat_data.accesses++;
				cache_stat_data.misses++;
				if(cache_writealloc == TRUE || access_type != TRACE_DATA_STORE) {
					cache_stat_data.replacements++;
					cache_stat_data.demand_fetches += cache_block_size/4;	
				}	
				
				if(access_type == TRACE_DATA_STORE && cache_writealloc == TRUE) {
					if(cache_writeback == TRUE) {
						line->dirty = TRUE;						
					}
					else {
						//if write through, then copy back one word
						cache_stat_data.copies_back++;
					}
				}
				else if(access_type == TRACE_DATA_STORE && cache_writealloc == FALSE){
					cache_stat_data.copies_back++;					
				}
			}
			else if(access_type == TRACE_INST_LOAD) {
				cache_stat_inst.accesses++;
				cache_stat_inst.misses++;
				if(cache_writealloc == TRUE || access_type != TRACE_DATA_STORE) {
					cache_stat_inst.replacements++;
					cache_stat_inst.demand_fetches += cache_block_size/4;	
				}				
			}
			if(cache_writealloc == TRUE || access_type != TRACE_DATA_STORE) {
				if(c.LRU_tail[index]->dirty == TRUE && (access_type == TRACE_DATA_LOAD || access_type == TRACE_DATA_STORE)) {
					cache_stat_data.copies_back += cache_block_size/4;
				}
				else if(c.LRU_tail[index]->dirty == TRUE && access_type == TRACE_INST_LOAD) {
					cache_stat_inst.copies_back += cache_block_size/4;
				}
				
				delete(&c.LRU_head[index], &c.LRU_tail[index], c.LRU_tail[index]);
				insert(&c.LRU_head[index], &c.LRU_tail[index], line);
			}
		}
	}
}