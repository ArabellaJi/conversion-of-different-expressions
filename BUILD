# Contains student code to convert and evaluate expressions.
cc_library(
  name = "expression",
  srcs = ["expression.cc"],
  hdrs = ["expression.h"],
)

# Unit tests: students should add a lot more tests to expression_test.cc
cc_test(
  name = "expression_test",
  size = "small",
  srcs = ["expression_test.cc"],
  deps = [":expression",
          "@com_google_googletest//:gtest_main"],
)

# Binary for manually testing :expression.
# Sometimes useful for debugging, but don't depend on it for correctness.
# Use expression_test to ensure correctness.
cc_binary(
  name = "project2",
  srcs = ["project2.cc"],
  deps = [":expression"],
)

# Example program demonstrating use of std::stack
cc_binary(
  name = "reverse",
  srcs = ["reverse.cc"],
)

# Example program demonstrating use of std::stack
cc_binary(
  name = "palindrome",
  srcs = ["palindrome.cc"],
)
