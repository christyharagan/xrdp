/**
 * RemoteFX Codec Library
 *
 * Copyright 2024 Jay Sorg <jay.sorg@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * DWT Reduce-Extrapolate Method MS-RDPEGFX 3.2.8.1.2.2
 * also does Quantization and Linearization 3.2.8.1.3
 * SSE2 accel
*/

#ifndef __RFXENCODE_DWT_SHIFT_REM_SSE2_H
#define __RFXENCODE_DWT_SHIFT_REM_SSE2_H

int
rfx_encode_dwt_shift_rem_sse2(const uint8 *in_buffer, sint16 *out_buffer,
                              sint16 *tmp_buffer, const char *quants);

#endif
