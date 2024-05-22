#pragma once
#include "types.h"
#include "gpu_types.h"
#include <array>

namespace Screenshot3D {

void NextFrame();
void Shutdown();

// Use to modify GTE.NCLIP behavior
bool WantsModifyNCLIP();
void ModifyNCLIP(s64& value);

// Called in GTE.RTPS to track 3D verts
void PushVertex(float x, float y, float z, s32& Sx, s32& Sy);
bool ShouldUsePGXP();

// Called when a polygon is drawn
bool WantsPolygon();
void DrawPolygon(
  GPURenderCommand rc,
  const GPUBackendDrawPolygonCommand::Vertex verts[4],
  GPUDrawModeReg mode_reg,
  u16 palette_reg,
  GPUTextureWindow texture_window,
  const std::array<float, 3> pgxp_verts[4]
);

// Called when a rectangle is drawn (2D mode only)
bool WantsRectangle();
void DrawRectangle(
  GPURenderCommand rc,
  GPUBackendDrawPolygonCommand::Vertex vert,
  u16 width,
  u16 height,
  GPUDrawModeReg mode_reg,
  u16 palette_reg,
  GPUTextureWindow texture_window
);

// Called once just before NextFrame to fill texture data from the
// contents of VRAM.
//
// Textures always use the content of VRAM at frame end. Tracking of
// mid-frame VRAM changes via dirty rects, etc. is not implemented.
bool WantsUpdateFromVRAM();
void UpdateFromVRAM(const u16* vram_ptr);

// Intended to block outside input eg. controllers. Used when getting
// multiple "exposures" by re-running from a state state to make the
// runs repeatable.
bool BlockingInput();

void DrawGuiWindow();

} // namespace Screenshot3D
