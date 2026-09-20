#include <gtest/gtest.h>
#include "hmi_core.h"

// [utest->req~signal-processing~1]
TEST(SignalProcessing, LatencyTest) {
    auto start = get_now();
    process_zub_signal(sample_data);
    auto end = get_now();
    
    ASSERT_LT(end - start, 50ms);
}
