// Copyright 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <vector>

#include "test/syscalls/linux/socket_test_util.h"
#include "test/syscalls/linux/socket_unix.h"
#include "test/syscalls/linux/unix_domain_socket_test_util.h"
#include "test/util/test_util.h"

namespace gvisor {
namespace testing {

std::vector<SocketPairKind> GetSocketPairs() {
  return VecCat<SocketPairKind>(ApplyVec<SocketPairKind>(
      UnixDomainSocketPair,
      AllBitwiseCombinations(List<int>{SOCK_STREAM, SOCK_DGRAM, SOCK_SEQPACKET},
                             List<int>{0, SOCK_NONBLOCK},
                             List<int>{0, SOCK_CLOEXEC})));
}

INSTANTIATE_TEST_CASE_P(
    AllUnixDomainSockets, UnixSocketPairTest,
    ::testing::ValuesIn(IncludeReversals(GetSocketPairs())));

}  // namespace testing
}  // namespace gvisor
