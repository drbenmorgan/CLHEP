/*
Temporary holding space used by mcfio to allow combining collisions
*/
extern struct stdtmp_t {
double phept[NMXHEP][5];    /* 4-Momentum, mass */
double vhept[NMXHEP][4];    /* Vertex information */
int nevhept;		/* The event number */
int nhept;		/* The number of entries in this event */
int isthept[NMXHEP]; 	/* The Particle id */
int idhept[NMXHEP];      /* The particle id */
int jmohept[NMXHEP][2];    /* The position of the mother particle */
int jdahept[NMXHEP][2];    /* Position of the first daughter... */
} stdtmp_;

extern struct tmpev4_t {
  double eventweightt;			/* event weight */
  double alphaqedt; 			/* QED coupling alpha_em */
  double alphaqcdt;			/* QCD coupling alpha_s */
  double scalet[10]; 			/* Scale Q of the event */
  double spint[NMXHEP][3]; 		/* spin information */
  int    icolorflowt[NMXHEP][2]; 	/* (Anti-)Colour flow */
  int    idrupt;			/* ID, as given by LPRUP codes */
} tmpev4_;
