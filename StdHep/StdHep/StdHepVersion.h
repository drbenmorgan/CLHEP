/*   This holds the StdHep version so it can also be accessed by C */

#ifdef __cplusplus
extern "C" {
#endif

struct StdHepVer {
  char version[10];   	/* version numver */
  char date[20];     	/* date of this version */
} StdHepVersion;

#ifdef __cplusplus
}
#endif
