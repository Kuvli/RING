/* future.h
 * 
 * Copyright (c) 2016 Institute of Computing Technology.
 * All rights reserved.
 * 
 * Author: Ke Meng <mengke@ncic.ac.cn>
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Institute of Computing Technology, Chinese 
 *       Academy of Sciences nor the names of its contributors may be used 
 *       to endorse or promote products derived from this software without 
 *       specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * INSTITUTE OF COMPUTING TECHNOLOGY AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 */

#ifndef _FUTURE_H_
#define _FUTURE_H_

#include "sched/coroutine.h"
#include "sched/scheduler.h"

namespace Ring{

template<typename T>
class Future{
  
public:
  Future(): done_tag(false) {}

  void set_value(T t) {
    _content = t;
    done_tag = true;
    auto w = global_scheduler->get_cur_worker();
    w->signal(&cv);
  }

  T get() {
    if(!done_tag){
      auto w = global_scheduler->get_cur_worker();
      w->wait(&cv);
    }
    return _content;
  }
private:
  bool done_tag;
  T _content;
  Condition cv;
};

}//namespace Ring
#endif