/*
 * QTI GStreamer format compatibility header (local build input, not upstream)
 *
 * meta-qcom patches gstreamer1.0-plugins-base to append the Qualcomm-specific
 * formats NV12_Q08C / NV12_Q10LE32C to the end of GstVideoFormat and to bump
 * GST_VIDEO_FORMAT_LAST along with them. Stock GStreamer 1.28.2 on Ubuntu
 * 26.04 lacks both, so the plugin sources fail to build with
 * "'GST_VIDEO_FORMAT_NV12_Q08C' was not declared". Defining them here with the
 * same numbering as the patch is enough: the values are appended at the end of
 * the enum, so existing ones keep their numbers and this stays ABI-safe for
 * stock GStreamer. Stock GStreamer never produces these formats at runtime, so
 * the branches using them are never taken.
 */
#ifndef QTI_GST_FORMAT_COMPAT_H
#define QTI_GST_FORMAT_COMPAT_H

/* This header is injected globally via -include, so CMake's compiler ABI
 * self-check loads it too, at a point where the gstreamer headers are not on
 * the include path yet. It must therefore degrade silently, otherwise that
 * self-check fails and configure errors out. */
#if defined(__has_include)
#if __has_include(<gst/video/video-format.h>)
#include <gst/video/video-format.h>
#define QTI_GST_FORMAT_HDR_VISIBLE 1
#endif
#endif

#ifdef QTI_GST_FORMAT_HDR_VISIBLE

/* GST_VIDEO_FORMAT_* are enum constants, not macros, so their presence cannot
 * be tested with #ifdef. */
#ifndef GST_VIDEO_FORMAT_NV12_Q08C
#define GST_VIDEO_FORMAT_NV12_Q08C ((GstVideoFormat) (GST_VIDEO_FORMAT_LAST))
#endif

#ifndef GST_VIDEO_FORMAT_NV12_Q10LE32C
#define GST_VIDEO_FORMAT_NV12_Q10LE32C \
  ((GstVideoFormat) (GST_VIDEO_FORMAT_LAST + 1))
#endif

#endif /* QTI_GST_FORMAT_HDR_VISIBLE */

#endif /* QTI_GST_FORMAT_COMPAT_H */
