#define RFI_NUMHARMSUM 4
#define RFI_NUMBETWEEN 2
#define RFI_LOBIN      5
#define RFI_FRACTERROR 0.002
#define NUM_RFI_VECT   30

#define GET_BIT(c, n) (*(c+(n>>3)) >> (7-(n&7)) & 1)
#define SET_BIT(c, n) (*(c+(n>>3)) |= 1 << (7-(n&7)))
#define UNSET_BIT(c, n) (*(c+(n>>3)) &= ~(1 << (7-(n&7))))

typedef enum {
  GOOD, USER, POW, AVG, VAR
} mask_flags;

typedef struct RFI {
  float freq_avg;   /* Average frequency of detection (Hz)  */
  float freq_var;   /* Variance of the measured frequencies */
  float sigma_avg;  /* True significance (including N)      */
  int numobs;       /* Number of times the RFI was detected */
  unsigned char *times; /* Bit array showing 1 where seen   */
  unsigned char *chans; /* Bit array showing 1 where seen   */
} rfi;

rfi *new_rfi(int numchan, int numint);
/* Create an rfi structure */

void write_rfi(FILE *outfile, rfi *outrfi, 
	       int numchan, int numint);
/* Write the contents of an rfi structure to a file */

void read_rfi(FILE *infile, rfi *inrfi, 
	      int numchan, int numint);
/* Read the contents of an rfi structure to a file */

void free_rfi(rfi oldrfi);
/* Free an rfi structure and its contents */

rfi *rfi_vector(rfi *rfivect, int numchan, int numint, 
		int oldnum, int newnum);
/* Create or reallocate an rfi_vector */

void free_rfi_vector(rfi *rfivect, int numrfi);
/* Free an rfi vector and its contents */

void update_rfi(rfi *oldrfi, float freq, float sigma, 
		int channel, int interval);
/* Updates an rfi structure with a new detection */

int find_rfi(rfi *rfivect, int numrfi, 
	     double freq, double fract_error);
/* Try to find a birdie in an rfi ector.  Compare all */
/* currently known birdies with the new freq.  If it  */
/* finds one with a freq within fractional error, it  */
/* returns the number of the birdie -- otherwise, -1. */

int compare_rfi(void *ca, void *cb);
/*  Used as compare function for qsort() */
