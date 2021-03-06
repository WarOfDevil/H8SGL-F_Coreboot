/*
 *****************************************************************************
 *
 * Copyright (c) 2011, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***************************************************************************
 *
 */

#include "SBPLATFORM.h"
#include "cbtypes.h"

VOID
ReadMEM (
  IN       UINT32 Address,
  IN       UINT8 OpFlag,
  IN       VOID* Value
  )
{
  OpFlag = OpFlag & 0x7f;
  switch ( OpFlag ) {
  case AccWidthUint8:
    *((UINT8*)Value) = *((UINT8*) ((UINTN)Address));
    break;
  case AccWidthUint16:
    //*((UINT16*)Value) = *((UINT16*) ((UINTN)Address)); //gcc break strict-aliasing rules
    *((UINT8*)Value) = *((UINT8*) ((UINTN)Address));
    *((UINT8*)Value + 1) = *((UINT8*)((UINTN)Address) + 1);
    break;
  case AccWidthUint32:
    *((UINT32*)Value) = *((UINT32*) ((UINTN)Address));
    break;
  }
}

VOID
WriteMEM (
  IN       UINT32 Address,
  IN       UINT8 OpFlag,
  IN       VOID* Value
  )
{
  OpFlag = OpFlag & 0x7f;
  switch ( OpFlag ) {
  case AccWidthUint8 :
    *((UINT8*) ((UINTN)Address)) = *((UINT8*)Value);
    break;
  case AccWidthUint16:
    //*((UINT16*) ((UINTN)Address)) = *((UINT16*)Value); //gcc break strict-aliasing rules
    *((UINT8*)((UINTN)Address)) = *((UINT8*)Value);
    *((UINT8*)((UINTN)Address) + 1) = *((UINT8*)Value + 1);
    break;
  case AccWidthUint32:
    *((UINT32*) ((UINTN)Address)) = *((UINT32*)Value);
    break;
  }
}

VOID
RWMEM (
  IN       UINT32 Address,
  IN       UINT8 OpFlag,
  IN       UINT32 Mask,
  IN       UINT32 Data
  )
{
  UINT32 Result;
  ReadMEM (Address, OpFlag, &Result);
  Result = (Result & Mask) | Data;
  WriteMEM (Address, OpFlag, &Result);
}


