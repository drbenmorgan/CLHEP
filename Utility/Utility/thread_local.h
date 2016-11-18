#ifndef CLHEP_THREAD_LOCAL_H
#define CLHEP_THREAD_LOCAL_H

// ======================================================================
//
// Use thread_local when the compiler declares it uses the C++11 standard
//
// ======================================================================
#ifdef CLHEP_SINGLE_THREAD
  #define CLHEP_THREAD_LOCAL
#else
  #if __cplusplus >= 201103L

    #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 7)
      #define CLHEP_THREAD_LOCAL thread_local
    #elif __clang__
      #if __has_feature(cxx_thread_local)
	#define CLHEP_THREAD_LOCAL thread_local
      #else
	#define CLHEP_THREAD_LOCAL
      #endif
    #else
      #define CLHEP_THREAD_LOCAL
    #endif

  #else
    #define CLHEP_THREAD_LOCAL
  #endif
#endif

#endif // CLHEP_THREAD_LOCAL_H
