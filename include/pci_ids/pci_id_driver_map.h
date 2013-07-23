#ifndef _PCI_ID_DRIVER_MAP_H_
#define _PCI_ID_DRIVER_MAP_H_

#include <stddef.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

static const int i915_chip_ids[] = {
#define CHIPSET(chip, desc, name) chip,
#include "pci_ids/i915_pci_ids.h"
#undef CHIPSET
};

static const int i965_chip_ids[] = {
#define CHIPSET(chip, desc, name) chip,
#include "pci_ids/i965_pci_ids.h"
#undef CHIPSET
};

#ifndef DRIVER_MAP_GALLIUM_ONLY
static const int r100_chip_ids[] = {
#define CHIPSET(chip, name, family) chip,
#include "pci_ids/radeon_pci_ids.h"
#undef CHIPSET
};

static const int r200_chip_ids[] = {
#define CHIPSET(chip, name, family) chip,
#include "pci_ids/r200_pci_ids.h"
#undef CHIPSET
};
#endif

static const int r300_chip_ids[] = {
#define CHIPSET(chip, name, family) chip,
#include "pci_ids/r300_pci_ids.h"
#undef CHIPSET
};

static const int r600_chip_ids[] = {
#define CHIPSET(chip, name, family) chip,
#include "pci_ids/r600_pci_ids.h"
#undef CHIPSET
};

static const int radeonsi_chip_ids[] = {
#define CHIPSET(chip, name, family) chip,
#include "pci_ids/radeonsi_pci_ids.h"
#undef CHIPSET
};

static const int vmwgfx_chip_ids[] = {
#define CHIPSET(chip, name, family) chip,
#include "pci_ids/vmwgfx_pci_ids.h"
#undef CHIPSET
};

static const struct {
   int vendor_id;
   const char *driver;
   const int *chip_ids;
   int num_chips_ids;
} driver_map[] = {
   { 0x8086, "i915", i915_chip_ids, ARRAY_SIZE(i915_chip_ids) },
   { 0x8086, "i965", i965_chip_ids, ARRAY_SIZE(i965_chip_ids) },
#ifndef DRIVER_MAP_GALLIUM_ONLY
   { 0x1002, "radeon", r100_chip_ids, ARRAY_SIZE(r100_chip_ids) },
   { 0x1002, "r200", r200_chip_ids, ARRAY_SIZE(r200_chip_ids) },
#endif
   { 0x1002, "r300", r300_chip_ids, ARRAY_SIZE(r300_chip_ids) },
   { 0x1002, "r600", r600_chip_ids, ARRAY_SIZE(r600_chip_ids) },
   { 0x1002, "radeonsi", radeonsi_chip_ids, ARRAY_SIZE(radeonsi_chip_ids) },
   { 0x10de, "nouveau", NULL, -1 },
   { 0x15ad, "vmwgfx", vmwgfx_chip_ids, ARRAY_SIZE(vmwgfx_chip_ids) },
   { 0x0000, NULL, NULL, 0 },
};

#ifdef HAVE_LIBUDEV
#include <libudev.h>
#include <xf86drm.h>

static inline struct udev_device *
common_udev_device_new_from_fd(struct udev *udev, int fd)
{
   struct udev_device *device;
   struct stat buf;

   if (fstat(fd, &buf) < 0) {
      _eglLog(_EGL_WARNING, "EGL-DRI2: failed to stat fd %d", fd);
      return NULL;
   }

   device = udev_device_new_from_devnum(udev, 'c', buf.st_rdev);
   if (device == NULL) {
      _eglLog(_EGL_WARNING,
              "EGL-DRI2: could not create udev device for fd %d", fd);
      return NULL;
   }

   return device;
}

static inline char *
common_get_device_name_for_fd(int fd)
{
   struct udev *udev;
   struct udev_device *device;
   const char *const_device_name;
   char *device_name = NULL;

   udev = udev_new();
   device = common_udev_device_new_from_fd(udev, fd);
   if (device == NULL)
      return NULL;

   const_device_name = udev_device_get_devnode(device);
   if (!const_device_name)
      goto out;
   device_name = strdup(const_device_name);

out:
   udev_device_unref(device);
   udev_unref(udev);

   return device_name;
}
#endif

static inline char *
common_get_driver_for_fd(int fd)
{
   struct udev *udev;
   struct udev_device *device, *parent;
   const char *pci_id;
   char *driver = NULL;
   int vendor_id, chip_id, i, j;

   udev = udev_new();
   device = common_udev_device_new_from_fd(udev, fd);
   if (device == NULL)
      return NULL;

   parent = udev_device_get_parent(device);
   if (parent == NULL) {
      _eglLog(_EGL_WARNING, "DRI2: could not get parent device");
      goto out;
   }

   pci_id = udev_device_get_property_value(parent, "PCI_ID");
   if (pci_id == NULL) {
      drmVersionPtr version = drmGetVersion(fd);
      if (version) {
         driver = strndup(version->name, version->name_len);
         _eglLog(_EGL_DEBUG, "using driver %s for %d", driver, fd);
         drmFreeVersion(version);
      }
      goto out;
   } else if (sscanf(pci_id, "%x:%x", &vendor_id, &chip_id) != 2) {
      _eglLog(_EGL_WARNING, "EGL-DRI2: malformed or no PCI ID");
      goto out;
   }

   for (i = 0; driver_map[i].driver; i++) {
      if (vendor_id != driver_map[i].vendor_id)
         continue;
      if (driver_map[i].num_chips_ids == -1) {
         driver = strdup(driver_map[i].driver);
         _eglLog(_EGL_DEBUG, "pci id for %d: %04x:%04x, driver %s",
                 fd, vendor_id, chip_id, driver);
         goto out;
      }

      for (j = 0; j < driver_map[i].num_chips_ids; j++)
         if (driver_map[i].chip_ids[j] == chip_id) {
            driver = strdup(driver_map[i].driver);
            _eglLog(_EGL_DEBUG, "pci id for %d: %04x:%04x, driver %s",
                    fd, vendor_id, chip_id, driver);
            goto out;
         }
   }

out:
   udev_device_unref(device);
   udev_unref(udev);

   return driver;
}

#endif /* _PCI_ID_DRIVER_MAP_H_ */
