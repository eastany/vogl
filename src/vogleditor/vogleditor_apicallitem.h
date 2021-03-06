/**************************************************************************
 *
 * Copyright 2013-2014 RAD Game Tools and Valve Software
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/

#ifndef VOGLEDITOR_APICALLITEM_H
#define VOGLEDITOR_APICALLITEM_H

#include <QList>

#include "vogleditor_snapshotitem.h"

// predeclared classes
class vogleditor_frameItem;
class vogl_trace_packet;

class vogleditor_apiCallItem : public vogleditor_snapshotItem
{
public:
   vogleditor_apiCallItem(vogleditor_frameItem* pFrame, vogl_trace_packet* pTracePacket, const vogl_trace_gl_entrypoint_packet& glPacket)
       : m_pParentFrame(pFrame),
        m_glPacket(glPacket),
        m_pTracePacket(pTracePacket),
        m_globalCallIndex(glPacket.m_call_counter),
        m_begin_rdtsc(glPacket.m_packet_begin_rdtsc),
        m_end_rdtsc(glPacket.m_packet_end_rdtsc),
        m_backtrace_hash_index(glPacket.m_backtrace_hash_index)
   {
      if (m_end_rdtsc < m_begin_rdtsc)
      {
         m_end_rdtsc = m_begin_rdtsc + 1;
      }
   }

   ~vogleditor_apiCallItem()
   {
       if (m_pTracePacket != NULL)
       {
           vogl_delete(m_pTracePacket);
           m_pTracePacket = NULL;
       }
   }

   inline vogleditor_frameItem* frame() const
   {
      return m_pParentFrame;
   }

   inline uint64_t globalCallIndex() const
   {
      return m_globalCallIndex;
   }

   inline uint64_t startTime() const
   {
      return m_begin_rdtsc;
   }

   inline uint64_t endTime() const
   {
      return m_end_rdtsc;
   }

   inline uint64_t duration() const
   {
      return endTime() - startTime();
   }

   const vogl_trace_gl_entrypoint_packet* getGLPacket() const
   {
      return &m_glPacket;
   }

   vogl_trace_packet* getTracePacket()
   {
      return m_pTracePacket;
   }

   inline uint64_t backtraceHashIndex() const
   {
       return m_backtrace_hash_index;
   }

private:
   vogleditor_frameItem* m_pParentFrame;
   const vogl_trace_gl_entrypoint_packet m_glPacket;
   vogl_trace_packet* m_pTracePacket;

   uint64_t m_globalCallIndex;
   uint64_t m_begin_rdtsc;
   uint64_t m_end_rdtsc;
   uint64_t m_backtrace_hash_index;
};

#endif // VOGLEDITOR_APICALLITEM_H
