//
// Basisdatei zum Erstellen von Tests
//

#include "gtest/gtest.h"
//#include "Dummy.h"
#include "plugin/defectDetector.h"

TEST(TESTS, TEST1) {
    defectDetector defectDetector;
    defectDetector.evalCycle();

    EXPECT_EQ(d.one(), 1);
}