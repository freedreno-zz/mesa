/* File to perform the device-specfic initialization tasks typically
 * done in the X server.
 *
 * Here they are converted to run in the client (or perhaps a
 * standalone process), and to work with fbdev rather than the X
 * server infrastructure.
 */

/* Memory map the MMIO region.  Used during pre-init and by RADEONMapMem,
 * below
 */
static Bool RADEONMapMMIO(RADEONInfoPtr info)
{
    info->MMIO = fbdevHWMapMMIO();

    if (!info->MMIO) return FALSE;
    return TRUE;
}

/* Unmap the MMIO region.  Used during pre-init and by RADEONUnmapMem,
 * below
 */
static Bool RADEONUnmapMMIO(RADEONInfoPtr info)
{
    fbdevHWUnmapMMIO();
    info->MMIO = NULL;
    return TRUE;
}


/* Initialize the AGP state.  Request memory for use in AGP space, and
 * initialize the Radeon registers to point to that memory.
 */
static Bool RADEONDRIAgpInit(RADEONInfoPtr info)
{
    unsigned char *RADEONMMIO = info->MMIO;
    unsigned long  mode;
    unsigned int   vendor, device;
    int            ret;
    int            s, l;

    if (drmAgpAcquire(info->drmFD) < 0) {
	fprintf(stderr, "[agp] AGP not available\n");
	return FALSE;
    }
    
    /* Workaround for some hardware bugs */
    if (info->ChipFamily < CHIP_FAMILY_R200)
	OUTREG(RADEON_AGP_CNTL, INREG(RADEON_AGP_CNTL) | 0x000e0020);

    /* Modify the mode if the default mode is not appropriate for this
     * particular combination of graphics card and AGP chipset.
     */

    mode   = drmAgpGetMode(info->drmFD);	/* Default mode */
    vendor = drmAgpVendorId(info->drmFD);
    device = drmAgpDeviceId(info->drmFD);

    mode &= ~RADEON_AGP_MODE_MASK;
    switch (info->agpMode) {
    case 4:          mode |= RADEON_AGP_4X_MODE;
    case 2:          mode |= RADEON_AGP_2X_MODE;
    case 1: default: mode |= RADEON_AGP_1X_MODE;
    }

    
    /* Disable fast write for AMD 761 chipset, since they cause
     * lockups when enabled.
     */
    if ((vendor == PCI_VENDOR_AMD) &&
	(device == PCI_CHIP_AMD761)) {
	/* The combination of 761 with MOBILITY chips will lockup the
	 * system; however, currently there is no such a product on the
	 * market, so this is not yet a problem.
	 */
	if ((info->ChipFamily == CHIP_FAMILY_M6) ||
	    (info->ChipFamily == CHIP_FAMILY_M7) || 
	    (info->ChipFamily == CHIP_FAMILY_M9))
	    return FALSE;
    }
    else if (info->agpFastWrite) 
       mode |= RADEON_AGP_FW_MODE;

    fprintf(stderr,
	    "[agp] Mode 0x%08lx [AGP 0x%04x/0x%04x; Card 0x%04x/0x%04x]\n",
	    mode, vendor, device,
	    info->PciInfo->vendor,
	    info->PciInfo->chipType);

    if (drmAgpEnable(info->drmFD, mode) < 0) {
	fprintf(stderr, "[agp] AGP not enabled\n");
	drmAgpRelease(info->drmFD);
	return FALSE;
    }
    
    info->agpOffset = 0;

    if ((ret = drmAgpAlloc(info->drmFD, info->agpSize*1024*1024, 0, NULL,
			   &info->agpMemHandle)) < 0) {
	fprintf(stderr, "[agp] Out of memory (%d)\n", ret);
	drmAgpRelease(info->drmFD);
	return FALSE;
    }
    fprintf(stderr,
	    "[agp] %d kB allocated with handle 0x%08x\n",
	    info->agpSize*1024, info->agpMemHandle);
    
    if (drmAgpBind(info->drmFD,
		   info->agpMemHandle, info->agpOffset) < 0) {
	fprintf(stderr, "[agp] Could not bind\n");
	drmAgpFree(info->drmFD, info->agpMemHandle);
	drmAgpRelease(info->drmFD);
	return FALSE;
    }

				/* Initialize the CP ring buffer data */
    info->ringStart       = info->agpOffset;
    info->ringMapSize     = info->ringSize*1024*1024 + DRM_PAGE_SIZE;
    info->ringSizeLog2QW  = RADEONMinBits(info->ringSize*1024*1024/8)-1;

    info->ringReadOffset  = info->ringStart + info->ringMapSize;
    info->ringReadMapSize = DRM_PAGE_SIZE;

				/* Reserve space for vertex/indirect buffers */
    info->bufStart        = info->ringReadOffset + info->ringReadMapSize;
    info->bufMapSize      = info->bufSize*1024*1024;

				/* Reserve the rest for AGP textures */
    info->agpTexStart     = info->bufStart + info->bufMapSize;
    s = (info->agpSize*1024*1024 - info->agpTexStart);
    l = RADEONMinBits((s-1) / RADEON_NR_TEX_REGIONS);
    if (l < RADEON_LOG_TEX_GRANULARITY) l = RADEON_LOG_TEX_GRANULARITY;
    info->agpTexMapSize   = (s >> l) << l;
    info->log2AGPTexGran  = l;

    if (drmAddMap(info->drmFD, info->ringStart, info->ringMapSize,
		  DRM_AGP, DRM_READ_ONLY, &info->ringHandle) < 0) {
       fprintf(stderr,
	       "[agp] Could not add ring mapping\n");
       return FALSE;
    }
    fprintf(stderr,
	    "[agp] ring handle = 0x%08lx\n", info->ringHandle);
    
    if (drmMap(info->drmFD, info->ringHandle, info->ringMapSize,
	       (drmAddressPtr)&info->ring) < 0) {
	fprintf(stderr, "[agp] Could not map ring\n");
	return FALSE;
    }
    
    fprintf(stderr,
	    "[agp] Ring mapped at 0x%08lx\n",
	    (unsigned long)info->ring);
    
    if (drmAddMap(info->drmFD, info->ringReadOffset, info->ringReadMapSize,
		  DRM_AGP, DRM_READ_ONLY, &info->ringReadPtrHandle) < 0) {
       fprintf(stderr,
	       "[agp] Could not add ring read ptr mapping\n");
       return FALSE;
    }
    
    fprintf(stderr,
	    "[agp] ring read ptr handle = 0x%08lx\n",
	    info->ringReadPtrHandle);
    
    if (drmMap(info->drmFD, info->ringReadPtrHandle, info->ringReadMapSize,
	       (drmAddressPtr)&info->ringReadPtr) < 0) {
       fprintf(stderr,
	       "[agp] Could not map ring read ptr\n");
       return FALSE;
    }
    fprintf(stderr,
	    "[agp] Ring read ptr mapped at 0x%08lx\n",
	    (unsigned long)info->ringReadPtr);
    
    if (drmAddMap(info->drmFD, info->bufStart, info->bufMapSize,
		  DRM_AGP, 0, &info->bufHandle) < 0) {
       fprintf(stderr,
	       "[agp] Could not add vertex/indirect buffers mapping\n");
       return FALSE;
    }
    fprintf(stderr,
	    "[agp] vertex/indirect buffers handle = 0x%08lx\n",
	    info->bufHandle);
    
    if (drmMap(info->drmFD, info->bufHandle, info->bufMapSize,
	       (drmAddressPtr)&info->buf) < 0) {
       fprintf(stderr,
	       "[agp] Could not map vertex/indirect buffers\n");
       return FALSE;
    }
    fprintf(stderr,
	    "[agp] Vertex/indirect buffers mapped at 0x%08lx\n",
	    (unsigned long)info->buf);
    
    if (drmAddMap(info->drmFD, info->agpTexStart, info->agpTexMapSize,
		  DRM_AGP, 0, &info->agpTexHandle) < 0) {
       fprintf(stderr,
	       "[agp] Could not add AGP texture map mapping\n");
       return FALSE;
    }
    fprintf(stderr,
	    "[agp] AGP texture map handle = 0x%08lx\n",
	    info->agpTexHandle);
    
    if (drmMap(info->drmFD, info->agpTexHandle, info->agpTexMapSize,
	       (drmAddressPtr)&info->agpTex) < 0) {
       fprintf(stderr,
	       "[agp] Could not map AGP texture map\n");
       return FALSE;
    }
    fprintf(stderr,
	    "[agp] AGP Texture map mapped at 0x%08lx\n",
	    (unsigned long)info->agpTex);
    
    /* Initialize Radeon's AGP registers */
    /* Ring buffer is at AGP offset 0 */
    OUTREG(RADEON_AGP_BASE, info->ringHandle);

    return TRUE;
}


/* Add a map for the MMIO registers that will be accessed by any
 * DRI-based clients.
 */
static Bool RADEONDRIMapInit(RADEONInfoPtr info)
{
				/* Map registers */
    info->registerSize = RADEON_MMIOSIZE;
    if (drmAddMap(info->drmFD, info->MMIOAddr, info->registerSize,
		  DRM_REGISTERS, DRM_READ_ONLY, &info->registerHandle) < 0) {
	return FALSE;
    }
    fprintf(stderr,
	    "[drm] register handle = 0x%08lx\n", info->registerHandle);
    
    return TRUE;
}

/* Initialize the kernel data structures */
static int RADEONDRIKernelInit(RADEONInfoPtr info)
{
    int            cpp   = info->CurrentLayout.pixel_bytes;
    drmRadeonInit  drmInfo;

    memset(&drmInfo, 0, sizeof(drmRadeonInit));

    if ( (info->ChipFamily == CHIP_FAMILY_R200) ||
		 (info->ChipFamily == CHIP_FAMILY_RV250) ||
		 (info->ChipFamily == CHIP_FAMILY_M9) )
       drmInfo.func             = DRM_RADEON_INIT_R200_CP;
    else
       drmInfo.func             = DRM_RADEON_INIT_CP;

    drmInfo.sarea_priv_offset   = sizeof(XF86DRISAREARec);
    drmInfo.is_pci              = info->IsPCI;
    drmInfo.cp_mode             = info->CPMode;
    drmInfo.agp_size            = info->agpSize*1024*1024;
    drmInfo.ring_size           = info->ringSize*1024*1024;
    drmInfo.usec_timeout        = info->CPusecTimeout;

    drmInfo.fb_bpp              = info->CurrentLayout.pixel_code;
    drmInfo.depth_bpp           = info->CurrentLayout.pixel_code;

    drmInfo.front_offset        = info->frontOffset;
    drmInfo.front_pitch         = info->frontPitch * cpp;
    drmInfo.back_offset         = info->backOffset;
    drmInfo.back_pitch          = info->backPitch * cpp;
    drmInfo.depth_offset        = info->depthOffset;
    drmInfo.depth_pitch         = info->depthPitch * cpp;

    drmInfo.fb_offset           = info->LinearAddr;
    drmInfo.mmio_offset         = info->registerHandle;
    drmInfo.ring_offset         = info->ringHandle;
    drmInfo.ring_rptr_offset    = info->ringReadPtrHandle;
    drmInfo.buffers_offset      = info->bufHandle;
    drmInfo.agp_textures_offset = info->agpTexHandle;

    if (drmCommandWrite(info->drmFD, DRM_RADEON_CP_INIT,
			&drmInfo, sizeof(drmRadeonInit)) < 0)
	return FALSE;

    return TRUE;
}

static void RADEONDRIAgpHeapInit(RADEONInfoPtr info)
{
    drmRadeonMemInitHeap drmHeap;

    /* Start up the simple memory manager for agp space */
    if (info->drmMinor >= 6) {
	drmHeap.region = RADEON_MEM_REGION_AGP;
	drmHeap.start  = 0;
	drmHeap.size   = info->agpTexMapSize;
    
	if (drmCommandWrite(info->drmFD, DRM_RADEON_INIT_HEAP,
			    &drmHeap, sizeof(drmHeap))) {
	   fprintf(stderr,
		   "[drm] Failed to initialized agp heap manager\n");
	} else {
	   fprintf(stderr,
		   "[drm] Initialized kernel agp heap manager, %d\n",
		   info->agpTexMapSize);
	}
    } else {
       fprintf(stderr,
	       "[drm] Kernel module too old (1.%d) for agp heap manager\n",
	       info->drmMinor);
    }
}

/* Add a map for the vertex buffers that will be accessed by any
 * DRI-based clients.
 */
static Bool RADEONDRIBufInit(RADEONInfoPtr info )
{
   /* Initialize vertex buffers */
   info->bufNumBufs = drmAddBufs(info->drmFD,
				 info->bufMapSize / RADEON_BUFFER_SIZE,
				 RADEON_BUFFER_SIZE,
				 DRM_AGP_BUFFER,
				 info->bufStart);

   if (info->bufNumBufs <= 0) {
      fprintf(stderr,
	      "[drm] Could not create vertex/indirect buffers list\n");
      return FALSE;
   }
   fprintf(stderr,
	   "[drm] Added %d %d byte vertex/indirect buffers\n",
	   info->bufNumBufs, RADEON_BUFFER_SIZE);
   
   if (!(info->buffers = drmMapBufs(info->drmFD))) {
      fprintf(stderr,
	      "[drm] Failed to map vertex/indirect buffers list\n");
      return FALSE;
   }

   fprintf(stderr,
	   "[drm] Mapped %d vertex/indirect buffers\n",
	   info->buffers->count);
   
   return TRUE;
}

static void RADEONDRIIrqInit(RADEONInfoPtr info)
{
    if (!info->irq) {
	info->irq = drmGetInterruptFromBusID(
	    info->drmFD,
	    ((pciConfigPtr)info->PciInfo->thisCard)->busnum,
	    ((pciConfigPtr)info->PciInfo->thisCard)->devnum,
	    ((pciConfigPtr)info->PciInfo->thisCard)->funcnum);

	if ((drmCtlInstHandler(info->drmFD, info->irq)) != 0) {
	   fprintf(stderr,
		   "[drm] failure adding irq handler, "
		   "there is a device already using that irq\n"
		   "[drm] falling back to irq-free operation\n");
	   info->irq = 0;
	} else {
	    unsigned char *RADEONMMIO = info->MMIO;
	    info->gen_int_cntl = INREG( RADEON_GEN_INT_CNTL );
	}
    }

    if (info->irq)
       fprintf(stderr,
	       "[drm] dma control initialized, using IRQ %d\n",
	       info->irq);
}


#define RADEONCP_START(pScrn, info)					\
do {									\
} while (0)


/* Initialize the CP state, and start the CP (if used by the X server) */
static void RADEONDRICPInit(RADEONInfoPtr info)
{
				/* Turn on bus mastering */
    info->BusCntl &= ~RADEON_BUS_MASTER_DIS;

				/* Make sure the CP is on for the X server */
    int _ret = drmCommandNone(info->drmFD, DRM_RADEON_CP_START);
    if (_ret) {
       fprintf(stderr, "%s: CP start %d\n", __FUNCTION__, _ret);
    }
    info->CPStarted = TRUE;
}


/* Initialize the screen-specific data structures for the DRI and the
 * Radeon.  This is the main entry point to the device-specific
 * initialization code.  It calls device-independent DRI functions to
 * create the DRI data structures and initialize the DRI state.
 */
Bool RADEONDRIScreenInit(RADEONInfoPtr info)
{
    DRIInfoPtr     pDRIInfo;
    RADEONDRIPtr   pRADEONDRI;
    int            major, minor, patch;
    drmVersionPtr  version;

    /* Create the DRI data structure, and fill it in before calling the
     * DRIScreenInit().
     */
    if (!(pDRIInfo = DRICreateInfoRec())) return FALSE;

    info->pDRIInfo                       = pDRIInfo;
    pDRIInfo->drmDriverName              = RADEON_DRIVER_NAME;

    if (info->ChipFamily == CHIP_FAMILY_R200 ||
	info->ChipFamily == CHIP_FAMILY_RV250 ||
	info->ChipFamily == CHIP_FAMILY_M9)
       pDRIInfo->clientDriverName        = R200_DRIVER_NAME;
    else 
       pDRIInfo->clientDriverName        = RADEON_DRIVER_NAME;

    pDRIInfo->busIdString                = xalloc(64);
    sprintf(pDRIInfo->busIdString,
	    "PCI:%d:%d:%d",
	    info->PciInfo->bus,
	    info->PciInfo->device,
	    info->PciInfo->func);
    pDRIInfo->ddxDriverMajorVersion      = RADEON_VERSION_MAJOR;
    pDRIInfo->ddxDriverMinorVersion      = RADEON_VERSION_MINOR;
    pDRIInfo->ddxDriverPatchVersion      = RADEON_VERSION_PATCH;
    pDRIInfo->frameBufferPhysicalAddress = info->LinearAddr;
    pDRIInfo->frameBufferSize            = info->FbMapSize;
    pDRIInfo->frameBufferStride          = (pScrn->displayWidth *
					    info->CurrentLayout.pixel_bytes);
    pDRIInfo->ddxDrawableTableEntry      = RADEON_MAX_DRAWABLES;
    pDRIInfo->maxDrawableTableEntry      = (SAREA_MAX_DRAWABLES
					    < RADEON_MAX_DRAWABLES
					    ? SAREA_MAX_DRAWABLES
					    : RADEON_MAX_DRAWABLES);

    /* For now the mapping works by using a fixed size defined
     * in the SAREA header
     */
    if (sizeof(XF86DRISAREARec)+sizeof(RADEONSAREAPriv) > SAREA_MAX) {
	ErrorF("Data does not fit in SAREA\n");
	return FALSE;
    }
    pDRIInfo->SAREASize = SAREA_MAX;

    if (!(pRADEONDRI = (RADEONDRIPtr)xcalloc(sizeof(RADEONDRIRec),1))) {
	DRIDestroyInfoRec(info->pDRIInfo);
	info->pDRIInfo = NULL;
	return FALSE;
    }
    pDRIInfo->devPrivate     = pRADEONDRI;
    pDRIInfo->devPrivateSize = sizeof(RADEONDRIRec);
    pDRIInfo->contextSize    = sizeof(RADEONDRIContextRec);

    pDRIInfo->CreateContext  = RADEONCreateContext;
    pDRIInfo->DestroyContext = RADEONDestroyContext;
    pDRIInfo->SwapContext    = RADEONDRISwapContext;
    pDRIInfo->InitBuffers    = RADEONDRIInitBuffers;
    pDRIInfo->MoveBuffers    = RADEONDRIMoveBuffers;
    pDRIInfo->bufferRequests = DRI_ALL_WINDOWS;
    pDRIInfo->OpenFullScreen = RADEONDRIOpenFullScreen;
    pDRIInfo->CloseFullScreen = RADEONDRICloseFullScreen;
    pDRIInfo->TransitionTo2d = RADEONDRITransitionTo2d;
    pDRIInfo->TransitionTo3d = RADEONDRITransitionTo3d;
    pDRIInfo->TransitionSingleToMulti3D = RADEONDRITransitionSingleToMulti3d;
    pDRIInfo->TransitionMultiToSingle3D = RADEONDRITransitionMultiToSingle3d;

    pDRIInfo->createDummyCtx     = TRUE;
    pDRIInfo->createDummyCtxPriv = FALSE;

    if (!DRIScreenInit(pScreen, pDRIInfo, &info->drmFD)) {
       fprintf(stderr,
	       "[dri] DRIScreenInit failed.  Disabling DRI.\n");
       xfree(pDRIInfo->devPrivate);
       pDRIInfo->devPrivate = NULL;
       DRIDestroyInfoRec(pDRIInfo);
	pDRIInfo = NULL;
	return FALSE;
    }

    /* Check the DRM lib version.
     * drmGetLibVersion was not supported in version 1.0, so check for
     * symbol first to avoid possible crash or hang.
     */
    if (xf86LoaderCheckSymbol("drmGetLibVersion")) {
	version = drmGetLibVersion(info->drmFD);
    } else {
	/* drmlib version 1.0.0 didn't have the drmGetLibVersion
	 * entry point.  Fake it by allocating a version record
	 * via drmGetVersion and changing it to version 1.0.0.
	 */
	version = drmGetVersion(info->drmFD);
	version->version_major      = 1;
	version->version_minor      = 0;
	version->version_patchlevel = 0;
    }

    if (version) {
	if (version->version_major != 1 ||
	    version->version_minor < 1) {
	    /* incompatible drm library version */
	   fprintf(stderr,
		   "[dri] RADEONDRIScreenInit failed because of a "
		   "version mismatch.\n"
		   "[dri] libdrm.a module version is %d.%d.%d but "
		   "version 1.1.x is needed.\n"
		       "[dri] Disabling DRI.\n",
		       version->version_major,
		       version->version_minor,
		       version->version_patchlevel);
	    drmFreeVersion(version);
	    RADEONDRICloseScreen(info);
	    return FALSE;
	}
	drmFreeVersion(version);
    }

    /* Check the radeon DRM version */
    version = drmGetVersion(info->drmFD);
    if (version) {
	int req_minor, req_patch;

   	if ((info->ChipFamily == CHIP_FAMILY_R200) ||
		(info->ChipFamily == CHIP_FAMILY_RV250) ||
		(info->ChipFamily == CHIP_FAMILY_M9)) {
	    req_minor = 5;
	    req_patch = 0;	
	} else {
#if X_BYTE_ORDER == X_LITTLE_ENDIAN
	    req_minor = 1;
	    req_patch = 0;
#else
	    req_minor = 2;
	    req_patch = 1;	     
#endif
	}

	if (version->version_major != 1 ||
	    version->version_minor < req_minor ||
	    (version->version_minor == req_minor && 
	     version->version_patchlevel < req_patch)) {
	    /* Incompatible drm version */
	   fprintf(stderr,
		   "[dri] RADEONDRIScreenInit failed because of a version "
		   "mismatch.\n"
		   "[dri] radeon.o kernel module version is %d.%d.%d "
		   "but version 1.%d.%d or newer is needed.\n"
		       "[dri] Disabling DRI.\n",
		       version->version_major,
		       version->version_minor,
		       version->version_patchlevel,
		       req_minor,
		       req_patch);
	    drmFreeVersion(version);
	    RADEONDRICloseScreen(info);
	    return FALSE;
	}

	if (version->version_minor < 3) {
	   fprintf(stderr,
		   "[dri] Some DRI features disabled because of version "
		   "mismatch.\n"
		   "[dri] radeon.o kernel module version is %d.%d.%d but "
		   "1.3.1 or later is preferred.\n",
		       version->version_major,
		       version->version_minor,
		       version->version_patchlevel);
	}
	info->drmMinor = version->version_minor;
	drmFreeVersion(version);
    }

				/* Initialize AGP */
    if (!info->IsPCI && !RADEONDRIAgpInit(info)) {
	RADEONDRICloseScreen(info);
	return FALSE;
    }

				/* Initialize PCI */
    if (info->IsPCI) {
	fprintf(stderr, "[dri] PCI cards not yet "
		"supported.  Disabling DRI.\n");
	RADEONDRICloseScreen(info);
	return FALSE;
    }

				/* DRIScreenInit doesn't add all the
				 * common mappings.  Add additional
				 * mappings here.
				 */
    if (!RADEONDRIMapInit(info)) {
	RADEONDRICloseScreen(info);
	return FALSE;
    }

    
    return TRUE;
}

/* Finish initializing the device-dependent DRI state, and call
 * DRIFinishScreenInit() to complete the device-independent DRI
 * initialization.
 */
Bool RADEONDRIFinishScreenInit(RADEONInfoPtr info)
{
    RADEONSAREAPrivPtr  pSAREAPriv;
    RADEONDRIPtr        pRADEONDRI;

    info->pDRIInfo->driverSwapMethod = DRI_HIDE_X_CONTEXT;
    /* info->pDRIInfo->driverSwapMethod = DRI_SERVER_SWAP; */

    /* NOTE: DRIFinishScreenInit must be called before *DRIKernelInit
     * because *DRIKernelInit requires that the hardware lock is held by
     * the X server, and the first time the hardware lock is grabbed is
     * in DRIFinishScreenInit.
     */
    if (!DRIFinishScreenInit(pScreen)) {
	RADEONDRICloseScreen(pScreen);
	return FALSE;
    }

    /* Initialize the kernel data structures */
    if (!RADEONDRIKernelInit(info, pScreen)) {
	RADEONDRICloseScreen(pScreen);
	return FALSE;
    }

    /* Initialize the vertex buffers list */
    if (!RADEONDRIBufInit(info, pScreen)) {
	RADEONDRICloseScreen(pScreen);
	return FALSE;
    }

    /* Initialize IRQ */
    RADEONDRIIrqInit(info, pScreen);

    /* Initialize kernel agp memory manager */
    RADEONDRIAgpHeapInit(info, pScreen);

    /* Initialize and start the CP if required */
    RADEONDRICPInit(pScrn);

    /* Initialize the SAREA private data structure */
    pSAREAPriv = (RADEONSAREAPrivPtr)DRIGetSAREAPrivate(pScreen);
    memset(pSAREAPriv, 0, sizeof(*pSAREAPriv));

    pRADEONDRI                    = (RADEONDRIPtr)info->pDRIInfo->devPrivate;

    pRADEONDRI->deviceID          = info->Chipset;
    pRADEONDRI->width             = pScrn->virtualX;
    pRADEONDRI->height            = pScrn->virtualY;
    pRADEONDRI->depth             = pScrn->depth;
    pRADEONDRI->bpp               = pScrn->bitsPerPixel;

    pRADEONDRI->IsPCI             = info->IsPCI;
    pRADEONDRI->AGPMode           = info->agpMode;

    pRADEONDRI->frontOffset       = info->frontOffset;
    pRADEONDRI->frontPitch        = info->frontPitch;
    pRADEONDRI->backOffset        = info->backOffset;
    pRADEONDRI->backPitch         = info->backPitch;
    pRADEONDRI->depthOffset       = info->depthOffset;
    pRADEONDRI->depthPitch        = info->depthPitch;
    pRADEONDRI->textureOffset     = info->textureOffset;
    pRADEONDRI->textureSize       = info->textureSize;
    pRADEONDRI->log2TexGran       = info->log2TexGran;

    pRADEONDRI->registerHandle    = info->registerHandle;
    pRADEONDRI->registerSize      = info->registerSize;

    pRADEONDRI->statusHandle      = info->ringReadPtrHandle;
    pRADEONDRI->statusSize        = info->ringReadMapSize;

    pRADEONDRI->agpTexHandle      = info->agpTexHandle;
    pRADEONDRI->agpTexMapSize     = info->agpTexMapSize;
    pRADEONDRI->log2AGPTexGran    = info->log2AGPTexGran;
    pRADEONDRI->agpTexOffset      = info->agpTexStart;

    pRADEONDRI->sarea_priv_offset = sizeof(XF86DRISAREARec);

    return TRUE;
}

/* The screen is being closed, so clean up any state and free any
 * resources used by the DRI.
 */
void RADEONDRICloseScreen(ScreenPtr pScreen)
{
    ScrnInfoPtr    pScrn = xf86Screens[pScreen->myNum];
    RADEONInfoPtr  info  = RADEONPTR(pScrn);
    drmRadeonInit  drmInfo;
    RING_LOCALS;

				/* Stop the CP */
    if (info->directRenderingEnabled) {
	RADEONCP_STOP(pScrn, info);
    }

    if (info->irq) {
	drmCtlUninstHandler(info->drmFD);
	info->irq = 0;
    }

				/* De-allocate vertex buffers */
    if (info->buffers) {
	drmUnmapBufs(info->buffers);
	info->buffers = NULL;
    }

				/* De-allocate all kernel resources */
    memset(&drmInfo, 0, sizeof(drmRadeonInit));
    drmInfo.func = DRM_RADEON_CLEANUP_CP;
    drmCommandWrite(info->drmFD, DRM_RADEON_CP_INIT,
		    &drmInfo, sizeof(drmRadeonInit));

				/* De-allocate all AGP resources */
    if (info->agpTex) {
	drmUnmap(info->agpTex, info->agpTexMapSize);
	info->agpTex = NULL;
    }
    if (info->buf) {
	drmUnmap(info->buf, info->bufMapSize);
	info->buf = NULL;
    }
    if (info->ringReadPtr) {
	drmUnmap(info->ringReadPtr, info->ringReadMapSize);
	info->ringReadPtr = NULL;
    }
    if (info->ring) {
	drmUnmap(info->ring, info->ringMapSize);
	info->ring = NULL;
    }
    if (info->agpMemHandle) {
	drmAgpUnbind(info->drmFD, info->agpMemHandle);
	drmAgpFree(info->drmFD, info->agpMemHandle);
	info->agpMemHandle = 0;
	drmAgpRelease(info->drmFD);
    }
    if (info->pciMemHandle) {
	drmScatterGatherFree(info->drmFD, info->pciMemHandle);
	info->pciMemHandle = 0;
    }

				/* De-allocate all DRI resources */
    DRICloseScreen(pScreen);

				/* De-allocate all DRI data structures */
    if (info->pDRIInfo) {
	if (info->pDRIInfo->devPrivate) {
	    xfree(info->pDRIInfo->devPrivate);
	    info->pDRIInfo->devPrivate = NULL;
	}
	DRIDestroyInfoRec(info->pDRIInfo);
	info->pDRIInfo = NULL;
    }
    if (info->pVisualConfigs) {
	xfree(info->pVisualConfigs);
	info->pVisualConfigs = NULL;
    }
    if (info->pVisualConfigsPriv) {
	xfree(info->pVisualConfigsPriv);
	info->pVisualConfigsPriv = NULL;
    }
}



