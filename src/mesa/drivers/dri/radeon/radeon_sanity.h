#ifndef RADEON_SANITY_H
#define RADEON_SANITY_H

#include "radeon_context.h"

extern int radeonSanityCmdBuffer( radeonContextPtr rmesa,
				  int nbox,
				  XF86DRIClipRectRec *boxes );

#endif
