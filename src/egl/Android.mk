LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES :=			\
	main/eglapi.c			\
	main/eglclient.c		\
	main/eglconfig.c		\
	main/eglconfigutil.c		\
	main/eglcontext.c		\
	main/eglcurrent.c		\
	main/egldisplay.c		\
	main/egldriver.c		\
	main/eglglobals.c		\
	main/eglimage.c			\
	main/egllog.c			\
	main/eglmisc.c			\
	main/eglmode.c			\
	main/eglscreen.c		\
	main/eglstring.c		\
	main/eglsurface.c

LOCAL_SRC_FILES +=			\
	drivers/android/egl_android.c	\
	drivers/android/droid_loader.c	\
	drivers/android/droid_ui.cpp	\
	drivers/android/droid_intel.c

LOCAL_C_INCLUDES +=			\
	$(LOCAL_PATH)/main		\
	external/mesa/include		\
	external/mesa/src/mesa		\
	external/drm/shared-core

LOCAL_CFLAGS +=	-DPTHREADS
LOCAL_SHARED_LIBRARIES := libdl libui libutils
LOCAL_STATIC_LIBRARIES := libes1api

LOCAL_MODULE := libhgl

include $(BUILD_SHARED_LIBRARY)
