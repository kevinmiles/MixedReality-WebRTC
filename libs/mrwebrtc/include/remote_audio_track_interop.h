// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include "audio_frame_observer.h"
#include "export.h"
#include "interop_api.h"

extern "C" {

/// Assign some opaque user data to the remote audio track. The implementation
/// will store the pointer in the remote audio track object and not touch it. It
/// can be retrieved with |mrsRemoteAudioTrackGetUserData()| at any point during
/// the remote audio track lifetime. This is not multithread-safe.
MRS_API void MRS_CALL
mrsRemoteAudioTrackSetUserData(mrsRemoteAudioTrackHandle handle,
                               void* user_data) noexcept;

/// Get the opaque user data pointer previously assigned to the remote audio
/// track with |mrsRemoteAudioTrackSetUserData()|. If no value was previously
/// assigned, return |nullptr|. This is not multithread-safe.
MRS_API void* MRS_CALL
mrsRemoteAudioTrackGetUserData(mrsRemoteAudioTrackHandle handle) noexcept;

/// Register a custom callback to be called when the local audio track received
/// a frame.
MRS_API void MRS_CALL
mrsRemoteAudioTrackRegisterFrameCallback(mrsRemoteAudioTrackHandle trackHandle,
                                         mrsAudioFrameCallback callback,
                                         void* user_data) noexcept;

/// Enable or disable a remote audio track. Enabled tracks output their media
/// content as usual. Disabled tracks output some void media content (silent
/// audio frames). Enabling/disabling a track is a lightweight concept similar
/// to "mute", which does not require an SDP renegotiation.
MRS_API mrsResult MRS_CALL
mrsRemoteAudioTrackSetEnabled(mrsRemoteAudioTrackHandle track_handle,
                              mrsBool enabled) noexcept;

/// Query a local audio track for its enabled status.
MRS_API mrsBool MRS_CALL
mrsRemoteAudioTrackIsEnabled(mrsRemoteAudioTrackHandle track_handle) noexcept;

/// Render the audio track to the system audio device.
///
/// The default behavior is for every remote audio frame to be passed to
/// remote audio frame callbacks, as well as rendered automatically to the
/// system audio device. If |false| is passed to this function, remote audio
/// frames will still be received and passed to callbacks, but won't be rendered
/// to the system device.
///
/// NOTE: Changing the default behavior is not supported on UWP.
MRS_API void MRS_CALL
mrsRemoteAudioRenderToDevice(mrsRemoteAudioTrackHandle track_handle, bool render) noexcept;

/// Returns whether the track is rendering directly to the system audio device.
MRS_API mrsBool MRS_CALL
mrsRemoteAudioTrackIsRenderingToDevice(mrsRemoteAudioTrackHandle track_handle) noexcept;

}  // extern "C"
