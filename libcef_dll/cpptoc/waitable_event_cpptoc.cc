// Copyright (c) 2018 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=810cadf7f378fbcbc15f39cbfdb1b13fb470d613$
//

#include "libcef_dll/cpptoc/waitable_event_cpptoc.h"

// GLOBAL FUNCTIONS - Body may be edited by hand.

CEF_EXPORT cef_waitable_event_t* cef_waitable_event_create(
    int automatic_reset,
    int initially_signaled) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  CefRefPtr<CefWaitableEvent> _retval = CefWaitableEvent::CreateWaitableEvent(
      automatic_reset ? true : false, initially_signaled ? true : false);

  // Return type: refptr_same
  return CefWaitableEventCppToC::Wrap(_retval);
}

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

void CEF_CALLBACK waitable_event_reset(struct _cef_waitable_event_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefWaitableEventCppToC::Get(self)->Reset();
}

void CEF_CALLBACK waitable_event_signal(struct _cef_waitable_event_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefWaitableEventCppToC::Get(self)->Signal();
}

int CEF_CALLBACK
waitable_event_is_signaled(struct _cef_waitable_event_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  bool _retval = CefWaitableEventCppToC::Get(self)->IsSignaled();

  // Return type: bool
  return _retval;
}

void CEF_CALLBACK waitable_event_wait(struct _cef_waitable_event_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefWaitableEventCppToC::Get(self)->Wait();
}

int CEF_CALLBACK waitable_event_timed_wait(struct _cef_waitable_event_t* self,
                                           int64 max_ms) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  bool _retval = CefWaitableEventCppToC::Get(self)->TimedWait(max_ms);

  // Return type: bool
  return _retval;
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

CefWaitableEventCppToC::CefWaitableEventCppToC() {
  GetStruct()->reset = waitable_event_reset;
  GetStruct()->signal = waitable_event_signal;
  GetStruct()->is_signaled = waitable_event_is_signaled;
  GetStruct()->wait = waitable_event_wait;
  GetStruct()->timed_wait = waitable_event_timed_wait;
}

template <>
CefRefPtr<CefWaitableEvent> CefCppToCRefCounted<
    CefWaitableEventCppToC,
    CefWaitableEvent,
    cef_waitable_event_t>::UnwrapDerived(CefWrapperType type,
                                         cef_waitable_event_t* s) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#if DCHECK_IS_ON()
template <>
base::AtomicRefCount CefCppToCRefCounted<CefWaitableEventCppToC,
                                         CefWaitableEvent,
                                         cef_waitable_event_t>::DebugObjCt
    ATOMIC_DECLARATION;
#endif

template <>
CefWrapperType CefCppToCRefCounted<CefWaitableEventCppToC,
                                   CefWaitableEvent,
                                   cef_waitable_event_t>::kWrapperType =
    WT_WAITABLE_EVENT;
