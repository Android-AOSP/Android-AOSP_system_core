/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "thread_utils.h"

#if defined(__APPLE__)

#include <sys/syscall.h>

// Mac OS >= 10.6 has a system call equivalent to Linux's gettid().
pid_t gettid() {
  return syscall(SYS_thread_selfid);
}

#elif !defined(__BIONIC__)

// glibc doesn't implement or export either gettid or tgkill.
#include <unistd.h>
#include <sys/syscall.h>

pid_t gettid() {
  return syscall(__NR_gettid);
}

int tgkill(int tgid, int tid, int sig) {
  return syscall(__NR_tgkill, tgid, tid, sig);
}

#endif
