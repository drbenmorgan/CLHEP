
#ifndef MODEA_HPP
#define MODEA_HPP

#if defined(NT_MSVCPP)
#pragma warning (disable: 4786)
#endif

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "ModeAT.hh"

typedef  HepPDT::ModeAT<DefaultConfig>  ModeA;

REGISTER_DECAY_MODE(ModeA,ModeA::Config)

#endif // #ifndef MODEA_HPP

/*
** Local Variables: --
** mode: c++ --
** c-file-style: "gnu" --
** tab-width: 2 --
** End: --
*/
