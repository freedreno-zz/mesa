/* File to perform the device-specfic initialization tasks typically
 * done in the X server.
 *
 * Here they are converted to run in the client (or perhaps a
 * standalone process), and to work with fbdev rather than the X
 * server infrastructure.
 */


/* Compute log base 2 of val */
static int RADEONMinBits(int val)
{
    int  bits;

    if (!val) return 1;
    for (bits = 0; val; val >>= 1, ++bits);
    return bits;
}

/* Initialize the AGP state.  Request memory for use in AGP space, and
 * initialize the Radeon registers to point to that memory.
 */
static GLboolean RADEONDRIAgpInit(RADEONInfoPtr info)
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
       fprintf(stderr, "[agp] Could not add ring mapping\n");
       return FALSE;
    }
    fprintf(stderr, "[agp] ring handle = 0x%08lx\n", info->ringHandle);
    
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
static GLboolean RADEONDRIMapInit(RADEONInfoPtr info)
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

    /* This is the struct passed to the kernel module for its initialization */
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
static GLboolean RADEONDRIBufInit(RADEONInfoPtr info )
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
	    info->PciInfo->bus,
	    info->PciInfo->device,
	    info->PciInfo->func);

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
static GLboolean RADEONDRIScreenInit(MiniGLXDisplayRec *dpy, RADEONInfoPtr info)
{
    DRIInfoPtr     pDRIInfo;
    RADEONDRIPtr   pRADEONDRI;
    int            major, minor, patch;
    drmVersionPtr  version;


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
	    req_minor = 3;
	    req_patch = 0;	     
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

	info->drmMinor = version->version_minor;
	drmFreeVersion(version);
    }

    /* Initialize AGP */
    if (!RADEONDRIAgpInit(info)) {
	RADEONDRICloseScreen(info);
	return FALSE;
    }


    /* DRIScreenInit doesn't add all the common mappings.  Add
     * additional mappings here.
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
static GLboolean RADEONDRIFinishScreenInit(MiniGLXDisplayRec *dpy, RADEONInfoPtr info)
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
    if (!DRIFinishScreenInit()) {
	RADEONDRICloseScreen(info);
	return FALSE;
    }

    /* Initialize the kernel data structures */
    if (!RADEONDRIKernelInit(info)) {
	RADEONDRICloseScreen(info);
	return FALSE;
    }

    /* Initialize the vertex buffers list */
    if (!RADEONDRIBufInit(info)) {
	RADEONDRICloseScreen(info);
	return FALSE;
    }

    /* Initialize IRQ */
    RADEONDRIIrqInit(info);

    /* Initialize kernel agp memory manager */
    RADEONDRIAgpHeapInit(info);

    /* Initialize and start the CP if required */
    RADEONDRICPInit();

    /* Initialize the SAREA private data structure */
    pSAREAPriv = (RADEONSAREAPrivPtr)DRIGetSAREAPrivate();
    memset(pSAREAPriv, 0, sizeof(*pSAREAPriv));

    
    /* This is the struct passed to radeon_dri.so for its initialization */
    pRADEONDRI                    = (RADEONDRIPtr)info->pDRIInfo->devPrivate;
    pRADEONDRI->deviceID          = info->Chipset;
    pRADEONDRI->width             = dpy->VarInfo.xres_virtual;
    pRADEONDRI->height            = dpy->VarInfo.yres_virtual;
    pRADEONDRI->depth             = dpy->bpp; /* XXX: was depth */
    pRADEONDRI->bpp               = dpy->bpp;
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
static void RADEONDRICloseScreen( MiniGLXDisplayRec *dpy, RADEONInfoPtr info )
{
    drmRadeonInit  drmInfo;

				/* Stop the CP */
    RADEONCP_STOP(dpy, info);

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
    DRICloseScreen();

				/* De-allocate all DRI data structures */
    if (info->pDRIInfo) {
	if (info->pDRIInfo->devPrivate) {
	    free(info->pDRIInfo->devPrivate);
	    info->pDRIInfo->devPrivate = NULL;
	}
	DRIDestroyInfoRec(info->pDRIInfo);
	info->pDRIInfo = NULL;
    }
}



/* Will fbdev set a pitch appropriate for 3d?
 */
static GLboolean RADEONSetPitch (MiniGLXDisplayRec *dpy)
{
    int  dummy = dpy->VarInfo.xres_virtual;

    /* FIXME: May need to validate line pitch here */
    switch (dpy->bpp / 8) {
    case 1: dummy = (dpy->VarInfo->xres_virtual + 127) & ~127; break;
    case 2: dummy = (dpy->VarInfo->xres_virtual +  31) &  ~31; break;
    case 3:
    case 4: dummy = (dpy->VarInfo->xres_virtual +  15) &  ~15; break;
    }

    if (dpy->VarInfo.xres_virtual != dummy) {
       fprintf(stderr, "Didn't set a good pitch for 3d (Need to move this earlier in fbdev init!?!\n");
       return FALSE;
    }

    dpy->VarInfo.xres_virtual = dummy;
    return TRUE;
}

/* Called at the start of each server generation. */
static GLboolean RADEONScreenInit( MiniGLXDisplayRec *dpy, RADEONInfoPtr info )
{
    info->FBDev        = TRUE;
    info->CPInUse      = FALSE;
    info->CPStarted    = FALSE;

    {
	int  width_bytes = (dpy->VarInfo.xres_virtual *
			    info->CurrentLayout.pixel_bytes);
	int  maxy        = info->FbMapSize / width_bytes;


	if (maxy <= dpy->VarInfo.yres_virtual * 3) {
	   fprintf(stderr, 
		       "Static buffer allocation failed -- "
		       "need at least %d kB video memory\n",
		       (dpy->VarInfo.xres_virtual * dpy->VarInfo.yres_virtual *
			info->CurrentLayout.pixel_bytes * 3 + 1023) / 1024);
	    return FALSE;
	} 
    }


    if (info->ChipFamily >= CHIP_FAMILY_R300) {
       fprintf(stderr, 
	       "Direct rendering not yet supported on "
	       "Radeon 9700 and newer cards\n");
       return FALSE;
    }

    if (!RADEONDRIScreenInit(dpy, info))
       return FALSE;

    /* Memory manager setup */
    {
	FBAreaPtr  fbarea;
	int        width_bytes = (dpy->VarInfo.xres_virtual *
				  info->CurrentLayout.pixel_bytes);
	int        cpp         = info->CurrentLayout.pixel_bytes;
	int        bufferSize  = ((dpy->VarInfo.yres_virtual * width_bytes
				   + RADEON_BUFFER_ALIGN)
				  & ~RADEON_BUFFER_ALIGN);
	int        depthSize   = ((((dpy->VarInfo.yres_virtual+15) & ~15) * width_bytes
				   + RADEON_BUFFER_ALIGN)
				  & ~RADEON_BUFFER_ALIGN);
	int        l;
	int        scanlines;

	info->frontOffset = 0;
	info->frontPitch = dpy->varInfo.xres_virtual;

	switch (info->CPMode) {
	case RADEON_DEFAULT_CP_PIO_MODE:
	    fprintf(stderr,  "CP in PIO mode\n");
	    break;
	case RADEON_DEFAULT_CP_BM_MODE:
	    fprintf(stderr,  "CP in BM mode\n");
	    break;
	default:
	    fprintf(stderr,  "CP in UNKNOWN mode\n");
	    break;
	}

	fprintf(stderr, 
		   "Using %d MB AGP aperture\n", info->agpSize);
	fprintf(stderr, 
		   "Using %d MB for the ring buffer\n", info->ringSize);
	fprintf(stderr, 
		   "Using %d MB for vertex/indirect buffers\n", info->bufSize);
	fprintf(stderr, 
		   "Using %d MB for AGP textures\n", info->agpTexSize);

	/* Front, back and depth buffers - everything else texture??
	 */
	info->textureSize = info->FbMapSize - 2 * bufferSize - depthSize;

	if (info->textureSize < 0) 
	   return FALSE;

	l = RADEONMinBits((info->textureSize-1) / RADEON_NR_TEX_REGIONS);
	if (l < RADEON_LOG_TEX_GRANULARITY) l = RADEON_LOG_TEX_GRANULARITY;

	/* Round the texture size up to the nearest whole number of
	 * texture regions.  Again, be greedy about this, don't
	 * round down.
	 */
	info->log2TexGran = l;
	info->textureSize = (info->textureSize >> l) << l;

	/* Set a minimum usable local texture heap size.  This will fit
	 * two 256x256x32bpp textures.
	 */
	if (info->textureSize < 512 * 1024) {
	    info->textureOffset = 0;
	    info->textureSize = 0;
	}

				/* Reserve space for textures */
	info->textureOffset = ((info->FbMapSize - info->textureSize +
				RADEON_BUFFER_ALIGN) &
			       ~(CARD32)RADEON_BUFFER_ALIGN);

				/* Reserve space for the shared depth
                                 * buffer.
				 */
	info->depthOffset = ((info->textureOffset - depthSize +
			      RADEON_BUFFER_ALIGN) &
			     ~(CARD32)RADEON_BUFFER_ALIGN);
	info->depthPitch = dpy->VarInfo.xres_virtual;

	info->backOffset = ((info->depthOffset - bufferSize +
			     RADEON_BUFFER_ALIGN) &
			    ~(CARD32)RADEON_BUFFER_ALIGN);
	info->backPitch = dpy->VarInfo.xres_virtual;


	fprintf(stderr, 
		   "Will use back buffer at offset 0x%x\n",
		   info->backOffset);
	fprintf(stderr, 
		   "Will use depth buffer at offset 0x%x\n",
		   info->depthOffset);
	fprintf(stderr, 
		   "Will use %d kb for textures at offset 0x%x\n",
		   info->textureSize/1024, info->textureOffset);

	info->frontPitchOffset = (((info->frontPitch * cpp / 64) << 22) |
				  (info->frontOffset >> 10));

	info->backPitchOffset = (((info->backPitch * cpp / 64) << 22) |
				 (info->backOffset >> 10));

	info->depthPitchOffset = (((info->depthPitch * cpp / 64) << 22) |
				  (info->depthOffset >> 10));
    } 

    if (!RADEONDRIFinishScreenInit(dpy, info)) {
       return FALSE;
    }

    return TRUE;
}


static void get_chipfamily_from_chipset( RADEONInfoPtr info )
{
    switch (info->Chipset) {
    case PCI_CHIP_RADEON_LY:
    case PCI_CHIP_RADEON_LZ:
	info->ChipFamily = CHIP_FAMILY_M6;
	break;

    case PCI_CHIP_RADEON_QY:
    case PCI_CHIP_RADEON_QZ:
	info->ChipFamily = CHIP_FAMILY_VE;
	break;

    case PCI_CHIP_R200_QL:
    case PCI_CHIP_R200_QN:
    case PCI_CHIP_R200_QO:
    case PCI_CHIP_R200_Ql:
    case PCI_CHIP_R200_BB:
	info->ChipFamily = CHIP_FAMILY_R200;
	break;

    case PCI_CHIP_RV200_QW: /* RV200 desktop */
    case PCI_CHIP_RV200_QX:
	info->ChipFamily = CHIP_FAMILY_RV200;
	break;

    case PCI_CHIP_RADEON_LW:
    case PCI_CHIP_RADEON_LX:
	info->ChipFamily = CHIP_FAMILY_M7;
	break;

    case PCI_CHIP_RV250_Id:
    case PCI_CHIP_RV250_Ie:
    case PCI_CHIP_RV250_If:
    case PCI_CHIP_RV250_Ig:
	info->ChipFamily = CHIP_FAMILY_RV250;
	break;

    case PCI_CHIP_RV250_Ld:
    case PCI_CHIP_RV250_Le:
    case PCI_CHIP_RV250_Lf:
    case PCI_CHIP_RV250_Lg:
	info->ChipFamily = CHIP_FAMILY_M9;
	break;

    case PCI_CHIP_R300_ND:
    case PCI_CHIP_R300_NE:
    case PCI_CHIP_R300_NF:
    case PCI_CHIP_R300_NG:
	info->ChipFamily = CHIP_FAMILY_R300;
        break;

    default:
	/* Original Radeon/7200 */
	info->ChipFamily = CHIP_FAMILY_RADEON;
    }
}


/*
 */
GLboolean __driInitFBDev( struct MiniGLXDisplayRec *dpy )
{
   RADEONInfoPtr info = calloc(sizeof(*info));

   dpy->driverInfo = (void *)info;
   
   info->PciInfo.bus = dpy->pciBus;
   info->PciInfo.device = dpy->pciDevice;
   info->PciInfo.func = dpy->pciFunc;
   info->PciInfo.memBase[0] = ??;
   info->PciInfo.chipType = dpy->chipset;

   info->IsPCI = 0;
   info->CPMode        = RADEON_DEFAULT_CP_BM_MODE;
   info->CPusecTimeout = RADEON_DEFAULT_CP_TIMEOUT;
   info->agpFastWrite  = RADEON_DEFAULT_AGP_FAST_WRITE;
   info->agpMode       = RADEON_DEFAULT_AGP_MODE;
   info->agpSize       = RADEON_DEFAULT_AGP_SIZE;
   info->agpTexSize    = RADEON_DEFAULT_AGP_TEX_SIZE;
   info->bufSize       = RADEON_DEFAULT_BUFFER_SIZE;
   info->ringSize      = RADEON_DEFAULT_RING_SIZE;
  
   info->CurrentLayout.bitsPerPixel = dpy->bpp;
   info->CurrentLayout.depth        = dpy->bpp;	/* NOTE: was depth */
   info->CurrentLayout.pixel_bytes  = dpy->bpp / 8;
   info->CurrentLayout.pixel_code   = dpy->bpp;	/* NOTE: was depth or bpp */

   info->BusCntl = INREG(RADEON_BUS_CNTL);
   info->Chipset = info->PciInfo->chipType;
   get_chipfamily_from_chipset( info );

   info->frontPitch = dpy->VarInfo.xres_virtual;
   info->FbMapSize = dpy->FrameBufferSize;
   info->LinearAddr = info->PciInfo->memBase[0] & 0xfc000000;
    

   /* Choose dpy->VarInfo.xres_virtual?? */
   if (!RADEONSetPitch( dpy ))
      return GL_FALSE;

   
   /* Jump to cut down code from X driver */
   if (!RADEONScreenInit( dpy, info ))
      return GL_FALSE;

   return GL_TRUE;
}

void RADEON_ServerHalt( void )
{
   RADEONDRICloseScreen(info)
}
