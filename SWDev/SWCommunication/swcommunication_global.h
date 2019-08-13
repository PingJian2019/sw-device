#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SWCOMMUNICATION_LIB)
#  define SWCOMMUNICATION_EXPORT Q_DECL_EXPORT
# else
#  define SWCOMMUNICATION_EXPORT Q_DECL_IMPORT
# endif
#else
# define SWCOMMUNICATION_EXPORT
#endif
