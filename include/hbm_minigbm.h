// Copyright 2024 Google LLC
// SPDX-License-Identifier: MIT

#ifndef HBM_MINIGBM_H
#define HBM_MINIGBM_H

/* Generated with cbindgen:0.27.0 */

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

/**
 * The BO can be exported/imported.
 */
#define HBM_FLAG_EXTERNAL (1 << 0)

/**
 * The BO can be mapped.
 */
#define HBM_FLAG_MAP (1 << 1)

/**
 * The BO can be copied to or copied from.
 */
#define HBM_FLAG_COPY (1 << 2)

/**
 * The BO must be on a protected heap.
 */
#define HBM_FLAG_PROTECTED (1 << 3)

/**
 * The BO must not be compressed.
 */
#define HBM_FLAG_NO_COMPRESSION (1 << 4)

/**
 * The BO can be used for GPU copies.
 */
#define HBM_USAGE_GPU_TRANSFER (1ull << 0)

/**
 * The BO can be used as a GPU uniform buffer.
 */
#define HBM_USAGE_GPU_UNIFORM (1ull << 1)

/**
 * The BO can be used as a GPU storage buffer or image.
 */
#define HBM_USAGE_GPU_STORAGE (1ull << 2)

/**
 * The BO can be used as a GPU sampled image.
 */
#define HBM_USAGE_GPU_SAMPLED (1ull << 3)

/**
 * The BO can be used as a GPU color image.
 */
#define HBM_USAGE_GPU_COLOR (1ull << 4)

/**
 * The BO can be scanned out.  This is only meaningful when HBM lacks modifier support.
 */
#define HBM_USAGE_GPU_SCANOUT_HACK (1ull << 5)

/**
 * The memory type is local to the device.
 */
#define HBM_MEMORY_TYPE_LOCAL (1 << 0)

/**
 * The memory type is mappable.
 */
#define HBM_MEMORY_TYPE_MAPPABLE (1 << 1)

/**
 * The memory type is coherent.
 */
#define HBM_MEMORY_TYPE_COHERENT (1 << 2)

/**
 * The memory type is cached.
 */
#define HBM_MEMORY_TYPE_CACHED (1 << 3)

/**
 * Log level of a message or the message filter.
 */
enum hbm_log_level {
  /**
   * A pseudo level used to disable all messages.
   */
  HBM_LOG_LEVEL_OFF,
  /**
   * Indicates a failure of a mandatory operation.
   */
  HBM_LOG_LEVEL_ERROR,
  /**
   * Indicates a failure of an optional operation.
   */
  HBM_LOG_LEVEL_WARN,
  /**
   * Indicates an informative message.
   */
  HBM_LOG_LEVEL_INFO,
  /**
   * Indicates a debug message.
   */
  HBM_LOG_LEVEL_DEBUG,
};

/**
 * A message log callback.
 */
typedef void (*hbm_log_callback)(enum hbm_log_level lv, const char *msg, void *cb_data);

/**
 * A hardware device.
 *
 * This opaque struct represents a device.  There are module-level functions to query device info
 * and allocate BOs from the device.
 */
struct hbm_device {
  uint8_t _data[0];
};

/**
 * The description of a BO.
 */
struct hbm_description {
  /**
   * A bitmask of `HBM_FLAG_*`.
   */
  uint32_t flags;
  /**
   * When the format is `DRM_FORMAT_INVALID`, the BO is a buffer.  Otherwise,
   * the BO is an image.
   */
  uint32_t format;
  /**
   * When the modifier is `DRM_FORMAT_MOD_INVALID`, HBM will pick the optimal modifier.
   * Otherwise, HBM will use the specified modifier.
   */
  uint64_t modifier;
  /**
   * A bitmask of `HBM_USAGE_*`.
   */
  uint64_t usage;
};

/**
 * A hardware buffer object (BO).
 *
 * This opaque struct represents a BO.  A BO can be allocated by HBM or imported from a dma-buf.
 * A BO can only be manipulated with module-level functions.
 */
struct hbm_bo {
  uint8_t _data[0];
};

/**
 * The extent of a buffer BO.
 */
struct hbm_extent_buffer {
  /**
   * Size of the buffer in bytes.
   */
  uint64_t size;
};

/**
 * The extent of an image BO.
 */
struct hbm_extent_image {
  /**
   * Width of the image in texels.
   */
  uint32_t width;
  /**
   * Height of the image in texels.
   */
  uint32_t height;
};

/**
 * The extent of a BO.
 */
union hbm_extent {
  /**
   * Used when the BO is a buffer.
   */
  struct hbm_extent_buffer buffer;
  /**
   * Used when the BO is an image.
   */
  struct hbm_extent_image image;
};

/**
 * A BO allocation constraint.
 *
 * A constraint describes additional requirements that the BO layout must follow.
 */
struct hbm_constraint {
  /**
   * Alignment for plane offsets in bytes.
   */
  uint64_t offset_align;
  /**
   * Alignment for row strides in bytes.
   */
  uint64_t stride_align;
  /**
   * Alignment for plane sizes in bytes.
   */
  uint64_t size_align;
  /**
   * An optional array of allowed modifiers.
   */
  const uint64_t *modifiers;
  /**
   * The size of the modifier array.
   */
  uint32_t modifier_count;
};

/**
 * The physical layout of a BO.
 */
struct hbm_layout {
  /**
   * Size of the BO in bytes.
   */
  uint64_t size;
  /**
   * Modifier of the BO.  If the BO is a buffer, this is `DRM_FORMAT_MOD_INVALID`.
   */
  uint64_t modifier;
  /**
   * Memory plane count, which can be equal to or greater than the format plane count.  If the
   * BO is a buffer, this is 0.
   */
  uint32_t plane_count;
  /**
   * Plane offsets.
   */
  uint64_t offsets[4];
  /**
   * Plane row strides.
   */
  uint64_t strides[4];
};

/**
 * Describes a buffer-buffer copy.
 */
struct hbm_copy_buffer {
  /**
   * Starting offset of the source buffer in bytes.
   */
  uint64_t src_offset;
  /**
   * Starting offset of the destination buffer in bytes.
   */
  uint64_t dst_offset;
  /**
   * Number of bytes to copy.
   */
  uint64_t size;
};

/**
 * Describes a buffer-image copy.
 */
struct hbm_copy_buffer_image {
  /**
   * Starting offset of the buffer in bytes.
   */
  uint64_t offset;
  /**
   * Row stride of buffer in bytes.
   */
  uint64_t stride;
  /**
   * Format plane of the image.
   */
  uint32_t plane;
  /**
   * Starting X coordinate of the image in texels.
   */
  uint32_t x;
  /**
   * Starting Y coordinate of the image in texels.
   */
  uint32_t y;
  /**
   * Number of texels in X coordinate to copy.
   */
  uint32_t width;
  /**
   * Number of texels in Y coordinate to copy.
   */
  uint32_t height;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Initializes logging.
 *
 * # Safety
 *
 * If `log_cb` is non-NULL, it must be valid.
 */
void hbm_log_init(enum hbm_log_level log_lv_max, hbm_log_callback log_cb, void *cb_data);

/**
 * Creates a device.
 *
 * # Safety
 *
 * This function is always safe.
 */
struct hbm_device *hbm_device_create(dev_t dev, bool debug);

/**
 * Destroys a device.
 *
 * # Safety
 *
 * `dev` must be valid.
 */
void hbm_device_destroy(struct hbm_device *dev);

/**
 * Queries the memory plane count for the speicifed format modifier.  Returns 0 if the format or
 * the modifier is not supported.
 *
 * TODO do we need this?
 *
 * # Safety
 *
 * `dev` must be valid.
 */
uint32_t hbm_device_get_plane_count(struct hbm_device *dev, uint32_t fmt, uint64_t modifier);

/**
 * Queries supported modifiers for a BO description.
 *
 * If the BO description is not supported or refers to a buffer, there is no supported modifier
 * and 0 is always returned.
 *
 * If `mod_max` is 0, the number of supported modifiers is returned.  Otherwise, the number of
 * supported modifiers written to `out_mods` is returned.
 *
 * # Safety
 *
 * `dev` and `desc` must be valid.
 *
 * `out_mods` must point to an array of at least `mod_max` modifiers.
 */
uint32_t hbm_device_get_modifiers(struct hbm_device *dev,
                                  const struct hbm_description *desc,
                                  uint32_t mod_max,
                                  uint64_t *out_mods);

/**
 * Queries modifier support for a BO description.
 *
 * # Safety
 *
 * `dev` and `desc` must be valid.
 */
bool hbm_device_has_modifier(struct hbm_device *dev,
                             const struct hbm_description *desc,
                             uint64_t modifier);

/**
 * Create a BO with a constraint.
 *
 * `con` is optional.
 *
 * # Safety
 *
 * `dev`, `desc`, and `extent` must be valid.
 */
struct hbm_bo *hbm_bo_create_with_constraint(struct hbm_device *dev,
                                             const struct hbm_description *desc,
                                             const union hbm_extent *extent,
                                             const struct hbm_constraint *con);

/**
 * Create a BO with an explicit layout.
 *
 * If `dmabuf` is non-negative, it restricts the supported memory types.  Ownership of `dmabuf` is
 * never transferred.
 *
 * # Safety
 *
 * `dev`, `desc`, `extent`, and `layout` must be valid.
 *
 * If `dmabuf` is non-negative, it must be a valid dma-buf.
 */
struct hbm_bo *hbm_bo_create_with_layout(struct hbm_device *dev,
                                         const struct hbm_description *desc,
                                         const union hbm_extent *extent,
                                         const struct hbm_layout *layout,
                                         int32_t dmabuf);

/**
 * Destroys a BO.
 *
 * # Safety
 *
 * `bo` must be valid.
 */
void hbm_bo_destroy(struct hbm_bo *bo);

/**
 * Queries the physical layout of a BO.
 *
 * # Safety
 *
 * `bo` must be valid.
 *
 * `out_layout` must be non-NULL.
 */
void hbm_bo_layout(struct hbm_bo *bo, struct hbm_layout *out_layout);

/**
 * Queries supported memory types of a BO.
 *
 * If `mt_max` is 0, the number of supported memory types is returned.  Otherwise, the number of
 * supported memory types written to `out_mts` is returned.
 *
 * # Safety
 *
 * `bo` must be valid.
 *
 * `out_mts` must point to an array of at least `mt_max` memory types.
 */
uint32_t hbm_bo_memory_types(struct hbm_bo *bo, uint32_t mt_max, uint32_t *out_mts);

/**
 * Bind a memory to a BO.
 *
 * If `dmabuf` is negative, the memory is allocated.  Otherwise, the BO must have `HBM_FLAG_EXTERNAL` and
 * the memory is imported from `dmabuf`.  Ownership of `dmabuf` is always transferred.
 *
 * # Safety
 *
 * `bo` must be valid.
 *
 * If `dmabuf` is non-negative, it must be a valid dma-buf.
 */
bool hbm_bo_bind_memory(struct hbm_bo *bo,
                        uint32_t mt,
                        int32_t dmabuf);

/**
 * Exports a dma-buf from a BO.
 *
 * The BO must have `HBM_FLAG_EXTERNAL` and must have a memory bound.
 *
 * # Safety
 *
 * `bo` must be valid.
 *
 * If `name` is non-NULL, it must be a valid C-string.
 */
int32_t hbm_bo_export_dma_buf(struct hbm_bo *bo, const char *name);

/**
 * Map a BO for direct CPU access.
 *
 * The BO must have `HBM_FLAG_MAP` and must have an `HBM_MEMORY_TYPE_MAPPABLE` memory bound.
 *
 * # Safety
 *
 * `bo` must be valid.
 */
void *hbm_bo_map(struct hbm_bo *bo);

/**
 * Unmap a mapped BO.
 *
 * # Safety
 *
 * `bo` must be valid.
 */
void hbm_bo_unmap(struct hbm_bo *bo);

/**
 * Flush the CPU cache for a non-coherent mapped BO.
 *
 * # Safety
 *
 * `bo` must be valid.
 */
void hbm_bo_flush(struct hbm_bo *bo);

/**
 * Invalidate the CPU cache for a non-coherent mapped BO.
 *
 * # Safety
 *
 * `bo` must be valid.
 */
void hbm_bo_invalidate(struct hbm_bo *bo);

/**
 * Performs a buffer-buffer copy from `src` to `bo`.
 *
 * Both BOs must have `HBM_FLAG_COPY`, must have memories bound, and must be buffers.
 *
 * If `in_sync_fd` is non-negative, the copy starts after the sync file signals.  Ownership of
 * `in_sync_fd` is always transferred.
 *
 * If `out_sync_fd` is non-NULL, a valid sync file or -1 is returned.  If a valid sync file is
 * returned, the copy completes after the sync file signals.  If -1 is returned, or if
 * `out_sync_fd` is NULL, the copy completes before this function returns.
 *
 * # Safety
 *
 * `bo`, `src`, and `copy` must be valid.  `bo` and `src` must belong to the same device.
 *
 * If `in_sync_fd` is non-negative, it must be a valid sync file.
 *
 * If `out_sync_fd` is non-NULL, it must be point to an i32.
 */
bool hbm_bo_copy_buffer(struct hbm_bo *bo,
                        struct hbm_bo *src,
                        const struct hbm_copy_buffer *copy,
                        int32_t in_sync_fd,
                        int32_t *out_sync_fd);

/**
 * Performs a buffer-image copy from `src` to `bo`.
 *
 * This is similar to `hbm_bo_copy_buffer`, except one of the BO must be a buffer and the other
 * must be an image.
 *
 * # Safety
 *
 * `bo`, `src`, and `copy` must be valid.  `bo` and `src` must belong to the same device.
 *
 * If `in_sync_fd` is non-negative, it must be a valid sync file.
 *
 * If `out_sync_fd` is non-NULL, it must be point to an i32.
 */
bool hbm_bo_copy_buffer_image(struct hbm_bo *bo,
                              struct hbm_bo *src,
                              const struct hbm_copy_buffer_image *copy,
                              int32_t in_sync_fd,
                              int32_t *out_sync_fd);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* HBM_MINIGBM_H */
